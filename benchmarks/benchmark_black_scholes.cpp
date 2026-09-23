#include "black_scholes.hpp"
#include "option_parameters.hpp"
#include <chrono>
#include <iostream>

int main() {
  OptionParameters parameters{100.0, 100.0, 0.2, 0.05, 1.0};
  BlackScholesPricer pricer{parameters};

  constexpr int iterations{1'000'000};

  auto start{std::chrono::high_resolution_clock::now()};

  double result{0.0};

  for (int i{0}; i < iterations; ++i) {
    result = pricer.price();
  }

  auto end{std::chrono::high_resolution_clock::now()};

  auto runtime_us{
      std::chrono::duration_cast<std::chrono::microseconds>(end - start)
          .count()};

  std::cout << "black scholes benchmark\n";
  std::cout << "iterations: " << iterations << '\n';
  std::cout << "runtime: " << runtime_us << " us\n";
  std::cout << "last price: " << result << '\n';
}
