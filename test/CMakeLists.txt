add_executable(TCC.Tests Matrix.test.cpp)
target_link_libraries(TCC.Tests PUBLIC CONAN_PKG::gtest TCC.Library)

include(GoogleTest)
gtest_discover_tests(TCC.Tests)