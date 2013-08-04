// Copyright (c) 2013, Huang-Ming Huang,  Object Computing, Inc.
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
#include <mfast/encoder/fast_ostream.h>
#include <mfast/encoder/fast_ostream_inserter.h>
#include <mfast/encoder/encoder_presence_map.h>
#include <mfast/output.h>
#define BOOST_TEST_DYN_LINK
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test.hpp>

#include "debug_allocator.h"
#include <stdexcept>
#include "byte_stream.h"

using namespace mfast;

template <typename T>
boost::test_tools::predicate_result
encode_integer(T value, bool nullable, const byte_stream& result)
{  
  char buffer[16];
  debug_allocator alloc;
  fast_ostreambuf sb(buffer);
  fast_ostream strm(&alloc);
  strm.rdbuf(&sb);

  strm.encode(value, nullable);

  if (byte_stream(sb) == result)
    return true;

  boost::test_tools::predicate_result res( false );
  res.message() << "Got \"" << byte_stream(sb) << "\" instead.";
  return res;

}

BOOST_AUTO_TEST_SUITE( test_fast_ostream )


BOOST_AUTO_TEST_CASE(int_test)
{

  BOOST_CHECK(encode_integer(INT32_C(942755), true, "\x39\x45\xa4" ));
  BOOST_CHECK(encode_integer(INT32_C(942755), false, "\x39\x45\xa3"));
  BOOST_CHECK(encode_integer(INT32_C(-942755), true, "\x46\x3a\xdd"));
  BOOST_CHECK(encode_integer(INT32_C(-7942755), false, "\x7c\x1b\x1b\x9d"));
  BOOST_CHECK(encode_integer(INT32_C(8193), false, "\x00\x40\x81"));
  BOOST_CHECK(encode_integer(INT32_C(-8193), false, "\x7F\x3f\xff"));

  BOOST_CHECK(encode_integer(UINT32_C(0), true, "\x81"));
  BOOST_CHECK(encode_integer(UINT32_C(1), true, "\x82"));
  BOOST_CHECK(encode_integer(UINT32_C(942755), true, "\x39\x45\xa4"));
  BOOST_CHECK(encode_integer(UINT32_C(0), false, "\x80"));
  BOOST_CHECK(encode_integer(UINT32_C(1), false, "\x81"));
  BOOST_CHECK(encode_integer(UINT32_C(942755), false, "\x39\x45\xa3"));
  BOOST_CHECK(encode_integer(UINT32_C(4294967295), true,"\x10\x00\x00\x00\x80"));

  BOOST_CHECK(encode_integer(std::numeric_limits<int64_t>::max(), true, "\x01\x00\x00\x00\x00\x00\x00\x00\x00\x80"));
  BOOST_CHECK(encode_integer(std::numeric_limits<uint64_t>::max(), true, "\x02\x00\x00\x00\x00\x00\x00\x00\x00\x80"));
}


boost::test_tools::predicate_result
encode_string(const char* str,std::size_t len, bool nullable, const byte_stream& result)
{
  char buffer[16];
  ascii_field_instruction* instruction = 0;

  debug_allocator alloc;
  fast_ostreambuf sb(buffer);
  fast_ostream strm(&alloc);
  strm.rdbuf(&sb);


  strm.encode(str, len, nullable, instruction);

  if (byte_stream(sb) == result)
    return true;

  boost::test_tools::predicate_result res( false );
  res.message() << "Got \"" << byte_stream(sb) << "\" instead.";
  return res;
}

BOOST_AUTO_TEST_CASE(ascii_string_test)
{
  BOOST_CHECK(encode_string("", 0, false, "\x80"));
  BOOST_CHECK(encode_string("\x0", 1, false, "\x00\x80"));

  BOOST_CHECK(encode_string(0, 0, true, "\x80"));
  BOOST_CHECK(encode_string("", 0, true, "\x00\x80"));
  BOOST_CHECK(encode_string("\x0", 1, true, "\x00\x00\x80"));
  
  BOOST_CHECK(encode_string("\x40\x40\xC0", 3, true, "\x40\x40\xC0"));
  BOOST_CHECK(encode_string("\x40\x40\xC0", 3, false, "\x40\x40\xC0"));

}

