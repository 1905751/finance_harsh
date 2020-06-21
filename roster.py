# importing files
import cs50
import csv
from sys import argv

# checking correct format for cmd prompt
if len(argv) != 2:
    print("usage error, roster.py house")
    exit()
# linking dbms to python
db = cs50.SQL("sqlite:///students.db")

# execution of desired command
x = db.execute("SELECT first, middle, last, birth FROM students WHERE house = (?) ORDER BY last, first", argv[1])

# printing desired output
for row in x:
    if row["middle"] == None:
        print(row["first"] + " " + row["last"] + "," + " " + "born" + " " + str(row["birth"]))
    else:
        print(row["first"] + " " + row["middle"] + " " + row["last"] + "," + " " + "born" + " " + str(row["birth"]))