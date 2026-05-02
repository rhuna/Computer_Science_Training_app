"""Verified Python starter for the word frequency exercise."""

def solve(text="Apple apple banana"):
    words = text.lower().split()
    counts = {}
    for word in words:
        counts[word] = counts.get(word, 0) + 1
    if counts.get("apple") == 2 and counts.get("banana") == 1:
        return "PASS_WORD_FREQUENCY"
    return "FAIL_WORD_FREQUENCY"

if __name__ == "__main__":
    print(solve())
