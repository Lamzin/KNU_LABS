# -*- coding: utf-8 -*-


import math
import numpy as np

from scipy import integrate


class Galerkin(object):

    def __init__(s, n, a, b, m_koef, k_koef, q_koef, p_koef, alpha_koef, u, k, p, q, f):
        s.n = n
        s.a = a
        s.b = b
        s.m_koef = m_koef
        s.k_koef = k_koef
        s.q_koef = q_koef
        s.p_koef = p_koef
        s.alpha_koef = alpha_koef
        s.u = u
        s.k = k
        s.p = p
        s.q = q
        s.f = f

        s.__init_mu__()
        s.__init_psi__()
        s.__init_v__()
        s.__init_phi__()

    def __init_mu__(s):
        s.mu = [
            -s.k[0](s.a)*s.u[1](s.a) + s.alpha_koef[0]*s.u[0](s.a),
            s.k[0](s.b)*s.u[1](s.b) + s.alpha_koef[1]*s.u[0](s.b)
        ]

    def __init_psi__(s):
        s.psi_koef_a = (s.alpha_koef[1]*s.mu[0] - s.alpha_koef[0]*s.mu[1]) / \
                          (s.alpha_koef[1]*(-s.k[0](s.a) + s.a*s.alpha_koef[0]) -
                           s.alpha_koef[0]*(s.k[0](s.b) + s.b*s.alpha_koef[1]))
        s.psi_koef_b = (s.mu[1] - s.psi_koef_a*(s.k[0](s.b) + s.b*s.alpha_koef[1])) / s.alpha_koef[1]
        s.psi = lambda x: s.psi_koef_a*x + s.psi_koef_b

    def __init_v__(s):
        s.v = [
            lambda x: s.u[0](x) - s.psi(x),
            lambda x: s.u[1](x) - s.psi_koef_a,
            lambda x: s.u[2](x)
        ]
        s.Av = lambda x: - s.k[1](x)*s.v[1](x) - s.k[0](x)*s.v[2](x) + s.p(x)*s.v[1](x) + s.q(x)*s.v[0](x)

    def __init_phi__(s):
        s.phi_koef_a = s.k[0](s.b) * (s.b - s.a) / \
                          (2*s.k[0](s.b) + s.alpha_koef[1]*(s.b-s.a)) + \
                          s.b
        s.phi_koef_b = s.a - s.k[0](s.a) * (s.b - s.a) / (2*s.k[0](s.a) + s.alpha_koef[0]*(s.b-s.a))

        s.phi = [[
            lambda x: math.pow(x - s.a, 2)*(x - s.phi_koef_a),
            lambda x: math.pow(x - s.a, 2) + 2*(x - s.a)*(x - s.phi_koef_a),
            lambda x: 2*(x - s.a) + 2*(x - s.phi_koef_a) + 2*(x - s.a)
        ]] + \
        [[
            lambda x: math.pow(s.b - x, 2) * (s.phi_koef_b - x),
            lambda x: -math.pow(s.b - x, 2) - 2 * (s.b - x) * (s.phi_koef_b - x),
            lambda x: 2*(s.b - x) + 2*(s.b - x) + 2*(s.phi_koef_b - x)
        ]] + \
        [
            [
                lambda x, i=i: math.pow(x - s.a, 2) * math.pow(s.b - x, i - 1),
                lambda x, i=i: 2*(x - s.a)*math.pow(s.b - x, i - 1) - (i - 1)*math.pow(x - s.a, 2)*math.pow(s.b - x, i - 2),
                lambda x, i=i: 2*math.pow(s.b - x, i - 1) - 2*(i - 1)*(x - s.a)*math.pow(s.b - x, i - 2) + (i - 1)*(i - 2)*(x - s.a)*(x - s.a)*math.pow(s.b - x, i - 3) - 2*(i - 1)*(x - s.a)*math.pow(s.b - x, i - 2)
            ]
            for i in range(3, s.n + 1)
        ]

        s.A_phi = lambda i, x: -s.k[1](x)*s.phi[i][1](x) - s.k[0](x)*s.phi[i][2](x) + s.p(x)*s.phi[i][1](x) + s.q(x)*s.phi[i][0](x)

    def solve(s):
        matrix = [
            [
                (integrate.quad(lambda x: s.A_phi(j, x)*s.phi[i][0](x), s.a, s.b))[0]
                for j in range(s.n)
            ]
            for i in range(s.n)
        ]
        b = [
            (integrate.quad(lambda x: s.Av(x)*s.phi[i][0](x), s.a, s.b))[0]
            for i in range(s.n)
        ]
        c = np.linalg.solve(np.array(matrix), np.array(b))

        u_approximation = lambda x: sum([c[i] * s.phi[i][0](x) for i in range(s.n)]) + s.psi(x)
        return u_approximation
