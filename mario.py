# taking input
x = int(input("enter the height of pyramid :"))
# checking condition
while x < 1 or x > 8:
    x = int(input("enter the height of pyramid :"))
# printing loop
for i in range(x):
    for j in range(x + 3 + i):
        if j == x + 1:
            print(" ", end="")
        elif j >= x - i:
            print("#", end="")
        else:
            print(" ", end="")
    print()