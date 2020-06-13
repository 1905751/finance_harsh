# imp headers
import csv
from sys import argv

# checking for correct format
if len(argv) != 3:
    print("usage error, dna.py sequence.txt database.csv")
    exit()
#reading keys for database
with open(argv[1]) as info_files:
    info = csv.reader(info_files)

    for row in info:
        key = row
        break
#removing 1st row
key.pop(0)

# reading the dna sequence
with open(argv[2]) as dna_file:
    read = csv.reader(dna_file)

    for line in read:
        seq  = line[0]
# loop for counting
i = 0
while i < len(key):
    counter = 0
    big = 0
    j = 0

    while j < len(seq):
        # taking sub string
        sub = seq[j : j + len(key[i])]
        if sub == key[i]:
            counter += 1
            j += len(key[i])
        else:
            # checking for repetetion
            if counter > big:
                big = counter
            if counter != 0:
                counter = 0
            j += 1
# storing numbers
    key[i] = big
    i += 1
# comparing
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
# condition if no match found
if nm == 0:
    print("no match")