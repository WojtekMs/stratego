from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMake


class ExampleRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def layout(self):
        cmake_layout(self)

    def requirements(self):
        self.requires("sfml/2.6.1")
    
    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.install()