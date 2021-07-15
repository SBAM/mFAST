if (NOT Boost_FOUND)
  find_package(Boost 1.59.0 REQUIRED)
endif()

### alter standard only if undefined or lower that c++17
if (NOT DEFINED CMAKE_CXX_STANDARD OR CMAKE_CXX_STANDARD STRLESS 17)
    set(CMAKE_CXX_STANDARD 17)
endif()
