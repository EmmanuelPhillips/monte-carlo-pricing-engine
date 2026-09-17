#include "monte_carlo.hpp"
#include <chrono>
#include <iostream>

void benchmark_monte_carlo() {
  std::cout << "monte carlo benchmarks\n";
  int simulations{1000};
  for (int i{0}; i < 5; ++i) {
    auto start{std::chrono::high_resolution_clock::now()};
    monte_carlo(100.0, 100.0, 0.2, 0.05, 1.0, simulations);
    auto end{std::chrono::high_resolution_clock::now()};
    auto runtime_ms{
        std::chrono::duration_cast<std::chrono::microseconds>(end - start)
            .count()};
    std::cout << "simulations: " << simulations << " | runtime: " << runtime_ms
              << "microseconds\n";
    simulations *= 10;
  }
}

int main() { benchmark_monte_carlo(); }
