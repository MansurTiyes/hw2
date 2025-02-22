#include "book.h"
#include <set>
#include <string>
#include "util.h"
#include "product.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, std::string author, std::string isbn) : Product(category, name, price, qty) {
    author_ = author;
    isbn_ = isbn;
}

Book::~Book() {

}

// calls parseStringToWords
// searches for the 
//  1) name of the book
//  2) words in author's name
//  3) book's isbn
// std::set<std::string> parseStringToWords(string rawWords)
// std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
set<string> Book::keywords() const {
    set<string> keywords; 
    keywords.insert(isbn_);
    // call setUnion on name of the book and keywords
    set<string> bookTitle = parseStringToWords(name_);
    keywords = setUnion(keywords, bookTitle);
    set<string> authorWords = parseStringToWords(author_);
    return setUnion(keywords, authorWords);
}

// std::string displayString();
string Book::displayString() const{
    string bookInfo = name_ + "\n" + "Author: " + author_ + " " + "ISBN: " + isbn_ +"\n" + to_string(price_) + " " + to_string(qty_) + " left.";
    return bookInfo;
}

// void dump(std::ostream& os) const;
void Book::dump(ostream& os) const {
    Product::dump(os);
    os << isbn_ << "\n" << author_ << endl;
}

// book
// Data Abstraction & Problem Solving with C++
// 79.99
// 20
// 978-013292372-9
// Carrano and Henry

string Book::getAuthor() {
    return author_;
}

string Book::getIsbn() {
    return isbn_;
}
