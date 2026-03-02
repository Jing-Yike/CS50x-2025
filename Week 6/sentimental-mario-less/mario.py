while True:
    try:
        height = int(input("Height: "))
    except ValueError:
        continue

    if height >= 1 and height <= 8:
        break

for i in range(height):
    print(" " * (height - 1 - i), end="")
    print("#" * (i + 1))