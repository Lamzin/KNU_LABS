import matplotlib.pyplot as plt

file = open('expressions.txt', 'r')
exact = map(float, file.readline().split())
approximation = map(float, file.readline().split())

plt.plot(exact[0::2], exact[1::2])
plt.plot(approximation[0::2], approximation[1::2])
plt.show()