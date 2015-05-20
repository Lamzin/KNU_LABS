first = ["Oleg",
"Vasya",
"Petya",
"Grisha",
"Vanya",
"Sasha",
"Misha",
"Anton"]

middle = ["Mikhailovich",
"Vasilevich",
"Olegovich",
"Oleksandrovych",
"Nikolaevich",
"Anatolechiv",
"Arkadievich",
"Antonovich"]

last= ["Lamzin",
"Paly",
"Medvedev",
"Cheshulko",
"Gavrilko",
"Dragomirik"]

subj = ["mathematics",
"physics",
"biology",
"psychology",
"programming"]

import random

file = open("input_gen.txt", "w")

file.write("20\n")
total = 0
for i in range(20):
    f = first[random.randint(0, len(first) - 1)]
    m = middle[random.randint(0, len(middle) - 1)]
    l = last[random.randint(0, len(last) - 1)]

    for j in range(4):
        s = subj[random.randint(0, len(subj) - 1)]
        score = random.randint(1, 100)
        total += score

        file.write("%s; %s; %s; %s; %i; %i\n" % (f, m, l, s, score, float(score)/20))
file.write("80 %i" % total)
file.close()
