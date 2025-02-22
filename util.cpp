#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
#include <set>
#include <string>

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

// 1) substring should be more tahn 2 characters 
// 2) should split at each punctation character 
// and the resulting substrings should be used as keywords 
// Examples
// 1) Men's -> Men
// 2) J. -> J (not yield since <=2 characters)
// 3) I'll -> Ill 
/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    // find -> find content in string
    // substr (first character index, number of characters to include)

    // create a set of strings keywords
    // call a trim function to remove any white spaces from original string
    // call convToLower on string
    // int startIndex -> keeps track of started Index
    // create a set that holds all punctuation signs
    // start a loop through rawWords
    // check if each character is in punctuation set
    // if it is 
        // push to keywords(trim(substr(startIndex, i-startIndex)))
        // move startIndex to next index
    set<string> keywords; 
    string processedWords = convToLower(trim(rawWords));
    processedWords.push_back(' '); // so last character is counted
    int startIndex = 0;
    set<char> punctuation = {
        '.', ' ', ',', '!', '?',
        ':', ';', '\'', '`', '(',
        ')', '[', ']', '{', '}',
        '<', '-', '_', '/', '|',
        '~'
    };
    for(int i = 0; i<processedWords.length(); i++) {
        if (punctuation.find(processedWords[i])!=punctuation.end()) {
            if (i-startIndex>2) {
                string wordToBeAdded = processedWords.substr(startIndex, i-startIndex);
                keywords.insert(trim(wordToBeAdded));
            }
            startIndex = i+1;
        }
    }
    
    return keywords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
