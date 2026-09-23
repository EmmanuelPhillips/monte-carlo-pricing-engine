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

  MonteCarloPricer pricer{parameters, simulations};
  double monte_carlo_option_price{pricer.price()};

  assert(std::abs(monte_carlo_option_price - black_scholes_option_price) <
         tolerance);

  std::cout << "MC vs BS test passed.\n";
}

void test_higher_volatility_increases_price() {
  OptionParameters parameters{100.0, 100.0, 0.2, 0.05, 1.0};

  constexpr double low_volatility{0.1};
  constexpr double high_volatility{0.3};
  constexpr int simulations{1'000'000};

  parameters.set_volatility(low_volatility);
  MonteCarloPricer low_volatility_pricer{parameters, simulations};
  double low_volatility_price{low_volatility_pricer.price()};

  parameters.set_volatility(high_volatility);
  MonteCarloPricer high_volatility_pricer{parameters, simulations};
  double high_volatility_price{high_volatility_pricer.price()};

  assert(high_volatility_price > low_volatility_price);

  std::cout << "higher volatility test passed.\n";
}

void test_longer_expiry_increases_price() {
  OptionParameters parameters{100.0, 100.0, 0.2, 0.05, 1.0};
  constexpr int simulations{1'000'000};

  constexpr double short_expiry{1.0};
  constexpr double long_expiry{2.0};

  parameters.set_expiry(short_expiry);
  MonteCarloPricer short_expiry_pricer{parameters, simulations};
  double short_expiry_price{short_expiry_pricer.price()};

  parameters.set_expiry(long_expiry);
  MonteCarloPricer long_expiry_pricer{parameters, simulations};
  double long_expiry_price{long_expiry_pricer.price()};

  assert(long_expiry_price > short_expiry_price);

  std::cout << "longer expiry test passed.\n";
}

void test_higher_spot_increases_price() {
  OptionParameters parameters{100.0, 100.0, 0.2, 0.05, 1.0};
  constexpr int simulations{1'000'000};

  constexpr double low_spot{80.0};
  constexpr double high_spot{120.0};

  parameters.set_spot(low_spot);
  MonteCarloPricer low_spot_pricer{parameters, simulations};
  double low_spot_price{low_spot_pricer.price()};

  parameters.set_spot(high_spot);
  MonteCarloPricer high_spot_pricer{parameters, simulations};
  double high_spot_price{high_spot_pricer.price()};

  assert(high_spot_price > low_spot_price);

  std::cout << "higher spot test passed.\n";
}

void test_higher_strike_decreases_price() {
  OptionParameters parameters{100.0, 100.0, 0.2, 0.05, 1.0};
  constexpr int simulations{1'000'000};

  constexpr double low_strike{80.0};
  constexpr double high_strike{120.0};

  parameters.set_strike(low_strike);
  MonteCarloPricer low_strike_pricer{parameters, simulations};
  double low_strike_price{low_strike_pricer.price()};

  parameters.set_strike(high_strike);
  MonteCarloPricer high_strike_pricer{parameters, simulations};
  double high_strike_price{high_strike_pricer.price()};

  assert(low_strike_price > high_strike_price);

  std::cout << "higher strike test passed.\n";
}

void test_zero_volatility() {
  OptionParameters parameters{100.0, 100.0, 0.0, 0.05, 1.0};
  constexpr int simulations{10'000};

  MonteCarloPricer mc_pricer{parameters, simulations};
  double monte_carlo_option_price{mc_pricer.price()};

  BlackScholesPricer bs_pricer{parameters};
  double black_scholes_option_price{bs_pricer.price()};

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
