using System;
using System.Collections.Generic;

Console.Write("C# Word Frequency Starter - enter a sentence: ");
string text = Console.ReadLine() ?? string.Empty;
Dictionary<string, int> counts = new();
foreach (string word in text.Split(' ', StringSplitOptions.RemoveEmptyEntries))
{
    counts[word] = counts.TryGetValue(word, out int count) ? count + 1 : 1;
}
foreach (var pair in counts)
{
    Console.WriteLine($"{pair.Key}: {pair.Value}");
}
