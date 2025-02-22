#include "movie.h"
#include <set>
#include <string>
#include "util.h"
#include "product.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string rating, std::string genre) : Product (category, name, price, qty) {
    rating_ = rating;
    genre_ = genre;
}

Movie::~Movie() {

}

// 1) Name of the movie
// 2) words in movie genre
set<string> Movie::keywords() const {
    // call setUnion on name of movie and words in genre
    set<string> movieName = parseStringToWords(name_);
    set<string> genreWords = parseStringToWords(genre_);
    return setUnion(movieName, genreWords);
}

string Movie::displayString() const {
    string movieInfo = name_ + "\n" + "Genre: " + genre_ + " " + "Rating: " + rating_ +"\n" + to_string(price_) + " " + to_string(qty_) + " left.";
    return movieInfo;
}

void Movie::dump(ostream& os) const {
    Product::dump(os);
    os << genre_ << "\n" << rating_ << endl;
}

// Hidden Figures DVD
// 17.99
// 1
// Drama
// PG

string Movie::getGenre() {
    return genre_;
}

string Movie::getRating() {
    return rating_;
}