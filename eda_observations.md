# Monte Carlo Pricing Engine - EDA Observations

## Intro

- Having recently learnt how Geometric Brownian Motion can be used to simulate
  stock price movements and estimate the fair value of an option through Monte
  Carlo simulation, I wanted to investigate the behaviour of my pricing engine
  in more detail.
- I also implemented the Black-Scholes model, which provides an analytical
  option price without requiring simulation, giving me a benchmark for
  comparison.
- This led me to use Python, primarily pandas and matplotlib, to explore the
  differences between the two approaches, investigate how different parameters
  affect the resulting price, and examine how the accuracy and variability of
  Monte Carlo option pricing changes as the number of simulations increases.

## Observations

### Parameter effects on price

- Spot has the strongest association with price (correlation $0.649$), followed
  by strike ($-0.552$), volatility ($0.276$) and rate ($0.104$).
- Spot: clear upward trend, with higher spot generally increasing the price.
- Strike: clear downward trend, with higher strike generally decreasing the
  price.
- Volatility: generally increases the price, but shows a weaker linear
  correlation ($0.276$). The scatter is relatively wide and noisy because the
  other parameters also vary between observations.
- Rate: very weak linear relationship, with the scatter appearing close to a
  flat cloud.
- These correlations describe the relationships observed within my generated
  dataset and do not necessarily represent the overall importance of each
  parameter in option pricing.

### Monte Carlo vs Black-Scholes error

- Typical MC-BS error is small: average absolute error is about $0.017$ and the
  largest is about $0.157$, against a mean price of about $14.7$.
- Mean price is almost identical between methods ($14.698016$ for MC vs
  $14.698104$ for BS).
- The error does not appear to depend strongly on any single parameter.
- Error rises mildly with spot and volatility (red trend lines slope upward),
  falls slightly with strike, and is relatively flat across rate.
- Volatility shows the clearest apparent dependence, with the largest errors
  clustering at higher volatility.

### Convergence with num_sims

- Mean absolute error falls steadily as num_sims increases: $0.593$ -> $0.201$
  -> $0.062$ -> $0.0195$ -> $0.0057$.
- This is roughly a $3\\times$ reduction per $10\\times$ increase in
  simulations, which is consistent with the expected $\\frac{1}{\\sqrt{N}}$
  relationship for Monte Carlo error.
- The standard deviation of the MC price barely changes ($10.695$ -> $10.653$)
  because it reflects the spread of prices across the different option
  parameters, rather than the Monte Carlo sampling noise.
- Improvement becomes relatively small around $10^6$ simulations, where the
  error is already about $0.02$ and the absolute gain from increasing to $10^7$
  simulations is only about $0.014 for $10\\times$ the computational cost.
- The boxplot shows the error distribution tightening as the number of
  simulations increases: the box, whiskers, median and outliers all shrink.
- At $10^3$ simulations, errors reach above $3.4$, while at $10^7$ the
  distribution is concentrated very close to zero.

## Conclusions

- The Monte Carlo engine agrees closely with the Black-Scholes analytical model,
  with an average absolute error of approximately $0.017$ against a mean price
  of about $14.7$. The results provide evidence that the Monte Carlo
  implementation is behaving as expected.
- Within the generated dataset, spot and strike showed the strongest linear
  associations with price, while volatility and rate showed weaker linear
  correlations.
- Monte Carlo error is primarily affected by the number of simulations.
- Convergence follows the expected $\\frac{1}{\\sqrt{N}}$ pattern, meaning that
  increasing the number of simulations by $10\\times$ produces approximately a
  $3\\times$ reduction in error.
- For this implementation and dataset, $10^6$ simulations appears to provide a
  useful balance between pricing accuracy and computational cost.
