from conans import CMake, ConanFile, tools

class MfastConan(ConanFile):
  name = "mfast"
  version = "1.2.4"
  license = "BSD 3-Clause 'New' or 'Revised' License"
  author = "Object Computing, Inc. (info@ociweb.com)"
  url = "https://github.com/objectcomputing/mFAST"
  description = "A FAST (FIX Adapted for STreaming) encoder/decoder"
  topics = ("c++", "FIX", "FAST")
  settings = "os", "compiler", "build_type", "arch"
  requires = ( "boost/[>=1.69.0]",
               "tinyxml2/9.0.0" )
  options = { "shared": [True, False],
              "fPIC": [True, False],
              "build_tests": [True, False],
              "build_examples": [True, False],
              "build_packages": [True, False] }
  default_options = { "shared": False,
                      "fPIC": True,
                      "build_tests": False,
                      "build_examples": False,
                      "build_packages": False }
  generators = "cmake", "cmake_find_package"
  exports_sources = "CMakeLists.txt", "cmake/*", "src/*", "examples/*", "tests/*"

  def configure(self):
    if self.options.shared:
      del self.options.fPIC

  def requirements(self):
    if self.options.build_tests:
      self.requires("catch2/3.1.0")

  def build(self):
    cmake = CMake(self)
    cmake.definitions["BUILD_TESTS"] = "ON" if self.options.build_tests else "OFF"
    cmake.definitions["BUILD_EXAMPLES"] = "ON" if self.options.build_examples else "OFF"
    cmake.definitions["BUILD_PACKAGES"] = "ON" if self.options.build_packages else "OFF"
    cmake.definitions["BUILD_SHARED_LIBS"] = "ON" if self.options.shared else "OFF"
    cmake.definitions["STATIC_GEN"] = "ON" if not self.options.shared else "OFF"
    cmake.configure(args=["--no-warn-unused-cli"])
    cmake.build()
    cmake.install()

  def package(self):
    # packaging taken care of above (with cmake install)
    pass

  def package_info(self):
    self.cpp_info.libs = ["mfast"]
    # no generator name provided, packaged CMake helpers are expected to be used

  def validate(self):
    tools.check_min_cppstd(self, "17")
