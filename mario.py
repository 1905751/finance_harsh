from cs50 import get_int

while True:
    x = get_int("Height: ")
    if x >= 1 and x <= 8:
        break
for i in range(x):
    for j in range(x + 2 + i):
        if j == x:
            print("  ", end="")
        elif j >= x - 1 - i:
            print("#", end="")
        else:
            print(" ", end="")
    print()