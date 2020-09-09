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
        std::string title, author, genre;
        double price; 
        Book(std::string title, std::string author, std::string genre, double price) {
            this->title = title;
            this->author = author;
            this->price = price;
            this->genre = genre;
            this->id = generate_uuid_v4();
        }
        std::string getData(std::string data) {
            if(data == "title") return this->title;
            if(data == "author") return this->author;
            if(data == "genre") return this->genre;
            return "null";
        }
};
std::vector<Book> books;

void sell(std::string id) {
    for(int i = 0; i < books.size(); i++) {
        if(books[i].id == id) {
            books.erase(books.begin() + i);
            std::cout << "Sold " << books[i].title << " for $" << books[i].price << std::endl;
            break;
        }
    }
}

std::vector<Book> find(std::string filter, std::string data) {
    std::vector<Book> matches;
    for(Book book : books) {
        if(book.getData(filter) == data) matches.push_back(book); 
    }
    return matches;
}

int main() {
    std::string const shopName = "Book Shop";
    std::cout << shopName << std::endl;
    while(true) {
        std::cout << "Select option [add|sell|find|remove|exit] > ";
        std::string option;
        std::cin >> option;
        // clear buffer
        std::cin.ignore();
        if(option == "exit") return 0;
        if(option == "add") {
            std::string author, title, stringPrice, genre;
            std::cout << "Enter the name of the author > ";
            std::cin >> author;
            std::cin.ignore();
            std::cout << "Enter the title > ";
            std::cin >> title;
            std::cin.ignore();
            std::cout << "Enter the genre > ";
            std::cin >> genre;
            std::cin.ignore();
            std::cout << "Enter the price > ";
            std::cin >> stringPrice;
            double price = std::stod(stringPrice);
            Book newBook(title, author, genre, price);
            books.push_back(newBook);
        }
        if(option == "sell") {
            std::string option;
            std::cout << "What would you like to search by? [title|author|genre|id] > ";
            std::cin >> option;
            std::cin.ignore();
            if(option == "title" || option == "author" || option == "id" || option == "genre") {
                std::string data;
                std::cout << "Enter value of " << option << " > ";
                std::cin >> data;
                std::cin.ignore();
                std::vector<Book> matches;
                for(Book book : books) {
                    if(book.getData(option) == data) matches.push_back(book); 
                }
                if(matches.size() != 0) {
                    if(matches.size() > 1) {
                        std::cout << "\nMore than one match:\n";
                        for(Book book : matches) {
                            std::cout << book.title << "\n" << book.author << "\n" << book.price << book.genre << "\n\n";
                        }
                    } else sell(matches[0].id);
                }
            }
        }
        if(option == "find") {
            std::cout << "How would you like to filter [title|author|genre] > ";
            std::string filter;
            std::cin >> filter;
            std::cin.ignore();
            if(filter == "title" || filter == "author" || filter == "genre") {
                std::string data;
                std::cout << "Enter the " << filter << " of the book > ";
                std::cin >> data;
                std::cin.ignore();
                std::vector<Book> matches = find(filter, data);
                if(matches.size() != 0) {
                    if(matches.size() == 1) std::cout << "\nFound match:\n\nTitle: " << matches[0].title << "\nAuthor: " << matches[0].author << "\nGenre: " << matches[0].genre << "\nPrice: " << matches[0].price << "\n" << std::endl; 
                } else std::cout << "No matches found for the filter: " << filter << ", and the " << filter << ": " << data << std::endl;
            }
        }
    }
}