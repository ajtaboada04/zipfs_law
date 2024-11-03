// Test main_zipfs_container.cpp

#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include "zipfs.h"

TEST(ReadBook, ReadBookTest) {
    std::vector<char> book = zipfs::readBook("pg2701.txt");
    std::ifstream file("pg2701.txt");
    std::vector<char> bookCharacters;
    if(file.is_open()){
        char c;
        while(file.get(c)){
            if (isalpha(c)) {
                bookCharacters.push_back(c);
            }
            else {
                bookCharacters.push_back(' ');
            }
        }
    };
    EXPECT_EQ(book, bookCharacters);
}

TEST(ComputeWordFrequency, ComputeWordFrequencyTest) {
    std::vector<char> book = zipfs::readBook("pg2701.txt");
    std::map<std::string, int> wordFrequencies = zipfs::computeWordFrequency(book);
    std::map<std::string, int> wordFrecuencies;
    std::string word;
    std::stringstream ss;

    for (char c : book) {
        ss << (isalpha(c) ? tolower(c) : ' '); // Convert all characters to lowercase 

        while (ss >> word) {
            wordFrecuencies[word]++;
        }
    };
    EXPECT_EQ(wordFrequencies, wordFrecuencies);
}

TEST(CountUniqueWords, CountUniqueWordsTest) {
    std::vector<char> book = zipfs::readBook("pg2701.txt");
    int uniqueWords = zipfs::countUniqueWords(book);
    std::set<std::string> uniqueWordsSet;
    std::string word;
    std::stringstream ss;

    for (char c : book) {
        ss << (isalpha(c) ? tolower(c) : ' '); // Convert all characters to lowercase 

        while (ss >> word) {
            uniqueWordsSet.insert(word);
        }
    };
    EXPECT_EQ(uniqueWords, uniqueWordsSet.size());
}

TEST(SortFrequencies, SortFrequenciesTest) {
    std::vector<char> book = zipfs::readBook("pg2701.txt");
    std::map<std::string, int> wordFrequencies = zipfs::computeWordFrequency(book);
    std::multimap<int, std::string> sortedWords = zipfs::sortFrequencies(wordFrequencies);
    std::multimap<int, std::string> sortedWordsTest;
    for (auto it = wordFrequencies.begin(); it != wordFrequencies.end(); ++it) {
        sortedWordsTest.insert(std::make_pair(it->second, it->first));
    }
    EXPECT_EQ(sortedWords, sortedWordsTest);
}

TEST(OutputRankedFrequencies, OutputRankedFrequenciesTest) {
    std::vector<char> book = zipfs::readBook("pg2701.txt");
    std::map<std::string, int> wordFrequencies = zipfs::computeWordFrequency(book);
    std::multimap<int, std::string> sortedWords = zipfs::sortFrequencies(wordFrequencies);
    zipfs::outputRankedFrequencies(sortedWords, "output.txt");
    std::ifstream file("output.txt");
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    std::vector<std::string> linesTest;
    for (auto it = sortedWords.rbegin(); it != sortedWords.rend(); ++it) {
        linesTest.push_back(std::to_string(it->first) + ": " + it->second);
    }
    EXPECT_EQ(lines, linesTest);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}