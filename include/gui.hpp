#pragma once

#include "option_parameters.hpp"
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow {
  Q_OBJECT

private slots:
  void runMonteCarloSimulation();

private:
  void setupUi();
  QLineEdit *spotInput;
  QLineEdit *strikeInput;
  QLineEdit *volatilityInput;
  QLineEdit *rateInput;
  QLineEdit *expiryInput;
  QLineEdit *numSimulationsInput;

  QPushButton *calculateButton;
  QLabel *resultLabel;

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override = default;
};
