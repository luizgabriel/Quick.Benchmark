add_executable(TCC.Benchmark RowMajorVsColumnMajor.cpp)
target_link_libraries(TCC.Benchmark PRIVATE CONAN_PKG::benchmark CONAN_PKG::fmt TCC.Library)
