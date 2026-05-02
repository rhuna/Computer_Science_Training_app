from collections import Counter

text = input("Python Word Frequency Starter - enter a sentence: ")
counts = Counter(text.split())
for word, count in counts.items():
    print(f"{word}: {count}")
