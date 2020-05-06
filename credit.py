from cs50 import get_int
# number input
n = get_int("Number :")
# var declaration
length = 0
ld = 0
s = 0
y = 0
i = 0
x = 0
z = 0
# loop to find last digit
# length
# sum
while n != 0:
    length = length + 1
    if i % 2 == 0:
        s = s + n % 10
    else:
        if (2 * (n % 10)) > 9:
            y = 2 * (n % 10)
            s = s + (y % 10) + (y // 10)
        else:
            s = s + 2 * (n % 10)
    i = i + 1
    if z == 0:
        if n // 100 == 0:
            ld = n
            z = 1
    n = n // 10
# card validity
valid = s % 10 == 0

# conditions for diff cards
if length == 15 and (ld == 34 or ld == 37) and valid:
    print("AMEX")
    x = 1
if length == 13 and ld // 10 == 4 and valid:
    print("VISA")
    x = 1
if length == 16 and (ld >= 51 and ld <= 55) and valid:
    print("MASTERCARD")
    x = 1
if length == 16 and ld // 10 == 4 and valid:
    print("VISA")
    x = 1
if x == 0:
    print("INVALID")