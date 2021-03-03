import matplotlib.pyplot as plt
import numpy as np
from math import exp
from math import sin
from math import cos

def F(x):
    return x * sin(x) + cos(x)

f = open("euler_method1")

x1 = []
y1 = []
n = int(f.readline())
for i in range(n):
    x1.append(float(f.readline()))
for i in range(n):
    y1.append(float(f.readline()))

f.close()


exact_y = [F(i) for i in x1]

plt.subplot(211)
plt.plot(x1, exact_y, color='b', label='Exact solution')
plt.scatter(x1, y1, color="r", label='Euler method')

plt.title('h = 0.1')

f = open("rk_method1")

x2 = []
y2 = []
n = int(f.readline())
for i in range(n):
    x2.append(float(f.readline()))
for i in range(n):
    y2.append(float(f.readline()))

f.close()


plt.scatter(x2, y2, color='g', label='Runge-Kutta method')

f = open("adams_method1")

x3 = []
y3 = []
n = int(f.readline())
for i in range(n):
    x3.append(float(f.readline()))
for i in range(n):
    y3.append(float(f.readline()))

f.close()

plt.scatter(x3, y3, color="k", label='Adams method')

plt.legend(loc='upper left')


plt.subplot(212)
# plt.scatter(x2, y2, color="r")
# plt.plot(x2, exact_y, color='b')
# plt.title('Adams method')

f = open("euler_method2")

x1 = []
y1 = []
n = int(f.readline())
for i in range(n):
    x1.append(float(f.readline()))
for i in range(n):
    y1.append(float(f.readline()))


exact_y = [F(i) for i in x1]
plt.plot(x1, exact_y, color='b', label='Exact solution')
plt.scatter(x1, y1, color="r", label='Euler method')

plt.title('h = 0.2')

f = open("rk_method2")

x2 = []
y2 = []
n = int(f.readline())
for i in range(n):
    x2.append(float(f.readline()))
for i in range(n):
    y2.append(float(f.readline()))

plt.scatter(x2, y2, color='g', label='Runge-Kutta method')

f = open("adams_method2")

x3 = []
y3 = []
n = int(f.readline())
for i in range(n):
    x3.append(float(f.readline()))
for i in range(n):
    y3.append(float(f.readline()))
plt.scatter(x3, y3, color="k", label='Adams method')

plt.legend(loc='upper left')

plt.tight_layout()
plt.show()
