import re
""" Program check given number if it card number Visa,
MasterCard or American Express and print name of card or invalid in other case."""

summ = 0
while True:
    number = input("Number: ")
    # Check if typed string is number
    if number.isdigit():
        break

# Save namber from 13 to 16 digits long in card
card = re.match(r'\d{13,16}', number)
if card is not None:
    card = card.group()

# Check if card gets all number and its length 13, 15 or 16 digits, print IVALID in other case
if card == number and (len(card) == 13 or len(card) == 15 or len(card) == 16):
    # Make list of integers from card using list generator
    tmp = [int(x) for x in card]

    # Calculate summ by Luhn’s algorithm
    summ = sum(tmp[-1::-2])
    summ += sum([x * 2 if x < 5 else (
        (x * 2) // 10 + (x * 2) % 10) for x in tmp[-2::-2]])

    # Check if card number start with 4, 35, 37, from 51 to 55 and summ end with 0, print IVALID in other case
    if card.startswith('4') and summ % 10 == 0:
        print("VISA")
    elif (int(card[:2]) >= 51 and int(card[:2]) <= 55) and summ % 10 == 0:
        print('MASTERCARD')
    elif (card.startswith('35') or card.startswith('37')) and summ % 10 == 0:
        print("AMEX")
    else:
        print("INVALID")
else:
    print("INVALID")
