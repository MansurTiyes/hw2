#include "mydatastore.h"
#include <string>
#include <set>
#include <map>
#include <vector>
#include "product.h"
#include "user.h"
#include "util.h"
#include "book.h"
#include "movie.h"
#include "clothing.h"
#include <iostream>

using namespace std;

// remove all dynamically allocated propducts and users
// go through products set and delete products there
// go through users set and delete users there
MyDataStore::~MyDataStore() {
    map<string, User*>::iterator it_users;

    for(it_users = users_.begin(); it_users!=users_.end(); ++it_users) {
        delete it_users->second;
    }

    set<Product*>::iterator it_p;
    for(it_p = products_.begin(); it_p!=products_.end(); ++it_p) {
        delete (*it_p);
    } 
}

map<string, User*> MyDataStore::users() {
    return users_;
}

map<string, set<Product*>> MyDataStore::products() {
    return keywords_to_products_;
}

// 1) calls p->keywords() to get set of kewyords
// 2) Iterate over keywords
//       add new keywords to the map or look them up if exists (either way done with [])
//       insert to set of products at that keywords
void MyDataStore::addProduct(Product* p) {
    products_.insert(p); 
    set<string> keywords = p->keywords();

    set<string>::iterator it;
    for(it = keywords.begin(); it!=keywords.end(); ++it) {
        keywords_to_products_[*it].insert(p);
    }
}

// adds user to users map
void MyDataStore::addUser(User* u) {
    users_[u->getName()] = u;
}

// calls parseStringToWords() for terms
// 1) if 1 term provided -> check if exists
// if doesn't exist -> return empty vctor
// if exists -> return the set of products for that keyword
// 2) if 2 or more
// type 0 -> calls set intersection
// type 1 -> calls set union
vector<Product*> MyDataStore::search(vector<string>& terms, int type) {
    // declaring empty vetor products
    vector<Product*> products;

    // check if passed terms is an ISBN (by checking if first and last value is a number)
    set<char> numbers = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    // push vector of terms into parsedTerms
    set<string> parsedTerms;
    for(int i=0; i<terms.size(); i++) {
        // parseToString returns set<string>
        // call setUnion
        if (numbers.find((terms[i])[0]) != numbers.end()) {
            parsedTerms.insert(terms[i]);
        }
        else {
            set<string> tempSet = parseStringToWords(terms[i]);
            parsedTerms = setUnion(parsedTerms, tempSet);
        }
    }

    // if 0 terms passed the terms requirements
    if (parsedTerms.size() == 0) {
        return products;
    }

    // push keywords onto a vector for easier access
    vector<string> keywords;
    set<string>::iterator it;
    for(it = parsedTerms.begin(); it != parsedTerms.end(); ++it) {
        keywords.push_back(*it);
    }

    // if 1 term provided
    if (keywords.size() == 1) {
        // check if it doesn't exist in map
        if (keywords_to_products_.find(keywords[0]) == keywords_to_products_.end()) {
            return products;
        }
        else {
            // push the content of set of products at that keywords to products vector and return it
            return set_to_vector(keywords_to_products_[keywords[0]]);
        }
    }

    // type 0
    // 1) check if all keywords exist in a map, If 1 of them doesn't return empty products
    if (type == 0) {
        for(int i=0; i<keywords.size(); i++) {
            if (keywords_to_products_.find(keywords[i]) == keywords_to_products_.end()) {
                return products;
            }
        }
        set<Product*> matching_products = keywords_to_products_.at(keywords[0]);
        for(int i=1; i<keywords.size(); i++) {
            matching_products = setIntersection(matching_products, keywords_to_products_.at(keywords[i]));
        }
        return set_to_vector(matching_products);
    }
    // type 1
    // check if keyword exists in the map before adding
    else if (type == 1) {
        set<Product*> matching_products;
        for (int i=0; i<keywords.size(); i++) {
            if (keywords_to_products_.find(keywords[i]) != keywords_to_products_.end()) {
                matching_products = setUnion(matching_products, keywords_to_products_.at(keywords[i]));
            }
        }
        return set_to_vector(matching_products);
    }
}

// function that copies elements in product set onto vector
std::vector<Product*> MyDataStore::set_to_vector(std::set<Product*> products_in_keyword) {
    vector<Product*> products;

    set<Product*>::iterator it;
    for(it = products_in_keyword.begin(); it != products_in_keyword.end(); ++it) {
        products.push_back(*it);
    }

    return products;
}

// reproduces the database onto a new file
// calls user->dump
// calls product->dump
void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>" << endl;
    // iterates over products
    set<Product*>::iterator it;
    for(it = products_.begin(); it!=products_.end(); ++it) {
        (*it)->dump(ofile);
    }
    ofile << "</products>" << endl;
    ofile << "<users>" << endl;
    map<string, User*>::iterator it2;
    for(it2 = users_.begin(); it2!= users_.end(); ++it2) {
        (it2->second)->dump(ofile);
    }
    ofile << "</users>" << endl;
}
