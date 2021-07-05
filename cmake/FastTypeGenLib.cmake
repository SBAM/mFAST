#============================================================
# FASTTYPEGEN_LIB (public function)
#                 generates a library named according to
#                 output arg for input template
#============================================================
#

function(FASTTYPEGEN_LIB
    input     # path to fast template
    output    # ouput library name
    namespace # outer namespace name
    hdr_ext   # generated header extension
    src_ext   # generated compilation unit extension
    inl_ext   # inlined header extension
    static_lib)
  get_filename_component(input_abs ${input} ABSOLUTE)
  get_filename_component(input_noext ${input} NAME_WE)

  set(mfast_generated_sources
    ${CMAKE_CURRENT_BINARY_DIR}/${input_noext}.${hdr_ext}
    ${CMAKE_CURRENT_BINARY_DIR}/${input_noext}.${src_ext}
    ${CMAKE_CURRENT_BINARY_DIR}/${input_noext}.${inl_ext})

  add_custom_command(OUTPUT ${mfast_generated_sources}
    COMMAND $<TARGET_FILE:fast_type_gen>
            -n ${namespace} # outer namespace
            -H .${hdr_ext}  # headers extension
            -I .${inl_ext}  # inline headers extension
            -C .${src_ext}  # compilation units extension
            -- ${input_abs}
    DEPENDS ${input}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "mFAST generating library ${output}"
    VERBATIM)

  add_custom_target(mfast_${input_noext}_dep
    DEPENDS ${mfast_generated_sources})

  if(static_lib)
    add_library(${output} STATIC ${mfast_generated_sources})
  else()
    add_library(${output} ${mfast_generated_sources})
  endif()
  add_dependencies(${output} mfast_${input_noext}_dep)

  target_include_directories(${output}
    INTERFACE
      $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)

  target_link_libraries(${output}
    PUBLIC
      mFAST::mFAST)
endfunction(FASTTYPEGEN_LIB)
