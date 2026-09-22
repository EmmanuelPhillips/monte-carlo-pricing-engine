#include "black_scholes.hpp"
#include "monte_carlo.hpp"
#include "option_parameters.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

void test_mc_vs_bs() {
  OptionParameters parameters{100.0, 100.0, 0.2, 0.05, 1.0};
  constexpr int simulations{1'000'000};

  constexpr double black_scholes_option_price{10.4506};
  constexpr double tolerance{0.1};

  double monte_carlo_option_price{
      monte_carlo(spot, strike, volatility, rate, expiry, simulations)};

  assert(std::abs(monte_carlo_option_price - black_scholes_option_price) <
         tolerance);

  std::cout << "MC vs BS test passed.\n";
}

void test_higher_volatility_increases_price() {
  OptionParameters parameters{100.0, 100.0, 0.2, 0.05, 1.0};

  constexpr double low_volatility{0.1};
  constexpr double high_volatility{0.3};

  constexpr int simulations{1000000};

  parameters.set_volatility(low_volatility);
  double low_volatility_price{monte_carlo(parameters, simulations)};

  parameters.set_volatility(high_volatility);
  double high_volatility_price{monte_carlo(parameters, simulations)};

  assert(high_volatility_price > low_volatility_price);

  std::cout << "higher volatility test passed.\n";
}

void test_longer_expiry_increases_price() {
  OptionParameters parameters{100.0, 100.0, 0.2, 0.05, 1.0};
  constexpr int simulations{1000000};

  constexpr double short_expiry{1.0};
  constexpr double long_expiry{2.0};

  parameters.set_expiry(short_expiry);
  double short_expiry_price{monte_carlo(parameters, simulations)};

  parameters.set_expiry(long_expiry);
  double long_expiry_price{monte_carlo(parameters, simulations)};

  assert(long_expiry_price > short_expiry_price);

  std::cout << "longer expiry test passed.\n";
}

void test_higher_spot_increases_price() {
  OptionParameters parameters{100.0, 100.0, 0.2, 0.05, 1.0};
  constexpr int simulations{1'000'000};

  constexpr double low_spot{80.0};
  constexpr double high_spot{120.0};

  parameters.set_spot(low_spot);
  double low_spot_price{monte_carlo(parameters, simulations)};

  parameters.set_spot(high_spot);
  double high_spot_price{monte_carlo(parameters, simulations)};

  assert(high_spot_price > low_spot_price);

  std::cout << "higher spot test passed.\n";
}

void test_higher_strike_decreases_price() {
  OptionParameters parameters{100.0, 100.0, 0.2, 0.05, 1.0};
  constexpr int simulations{1000000};

  constexpr double low_strike{80.0};
  constexpr double high_strike{120.0};

  parameters.set_strike(low_strike);
  double low_strike_price{monte_carlo(parameters, simulations)};

  parameters.set_striek(high_strike);
  double high_strike_price{monte_carlo(parameters, simulations)};

  assert(low_strike_price > high_strike_price);

  std::cout << "higher strike test passed.\n";
}

void test_zero_volatility() {
  OptionParameters parameters{100.0, 100.0, 0.0, 0.05, 1.0};
  constexpr int simulations{10'000};

  double monte_carlo_option_price{monte_carlo(parameters, simulations)};

  double black_scholes_option_price{black_scholes(parameters)};

  constexpr double tolerance{1e-10};

  assert(std::abs(monte_carlo_option_price - black_scholes_option_price) <
         tolerance);

  std::cout << "zero volatility test passed.\n";
}

int main() {
  test_mc_vs_bs();
  test_higher_volatility_increases_price();
  test_longer_expiry_increases_price();
  test_higher_spot_increases_price();
  test_higher_strike_decreases_price();
  test_zero_volatility();

  std::cout << "all Monte Carlo tests passed.\n";

  return 0;
}
