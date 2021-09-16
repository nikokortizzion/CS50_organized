import re
""" Program that first asks the user to type in some text,
and then outputs the grade level for the text"""
while True:
    text = input("Text: ")
    if not text.isdigit():
        break

# Count number of words from text
count_words = len(text.split(" "))

# Count number of letters from text
count_letters = len(re.findall(r'\w', text))

# Count sentences from text
count_sentences = len(re.findall(r'\b[.?!]', text))

# Calculate Coleman-Liau index
indx = 0.0588 * (100 * count_letters / count_words) - 0.296 * (100 * count_sentences / count_words) - 15.8

# Print grade level
if round(indx) < 1:
    print("Before Grade 1")
elif round(indx) > 16:
    print("Grade 16+")
else:
    print(f"Grade {indx: .0f}")
