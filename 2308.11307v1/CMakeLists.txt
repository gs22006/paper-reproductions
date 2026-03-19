cmake_minimum_required(VERSION 3.16)
project(knapsack_paper_2308_11307 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_library(knapsack_core
    src/solvers/zero_one_dp.cpp
    src/solvers/alg1_interval_dp.cpp
)

target_include_directories(knapsack_core PUBLIC include)

target_compile_options(knapsack_core PRIVATE
    $<$<CONFIG:Release>:-O3 -DNDEBUG>
    $<$<CONFIG:Debug>:-O0 -g>
)

add_executable(test_alg1 apps/test_alg1.cpp)
target_link_libraries(test_alg1 PRIVATE knapsack_core)

add_executable(benchmark_alg1 apps/benchmark_alg1.cpp)
target_link_libraries(benchmark_alg1 PRIVATE knapsack_core)
