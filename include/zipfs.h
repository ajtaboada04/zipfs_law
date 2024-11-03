#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>


namespace zipfs {

/*@brief
    * Read a book from a file and return a vector of characters
    * @param fileName: the name of the file to read
    * @return a vector of characters representing the book
*/

std::vector<char> readBook(std::string fileName){
    std::ifstream file(fileName);
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
    return bookCharacters;
};

/*@brief
    * Compute the frequency of each word in the book
    * @param book: a vector of characters representing the book
    * @return a map with the frequency of each word
*/
std::map<std::string, int> computeWordFrequency(const std::vector<char> &book) {
    std::map<std::string, int> wordFrecuencies;
    std::string word;
    std::stringstream ss;

    for (char c : book) {
        ss << (isalpha(c) ? tolower(c) : ' '); // Convert all characters to lowercase 

        while (ss >> word) {
            wordFrecuencies[word]++;
        }
    };
    return wordFrecuencies;
}; 

/*@brief
    * Count the number of unique words in the book
    * @param book: a vector of characters representing the book
    * @return the number of unique words in the book
*/

int countUniqueWords(const std::vector<char>& book){
    std::set<std::string> unique;
    std::stringstream ss;
    std::string word;

    for (char c : book) {
        ss << (isalpha(c) ? tolower(c) : ' '); 
    }

    while (ss >> word) {
        unique.insert(word);
    }

    return unique.size();   
};

/*@brief
    * Sort the words by frequency
    * @param frequencies: a map with the frequency of each word
    * @return a multimap with the words sorted by frequency
*/

std::multimap<int, std::string> sortFrequencies(const std::map<std::string, int> &frequencies){
    std::multimap<int, std::string> sortedFrequencies;
    for (const auto &pair : frequencies) {
        sortedFrequencies.insert({pair.second, pair.first});
    }

    return sortedFrequencies;
};


/*@brief
    * Output the ranked frequencies of words to a file
    * @param sortedFrequencies: a multimap with the words sorted by frequency
    * @param outputFileName: the name of the output file to write the results
*/

void outputRankedFrequencies(const std::multimap<int, std::string> &sortedFrequencies, const std::string &outputFileName) {
    std::ofstream outFile(outputFileName);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file: " << outputFileName << std::endl;
        return;
    }

    int rank = 1; 
    // Reverse iterate so highest frequency comes first
    for (auto it = sortedFrequencies.rbegin(); it != sortedFrequencies.rend(); ++it) {
        outFile << rank << " " << it->first << " " << it->second << std::endl;
        rank++;
    }

    outFile.close();
}

// Session 19

/*@brief
    * Compute the frequency of each word in the book
    * @param book: a vector of characters representing the book
    * @return a vector of pairs with each word and its frequency
*/
std::vector<std::pair<std::string, int>> computeWordFrequency19(const std::vector<char> &book) {
    std::vector<std::pair<std::string, int>> wordFrequencies;
    std::string word;
    std::stringstream ss;

    // Process each character in the book
    for (char c : book) {
        ss << (std::isalpha(c) ? std::tolower(c) : ' ');

        // Extract words and update frequency count
        while (ss >> word) {
            // Check if the word already exists in wordFrequencies
            auto it = std::find_if(wordFrequencies.begin(), wordFrequencies.end(),
                                   [&word](const std::pair<std::string, int>& p) {
                                       return p.first == word;
                                   });

            if (it != wordFrequencies.end()) {
                // Increment the frequency if the word exists
                it->second++;
            } else {
                // Add a new word with a frequency of 1
                wordFrequencies.emplace_back(word, 1);
            }
        }
    }
    return wordFrequencies;
}

/*@brief
    * Count the number of unique words in the book
    * @param book: a vector of characters representing the book
    * @return the number of unique words in the book
*/
int countUniqueWords19(const std::vector<char>& book) {
    std::vector<std::string> uniqueWords;
    std::stringstream ss;
    std::string word;

    // Process each character in the book
    for (char c : book) {
        ss << (std::isalpha(c) ? std::tolower(c) : ' ');
    }

    // Extract words and check uniqueness
    while (ss >> word) {
        // Check if the word already exists in uniqueWords
        if (std::find(uniqueWords.begin(), uniqueWords.end(), word) == uniqueWords.end()) {
            uniqueWords.push_back(word); // Add word if it's not already present
        }
    }

    return uniqueWords.size();
}

/*@brief
    * Sort the words by frequency
    * @param frequencies: a vector of pairs with each word and its frequency
    * @return a vector of pairs with the words sorted by frequency
*/
std::vector<std::pair<int, std::string>> sortFrequencies19(const std::vector<std::pair<std::string, int>> &frequencies) {
    std::vector<std::pair<int, std::string>> sortedFrequencies;

    // Convert each frequency pair from (word, frequency) to (frequency, word)
    for (const auto &pair : frequencies) {
        sortedFrequencies.emplace_back(pair.second, pair.first);
    }

    // Sort the vector by frequency in ascending order
    std::sort(sortedFrequencies.begin(), sortedFrequencies.end(),
              [](const std::pair<int, std::string> &a, const std::pair<int, std::string> &b) {
                  return a.first < b.first;
              });

    return sortedFrequencies;
}

/*@brief
    * Output the words sorted by frequency to a file with ranks
    * @param sortedFrequencies: a vector of pairs with frequencies and words sorted by frequency
    * @param outputFileName: the name of the output file
*/
void outputRankedFrequencies19(const std::vector<std::pair<int, std::string>> &sortedFrequencies, const std::string &outputFileName) {
    std::ofstream outFile(outputFileName);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file: " << outputFileName << std::endl;
        return;
    }

    int rank = 1; 
    // Iterate from beginning to end (assuming sorted in descending order)
    for (const auto &pair : sortedFrequencies) {
        outFile << rank << " " << pair.first << " " << pair.second << std::endl;
        rank++;
    }

    outFile.close();
}

}
