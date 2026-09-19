#include "monte_carlo.hpp"
#include "monte_carlo_multithreaded.hpp"
#include <chrono>
#include <iostream>
#include <vector>

void benchmark_monte_carlo(std::vector<long long> &results, double spot,
                           double strike, double volatility, double rate,
                           double expiry, int simulations) {
  for (auto i{0}; i < results.size(); ++i) {
    auto start{std::chrono::high_resolution_clock::now()};
    monte_carlo(spot, strike, volatility, rate, expiry, simulations);
    auto end{std::chrono::high_resolution_clock::now()};
    auto runtime_us{
        std::chrono::duration_cast<std::chrono::microseconds>(end - start)
            .count()};
    results[i] = runtime_us;
    simulations *= 10;
  }
}

void benchmark_monte_carlo_multithreaded(std::vector<long long> &results,
                                         double spot, double strike,
                                         double volatility, double rate,
                                         double expiry, int simulations) {
  for (auto i{0}; i < results.size(); ++i) {
    auto start{std::chrono::high_resolution_clock::now()};
    monte_carlo_multithreaded(spot, strike, volatility, rate, expiry,
                              simulations);
    auto end{std::chrono::high_resolution_clock::now()};
    auto runtime_us{
        std::chrono::duration_cast<std::chrono::microseconds>(end - start)
            .count()};
    results[i] = runtime_us;
    simulations *= 10;
  }
}

void print_results(const std::vector<long long> &singlethread_results,
                   const std::vector<long long> &multithread_results,
                   int simulations) {
  std::cout << "monte carlo benchmark results:\n";
  for (int i{0}; i < singlethread_results.size(); ++i) {
    std::cout << "simulations: " << simulations << '\n';
    std::cout << "single threaded: " << singlethread_results[i] << "us\n";
    std::cout << "multi threaded: " << multithread_results[i] << "us\n";

    double speedup{static_cast<double>(singlethread_results[i]) /
                   multithread_results[i]};
    std::cout << "speedup: " << speedup << "x\n\n";
    simulations *= 10;
  }
}

int main() {
  constexpr double spot{100.0};
  constexpr double strike{100.0};
  constexpr double volatility{0.2};
  constexpr double rate{0.05};
  constexpr double expiry{1.0};
  int simulations{1000};

  std::vector<long long> singlethread_results(5, 0);
  benchmark_monte_carlo(singlethread_results, spot, strike, volatility, rate,
                        expiry, simulations);

  std::vector<long long> multithread_results(5, 0);
  benchmark_monte_carlo_multithreaded(multithread_results, spot, strike,
                                      volatility, rate, expiry, simulations);

  print_results(singlethread_results, multithread_results, simulations);
}
