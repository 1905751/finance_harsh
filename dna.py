import csv
from sys import argv

if len(argv) != 3:
    print("usage error, dna.py sequence.txt database.csv")
    exit()

with open(argv[1]) as info_files:
    info = csv.reader(info_files)

    for row in info:
        key = row
        break
key.pop(0)

with open(argv[2]) as dna_file:
    read = csv.reader(dna_file)

    for line in read:
        seq  = line[0]

x1 = 0
for i in range(len(key)):
    x = len(key[i])
    for j in range(len(seq)):
        if sub[j : j + x ] == key[i]:
            a = a + 1
        