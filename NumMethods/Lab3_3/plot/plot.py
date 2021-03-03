import matplotlib.pyplot as plt
import numpy as np

f = open("coeff")

a1 = []
a2 = []

x = []
y = []

n = int(f.readline())

for i in range(n):
    x.append(float(f.readline()))
for i in range(n):
    y.append(float(f.readline()))

for i in range(2):
    a1.append(float(f.readline()))

for i in range(3):
    a2.append(float(f.readline()))

def F(coefs, x):
    return sum([x ** i * c for i, c in enumerate(coefs)])

F1 = [F(a1, i) for i in x]
F2 = [F(a2, i) for i in x]

plt.scatter(x, y, color="r")

plt.plot(x, F1, color='k')
plt.plot(x, F2, color='k')
plt.show()