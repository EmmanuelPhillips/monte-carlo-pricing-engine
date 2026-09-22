#include "monte_carlo.hpp"
#include <algorithm>
#include <cmath>
#include <random>

MonteCarloPricer::MonteCarloPricer(const OptionParameters &parameters,
                                   int simulations)
    : m_parameters{parameters}, m_simulations{simulations} {};

double MonteCarloPricer::price() {
  std::random_device rd;
  std::mt19937 gen{rd()};
  std::normal_distribution<double> dist(0.0, 1.0);

  double spot{m_parameters.get_spot()};
  double strike{m_parameters.get_strike()};
  double volatility{m_parameters.get_volatility()};
  double rate{m_parameters.get_rate()};
  double expiry{m_parameters.get_expiry()};

  double total_payoff{0.0};

  double drift{(rate - (0.5 * volatility * volatility)) * expiry};
  double sqrt_expiry{std::sqrt(expiry)};

  for (int i{0}; i < m_simulations; ++i) {
    double Z{dist(gen)};

    double diffusion{volatility * sqrt_expiry * Z};
    double terminal_price{spot * std::exp(drift + diffusion)};
    double payoff{std::max(terminal_price - strike, 0.0)};

    total_payoff += payoff;
  }
  double average_payoff{total_payoff / m_simulations};
  double option_price{std::exp(-rate * expiry) * average_payoff};
  return option_price;
}
