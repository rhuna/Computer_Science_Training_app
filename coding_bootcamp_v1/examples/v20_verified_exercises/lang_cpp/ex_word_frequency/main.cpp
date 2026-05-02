#include <iostream>
#include <map>
#include <sstream>
#include <string>

int main()
{
    std::string text = "apple apple banana";
    std::istringstream input(text);
    std::map<std::string, int> counts;
    std::string word;
    while (input >> word) { counts[word]++; }
    if (counts["apple"] == 2 && counts["banana"] == 1) {
        std::cout << "PASS_WORD_FREQUENCY\n";
        return 0;
    }
    std::cout << "FAIL_WORD_FREQUENCY\n";
    return 1;
}
