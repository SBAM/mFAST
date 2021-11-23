// Copyright (c) 2013, 2014, Huang-Ming Huang,  Object Computing, Inc.
// All rights reserved.
//
// This file is part of mFAST.
//
//     mFAST is free software: you can redistribute it and/or modify
//     it under the terms of the GNU Lesser General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.
//
//     mFAST is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.
//
//     You should have received a copy of the GNU Lesser General Public License
//     along with mFast.  If not, see <http://www.gnu.org/licenses/>.
//

#include <optional>
#include <unordered_set>

#include "catch.hpp"

#include <mfast.h>
#include <mfast/coder/fast_decoder_v2.h>
#include <mfast/field_comparator.h>
#include "test6.h"
#include "debug_allocator.h"

#include "rdi_payload.h"

using namespace std::string_literals;
using namespace std::string_view_literals;

TEST_CASE("eurex enums", "[test_eurex_enums]")
{
  debug_allocator alloc;
  using namespace test6;

  MarketDataStatisticsReferenceData md(&alloc);
  MarketDataStatisticsReferenceData_mref md_mref(md.mref());

  REQUIRE(md_mref.get_MDStatisticStatus().is_Active());
  REQUIRE(md_mref.get_MDStatisticStatus().value() ==  TypeMDStatisticStatus::Active);
  REQUIRE(md_mref.get_MDStatisticStatus().value_name() == "Active"s);
  md_mref.set_MDStatisticStatus().as_Inactive();
  REQUIRE(md_mref.get_MDStatisticStatus().is_Inactive());
  REQUIRE(md_mref.get_MDStatisticStatus().value() ==  TypeMDStatisticStatus::Inactive);
  REQUIRE(md_mref.get_MDStatisticStatus().value_name() == "Inactive"s);

  REQUIRE_THROWS_AS(md_mref.try_get_MDStatisticFrequencyUnit(), const mfast::bad_optional_access&);
  md_mref.set_MDStatisticFrequencyUnit().as_Minutes();
  REQUIRE(md_mref.get_MDStatisticFrequencyUnit().is_Minutes());
  md_mref.omit_MDStatisticFrequencyUnit();
  REQUIRE_THROWS_AS(md_mref.try_get_MDStatisticFrequencyUnit(), const mfast::bad_optional_access&);

  REQUIRE(md_mref.get_MDStatisticIntervalUnit().is_Days());
  md_mref.set_MDStatisticIntervalUnit().as_MilliSeconds();
  REQUIRE(md_mref.get_MDStatisticIntervalUnit().is_MilliSeconds());

  REQUIRE(md_mref.get_TypeUnit().is_Minutes());
}


TEST_CASE("eurex timestamps", "[test_eurex_timestamps]")
{
  debug_allocator alloc;
  using namespace test6;

  MarketDataReport md(&alloc);
  MarketDataReport_mref md_mref(md.mref());
  md_mref.set_TransactTime().as(123456789);
  REQUIRE(md_mref.set_TransactTime().value() == 123456789);
}


TEST_CASE("eurex sets", "[test_eurex_sets]")
{
  debug_allocator alloc;
  using namespace test6;

  DepthIncremental md(&alloc);
  DepthIncremental_mref md_mref(md.mref());
  REQUIRE(md_mref.get_TradeCondition().value() == 1);
  REQUIRE(md_mref.get_TradeCondition().has_ExchangeLast());
  md_mref.omit_TradeCondition();
  REQUIRE_THROWS_AS(md_mref.try_get_TradeCondition(), const mfast::bad_optional_access&);
  md_mref.set_TradeCondition().set_LowPrice();
  REQUIRE(md_mref.get_TradeCondition().has_LowPrice());
  md_mref.set_TradeCondition().set_TradeAtClose();
  REQUIRE(md_mref.get_TradeCondition().has_LowPrice());
  REQUIRE(md_mref.get_TradeCondition().has_TradeAtClose());
  md_mref.set_TradeCondition().unset_LowPrice();
  REQUIRE(!md_mref.get_TradeCondition().has_LowPrice());
  REQUIRE(md_mref.get_TradeCondition().has_TradeAtClose());
  md_mref.set_TradeCondition().unset_TradeAtClose();
  REQUIRE(md_mref.set_TradeConditionSet().value() == 9);
  REQUIRE(md_mref.get_TradeConditionSet().has_ExchangeLast());
  REQUIRE(!md_mref.get_TradeConditionSet().has_HighPrice());
  REQUIRE(md_mref.get_TradeConditionSet().has_LowPrice());
  REQUIRE(!md_mref.get_TradeConditionSet().has_OfficialClosingPrice());
  REQUIRE(!md_mref.get_TradeConditionSet().has_TradeAtClose());
}


