# importing required headers
import cs50
import csv
from sys import argv

# checking for correct cmd syntax
if len(argv) != 2:
    print("usage error, import.py characters.csv")
    exit()

# linking sql
db = cs50.SQL("sqlite:///students.db")

# reading csv file
with open(argv[1], "r") as details_info:

    details = csv.DictReader(details_info)

    # loop to read
    for line in details:
        temp = line["name"].split()
    # breaking name pt 1
        if len(temp) == 2:
            first1 = temp[0]
            middle2 = None
            last3 = temp[1]

            db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       first1, middle2, last3, line["house"], line["birth"])
    # breaking name pt 2
        elif len(temp) == 3:
            first1 = temp[0]
            middle2 = temp[1]
            last3 = temp[2]

            db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       first1, middle2, last3, line["house"], line["birth"])