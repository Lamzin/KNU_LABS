# -*- coding: utf-8 -*-

import math


class Function(object):

    def __init__(self, f):
        self.f = f if hasattr(f, '__call__') else lambda x: f

    def __add__(self, g):
        return self.__helper__(g, lambda x, y: x + y)

    def __radd__(self, g):
        return self.__helper__(g, lambda x, y: x + y)

    def __sub__(self, g):
        return self.__helper__(g, lambda x, y: x - y)

    def __rsub__(self, g):
        return self.__helper__(g, lambda x, y: y - x)

    def __mul__(self, g):
        return self.__helper__(g, lambda x, y: x * y)

    def __rmul__(self, g):
        return self.__helper__(g, lambda x, y: x * y)

    def __div__(self, g):
        return self.__helper__(g, lambda x, y: x / y)

    def __rdiv__(self, g):
        return self.__helper__(g, lambda x, y: y / x)

    def __pow__(self, power):
        return self.__helper__(power, lambda x, y: x**y)

    def __rpow__(self, power):
        return self.__helper__(power, lambda x, y: y**x)

    def __neg__(self):
        return self.__helper__(lambda x: x, lambda x, y: -x)

    def __pos__(self):
        return self.__helper__(lambda x: x, lambda x, y: x)

    def __call__(self, x):
        if hasattr(self.f, '__call__'):
            return self.f(x)
        return self.f

    def __helper__(self, g, operator):
        if hasattr(g, '__call__'):
            return Function(lambda x, f=self.f: operator(f(x), g(x)))
        return Function(lambda x, f=self.f: operator(f(x), g))


X = Function(lambda x: x)


def cos(f):
    return Function(lambda x: math.cos(f(x)))


def sin(f):
    return Function(lambda x: math.sin(f(x)))


if __name__ == "__main__":
    f = Function(lambda x: x)
    g = Function(lambda x: 2*x)

    x = 9
    print(-f(x))
    print(+f(x))
    print(f(x))
    print((f + g)(x))
    print((f - g)(x))
    print((f * g)(x))
    print((f / g)(x))
