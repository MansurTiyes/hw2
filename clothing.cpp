#include "clothing.h"
#include <set>
#include <string>
#include "util.h"
#include "product.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) : Product (category, name, price, qty) {
    size_ = size; 
    brand_ = brand;
}

Clothing::~Clothing() {

}

// name of the clothing
// words in brand
set<string> Clothing::keywords() const {
    // call setUnion on name of clothes and brand
    set<string> clothingName = parseStringToWords(name_);
    set<string> brandWords = parseStringToWords(brand_);
    return setUnion(clothingName, brandWords);
}

string Clothing::displayString() const {
    string clothesInfo = name_ + "\n" + "Size: " + size_ + " " + "Brand: " + brand_ +"\n" + to_string(price_) + " " + to_string(qty_) + " left.";
    return clothesInfo;
}

// clothing
// Men's Fitted Shirt
// 39.99
// 25
// Medium
// J. Crew
void Clothing::dump(ostream& os) const {
    Product::dump(os);
    os << size_ << "\n" << brand_ << endl;
}

string Clothing::getSize() {
    return size_;
}

string Clothing::getBrand() {
    return brand_;
}