#include "user.h"
#include "product.h"
#include "book.h"
#include "movie.h"
#include "clothing.h"
#include <deque>
#include <iostream>
using namespace std;

User::User() : name_("unknown"), balance_(0.0), type_(1)
{

}
User::User(std::string name, double balance, int type) :
    name_(name), balance_(balance), type_(type)
{

}

User::~User()
{

}

deque<Product*> User::getCart() {
    return cart_;
}

// void push_to_cart(Product* product); 
void User::push_to_cart(Product* product) {
    cart_.push_back(product);
}

// given a product, remove that product from the cart
// uses deque erase method
// identify position of that product in the cart
// erase it
void User::remove_from_cart(Product* product) {
    // since called by buy_cart no need to consider that 
    // it might not be in cart
    for (deque<Product*>::iterator it = cart_.begin(); it != cart_.end(); ++it) {
        if (*it == product) {
            cart_.erase(it);
            return;
        }     
    }
}

std::string User::getName() const
{
    return name_;
}

double User::getBalance() const
{
    return balance_;
}

void User::deductAmount(double amt)
{
    balance_ -= amt;
}

void User::dump(std::ostream& os)
{
    os << name_ << " "  << balance_ << " " << type_ << endl;
}
