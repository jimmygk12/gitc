#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool issued;
};

void addBook() {
    Book b;
    ofstream file("books.txt", ios::app);

    cout << "Enter Book ID: ";
    cin >> b.id;
    cin.ignore();

    cout << "Enter Title: ";
    getline(cin, b.title);

    cout << "Enter Author: ";
    getline(cin, b.author);

    b.issued = false;

    file << b.id << "|" << b.title << "|" << b.author << "|" << b.issued << endl;
    file.close();

    cout << "Book added successfully!\n";
}

void displayBooks() {
    Book b;
    ifstream file("books.txt");

    cout << "\n--- Book List ---\n";
    while (file >> b.id) {
        file.ignore();
        getline(file, b.title, '|');
        getline(file, b.author, '|');
        file >> b.issued;
        file.ignore();

        cout << b.id << " | " << b.title << " | " << b.author
             << " | " << (b.issued ? "Issued" : "Available") << endl;
    }
    file.close();
}

void issueBook() {
    int searchId;
    Book b;
    bool found = false;

    ifstream file("books.txt");
    ofstream temp("temp.txt");

    cout << "Enter Book ID to issue: ";
    cin >> searchId;

    while (file >> b.id) {
        file.ignore();
        getline(file, b.title, '|');
        getline(file, b.author, '|');
        file >> b.issued;
        file.ignore();

        if (b.id == searchId && !b.issued) {
            b.issued = true;
            found = true;
        }
        temp << b.id << "|" << b.title << "|" << b.author << "|" << b.issued << endl;
    }

    file.close();
    temp.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (found)
        cout << "Book issued successfully!\n";
    else
        cout << "Book not available!\n";
}

int main() {
    int choice;
    do {
        cout << "\n--- Library Management System ---\n";
        cout << "1. Add Book\n";
        cout << "2. View Books\n";
        cout << "3. Issue Book\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addBook(); break;
        case 2: displayBooks(); break;
        case 3: issueBook(); break;
        case 4: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}