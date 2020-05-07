# prog to find readability grade

from cs50 import get_string
# required variables
l = 0
s = 0
w = 0

# test input
txt = get_string("Text: ")

# loop to check required conditions
for i in txt:
    if i.isalpha():
        l = l + 1
    if i == ' ' or i == '\0':
        w = w + 1
    if i == '.' or i == '!' or i == '?':
        s = s + 1
w = w + 1

# to calculate per 100
l = (l / w) * 100
s = (s / w) * 100

# finding index
index = 0.0588 * l - 0.296 * s - 15.8

# grade printing
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    if int(index + 0.5) > int(index):
        print(f"Grade {int(index + 1)}")
    else:
        print(f"Grade {int(index)}")