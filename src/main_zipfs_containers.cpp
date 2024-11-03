#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>

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
    * Output the contents of the multiple map to a file in format "rank freq word"
    * @param frequencies: a multimap with the words sorted by frequency
    * @param fileName: the name of the file to write
    * @return void
*/

void outputFrequencies(const std::multimap<int, std::string> &frequencies, std::string fileName){
    std::ofstream file(fileName);
    if (file.is_open()) {
        int rank = 1;
        for (auto it = frequencies.rbegin(); it != frequencies.rend(); it++) {
            file << rank << " " << it->first << " " << it->second << std::endl;
            rank++;
        }
    }
};


int main() {
    std::string fileName = "pg2701.txt";
    std::vector<char> book = readBook(fileName);
    std::map<std::string, int> frequencies = computeWordFrequency(book);
    int uniqueWords = countUniqueWords(book);
    std::multimap<int, std::string> sortedFrequencies = sortFrequencies(frequencies);
    std::string outputFileName = "output.txt";
    outputFrequencies(sortedFrequencies, outputFileName);
    return 0;
}