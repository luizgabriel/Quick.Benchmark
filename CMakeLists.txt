cmake_minimum_required(VERSION 3.16)

# Not ideal to use this global variable, but necessary to make sure
# that tooling and projects use the same version
set(CMAKE_CXX_STANDARD 20)

# strongly encouraged to enable this globally to avoid conflicts between
# -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example
# when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS ON)

# Set the project name and language
project(
  TCCBenchmark
  VERSION 0.0.1
  DESCRIPTION "Benchmark project for test algorithm"
  LANGUAGES CXX C)


set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)
include(CTest)
enable_testing()

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
          "${CMAKE_BINARY_DIR}/conan.cmake"
          TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

if(CONAN_EXPORTED)
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  conan_basic_setup(TARGETS NO_OUTPUT_DIRS)
else()
  if(CONAN_PROFILE)
    conan_cmake_run(
            CONANFILE conanfile.py
            BUILD missing
            PROFILE ${CONAN_PROFILE}
            BASIC_SETUP CMAKE_TARGETS NO_OUTPUT_DIRS)
  else()
    conan_cmake_autodetect(CONAN_SETTINGS)
    conan_cmake_run(
            CONANFILE conanfile.txt
            BUILD missing
            SETTINGS ${CONAN_SETTINGS}
            BASIC_SETUP CMAKE_TARGETS NO_OUTPUT_DIRS)
  endif()
endif()

get_property(BUILDING_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(BUILDING_MULTI_CONFIG)
  if(NOT CMAKE_BUILD_TYPE)
    # Make sure that all supported configuration types have their
    # associated conan packages available. You can reduce this
    # list to only the configuration types you use, but only if one
    # is not forced-set on the command line for VS
    message(TRACE "Setting up multi-config build types")
    set(CMAKE_CONFIGURATION_TYPES
        Debug
        Release
        RelWithDebInfo
        MinSizeRel
        CACHE STRING "Enabled build types" FORCE)
  else()
    message(TRACE "User chose a specific build type, so we are using that")
    set(CMAKE_CONFIGURATION_TYPES
        ${CMAKE_BUILD_TYPE}
        CACHE STRING "Enabled build types" FORCE)
  endif()
endif()

# Adding the src:
add_subdirectory(lib)
add_subdirectory(benchmark)
add_subdirectory(test)