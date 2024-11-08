#include "zipfs.h"

int main() {
    std::vector<char> book = zipfs::readBook("pg2701.txt");
    std::map<std::string, int> wordFrequencies = zipfs::computeWordFrequency(book);
    int uniqueWords = zipfs::countUniqueWords(book);
    std::cout << "Number of unique words: " << uniqueWords << std::endl;

    std::multimap<int, std::string> sortedWords = zipfs::sortFrequencies(wordFrequencies);
    int count = 0;
    for (auto it = sortedWords.rbegin(); it != sortedWords.rend() && count < 10; ++it, ++count) {
        std::cout << it->first << ": " << it->second << std::endl;
    }

    // Output the ranked frequencies of words to a file
    zipfs::outputRankedFrequencies(sortedWords, "output.txt");


    return 0;
}