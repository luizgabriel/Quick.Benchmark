add_executable(TCC.Benchmark main.cpp)
target_link_libraries(TCC.Benchmark PRIVATE CONAN_PKG::benchmark TCC.Library)
