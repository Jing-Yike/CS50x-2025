text = input("Text: ")

# Count the letters
letter = 0
for i in range(len(text)):
    if text[i].isalpha():
        letter += 1
    i += 1

# Count the words
word = 1
for j in range(len(text)):
    if text[j].isspace():
        word += 1
    j += 1

# Count the sentences
sentence = 0
for k in range(len(text)):
    if text[k] == '.' or text[k] == '!' or text[k] == '?':
        sentence += 1
    k += 1

L = letter / word * 100
S = sentence / word * 100
grade = round(0.0588 * L - 0.296 * S - 15.8)

if grade < 1:
    print("Before Grade 1")
elif grade >= 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")
