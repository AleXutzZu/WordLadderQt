import nltk
import random

# Make sure you've downloaded the corpus at least once
nltk.download('words')

from nltk.corpus import words

# Filter words: length between 4 and 8, alphabetic only, lowercase
word_list = [w.lower() for w in words.words() if 4 <= len(w) <= 8 and w.isalpha()]

# Remove duplicates
unique_words = list(set(word_list))

# Shuffle and select 1000 unique words
selected_words = random.sample(unique_words, 1000)

# Save to a text file, one word per line
with open("word_ladder_dictionary.txt", "w") as f:
    for word in selected_words:
        f.write(word + "\n")

print("Dictionary created: word_ladder_dictionary.txt")
