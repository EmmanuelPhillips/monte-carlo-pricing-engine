# Monte Carlo Pricing Engine

A C++20 option pricing engine implementing Monte Carlo simulation and the
Black-Scholes analytical model, with unit testing, multithreading, benchmarking,
and Python-based exploratory data analysis.

## Project Overview

The project began as an implementation of Monte Carlo option pricing using
Geometric Brownian Motion. I expanded this to compare the stochastic Monte Carlo
approach against the Black-Scholes analytical solution.

This was primarily a learning exercise to develop my understanding of
quantitative finance while improving my C++ software engineering skills.

The project includes:

- Monte Carlo European call option pricing
- Black-Scholes analytical pricing
- Object-oriented C++ design
- Multithreaded Monte Carlo simulation
- Unit tests
- Performance benchmarks
- CSV data generation
- Python EDA using pandas and matplotlib
- A basic Qt GUI

## Models

### Monte Carlo

The Monte Carlo pricer simulates terminal stock prices using Geometric Brownian
Motion and calculates the discounted average payoff across a specified number of
simulations.

### Black-Scholes

The Black-Scholes implementation provides an analytical European call option
price and is used as a benchmark for evaluating the Monte Carlo implementation.

## Project Structure

```text
.
├── app/
├── benchmarks/
├── data/
├── experiments/
├── include/
├── python/
├── src/
├── tests/
├── CMakeLists.txt
├── README.md
└── eda_observations.md
```

## Results

The Monte Carlo implementation was compared against Black-Scholes across a range
of option parameters.

The Python EDA investigated:

- The effect of option parameters on price
- Monte Carlo vs Black-Scholes pricing error
- Monte Carlo convergence as simulation count increases
- Error distributions at different simulation counts

The observed convergence was approximately consistent with the expected `1 / √N`
relationship.

## What I Learnt

- Monte Carlo option pricing using Geometric Brownian Motion
- Implementing the Black-Scholes model
- Designing C++ classes around numerical models
- Writing unit tests
- C++ concurrency fundamentals
- Benchmarking with `std::chrono`
- Working with CMake and multi-target C++ projects
- File I/O in C++
- Using pandas and matplotlib for EDA
- Integrating a C++ backend with a Qt GUI

## Possible Future Improvements

- Reproducible random-number generation
- Variance-reduction techniques
- Additional option types
- More detailed performance analysis
- Further EDA
- Improved GUI
