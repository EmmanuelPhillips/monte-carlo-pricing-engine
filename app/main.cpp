#include "black_scholes.hpp"
#include "monte_carlo.hpp"
#include <cmath>
#include <format>
#include <iostream>

int main() {
  double spot{100.0};
  double strike{100.0};
  double volatility{0.20};
  double rate{0.05};
  double expiry{1.0};
  int simulations{10000};

  double monte_carlo_option_price{
      monte_carlo(spot, strike, volatility, rate, expiry, simulations)};
  double black_scholes_option_price{
      black_scholes(spot, strike, volatility, rate, expiry)};

  std::cout << std::format(
      "option price results:\nmonte carlo: {:.2f}\nblack scholes: "
      "{:.2f}\nprice diff: "
      "{:.2f}\n",
      monte_carlo_option_price, black_scholes_option_price,
      std::abs(monte_carlo_option_price - black_scholes_option_price));

  return 0;
}
