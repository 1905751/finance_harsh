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
i = 0
while i < len(key):
    counter = 0
    big = 0
    j = 0

    while j < len(seq):
        sub = seq[j : j + len(key[i])]
        if sub == key[i]:
            counter += 1
            j += len(key[i])
        else:
            if counter > big:
                big = counter
            if counter != 0:
                counter = 0
            j += 1

    key[i] = big
    i += 1

with open(argv[1]) as people_info:
    people = csv.reader(people_info)

    next(people)
    nm = 0
    for p in people:
        i = 1
        match = 0
        while i < (len(p)):
            if int(p[i]) == key[i - 1]:
                match += 1

            i += 1
        if match == len(key):
                nm += 1
                print(p[0])
                break
if nm == 0:
    print("no match")