#pragma once

double monte_carlo_multithreaded(double spot, double strike, double volatility,
                                 double rate, double expiry, int simulations);