TEST_CASE("eurex constant sequences", "[test_eurex_rdi]")
{
  mfast::fast_decoder_v2<0> dec { test6::description() };
  auto [ first, last ] = get_rdi_msg();
  auto fast_reset = true;
  first += 19; // packet header (17 bytes) + fast reset (2 bytes)
  std::optional<std::uint32_t> prev_sqn;
  std::unordered_set<std::int64_t> secu_ids;
  std::unordered_set<std::string> mkt_ids;
  std::unordered_set<std::string> isins;
  while (first < last)
  {
    auto msg = dec.decode(first, last, fast_reset);
    fast_reset = false;
    REQUIRE(msg.id() == test6::InstrumentSnapshot::the_id);
    auto is = static_cast<test6::InstrumentSnapshot_cref>(msg);
    if (prev_sqn)
      // test consecutive SeqNum
      CHECK(*prev_sqn + 1 == is.get_MsgSeqNum().value());
    prev_sqn = is.get_MsgSeqNum().value();
    // test unique IDs
    CHECK(secu_ids.insert(is.get_SecurityID().value()).second);
    CHECK(is.get_SecurityIDSource().value() == "M"sv);
    for (auto curr : is.get_SecurityAlt())
    {
      auto alt_id_src = curr.get_SecurityAltIDSource().value();
      auto alt_id = std::string{curr.get_SecurityAltID().value()};
      if (alt_id_src == "M"sv)
        // test unique AltIDs
        CHECK(mkt_ids.insert(std::move(alt_id)).second);
      else if (alt_id_src == "4"sv)
        // test unique ISINs
        CHECK(isins.insert(std::move(alt_id)).second);
      else
        throw std::runtime_error("unexpected AltIDSource");
    }
    CHECK(is.get_SecurityType().is_Option());
    CHECK(is.get_SecurityStatus().is_Active());
    CHECK_NOTHROW(is.try_get_SecurityDesc());
    CHECK_THROWS(is.try_get_SecurityExchange());
    CHECK(is.get_ProductComplex().is_SimpleInstrument());
    {
      auto deriv_desc = is.try_get_DerivativesDescriptorGroup();
      auto cfi = deriv_desc.get_CFICode().value();
      CHECK(cfi.at(0) == 'O');
      auto desc = deriv_desc.get_SimpleInstrumentDescriptorGroup();
      if (desc.get_PutOrCall().is_Put())
        CHECK(cfi.at(1) == 'P');
      else
        CHECK(cfi.at(1) == 'C');
      if (desc.get_ExerciseStyle().is_European())
        CHECK(cfi.at(2) == 'E');
      else
        CHECK(cfi.at(2) == 'A');
      if (desc.get_SettlMethod().is_Physical())
        CHECK(cfi.at(4) == 'P');
      else
        CHECK(cfi.at(4) == 'C');
      CHECK_THROWS(deriv_desc.try_get_ComplexInstrumentDescriptorGroup());
      CHECK_THROWS(deriv_desc.try_get_UnderlyingInstrument());
    }
    {
      CHECK_THROWS(is.try_get_CashDescriptorGroup());
    }
    {
      auto attrs = is.try_get_InstrumentAttributes();
      for (auto curr : attrs)
      {
        switch (curr.get_InstrAttribType().value())
        {
          case test6::InstrumentAttributeType::HasPLP:
            CHECK(curr.get_InstrAttribValue().value() == "N"sv);
            break;
          case test6::InstrumentAttributeType::ReportingMarket:
            CHECK(curr.get_InstrAttribValue().value() == "XEUR"sv);
            break;
          case test6::InstrumentAttributeType::IlliquidAsDefinedByExchange:
            CHECK(curr.get_InstrAttribValue().value() == "N"sv);
            break;
          case test6::InstrumentAttributeType::MarketMakingObligation:
            CHECK(curr.get_InstrAttribValue().value() == "Y"sv);
            break;
          case test6::InstrumentAttributeType::EligibleForStressedMarketConditions:
            CHECK(curr.get_InstrAttribValue().value() == "Y"sv);
            break;
          default:
            throw std::runtime_error("unexpected instrument attribute");
        }
      }
    }
    {
      auto events = is.try_get_Events();
      std::optional<std::uint32_t> last_trade_date;
      std::optional<std::uint32_t> final_settl_date;
      for (auto curr : events)
      {
        if (curr.get_EventType().is_LastEligibleTradeDate())
          last_trade_date = curr.get_EventDate().value();
        else if (curr.get_EventType().is_FinalSettlementReferenceDate())
          final_settl_date = curr.get_EventDate().value();
      }
      CHECK(*last_trade_date + 1 == *final_settl_date);
    }
    CHECK(is.get_InstrumentPricePrecision().value() == 1);
    CHECK(is.get_MinPriceIncrement().mantissa() == 1);
    CHECK(is.get_MinPriceIncrement().exponent() == -1);
    CHECK_THROWS(is.try_get_SecuritySubType());
    for (auto curr : is.get_MarketSegmentGrp()) // constant length(=1) sequence
    {
      CHECK(curr.get_MarketSegmentID().value() == 201);
      CHECK(curr.get_ImpliedMarketIndicator().is_NotImplied());
      CHECK(curr.get_MultilegModel().is_PredefinedMultilegSecurity());
      CHECK(curr.get_PriceType().is_Shares());
      CHECK(curr.get_PostTradeAnonymity().is_Disabled());
      CHECK_THROWS(curr.try_get_SettlBusinessDays());
      CHECK_THROWS(curr.try_get_QuoteSizeRules());
      for (auto px_range : curr.get_PriceRangeRules())
        CHECK(px_range.get_PriceRangeRuleID().value() == 49);
      CHECK_THROWS(curr.try_get_TradingSessionRules());
    }
  }
}
