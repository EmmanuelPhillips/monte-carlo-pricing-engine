#include "black_scholes.hpp"
#include "monte_carlo.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string_view>

void ignoreLine() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool clearFailedExtraction() {
  if (!std::cin) {
    if (std::cin.eof()) {
      std::exit(0);
    }

    std::cin.clear();
    ignoreLine();
    return true;
  }

  return false;
}

double get_double_value(std::string_view word) {
  while (true) {
    std::cout << word << ": ";

    double x{};
    std::cin >> x;

    if (clearFailedExtraction()) {
      std::cout << "Invalid input. Please enter a number.\n";
      continue;
    }

    ignoreLine();
    return x;
  }
}

int get_int_value(std::string_view word) {
  while (true) {
    std::cout << word << ": ";

    int x{};
    std::cin >> x;

    if (clearFailedExtraction()) {
      std::cout << "Invalid input. Please enter a whole number.\n";
      continue;
    }

    ignoreLine();
    return x;
  }
}

double get_positive_double(std::string_view word) {
  while (true) {
    double value{get_double_value(word)};

    if (value > 0.0) {
      return value;
    }

    std::cout << "Value must be greater than 0.\n";
  }
}

int get_positive_int(std::string_view word) {
  while (true) {
    int value{get_int_value(word)};

    if (value > 0) {
      return value;
    }

    std::cout << "Value must be greater than 0.\n";
  }
}

void get_option_inputs(double &spot, double &strike, double &volatility,
                       double &rate, double &expiry) {
  std::cout << "\nPLEASE ENTER VALUES:\n";

  spot = get_positive_double("Spot");
  strike = get_positive_double("Strike");
  volatility = get_positive_double("Volatility");
  rate = get_double_value("Rate");
  expiry = get_positive_double("Expiry");
}

int main() {
  std::cout << "===============================\n";
  std::cout << "   MONTE CARLO OPTION PRICER   \n";
  std::cout << "===============================\n";

  while (true) {
    std::cout << "\nCHOOSE AN OPTION:\n";
    std::cout << "1. Monte Carlo\n";
    std::cout << "2. Black Scholes\n";
    std::cout << "3. Compare both\n";
    std::cout << "4. Exit\n";

    int option{get_int_value("> ")};

    switch (option) {
    case 1: {
      double spot{};
      double strike{};
      double volatility{};
      double rate{};
      double expiry{};

      get_option_inputs(spot, strike, volatility, rate, expiry);

      int simulations{get_positive_int("Number of simulations")};

      double result{
          monte_carlo(spot, strike, volatility, rate, expiry, simulations)};

      std::cout << "\nMonte Carlo price: " << result << '\n';

      break;
    }

    case 2: {
      double spot{};
      double strike{};
      double volatility{};
      double rate{};
      double expiry{};

      get_option_inputs(spot, strike, volatility, rate, expiry);

      double result{black_scholes(spot, strike, volatility, rate, expiry)};

      std::cout << "\nBlack-Scholes price: " << result << '\n';

      break;
    }

    case 3: {
      double spot{};
      double strike{};
      double volatility{};
      double rate{};
      double expiry{};

      get_option_inputs(spot, strike, volatility, rate, expiry);

      int simulations{get_positive_int("Number of simulations")};

      double mc_result{
          monte_carlo(spot, strike, volatility, rate, expiry, simulations)};

      double bs_result{black_scholes(spot, strike, volatility, rate, expiry)};

      double difference{std::abs(mc_result - bs_result)};

      std::cout << "\nMonte Carlo:   " << mc_result << '\n';
      std::cout << "Black-Scholes: " << bs_result << '\n';
      std::cout << "Difference:    " << difference << '\n';

      break;
    }

    case 4:
      std::cout << "Exiting...\n";
      return 0;

    default:
      std::cout << "Invalid option. Please choose 1-4.\n";
      break;
    }
  }
}
