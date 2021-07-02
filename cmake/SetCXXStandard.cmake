if (NOT Boost_FOUND)
  find_package(Boost 1.59.0 REQUIRED)
endif()

### alter standard only if undefined or lower that c++14
if (NOT DEFINED CMAKE_CXX_STANDARD OR
    CMAKE_CXX_STANDARD STRLESS 14)
  if(Boost_VERSION VERSION_LESS "1.72.0")
    set(CMAKE_CXX_STANDARD 11 CACHE INTERNAL "specifies the C++ standard whose features are requested to build this target")
  else()
    set(CMAKE_CXX_STANDARD 14 CACHE INTERNAL "specifies the C++ standard whose features are requested to build this target")
  endif()
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    ### Even though CMAKE_CXX_STANDARD_REQUIRED is supported since CMake 3.1, it doesn't work for Emscripten em++ together with
    ### Cmake 3.6.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++${CMAKE_CXX_STANDARD}")
  endif()
endif()
