from conans import CMake, ConanFile, tools

class MfastConan(ConanFile):
  name = "mfast"
  version = "1.2.3"
  license = "BSD 3-Clause 'New' or 'Revised' License"
  author = "Object Computing, Inc. (info@ociweb.com)"
  url = "https://github.com/objectcomputing/mFAST"
  description = "A FAST (FIX Adapted for STreaming) encoder/decoder"
  topics = ("c++", "FIX", "FAST")
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
  requires = "boost/[>=1.59.0]"
  generators = "cmake"
  exports_sources = "CMakeLists.txt", "cmake/*", "src/*", "examples/*", "tests/*"

  def configure(self):
    if self.options.shared:
      del self.options.fPIC

  def source(self):
    if self.options.build_tests:
      git_catch = tools.Git(folder="catch")
      git_catch.clone("https://github.com/catchorg/Catch2.git")
      git_catch.checkout("d758428fe297655e558a86cc6a013fcb1bcc8c7d")
    git_tinyxml2 = tools.Git(folder="tinyxml2")
    git_tinyxml2.clone("https://github.com/leethomason/tinyxml2.git")

  def configure_cmake(self):
    cmake = CMake(self)
    cmake.definitions["BUILD_TESTS"] = "ON" if self.options.build_tests else "OFF"
    cmake.definitions["BUILD_EXAMPLES"] = "ON" if self.options.build_examples else "OFF"
    cmake.definitions["BUILD_PACKAGES"] = "ON" if self.options.build_packages else "OFF"
    cmake.definitions["BUILD_SHARED_LIBS"] = "ON" if self.options.shared else "OFF"
    cmake.definitions["STATIC_GEN"] = "ON" if not self.options.shared else "OFF"
    cmake.configure()
    return cmake

  def build(self):
    cmake = self.configure_cmake()
    cmake.build()

  def package(self):
    cmake = self.configure_cmake()
    cmake.install()

  def package_info(self):
    self.cpp_info.libs = ["mfast"]

  def validate(self):
    tools.check_min_cppstd(self, "17")
