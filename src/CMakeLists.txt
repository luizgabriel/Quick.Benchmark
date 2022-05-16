# Generic test that uses conan libs
add_executable(Quick.Benchmark main.cpp)
target_link_libraries(Quick.Benchmark PRIVATE CONAN_PKG::benchmark)
