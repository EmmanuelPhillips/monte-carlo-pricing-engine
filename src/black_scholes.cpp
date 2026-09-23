#include "black_scholes.hpp"
#include <cmath>

namespace {
double N(double x) { return 0.5 * std::erfc(-x / std::sqrt(2.0)); }
} // namespace

BlackScholesPricer::BlackScholesPricer(const OptionParameters &parameters)
    : m_parameters{parameters} {}

double BlackScholesPricer::price() {
  double spot{m_parameters.get_spot()};
  double strike{m_parameters.get_strike()};
  double volatility{m_parameters.get_volatility()};
  double rate{m_parameters.get_rate()};
  double expiry{m_parameters.get_expiry()};

  double d_1{(std::log(spot / strike) +
              (rate + (0.5 * volatility * volatility)) * expiry) /
             (volatility * std::sqrt(expiry))};

  double d_2{d_1 - (volatility * std::sqrt(expiry))};

  double option_price{(spot * N(d_1)) -
                      (strike * std::exp(-rate * expiry) * N(d_2))};
  return option_price;
}
