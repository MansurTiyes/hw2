#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>
#include <algorithm>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */

// returns elements that are in both sets
// 1) create new set
// 2) iterate through set2
    // for each element check if find() in s2 is true
    // if true insert into intersection set
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
   std::set<T> intersectionSet;
    for(typename std::set<T>::iterator it = s1.begin(); it != s1.end(); ++it) {
        if(s2.find(*it)!=s2.end()) {
            intersectionSet.insert(*it);
        }
    }

    return intersectionSet;
}

// return elements that across both sets (no duplicates)
// 1) create unionSet
// 2) copy s1 to unionSet
// 3) iterate over s2 and if element is not in s1, insert into s2
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> unionSet = s1;
    for(typename std::set<T>::iterator it = s2.begin(); it != s2.end(); ++it) {
        if (s1.find(*it) == s1.end()) { 
            unionSet.insert(*it);
        }
    }
    return unionSet;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
