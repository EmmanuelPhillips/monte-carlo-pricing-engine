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

### Parameter effects on price

- Spot has the strongest association with price (correlation 0.649), followed by
  strike (-0.552), volatility (0.276) and rate (0.104)
- Spot: clear upward trend, higher spot generally increases the price
- Strike: clear downward trend, higher strike generally decreases the price
- Volatility: generally increases the price, but weakly (correlation 0.276). The
  scatter is wide and noisy because other parameters dominate
- Rate: very weak relationship, the scatter is close to a flat cloud

### Monte Carlo vs Black-Scholes error

- Typical MC-BS error is small: average absolute error is about 0.017 and the
  largest is about 0.157, against a mean price of about 14.7
- Mean price is almost identical between methods (14.698016 for MC vs 14.698104
  for BS)
- The error does not depend strongly on any single parameter
- Error rises mildly with spot and volatility (red trend lines slope upward),
  falls slightly with strike, and is flat across rate
- Volatility shows the clearest dependence, with the largest errors clustering
  at high volatility

### Convergence with num_sims

- Mean absolute error falls steadily as num_sims increases: 0.593 -> 0.201 ->
  0.062 -> 0.0195 -> 0.0057
- This is roughly a 3x drop per 10x more simulations, consistent with 1/sqrt(N)
  scaling
- Std of the MC price barely changes (10.695 -> 10.653) because it reflects the
  spread of prices across the different option parameters, not the MC noise
- Improvement becomes relatively small around 10^6 simulations, where error is
  already about 0.02 and the absolute gain going to 10^7 is only about 0.014 for
  10x the compute
- The boxplot shows the error distribution tightening as simulations increase:
  the box, whiskers, median and outliers all shrink
- At 10^3 the errors reach above 3.4, while at 10^7 the distribution is nearly
  flat near zero

## Conclusions

- The stochastic Monte Carlo engine agrees closely with the Black-Scholes
  deterministic formula. With an average absolute error of \~0.017, against a
  mean price of about 14.7. It appears to be implemented correctly.
- Spot and strike are the main drivers of price, while volatility and rate
  matter less (across my samples).
- Error is driver mainly by the number of simulations ran in the Monte Carlo
  engine.
- Convergence follows the expected $\\frac{1}{\\sqrt{N}}$ pattern, so increasing
  simulations by 10x gives around a 3x error reduction.
- In practice, $10^{6}$ simulations is a sensible balance between accuracy and
  compute.
