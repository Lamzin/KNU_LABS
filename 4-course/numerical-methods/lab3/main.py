import matplotlib.pyplot as plt
import numpy as np

from sympy import *

x = Symbol('x')
t = Symbol('t')
N = 20
M = 50
R = 0.05
T = 15 * 60
lamda = 42.1  # Bт/(м*K)
c = 0.445  # кДж/(кг*К)
ro = 7800  # кг/м^3
gamma = 140  # Bт/(м^2*K)
u_kr = 4
h = 1 / N
tau = T / M
alpha1, alpha2 = 1, 1
gamma1 = gamma / lamda
beta1, beta2 = 0, gamma1


def get_sigma(i):
    sigma = [0, 0.5, 1]
    return sigma[i]


def u_env(t_level):
    t = t_level * tau
    return sin(0.01 * t)


# def x1(x):
#     return x / R


def t1(t):
    return lamda * t / R / R / c / ro


def u(v, x, t):
    return (v(x, t) + 1) * u_kr


def v0():
    return (273 - u_kr) / u_kr


x0_ = integrate((x) ** 2, (x, 0, h)) / h

xN_ = integrate((x) ** 2, (x, 1, 1 - h)) / h


def xi_(i):
    return integrate((x) ** 2, (x, (i - 1)/N, (i + 1)/N)) / h / 2


def pi_(i):
    return h * (i - 0.5)


def bi_(sigma, i):
    return sigma * tau * pi_(i + 1) / h / h


def ci_(sigma, i):
    return -xi_(i) - di_(sigma, i) - bi_(sigma, i)


def di_(sigma, i):
    return sigma * tau * pi_(i) / h / h


def get_next_layer(y_prev, level):
    sigma = get_sigma(1)
    matrix = [[0 for j in range(N + 1)] for i in range(N + 1)]

    mu2 = (gamma / lamda) * u_env(level)

    b0 = sigma * tau * alpha1 * pi_(1) / h / h
    c0 = - alpha1 * x0_ / 2 - b0

    # phi0 = -tau * x0_ * mu2 / h \
    phi0 = - alpha1 * x0_ * y_prev[0] / 2 \
           - (1 - sigma) * tau * alpha1 * pi_(1) * (y_prev[1] - y_prev[0]) / h / h

    dN = sigma * tau * alpha2 * pi_(N - 1) / h / h
    cN = - alpha1 * x0_ / 2 - dN
    phiN = (1 - sigma) * tau * beta2 * (1 - h) * y_prev[N - 1] / h \
           - tau * xN_ * mu2 / h \
           - alpha2 * xN_ * y_prev[N - 1] / 2 \
           + (1 - sigma) * tau * alpha2 * pi_(N - 1) * (y_prev[N - 1] - y_prev[N - 2]) / h / h

    matrix[0][0] = c0
    matrix[0][1] = b0

    matrix[N][N] = cN
    matrix[N][N - 1] = dN

    for i in range(1, N):
        di = di_(sigma, i)
        ci = ci_(sigma, i)
        bi = bi_(sigma, i)

        matrix[i][i - 1] = di
        matrix[i][i] = ci
        matrix[i][i + 1] = bi

    b_array = [0 for i in range(N + 1)]
    b_array[0] = phi0
    b_array[N] = phiN

    for i in range(1, N):
        b_array[i] = - xi_(i) * y_prev[i] \
                     - (1 - sigma) * tau * (pi_(i + 1) * (y_prev[i + 1] - y_prev[i]) - pi_(i) * (y_prev[i] - y_prev[i - 1])) / h / h

    M = np.array(matrix, dtype='float')
    B = np.array(b_array, dtype='float')
    # print(M)
    # print(B)
    c = np.linalg.solve(M, B)
    # print(c)
    return c


def main():
    yi_cur = [1 for i in range(N + 1)]
    for j in range(M):
        yi_cur = get_next_layer(yi_cur, j)
        print(yi_cur)


if __name__ == "__main__":
    main()