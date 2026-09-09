#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>

int main() {
  double spot{100.0};
  double strike{100.0};
  double volatility{0.20};
  double rate{0.05};
  double expiry{1.0};
  int simulations{10000};

  std::random_device rd;
  std::mt19937 gen{rd()};
  std::normal_distribution<double> dist(0.0, 1.0);

  double total_payoff{0.0};

  double drift{(rate - 0.5 * volatility * volatility) * expiry};
  double sqrt_expiry{std::sqrt(expiry)};

  for (int i{0}; i < simulations; ++i) {
    double standard_normal{dist(gen)};

    double diffusion{volatility * sqrt_expiry * standard_normal};

    double terminal_price{spot * std::exp(drift + diffusion)};

    double payoff{std::max(terminal_price - strike, 0.0)};

    total_payoff += payoff;
  }

  double average_payoff{total_payoff / simulations};
  double option_price{std::exp(-rate * expiry) * average_payoff};

  std::cout << "Monte Carlo European Call Price: " << option_price << '\n';

  return 0;
}
