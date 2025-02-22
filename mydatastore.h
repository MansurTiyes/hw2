#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include <string>
#include <set>
#include <map>
#include <vector>
#include "product.h"
#include "user.h"

class MyDataStore: public DataStore {
    public:
        ~MyDataStore();

        // getter method for set of all users
        std::map<std::string, User*> users();

        // getter method for keywords_to_products
        std::map<std::string, std::set<Product*>> products();

        // adds product to the data store
        void addProduct(Product* p);

        // adds user to the data store
        void addUser(User* u);

        std::vector<Product*> search(std::vector<std::string>& terms, int type);

        void dump(std::ostream& ofile);

    private:
        // maps usernames to user objects
        std::map<std::string, User*> users_;
        // map that maps string keywords to set of corresponding keywords
        std::map<std::string, std::set<Product*>> keywords_to_products_;
        // set of all possible products (to make dump function more efficient and easier)
        std::set<Product*> products_;

        // function that pushes elements in a set to a vector
        std::vector<Product*> set_to_vector(std::set<Product*> products_in_keyword);
};

#endif