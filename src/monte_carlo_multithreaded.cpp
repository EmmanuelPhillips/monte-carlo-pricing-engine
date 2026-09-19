#include "monte_carlo.hpp"
#include <algorithm>
#include <cmath>
#include <random>
#include <thread>
#include <vector>

namespace {
double calculate_partial_payoff(double spot, double strike, double volatility,
                                double drift, double sqrt_expiry,
                                int num_sims) {
  std::random_device rd;
  std::mt19937 gen{rd()};
  std::normal_distribution<double> dist(0.0, 1.0);

  double partial_payoff{0.0};

  for (int i{0}; i < num_sims; ++i) {
    double Z{dist(gen)};

    double diffusion{volatility * sqrt_expiry * Z};
    double terminal_price{spot * std::exp(drift + diffusion)};
    double payoff{std::max(terminal_price - strike, 0.0)};

    partial_payoff += payoff;
  }
  return partial_payoff;
}
} // namespace

double monte_carlo_multithreaded(double spot, double strike, double volatility,
                                 double rate, double expiry, int simulations) {
  double drift{(rate - (0.5 * volatility * volatility)) * expiry};
  double sqrt_expiry{std::sqrt(expiry)};

  const int num_threads{4};
  const int chunk{simulations / num_threads};

  std::vector<std::thread> threads;
  std::vector<double> partial_payoffs(num_threads, 0.0);

  for (int i{0}; i < num_threads; ++i) {
    int num_sims{(i == num_threads - 1)
                     ? simulations - chunk * (num_threads - 1)
                     : chunk};
    threads.emplace_back([&, i, num_sims] {
      partial_payoffs[i] = calculate_partial_payoff(
          spot, strike, volatility, drift, sqrt_expiry, num_sims);
    });
  }

  for (auto &thread : threads) {
    thread.join();
  }

  double total_payoff{0.0};
  for (auto partial_payoff : partial_payoffs) {
    total_payoff += partial_payoff;
  }
  double average_payoff{total_payoff / simulations};
  double option_price{std::exp(-rate * expiry) * average_payoff};

  return option_price;
}
