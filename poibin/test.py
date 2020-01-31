from poibin import PoiBin
import numpy as np

print(1j)

probs = np.array([0.1, 0.2, 0.3, 0.4, 0.5])
x = PoiBin(probs)
x.cdf(2)
