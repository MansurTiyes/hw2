#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "movie.h"
#include "book.h"
#include "clothing.h"
#include "mydatastore.h"
#include <deque>

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    MyDataStore ds;



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    if( parser.parse(argv[1], ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
	    /* Add support for other commands here */
            // 1. if username is invalid -> print "Invalid username"
            // 2. call User's getCart() and print using for loop
            //    Print with ASCENDING INDEX NUMBER
            // call displayProducts
            // call displayString() from the product
                // index + display string

            // 1. obtain username
            else if ( cmd == "VIEWCART") {
                string username;
                if (ss >> username) {
                    // check if username exists
                    // call users() to get map of users
                    // check using .find()
                    map<string, User*> users = ds.users();
                    if (users.find(username) == users.end()) {
                        cout << "Invalid username" << endl;
                    }
                    else {
                        // call for users getCart() of set of products
                        // iterate over all products and call displayString()
                        deque<Product*> user_cart = (users[username])->getCart();
                        deque<Product*>::iterator it_cart;
                        int counter = 1;
                        for(it_cart = user_cart.begin(); it_cart != user_cart.end(); ++it_cart) {
                            cout << "Item " << counter << endl;
                            cout << (*it_cart)->displayString() << endl;
                            counter++;
                        }
                    }
                }
                else {
                    cout << "Invalid username" << endl;
                }
            }

            // ADD username search_hit_number
            // 1) take an input for username and hit_number
            // 2) if one of them is invalid in input -> cout "Invalid request"
                // if username doesn't exist or index < 0 or more than hits.size() -> cout "Invalid request"
            // 3) Add the product to user's cart
            // you need: user and the product
                // user is given by users_add[username_add]
                // product is given by hits[hit_index-1]
            // call user's push_to_cart
            else if ( cmd == "ADD") {
                string username_add;
                int hit_index;
                if (ss >> username_add && ss >> hit_index) {
                    // now check if username exist in database or hit_index out of bounds
                    map<string, User*> users_add = ds.users();
                    if (users_add.find(username_add) == users_add.end() || (hit_index <= 0 || hit_index > hits.size())) {
                        cout << "Invalid request" << endl;
                    }
                    else {
                        users_add[username_add]->push_to_cart(hits[hit_index-1]);
                        // users hit_index should be hit_index-1 when referencing vector hits
                    }
                }
                else {
                    cout << "Invalid request" << endl;
                }
            }

            // 1) if username is invalid (doesn't exist in the map) -> print "Invalid username"
            // 2) get user's cart
            // 3) iterate each of the items in the cart
                // if item's in stock AND user has enough moneu
                    // item in stock -> current_cart[i]->getQty() > 0
                    // user has enough money -> (users_buy[username_buy]->getBalance() >= current_cart[i]->getPrice() )
            //  // 1) remove from cart
                    // call users_buy[username_buy]->remove_from_cart(current_cart[i])
            //     2) reduce quantity
                    // call current_cart[i]->subtractQty(1)
            //     3) product prive should be devoted from user's available credit
                    // call users_buy[username_buy]->deductAmount(current_cart[i]->getPrice())
            // else -> don't do anything
            else if ( cmd == "BUYCART" ) {
                string username_buy;
                if (ss >> username_buy) {
                    map<string, User*> users_buy = ds.users();
                    if (users_buy.find(username_buy) == users_buy.end()) {
                        cout << "Invalid username" << endl;
                    }
                    else {
                        deque<Product*> current_cart = users_buy[username_buy]->getCart();
                        for(int i =0; i<current_cart.size(); i++) {
                            if ( (current_cart[i]->getQty() > 0) && (users_buy[username_buy]->getBalance() >= current_cart[i]->getPrice()) ) {
                                // remove from cart
                                users_buy[username_buy]->remove_from_cart(current_cart[i]);
                                current_cart[i]->subtractQty(1);
                                users_buy[username_buy]->deductAmount(current_cart[i]->getPrice());
                            }
                        }
                    }   
                }
            } 


            else {
                cout << "Unknown command" << endl;
            }
        }

    }
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
