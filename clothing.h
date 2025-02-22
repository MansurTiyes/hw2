#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

class Clothing : public Product {
    public:
        // unique methods
        Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand);
        ~Clothing();

        // overriden methods from Product
        std::string displayString() const;
        std::set<std::string> keywords() const;
        void dump(std::ostream& os) const;

        // getters and setters
        std::string getSize();
        std::string getBrand();

    private:
        std::string size_;
        std::string brand_;
};

#endif