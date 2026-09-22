#pragma once
#include "option_parameters.hpp"

class BlackScholesPricer {
private:
  OptionParameters m_parameters;

public:
  BlackScholesPricer(const OptionParameters &parameters);
  double price();
};
