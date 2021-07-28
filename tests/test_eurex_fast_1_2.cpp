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

#include "catch.hpp"

#include "test6.h"
#include <mfast/field_comparator.h>
#include "debug_allocator.h"

using namespace std::string_literals;

TEST_CASE("eurex enums","[test_eurex_enums]")
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


TEST_CASE("eurex timestamps","[test_eurex_timestamps]")
{
  debug_allocator alloc;
  using namespace test6;

  MarketDataReport md(&alloc);
  MarketDataReport_mref md_mref(md.mref());
  md_mref.set_TransactTime().as(123456789);
  REQUIRE(md_mref.set_TransactTime().value() == 123456789);
}


TEST_CASE("eurex sets","[test_eurex_sets]")
{
  debug_allocator alloc;
  using namespace test6;

  DepthIncremental md(&alloc);
  DepthIncremental_mref md_mref(md.mref());
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
  REQUIRE(!md_mref.get_TradeCondition().has_LowPrice());
  REQUIRE(!md_mref.get_TradeCondition().has_TradeAtClose());
  REQUIRE(md_mref.get_TradeConditionSet().has_VolumeOnly());
}
