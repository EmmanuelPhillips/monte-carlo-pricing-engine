#include "gui.hpp"
#include "black_scholes.hpp"
#include "monte_carlo.hpp"
#include <QDoubleValidator>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) { setupUi(); }

void MainWindow::setupUi() {
  auto *centralWidget = new QWidget(this);
  auto *layout = new QFormLayout(centralWidget);

  // Setup input fields with double/int validators
  spotInput = new QLineEdit("100.0", this);
  strikeInput = new QLineEdit("100.0", this);
  volatilityInput = new QLineEdit("0.2", this);
  rateInput = new QLineEdit("0.05", this);
  expiryInput = new QLineEdit("1.0", this);
  numSimulationsInput = new QLineEdit("100000", this);

  layout->addRow("Spot Price:", spotInput);
  layout->addRow("Strike Price:", strikeInput);
  layout->addRow("Volatility:", volatilityInput);
  layout->addRow("Risk-Free Rate:", rateInput);
  layout->addRow("expiry (Years):", expiryInput);
  layout->addRow("Simulations:", numSimulationsInput);

  calculateButton = new QPushButton("Run Simulation", this);
  resultLabel = new QLabel("Option Price: -", this);

  layout->addRow(calculateButton);
  layout->addRow(resultLabel);

  setCentralWidget(centralWidget);
  setWindowTitle("Monte Carlo Option Pricing Engine");

  // Connect button click to simulation runner
  connect(calculateButton, &QPushButton::clicked, this,
          &MainWindow::runMonteCarloSimulation);
}

void MainWindow::runMonteCarloSimulation() {
  bool okSpot{}, okStrike{}, okVol{}, okRate{}, okMat{}, okSims{};

  double spot{spotInput->text().toDouble(&okSpot)};
  double strike{strikeInput->text().toDouble(&okStrike)};
  double vol{volatilityInput->text().toDouble(&okVol)};
  double rate{rateInput->text().toDouble(&okRate)};
  double expiry{expiryInput->text().toDouble(&okMat)};
  int sims{numSimulationsInput->text().toInt(&okSims)};

  if (!(okSpot && okStrike && okVol && okRate && okMat && okSims)) {
    resultLabel->setText("Invalid input. Please enter numbers only.");
    return;
  }

  if (spot <= 0.0 || strike <= 0.0 || vol <= 0.0 || expiry <= 0.0 ||
      sims <= 0) {
    resultLabel->setText("All values except rate must be greater than 0.");
    return;
  }

  OptionParameters parameters{spot, strike, vol, rate, expiry};

  MonteCarloPricer mcPricer{parameters, sims};
  double mcResult{mcPricer.price()};

  BlackScholesPricer bsPricer{parameters};
  double bsResult{bsPricer.price()};

  resultLabel->setText(
      QString("Monte Carlo: %1\nBlack-Scholes: %2\nDifference: %3")
          .arg(mcResult)
          .arg(bsResult)
          .arg(std::abs(mcResult - bsResult)));
}
