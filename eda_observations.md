# Monte Carlo Pricing Engine - EDA Observations

## Intro

- Having recently learnt how Geometric Brownian Motion can be used to simulate
  stock price movements and estimate the fair value of an option through Monte
  Carlo simulation, I wanted to investigate the behaviours of my pricing engine
  in more detail.
- I also implemented the Black-Scholes model, which provides an analytical
  option price without requiring simulation, giving me a benchmark to compare.
- This led me to use Python (pandas and matplotlib libraries mainly), to explore
  the differences between the two approaches, investigate how different
  parameters affect the resulting price, and examine how the accuracy and
  variability of Monte Carlo option pricing changes as the number of simulations
  increases.

## Observations
