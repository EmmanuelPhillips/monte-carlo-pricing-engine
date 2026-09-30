#include "black_scholes.hpp"
#include "monte_carlo.hpp"
#include "option_parameters.hpp"
#include <fstream>
#include <iostream>
#include <random>

int main() {
  std::random_device rd;
  std::mt19937 gen{rd()};
  std::uniform_real_distribution<double> spot_dist(80.0, 120.0);
  std::uniform_real_distribution<double> strike_dist(80.0, 120.0);
  std::uniform_real_distribution<double> volatility_dist(0.1, 0.5);
  std::uniform_real_distribution<double> rate_dist(0.01, 0.05);
  std::uniform_real_distribution<double> expiry_dist(0.1, 2.0);

  std::ofstream file("data/monte_carlo_convergence.csv");
  if (!file) {
    std::cerr << "error: unable to open file.\n";
    return 1;
  }
  file << "num_sims,spot,strike,volatility,rate,expiry,price,bs_price\n";
  for (int i{0}; i < 500; ++i) {
    OptionParameters parameters{spot_dist(gen), strike_dist(gen),
                                volatility_dist(gen), rate_dist(gen),
                                expiry_dist(gen)};
    for (int num_sims{1000}; num_sims <= 10000000; num_sims *= 10) {
      MonteCarloPricer mc_pricer{parameters, num_sims};
      BlackScholesPricer bs_pricer{parameters};

      double spot{parameters.get_spot()};
      double strike{parameters.get_strike()};
      double volatility{parameters.get_volatility()};
      double rate{parameters.get_rate()};
      double expiry{parameters.get_expiry()};
      double price{mc_pricer.price()};
      double bs_price{bs_pricer.price()};

      file << num_sims << ',' << spot << ',' << strike << ',' << volatility
           << ',' << rate << ',' << expiry << ',' << price << ',' << bs_price
           << '\n';
    }
  }

  file.close();
  return 0;
}
