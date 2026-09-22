cmake_minimum_required(VERSION 3.20)

project(monte_carlo_pricing_engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    monte_carlo_pricing_engine
    app/main.cpp
    src/monte_carlo.cpp
    src/monte_carlo_multithreaded.cpp
    src/black_scholes.cpp
    src/option_parameters.cpp
)

target_include_directories(monte_carlo_pricing_engine PRIVATE include)

add_executable(
    test_black_scholes
    tests/test_black_scholes.cpp
    src/black_scholes.cpp
    src/option_parameters.cpp
)

target_include_directories(test_black_scholes PRIVATE include)

add_executable(
    test_monte_carlo
    tests/test_monte_carlo.cpp
    src/monte_carlo.cpp
    src/black_scholes.cpp
    src/option_parameters.cpp
)

target_include_directories(test_monte_carlo PRIVATE include)

add_executable(
    benchmark_monte_carlo
    benchmarks/benchmark_monte_carlo.cpp
    src/monte_carlo.cpp
    src/monte_carlo_multithreaded.cpp
    src/option_parameters.cpp
)

target_include_directories(benchmark_monte_carlo PRIVATE include)
