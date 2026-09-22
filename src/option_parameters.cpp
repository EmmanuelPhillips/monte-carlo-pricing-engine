#include "option_parameters.hpp"

OptionParameters::OptionParameters(double spot, double strike,
                                   double volatility, double rate,
                                   double expiry)
    : m_spot{spot}, m_strike{strike}, m_volatility{volatility}, m_rate{rate},
      m_expiry{expiry} {}

double OptionParameters::get_spot() const { return m_spot; }
double OptionParameters::get_strike() const { return m_strike; }
double OptionParameters::get_volatility() const { return m_volatility; }
double OptionParameters::get_rate() const { return m_rate; }
double OptionParameters::get_expiry() const { return m_expiry; }

void OptionParameters::set_volatility(double volatility) {
  m_volatility = volatility;
}
void OptionParameters::set_expiry(double expiry) { m_expiry = expiry; }
void OptionParameters::set_spot(double spot) { m_spot = spot; }
void OptionParameters::set_strike(double strike) { m_strike = strike; }
