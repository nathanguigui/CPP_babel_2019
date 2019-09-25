from conans import ConanFile, CMake

class CPP_Babel(ConanFile):
   name = "client"
   version = "0.1"
   settings = "os_build", "compiler", "build_type", "arch"
   requires = "boost/1.71.0@conan/stable", "qt/5.13.1@bincrafters/stable", "portaudio/v190600.20161030@bincrafters/stable", "opus/1.3.1@bincrafters/stable" # comma-separated list of requirements
   generators = "cmake", "gcc", "txt", "cmake_find_package"
   build_policy = "missing"

   def build(self):
      cmake = CMake(self)
      cmake.configure()
      cmake.build()