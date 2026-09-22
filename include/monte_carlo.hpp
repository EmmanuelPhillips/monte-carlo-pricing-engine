#pragma once
#include "option_parameters.hpp"

class MonteCarloPricer {
private:
  OptionParameters m_parameters;
  int m_simulations;

public:
  double price();
};
