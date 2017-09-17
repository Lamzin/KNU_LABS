file = open("input2.txt", "w")

for i in range(1024 * 1024):
	file.write("a" * 1024)