#include "monte_carlo.hpp"
#include <chrono>
#include <iostream>
#include <vector>

void benchmark_monte_carlo(std::vector<long long> &results,
                           const OptionParameters &parameters,
                           int simulations) {
  for (auto i{0}; i < results.size(); ++i) {
    auto start{std::chrono::high_resolution_clock::now()};

    MonteCarloPricer pricer{parameters, simulations};
    double price{pricer.price()};

    auto end{std::chrono::high_resolution_clock::now()};
    auto runtime_us{
        std::chrono::duration_cast<std::chrono::microseconds>(end - start)
            .count()};

    results[i] = runtime_us;
    simulations *= 10;
  }
}

void benchmark_monte_carlo_multithreaded(std::vector<long long> &results,
                                         const OptionParameters &parameters,
                                         int simulations) {
  for (auto i{0}; i < results.size(); ++i) {
    auto start{std::chrono::high_resolution_clock::now()};

    MonteCarloPricer pricer{parameters, simulations};
    double price{pricer.multithreaded_price()};

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

  OptionParameters parameters{spot, strike, volatility, rate, expiry};

  std::vector<long long> singlethread_results(5, 0);
  benchmark_monte_carlo(singlethread_results, parameters, simulations);

  std::vector<long long> multithread_results(5, 0);
  benchmark_monte_carlo_multithreaded(multithread_results, parameters,
                                      simulations);

  print_results(singlethread_results, multithread_results, simulations);
}
