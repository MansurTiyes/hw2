#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <deque>
#include "product.h"

/**
 * Implements User functionality and information storage
 *  You should not need to derive anything from User at this time
 */
class User {
public:
    User();
    User(std::string name, double balance, int type);
    virtual ~User();

    double getBalance() const;
    std::string getName() const;
    void deductAmount(double amt);
    virtual void dump(std::ostream& os);

    // Added methods for cart mutation
    void push_to_cart(Product* product); 
    std::deque<Product*> getCart(); // getter method for cart
    void remove_from_cart(Product* product); // remove from cart 


private:
    std::string name_;
    double balance_;
    int type_;
    // added cart property (stores cart of each user)
    std::deque<Product*> cart_;
};
#endif
