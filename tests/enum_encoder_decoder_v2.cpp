#include "catch_fwd.hpp"
#include <mfast.h>

#include "fast_test_coding_case_v2.hpp"
#include "byte_stream.h"

#include "simple16.h"

using namespace test::coding;

TEST_CASE("enum test encoder_V2/decoder_v2","[enum_encoder_v2_decoder_v2]")
{
    fast_test_coding_case_v2<simple16::templates_description> test_case;
    simple16::Test_1 test_1;
    simple16::Test_1_mref test_1_mref = test_1.mref();
    test_1_mref.set_discrete().as_Three();
    REQUIRE(test_case.encoding(test_1.cref(),"\xC0\x81\x83",true));
    REQUIRE(test_case.decoding("\xC0\x81\x83",test_1.cref(),true));
}
