from cs50 import get_int
"""Program ask height and print pyramid"""

while True:
    height = get_int("Height: ")
    # Check if given number more then 0 and less then 9
    if height > 0 and height < 9:
        break

# Print pyramid
for i in range(1, height + 1):
    print(" " * (height - i) + "#" * i + " " * 2 + "#" * i)
