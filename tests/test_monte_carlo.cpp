#include "black_scholes.hpp"
#include "monte_carlo.hpp"
#include <cassert>
#include <iostream>

void test_mc_vs_bs() {
  constexpr double spot{100.0};
  constexpr double strike{100.0};
  constexpr double volatility{0.2};
  constexpr double rate{0.05};
  constexpr double expiry{1.0};
  constexpr int simulations{10000};

  constexpr double black_scholes_option_price{10.4506};

  double monte_carlo_option_price{
      monte_carlo(spot, strike, volatility, rate, expiry, simulations)};

  constexpr double tolerance{0.1};

  assert(std::abs(monte_carlo_option_price - black_scholes_option_price) <
         tolerance);
  std::cout << "sensible estimation test passed";
}

int main() {
  test_mc_vs_bs();

  return 0;
}
