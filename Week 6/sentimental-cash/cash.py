while True:
    try:
        cash = float(input("Change: "))
    except ValueError:
        continue

    if cash >= 0:
        break

cents = int(cash * 100)
coin = 0

while cents > 0:
    if cents >= 25:
        cents = cents - 25
        coin += 1
    elif cents >= 10:
        cents = cents - 10
        coin += 1
    elif cents >= 5:
        cents = cents - 5
        coin += 1
    else:
        cents = cents - 1
        coin += 1

print(f"{coin}")
