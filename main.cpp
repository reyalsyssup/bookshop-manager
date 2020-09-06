#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <sstream>

// thank you stackoverflow
static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_int_distribution<> dis(0, 15);
static std::uniform_int_distribution<> dis2(8, 11);

std::string generate_uuid_v4() {
    std::stringstream ss;
    int i;
    ss << std::hex;
    for (i = 0; i < 8; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (i = 0; i < 4; i++) {
        ss << dis(gen);
    }
    ss << "-4";
    for (i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    ss << dis2(gen);
    for (i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (i = 0; i < 12; i++) {
        ss << dis(gen);
    };
    return ss.str();
}

class Book {
    public:
        std::string id;
        bool sold = false;
        std::string title, author;
        double price; 
        Book(std::string title, std::string author, double price) {
            this->title = title;
            this->author = author;
            this->price = price;
            this->id = generate_uuid_v4();
        }
};
std::vector<Book> books;

void sell(std::string id) {
    for(int i = 0; i < books.size(); i++) {
        if(books[i].id == id) {
            books.erase(books.begin() + i);
            break;
        }
    }
}

int main() {
    std::string const shopName = "Book Shop";
    std::cout << shopName << std::endl;
}