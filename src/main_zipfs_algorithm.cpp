#include "zipfs.h"

int main() {
    std::vector<char> book = zipfs::readBook("pg2701.txt");
    std::vector<std::pair<std::string, int>> wordFrequencies = zipfs::computeWordFrequency19(book);
    int uniqueWords = zipfs::countUniqueWords19(book);
    std::cout << "Number of unique words: " << uniqueWords << std::endl;

    std::vector<std::pair<int, std::string>> sortedWords = zipfs::sortFrequencies19(wordFrequencies);
    int count = 0;
    for (auto it = sortedWords.rbegin(); it != sortedWords.rend() && count < 10; ++it, ++count) {
        std::cout << it->first << ": " << it->second << std::endl;
    }

    // Output the ranked frequencies of words to a file
    zipfs::outputRankedFrequencies19(sortedWords, "output.txt");

    return 0;
}