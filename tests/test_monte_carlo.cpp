#include "black_scholes.hpp"
#include "monte_carlo.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

void test_mc_vs_bs() {
  constexpr double spot{100.0};
  constexpr double strike{100.0};
  constexpr double volatility{0.20};
  constexpr double rate{0.05};
  constexpr double expiry{1.0};
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
  constexpr double spot{100.0};
  constexpr double strike{100.0};
  constexpr double rate{0.05};
  constexpr double expiry{1.0};
  constexpr int simulations{1'000'000};

  constexpr double low_volatility{0.10};
  constexpr double high_volatility{0.30};

  double low_volatility_price{
      monte_carlo(spot, strike, low_volatility, rate, expiry, simulations)};

  double high_volatility_price{
      monte_carlo(spot, strike, high_volatility, rate, expiry, simulations)};

  assert(high_volatility_price > low_volatility_price);

  std::cout << "higher volatility test passed.\n";
}

void test_longer_expiry_increases_price() {
  constexpr double spot{100.0};
  constexpr double strike{100.0};
  constexpr double volatility{0.20};
  constexpr double rate{0.05};
  constexpr int simulations{1'000'000};

  constexpr double short_expiry{1.0};
  constexpr double long_expiry{2.0};

  double short_expiry_price{
      monte_carlo(spot, strike, volatility, rate, short_expiry, simulations)};

  double long_expiry_price{
      monte_carlo(spot, strike, volatility, rate, long_expiry, simulations)};

  assert(long_expiry_price > short_expiry_price);

  std::cout << "longer expiry test passed.\n";
}

void test_higher_spot_increases_price() {
  constexpr double low_spot{80.0};
  constexpr double high_spot{120.0};
  constexpr double strike{100.0};
  constexpr double volatility{0.20};
  constexpr double rate{0.05};
  constexpr double expiry{1.0};
  constexpr int simulations{1'000'000};

  double low_spot_price{
      monte_carlo(low_spot, strike, volatility, rate, expiry, simulations)};

  double high_spot_price{
      monte_carlo(high_spot, strike, volatility, rate, expiry, simulations)};

  assert(high_spot_price > low_spot_price);

  std::cout << "higher spot test passed.\n";
}

void test_higher_strike_decreases_price() {
  constexpr double spot{100.0};
  constexpr double low_strike{80.0};
  constexpr double high_strike{120.0};
  constexpr double volatility{0.20};
  constexpr double rate{0.05};
  constexpr double expiry{1.0};
  constexpr int simulations{1'000'000};

  double low_strike_price{
      monte_carlo(spot, low_strike, volatility, rate, expiry, simulations)};

  double high_strike_price{
      monte_carlo(spot, high_strike, volatility, rate, expiry, simulations)};

  assert(low_strike_price > high_strike_price);

  std::cout << "higher strike test passed.\n";
}

void test_zero_volatility() {
  constexpr double spot{100.0};
  constexpr double strike{100.0};
  constexpr double volatility{0.0};
  constexpr double rate{0.05};
  constexpr double expiry{1.0};
  constexpr int simulations{10'000};

  double monte_carlo_option_price{
      monte_carlo(spot, strike, volatility, rate, expiry, simulations)};

  double black_scholes_option_price{
      black_scholes(spot, strike, volatility, rate, expiry)};

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
