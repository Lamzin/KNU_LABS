# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np
import math as m
from scipy import integrate
from scipy.integrate import odeint


a, b = 0, 5
n = 5

m1, m2, m3, m4, m5 = 2, 1, 1.5, 0.5, 5
k1, k2, k3 = 2., 1., 4.
q1, q2, q3 = 2., 1., 4.
p1, p2, p3 = 2., 1., 4.
alfa1, alfa2 = 1, 1

c = []

# i >= 1

def u(x): #, m1, m2, m3, m4, m5):
    return m1 * m.sin(m2 * x) + m3 * m.cos(m4 * x) + m5

def k(x): #, k1, k2, k3):
    return k1 * m.sin(k2 * x) + k3

def der1_k(x): #, k1, k2, k3):
    return k1 * k2 * m.cos(k2 * x)

def q(x): # , q1, q2, q3):
    return q1 * m.cos(q2 * x) + q3

def p(x): #, p1, p2, p3):
    return p1 * m.cos(p2 * x) + p3

def u_derivative_1(x):
    return m1*m2*m.cos(m2*x) - m3*m4*m.sin(m4*x)

def u_derivative_2(x):
    return - m1*m2*m2*m.sin(m2*x) - m3*m4*m4*m.cos(m4*x)


# left part
def f(x):
    return - der1_k(x) * u_derivative_1(x) - k(x) * u_derivative_2(x) + p(x) * u_derivative_1(x) + q(x) * u(x)

myu1 = - k(a)*u_derivative_1(a) + alfa1 * u(a)

myu2 = k(b)*u_derivative_1(b) + alfa2 * u(b)

print("mu: ", myu1, myu2)

# зведення задачі до однорідних умов v = u - psi
# psi = A*x + B

A = (alfa2 * myu1 - alfa1 * myu2) / (alfa2*(-k(a)+a*alfa1) - alfa1*(k(b)+b*alfa2))
B = (myu2 - A*(k(b) + b * alfa2)) / alfa2

def psi(x):
    return A * x + B

def v(x):
    return u(x) - psi(x)

_A = k(b) * (b-a) / (2*k(b) + alfa2*(b-a)) + b
_B = a - k(a) * (b-a) / (2*k(a) + alfa1*(b-a))

def phi_i(i, x):
    if i == 1:
        return m.pow(x - a, 2) * (x - _A)
    if i == 2:
        return m.pow(b - x, 2) * (_B - x)
    return m.pow(x - a, 2) * m.pow(b - x, i-1)

def der1_phi_i(i, x):
    if i == 1:
        return m.pow(x - a, 2) + 2 * (x - a) * (x - _A)
    if i == 2:
        return - m.pow(b - x, 2) - 2 * (b - x) * (_B - x)
    return 2 * (x - a) * m.pow(b - x, i - 1) - (i - 1) * m.pow(x - a, 2) * m.pow(b - x, i - 2)

def der2_phi_i(i, x):
    if i == 1:
        return 2 * (x - a) + 2 * (x - _A) + 2 * (x - a)
    if i == 2:
        return 2 * (b - x) + 2 * (b - x) + 2 * (_B - x)
    return 2 * m.pow(b-x, i-1) - 2*(i-1)*(x-a)*m.pow(b-x,i-2) + (i-1)*(i-2)*(x-a)*(x-a)*m.pow(b-x,i-3) - 2*(i-1)*(x-a)*m.pow(b-x, i-2)

# Au = (-k(x)*u`)` + p(x)*u` + q(x)*u

def A_phi(phi_i, i, x):
    return - der1_k(x)*der1_phi_i(i,x) \
           - k(x)*der2_phi_i(i,x) \
           + p(x)*der1_phi_i(i,x) \
           + q(x)*phi_i(i, x)

def Au(u, x):
    return - der1_k(x)*u_derivative_1(x) - k(x)*u_derivative_2(x) + p(x)*u_derivative_1(x) + q(x)*u(x)

v_derivative_1 = lambda x: u_derivative_1(x) - A
v_derivative_2 = lambda x: u_derivative_2(x)

def Av(v, x):
    return - der1_k(x)*v_derivative_1(x) - k(x)*v_derivative_2(x) + p(x)*v_derivative_1(x) + q(x)*v(x)

# x = 3
matrixA=[
        [
            (integrate.quad(lambda x: A_phi(phi_i, j + 1, x) * phi_i(i + 1, x), a, b))[0]
            for j in range(n)
        ] for i in range(n)
    ]

b_array=[
    (integrate.quad(lambda x: Av(v, x) * phi_i(j+1, x), a, b))[0] for j in range(n)
    ]

def my_print(matrix):
    for row in matrix:
        print([round(value, 3) for value in row])

c = np.linalg.solve(np.array(matrixA), np.array(b_array))
my_print(matrixA)
print("c:", c)

approximate_v = lambda x: sum([c[i] * phi_i(i + 1, x) for i in range(n)])
approximate_u = lambda x: approximate_v(x) + psi(x)

x_i = np.arange(a, b, 0.01)
# y_u = []
y_v = []
y_apr_i = []

def fill_y_i():
    for i in x_i:
        y_v.append(v(i) + psi(i))
        # y_u.append(u(i))
        y_apr_i.append(approximate_u(i))

fill_y_i()
# plt.plot(x_i, y_u, 'r')
plt.plot(x_i, y_v, 'g')
plt.plot(x_i, y_apr_i, 'b')
plt.show()

res, _ = integrate.quad(u_derivative_1, 0, m.pi/4)
print(res)