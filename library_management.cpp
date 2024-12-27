#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
using namespace std;

// Structure for Book

struct Book {
    int id;
    string title;
    string author;
    bool isAvailable;
    time_t borrowDate; // Used for overdue calculation
    string borrowedBy; // To track the borrower
};

// Global Variables
vector<Book> library;

// Utility Functions
void saveBooks() {
    ofstream file("books.txt");
    for (const auto& book : library) {
        file << book.id << "|" << book.title << "|" << book.author << "|"
             << book.isAvailable << "|" << book.borrowDate << "|" << book.borrowedBy << "\n";
    }
    file.close();
}

void loadBooks() {
    library.clear();
    ifstream file("books.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Book book;
        string isAvailable, borrowDate;
        getline(ss, line, '|');
        book.id = stoi(line);
        getline(ss, book.title, '|');
        getline(ss, book.author, '|');
        getline(ss, isAvailable, '|');
        getline(ss, borrowDate, '|');
        getline(ss, book.borrowedBy);

        book.isAvailable = isAvailable == "1";
        book.borrowDate = stol(borrowDate);
        library.push_back(book);
    }
    file.close();
}

string hashPassword(const string& password) {
    // A basic hash function for simplicity.
    hash<string> hasher;
    return to_string(hasher(password));
}

// User Authentication Functions
void registerUser() {
	cout << "\n===============Registration==============\n";
    cout << "Enter username: ";
    string username;
    cin >> username;
    cout << "Enter password: ";
    string password;
    cin >> password;

    ofstream file("users.txt", ios::app);
    file << username << "|" << hashPassword(password) << "\n";
    file.close();
    cout << "User registered successfully.\n";
   
    
}

bool loginUser(string& username) {
	cout << "==============Login===============\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    string password;
    cin >> password;

    if (username == "admin" && password == "admin") {
        cout << "Admin login successful!\n";
        return true;
    }

    ifstream file("users.txt");
    string line;
    while (getline(file, line)) {
        string storedUsername, storedPassword;
        stringstream ss(line);
        getline(ss, storedUsername, '|');
        getline(ss, storedPassword);

        if (storedUsername == username && storedPassword == hashPassword(password)) {
            cout << "Login successful! Welcome, " << username << ".\n";
            return true;
        }
    }
    cout << "Invalid username or password.\n";
    return false;
}

// Library Functions
void addBook() {
    Book book;
    book.id = library.empty() ? 1 : library.back().id + 1;
    cin.ignore(); // Clear the newline character left in the input buffer by previous input
    cout << "\n=============================\n";
    cout << "Enter book title: ";
    getline(cin, book.title);

    cout << "Enter book author: ";
    getline(cin, book.author);

    book.isAvailable = true;
    book.borrowDate = 0; // Not borrowed
    book.borrowedBy = ""; // No one has borrowed the book yet

    library.push_back(book);
    cout << "Book added successfully! Book ID: " << book.id << "\n";

    saveBooks();
}


void searchBooks() {
	cout << "\n=============================\n";
    cout << "Enter keyword to search for books: ";
    string keyword;
    cin.ignore();
    getline(cin, keyword);

    for (const auto& book : library) {
        if (book.title.find(keyword) != string::npos || book.author.find(keyword) != string::npos) {
            cout << "ID: " << book.id << ", Title: " << book.title
                 << ", Author: " << book.author
                 << ", Available: " << (book.isAvailable ? "Yes" : "No") << "\n";
        }
    }
}

void borrowBook(const string& username) {
    cout << "\n=============================\n";
    int bookID;
    cout << "Enter book ID to borrow: ";
    cin >> bookID;

    for (auto& book : library) {
        if (book.id == bookID) {
            if (book.isAvailable) {
                book.isAvailable = false;
                book.borrowDate = time(0); // Current time
                book.borrowedBy = username;
                cout << "You have borrowed the book: " << book.title << "\n";
                saveBooks();
                return;
            } else {
                cout << "Book is currently unavailable.\n";
                return;
            }
        }
    }
    cout << "Book ID not found.\n";
}

void returnBook(const string& username) {
    int bookID;
    cout << "\n=============================\n";
    cout << "Enter book ID to return: ";
    cin >> bookID;

    for (auto& book : library) {
        if (book.id == bookID) {
            if (!book.isAvailable && book.borrowedBy == username) {
                book.isAvailable = true;
                book.borrowDate = 0; // Reset borrow date
                book.borrowedBy = ""; // Reset borrower
                cout << "Thank you for returning the book: " << book.title << "\n";
                saveBooks();
                return;
            } else if (book.borrowedBy != username) {
                cout << "You cannot return this book as you didn't borrow it.\n";
                return;
            } else {
                cout << "This book is not borrowed.\n";
                return;
            }
        }
    }
    cout << "Book ID not found.\n";
}

void calculateFine() {
    int bookID;
    cout << "\n=============================\n";
    cout << "Enter book ID to calculate overdue fine: ";
    cin >> bookID;

    for (const auto& book : library) {
        if (book.id == bookID) {
            if (!book.isAvailable) {
                time_t now = time(0);
                double daysBorrowed = difftime(now, book.borrowDate) / (60 * 60 * 24);
                if (daysBorrowed > 14) { // 14-day borrowing period
                    double fine = (daysBorrowed - 14) * 10; // ?10 per day overdue
                    cout << "Book is overdue by " << (daysBorrowed - 14) 
                         << " days. Fine: ?" << fine << "\n";
                } else {
                    cout << "No fine. Book is not overdue.\n";
                }
                return;
            } else {
                cout << "Book is not currently borrowed.\n";
                return;
            }
        }
    }
    cout << "Book ID not found.\n";
}

// Menu Functions
void displayMenu(const string& username) {
    cout << "=============================\n";
    cout << "   LIBRARY MANAGEMENT MENU   \n";
    cout << "=============================\n";
    if (username == "admin") {
        cout << "1. Add Book\n";
    } else {
        cout << "2. Search Books\n";
        cout << "3. Borrow Book\n";
        cout << "4. Return Book\n";
        cout << "5. Calculate Overdue Fine\n";
    }
    cout << "6. Exit\n";
    cout << "=============================\n";
    cout << "Enter your choice: ";
}

// Main Function
int main() {
    loadBooks();
    string username;
    bool loggedIn = false;

    while (!loggedIn) {
        int choice;
    cout << "=============================\n";
    cout << "      LIBRARY MANAGEMENT   \n";
    cout << "=============================\n";
        cout << "1. Register\n2. Login\nEnter your choice: ";
        cin >> choice;
        if (choice == 1) {
            registerUser();
        } else if (choice == 2) {
            loggedIn = loginUser(username);
        }
    }

    int choice;
    do {
        displayMenu(username);
        cin >> choice;
        if (username == "admin") {
            if (choice == 1) addBook();
        } else {
            switch (choice) {
                case 2: searchBooks(); break;
                case 3: borrowBook(username); break;
                case 4: returnBook(username); break;
                case 5: calculateFine(); break;
                case 6: cout << "Exiting program. Goodbye!\n"; break;
                default: cout << "Invalid choice. Try again.\n";
            }
        }
    } while (choice != 6);

    return 0;
}
