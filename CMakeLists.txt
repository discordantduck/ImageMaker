cmake_minimum_required(VERSION 3.17)
project(ImageMaker)

# Increase the stack memory.  ppm images are big!
MATH(EXPR stack_size "50 * 1024 * 1024") # 50 Mb
if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")
endif (WIN32)

if (UNIX)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-z,stack-size=${stack_size}")
endif (UNIX)

# link with lld if available for speed
option(ENABLE_LLD "LLD" ON)
if (ENABLE_LLD)
  execute_process(COMMAND ${CMAKE_CXX_COMPILER} -fuse-ld=lld -Wl,--version ERROR_QUIET OUTPUT_VARIABLE LLD_VERSION)
  if(LLD_VERSION MATCHES "LLD")
    SET(LLD_AVAILABLE ON)
    MESSAGE(STATUS "lld linker available")
  endif()
endif()

# Run demo showing functionality.
add_executable(ImageMaker_Demo ImageMaker_demo.cpp ImageMaker.cpp)

# Run all tests
add_executable(ImageMaker_Test unit_tests/catch_main.cpp unit_tests/ImageMaker_tests.cpp ImageMaker.cpp)

# Test getters, setters, constructors, save and load
add_executable(Getter_Setter_Test unit_tests/catch_main.cpp unit_tests/getter_setter_tests.cpp ImageMaker.cpp)
add_executable(Constructor_Test unit_tests/catch_main.cpp unit_tests/constructor_tests.cpp ImageMaker.cpp)
add_executable(Save_Load_Test unit_tests/catch_main.cpp unit_tests/save_load_tests.cpp ImageMaker.cpp)

# Draw Tests (requires getters, setters, constructors, save and load to work)
add_executable(DrawPixel_Test unit_tests/catch_main.cpp unit_tests/DrawPixel_tests.cpp ImageMaker.cpp)
add_executable(DrawRectangle_Test unit_tests/catch_main.cpp unit_tests/DrawRectangle_tests.cpp ImageMaker.cpp)
add_executable(DrawLine_Test unit_tests/catch_main.cpp unit_tests/DrawLine_tests.cpp ImageMaker.cpp)

# Used for your tests only.  Not used for grading.
add_executable(My_Test unit_tests/my_tests.cpp ImageMaker.cpp)

set_property(TARGET ImageMaker_Test PROPERTY CXX_STANDARD 14)
