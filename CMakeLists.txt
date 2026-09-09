cmake_minimum_required(VERSION 3.20)

project(monte_carlo_pricing_engine)

set(CMAKE_CXX_STANDARD 17)

add_executable(
    monte_carlo_pricing_engine
    app/main.cpp
    src/monte_carlo.cpp
    src/black_scholes.cpp
)

target_include_directories(monte_carlo_pricing_engine PRIVATE include)
