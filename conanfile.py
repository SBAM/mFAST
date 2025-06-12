from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMakeToolchain, CMake, CMakeDeps
from conan.tools import build
from pathlib import Path

class MfastConan(ConanFile):
  name = "mfast"
  version = "1.3.10"
  license = "BSD 3-Clause 'New' or 'Revised' License"
  author = "Object Computing, Inc. (info@ociweb.com)"
  url = "https://github.com/objectcomputing/mFAST"
  description = "A FAST (FIX Adapted for STreaming) encoder/decoder"
  topics = ("c++", "FIX", "FAST")
  generators = "CMakeDeps"
  settings = "os", "compiler", "build_type", "arch"
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
  exports_sources = "cmake/*", "CMakeLists.txt", "examples/*", "schema/*", "src/*", "tests/*"

  def build_requirements(self):
    if self.options.build_tests:
      self.test_requires("catch2/[>=3.8.1]")

  def requirements(self):
    self.requires("boost/[>=1.78.0]")
    self.requires("tinyxml2/[>=11.0.0]")

  def config_options(self):
    if self.options.shared:
      del self.options.fPIC

  def layout(self):
    cmake_layout(self)

  def generate(self):
    tc = CMakeToolchain(self)
    tc.user_presets_path = False
    tc.variables["BUILD_TESTS"] = "ON" if self.options.build_tests else "OFF"
    tc.variables["BUILD_EXAMPLES"] = "ON" if self.options.build_examples else "OFF"
    tc.variables["BUILD_PACKAGES"] = "ON" if self.options.build_packages else "OFF"
    tc.variables["BUILD_SHARED_LIBS"] = "ON" if self.options.shared else "OFF"
    tc.generate()

  def build(self):
    cmake = CMake(self)
    cmake.configure()
    cmake.build()

  def package(self):
    cmake = CMake(self)
    cmake.install()

  def package_info(self):
    self.cpp_info.libs = ["mfast", "mfast_coder"]
    self.cpp_info.set_property("cmake_target_name", "mFAST::mFAST")
    tmp_path = Path("lib")/"cmake"/"mFAST"/"FastTypeGenLib.cmake"
    self.cpp_info.set_property("cmake_build_modules", [ tmp_path ])

  def validate(self):
    build.check_min_cppstd(self, "17")
