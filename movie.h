#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

class Movie : public Product {
    public:
        Movie(const std::string category, const std::string name, double price, int qty, std::string rating, std::string genre);
        ~Movie();

        // overriden methods from Product
        std::string displayString() const;
        std::set<std::string> keywords() const;
        void dump(std::ostream& os) const;

        // getters and setters
        std::string getRating();
        std::string getGenre();
    private:
        std::string rating_;
        std::string genre_;
};

#endif