boost::test_tools::predicate_result
encode_byte_vector(const char* bv,std::size_t len, bool nullable, const byte_stream& result)
{
  char buffer[16];

  debug_allocator alloc;
  fast_ostreambuf sb(buffer);
  fast_ostream strm(&alloc);
  strm.rdbuf(&sb);


  strm.encode(reinterpret_cast<const unsigned char*>(bv), len, nullable, 0);

  if (byte_stream(sb) == result)
    return true;

  boost::test_tools::predicate_result res( false );
  res.message() << "Got \"" << byte_stream(sb) << "\" instead.";
  return res;
}

BOOST_AUTO_TEST_CASE(byte_vector_test)
{
  BOOST_CHECK(encode_byte_vector(0, 0, true, "\x80")); // null
  BOOST_CHECK(encode_byte_vector("", 0, false, "\x80")); // empty byte vector
  BOOST_CHECK(encode_byte_vector("", 0, true, "\x81")); // empty byte vector

  BOOST_CHECK(encode_byte_vector("\xC0", 1, false, "\x81\xC0"));
  BOOST_CHECK(encode_byte_vector("\xC0", 1, true, "\x82\xC0"));
}

template <typename T>
boost::test_tools::predicate_result
insert_to_stream(const T& value, const byte_stream& result)
{
  char buffer[16];

  debug_allocator alloc;
  fast_ostreambuf sb(buffer);
  fast_ostream strm(&alloc);
  strm.rdbuf(&sb);

  strm << value;

  if (byte_stream(sb) == result)
    return true;

  boost::test_tools::predicate_result res( false );
  res.message() << "Insert " << value << " failure!\nGot \"" << byte_stream(sb) << "\" instead.";
  return res;
}

BOOST_AUTO_TEST_CASE(inserter_test)
{
  debug_allocator alloc;
  value_storage storage;
  {
    const char* default_value = "initial_string";
    ascii_field_instruction inst(0, operator_copy,
                                 presence_optional,
                                 1,
                                 "test_ascii","",
                                 0,
                                 default_value, strlen(default_value));

    inst.construct_value(storage, &alloc);
    ascii_string_mref mref(&alloc, &storage, &inst);
    mref.shallow_assign("AAA");

    BOOST_CHECK(insert_to_stream(mref, "\x41\x41\xC1"));
  }

  {
    decimal_field_instruction inst(0, operator_copy,
                                   presence_optional,
                                   1,
                                   "test_decimal","",
                                   0,
                                   nullable_decimal(INT64_MAX,64));

    inst.construct_value(storage, &alloc);
    decimal_mref mref(&alloc, &storage, &inst);


    mref.as_absent();
    BOOST_CHECK(insert_to_stream(mref, "\x80"));

    mref.as(1, 4);
    BOOST_CHECK(insert_to_stream(mref, "\x85\x81"));
  }

}



boost::test_tools::predicate_result
encode_pmap(const char* bits, std::size_t maxbits, const byte_stream& result)
{
  char buffer[16];
  
  debug_allocator alloc;
  fast_ostreambuf sb(buffer);
  fast_ostream strm(&alloc);
  strm.rdbuf(&sb);
 
  encoder_presence_map pmap;
  pmap.init(&strm, maxbits);
  
  unsigned byte;
  
  for (std::size_t i = 0; i < maxbits; ++i ) {
    
    if (i % 8 == 0) {
      byte = bits[0];
      bits += 1;
    }
    
    pmap.set_next_bit( byte & 0x80 ) ;
    byte <<= 1;
  }
  
   pmap.commit();
   if (byte_stream(sb) == result)
     return true;
   boost::test_tools::predicate_result res( false );
   res.message() << "Got \"" << byte_stream(sb) << "\" instead.";
   return res;
}


BOOST_AUTO_TEST_CASE(encoder_presence_map_test)
{
  BOOST_CHECK( encode_pmap("\x80", 7, "\xC0" ) );
  BOOST_CHECK( encode_pmap("\x80\x04", 14, "\x40\x81" ) );
  BOOST_CHECK( encode_pmap("\x81\x02\x04\x08\x10\x20\x40\x80", 63, "\x40\x40\x40\x40\x40\x40\x40\x40\xC0" ) );
}

BOOST_AUTO_TEST_SUITE_END()
