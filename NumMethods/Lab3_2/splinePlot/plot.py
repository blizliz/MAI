import matplotlib.pyplot as plt
import numpy as np

f = open("spline")

n = int(f.readline())
x = []
y = []

for i in range(n):
    x.append(float(f.readline()))

for i in range(n):
    y.append(float(f.readline()))

plt.scatter(x, y, color="r")

m = int(f.readline())

a = []
b = []
c = []
d = []

for i in range(m):
    a.append(float(f.readline()))
for i in range(m):
    b.append(float(f.readline()))
for i in range(m):
    c.append(float(f.readline()))
for i in range(m):
    d.append(float(f.readline()))

def f(a, b, c, d, x):
    return a + b * x + c * (x ** 2) + d * (x ** 3)

x1 = np.linspace(x[0], x[1], 10, endpoint=True)
y1 = [f(a[1], b[1], c[1], d[1], i - x[0]) for i in x1]
x2 = np.linspace(x[1], x[2], 10, endpoint=True)
y2 = [f(a[2], b[2], c[2], d[2], i - x[1]) for i in x2]
x3 = np.linspace(x[2], x[3], 10, endpoint=True)
y3 = [f(a[3], b[3], c[3], d[3], i - x[2]) for i in x3]
x4 = np.linspace(x[3], x[4], 10, endpoint=True)
y4 = [f(a[4], b[4], c[4], d[4], i - x[3]) for i in x4]

plt.plot(x1, y1, color='b')
plt.plot(x2, y2, color='b')
plt.plot(x3, y3, color='b')
plt.plot(x4, y4, color='b')

plt.show()