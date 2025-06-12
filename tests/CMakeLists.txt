FASTTYPEGEN_TARGET(simple_types1 simple1.xml)
FASTTYPEGEN_TARGET(simple_types2 simple2.xml)
FASTTYPEGEN_TARGET(simple_types3 simple3.xml)
FASTTYPEGEN_TARGET(simple_types4 simple4.xml)
FASTTYPEGEN_TARGET(simple_types5 simple5.xml)
FASTTYPEGEN_TARGET(simple_types6 simple6.xml)
FASTTYPEGEN_TARGET(simple_types7 simple7.xml)
FASTTYPEGEN_TARGET(simple_types8 simple8.xml)
FASTTYPEGEN_TARGET(simple_types9 simple9.xml)
FASTTYPEGEN_TARGET(simple_types10 simple10.xml)
FASTTYPEGEN_TARGET(simple_types11 simple11.xml)
FASTTYPEGEN_TARGET(simple_types12 simple12.xml)
FASTTYPEGEN_TARGET(simple_types13 simple13.xml)
FASTTYPEGEN_TARGET(simple_types14 simple14.xml)
FASTTYPEGEN_TARGET(simple_types15 simple15.xml)
FASTTYPEGEN_TARGET(simple_types16 simple16.xml)
FASTTYPEGEN_TARGET(simple_types17 simple17.xml)

FASTTYPEGEN_TARGET(test_types1 test1.xml test2.xml)
FASTTYPEGEN_TARGET(test_types3 test3.xml)
FASTTYPEGEN_TARGET(test_types4 test4.xml)
FASTTYPEGEN_TARGET(test_types5 test5.xml)
FASTTYPEGEN_TARGET(test_types6 test6.xml)
FASTTYPEGEN_TARGET(test_scp scp.xml)

list(APPEND TESTS_OBJ
  test_main.cpp
  arena_allocator_test.cpp
  field_ref_test.cpp
  fast_istream_test.cpp
  fast_ostream_test.cpp
  decoder_operator_test.cpp
  encoder_operator_test.cpp
  encoder_test.cpp
  encoder_decoder_test.cpp
  encoder_decoder_test_v2.cpp
  encoder_decoder_pmap.cpp
  encoder_decoder_pmap_v2.cpp
  field_comparator_test.cpp
  group_encoder_decoder_v2.cpp
  group_encoder_decoder.cpp
  coder_test.cpp
  value_storage_test.cpp
  ${FASTTYPEGEN_test_types1_OUTPUTS}
  ${FASTTYPEGEN_test_types3_OUTPUTS}
  ${FASTTYPEGEN_test_types4_OUTPUTS}
  ${FASTTYPEGEN_test_types5_OUTPUTS}
  ${FASTTYPEGEN_test_types6_OUTPUTS}
  ${FASTTYPEGEN_test_scp_OUTPUTS}
  ${FASTTYPEGEN_simple_types1_OUTPUTS}
  ${FASTTYPEGEN_simple_types2_OUTPUTS}
  ${FASTTYPEGEN_simple_types3_OUTPUTS}
  ${FASTTYPEGEN_simple_types4_OUTPUTS}
  ${FASTTYPEGEN_simple_types5_OUTPUTS}
  ${FASTTYPEGEN_simple_types6_OUTPUTS}
  ${FASTTYPEGEN_simple_types7_OUTPUTS}
  ${FASTTYPEGEN_simple_types8_OUTPUTS}
  ${FASTTYPEGEN_simple_types9_OUTPUTS}
  ${FASTTYPEGEN_simple_types10_OUTPUTS}
  ${FASTTYPEGEN_simple_types11_OUTPUTS}
  ${FASTTYPEGEN_simple_types12_OUTPUTS}
  ${FASTTYPEGEN_simple_types13_OUTPUTS}
  ${FASTTYPEGEN_simple_types14_OUTPUTS}
  ${FASTTYPEGEN_simple_types15_OUTPUTS}
  ${FASTTYPEGEN_simple_types16_OUTPUTS}
  ${FASTTYPEGEN_simple_types17_OUTPUTS}
  fast_type_gen_test.cpp
  dictionary_builder_test.cpp
  json_test.cpp
  int_vector_test.cpp
  composite_type_test.cpp
  aggregate_view_test.cpp
  simple_coder_test.cpp
  sequence_encoder_decoder_v2.cpp
  sequence_encoder_decoder.cpp
  scp_reset_test.cpp
  template_repo_base.cpp
  message_pmap_test.cpp
  enum_encoder_decoder_v2.cpp
  enum_encoder_decoder.cpp
  test_eurex_fast_1_2.cpp
  timestamp_encoder_decoder_v2.cpp
  timestamp_encoder_decoder.cpp)

if (NOT Catch2_FOUND)
  include_directories(SYSTEM ${PROJECT_SOURCE_DIR}/Catch2/extras)
  list(APPEND TESTS_OBJ
    ${PROJECT_SOURCE_DIR}/Catch2/extras/catch_amalgamated.cpp)
  add_executable(mfast_test ${TESTS_OBJ})
  target_link_libraries(mfast_test
    mfast_static
    mfast_coder_static
    mfast_json_static
    mfast_xml_parser_static)
else()
  add_executable(mfast_test ${TESTS_OBJ})
  target_link_libraries (mfast_test
    PRIVATE
      mfast_static
      mfast_coder_static
      mfast_json_static
      mfast_xml_parser_static
      Catch2::Catch2WithMain)
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    add_test(mfast_test node mfast_test.js)
else()
    add_test(mfast_test mfast_test)
endif()
