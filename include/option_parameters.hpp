#pragma once

class OptionParameters {
private:
  double m_spot;
  double m_strike;
  double m_volatility;
  double m_rate;
  double m_expiry;

public:
  OptionParameters(double spot, double strike, double volatility, double rate,
                   double expiry);

  double get_spot() const;
  double get_strike() const;
  double get_volatility() const;
  double get_rate() const;
  double get_expiry() const;

  void set_volatility(double volatility);
  void set_expiry(double expiry);
};
