#include "black_scholes.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

void test_known_value() {
  OptionParameters parameters{100.0, 100.0, 0.2, 0.05, 1.0};

  constexpr double expected_option_price{10.4506};
  constexpr double tolerance = 1e-4;

  double option_price{black_scholes(parameters)};

  assert(std::abs(option_price - expected_option_price) < tolerance);
  std::cout << "known value test passed.\n";
}

void test_higher_volatility_increases_price() {
  OptionParameters parameters{100.0, 100.0, 0.2, 0.05, 1.0};

  double previous_option_price{black_scholes(parameters)};

  for (int i{0}; i < 5; ++i) {
    parameters.set_volatility(parameters.get_volatility() + 0.1);
    double current_option_price{black_scholes(parameters)};
    assert(current_option_price > previous_option_price);
    previous_option_price = current_option_price;
  }
  std::cout << "increasing volatility test passed.\n";
}

void test_longer_expiry_increases_price() {
  OptionParameters parameters{100.0, 100.0, 0.2, 0.05, 1.0};

  double previous_option_price{black_scholes(parameters)};
  for (int i{0}; i < 5; ++i) {
    parameters.set_expiry(parameters.get_expiry() + 1.0);
    double current_option_price{black_scholes(parameters)};
    assert(current_option_price > previous_option_price);
    previous_option_price = current_option_price;
  }
  std::cout << "increasing expiry time test passed.\n";
}

int main() {
  test_known_value();
  test_higher_volatility_increases_price();
  test_longer_expiry_increases_price();

  std::cout << "all tests passed.\n";

  return 0;
}
