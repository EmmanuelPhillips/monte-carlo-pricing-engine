#include "black_scholes.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

void test_known_value() {
  constexpr double spot{100};
  constexpr double strike{100};
  constexpr double volatility{0.20};
  constexpr double rate{0.05};
  constexpr double expiry{1.0};

  constexpr double expected_option_price{10.4506};
  constexpr double tolerance = 1e-4;

  double option_price{black_scholes(spot, strike, volatility, rate, expiry)};

  assert(std::abs(option_price - expected_option_price) < tolerance);
  std::cout << "known value test passed.\n";
}

void test_higher_volatility_increases_price() {
  constexpr double spot{100};
  constexpr double strike{100};
  double volatility{0.20};
  constexpr double rate{0.05};
  constexpr double expiry{1.0};

  double previous_option_price{
      black_scholes(spot, strike, volatility, rate, expiry)};

  for (int i{0}; i < 5; ++i) {
    volatility += 0.1;
    double current_option_price{
        black_scholes(spot, strike, volatility, rate, expiry)};
    assert(current_option_price > previous_option_price);
    previous_option_price = current_option_price;
  }
  std::cout << "increasing volatility test passed.\n";
}

void test_longer_expiry_increases_price() {
  constexpr double spot{100};
  constexpr double strike{100};
  constexpr double volatility{0.20};
  constexpr double rate{0.05};
  double expiry{1.0};

  double previous_option_price{
      black_scholes(spot, strike, volatility, rate, expiry)};
  for (int i{0}; i < 5; ++i) {
    expiry += 1;
    double current_option_price{
        black_scholes(spot, strike, volatility, rate, expiry)};
    assert(current_option_price > previous_option_price);
  }
  std::cout << "increasing expiry time test passed.\n";
}

int main() {
  test_known_value();
  test_higher_volatility_increases_price();

  return 0;
}
