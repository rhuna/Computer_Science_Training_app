#include <iostream>
#include <map>
#include <sstream>
#include <string>

int main()
{
    std::cout << "C++ Word Frequency Starter\n";
    std::cout << "Enter a sentence: ";

    std::string line;
    std::getline(std::cin, line);

    std::map<std::string, int> counts;
    std::stringstream stream(line);
    std::string word;

    while (stream >> word)
    {
        ++counts[word];
    }

    for (const auto& [key, value] : counts)
    {
        std::cout << key << ": " << value << "\n";
    }

    return 0;
}
