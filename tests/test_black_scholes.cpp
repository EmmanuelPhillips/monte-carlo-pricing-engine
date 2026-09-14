#include "black_scholes.hpp"
#include <cassert>
#include <cmath>

int main() {
  constexpr double spot{100};
  constexpr double strike{100};
  constexpr double volatility{0.20};
  constexpr double rate{0.05};
  constexpr double expiry{1.0};

  constexpr double expected_option_price{10.4506};
  constexpr double tolerance = 1e-4;

  double option_price{black_scholes(spot, strike, volatility, rate, expiry)};

  assert(std::abs(option_price - expected_option_price) < tolerance);

  return 0;
}
