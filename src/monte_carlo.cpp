#include "monte_carlo.hpp"
#include <algorithm>
#include <cmath>
#include <random>

double monte_carlo(double spot, double strike, double volatility, double rate,
                   double expiry, int simulations) {
  std::random_device rd;
  std::mt19937 gen{rd()};
  std::normal_distribution<double> dist(0.0, 1.0);

  double total_payoff{0.0};

  double drift{(rate - (0.5 * volatility * volatility)) * expiry};
  double sqrt_expiry{std::sqrt(expiry)};

  for (int i{0}; i < simulations; ++i) {
    double Z{dist(gen)};

    double diffusion{volatility * sqrt_expiry * Z};
    double terminal_price{spot * std::exp(drift + diffusion)};
    double payoff{std::max(terminal_price - strike, 0.0)};

    total_payoff += payoff;
  }
  double average_payoff{total_payoff / simulations};
  double option_price{std::exp(-rate * expiry) * average_payoff};
  return option_price;
}
