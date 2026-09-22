#include "black_scholes.hpp"
#include <cmath>

namespace {
double N(double x) { return 0.5 * std::erfc(-x / std::sqrt(2.0)); }
} // namespace

double black_scholes(const OptionParameters &parameters) {
  double spot{parameters.get_spot()};
  double strike{parameters.get_strike()};
  double volatility{parameters.get_volatility()};
  double rate{parameters.get_rate()};
  double expiry{parameters.get_expiry()};

  double d_1{(std::log(spot / strike) +
              (rate + (0.5 * volatility * volatility)) * expiry) /
             (volatility * std::sqrt(expiry))};

  double d_2{d_1 - (volatility * std::sqrt(expiry))};

  double option_price{(spot * N(d_1)) -
                      (strike * std::exp(-rate * expiry) * N(d_2))};
  return option_price;
}
