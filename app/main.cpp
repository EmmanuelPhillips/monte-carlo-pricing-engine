#include "monte_carlo.hpp"
#include <iostream>

int main() {
  double spot{100.0};
  double strike{100.0};
  double volatility{0.20};
  double rate{0.05};
  double expiry{1.0};
  int simulations{10000};

  double option_price{
      monte_carlo(spot, strike, volatility, rate, expiry, simulations)};
  std::cout << "Option price: " << option_price << '\n';

  return 0;
}
