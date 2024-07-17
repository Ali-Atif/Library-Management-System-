#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Book {
private:
    int id;
    string title;
    string author;
    string genre;
    bool isAvailable;

public:
    Book(int bookId, string bookTitle, string bookAuthor, string bookGenre)
        : id(bookId), title(bookTitle), author(bookAuthor), genre(bookGenre), isAvailable(true) {}

    int getId() const { return id; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getGenre() const { return genre; }
    bool getAvailability() const { return isAvailable; }

    void setAvailability(bool availability) { isAvailable = availability; }

    void updateDetails(string newTitle, string newAuthor, string newGenre) {
        title = newTitle;
        author = newAuthor;
        genre = newGenre;
    }
};

class Member {
private:
    int memberId;
    string name;
    vector<int> borrowedBooks;

public:
    Member(int id, string memberName) : memberId(id), name(memberName) {}

    int getId() const { return memberId; }
    string getName() const { return name; }

    void borrowBook(int bookId) {
        borrowedBooks.push_back(bookId);
    }

    void returnBook(int bookId) {
        borrowedBooks.erase(remove(borrowedBooks.begin(), borrowedBooks.end(), bookId), borrowedBooks.end());
    }

    vector<int> getBorrowedBooks() const { return borrowedBooks; }
};

class Librarian {
private:
    int librarianId;
    string name;

public:
    Librarian(int id, string librarianName) : librarianId(id), name(librarianName) {}

    int getId() const { return librarianId; }
    string getName() const { return name; }
};

class Library {
private:
    vector<Book> books;
    vector<Member> members;

public:
    // Book Management
    void addBook() {
        int id;
        string title, author, genre;
        cout << "Enter Book ID: ";
        cin >> id;
        cout << "Enter Book Title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter Book Author: ";
        getline(cin, author);
        cout << "Enter Book Genre: ";
        getline(cin, genre);

        books.push_back(Book(id, title, author, genre));
        cout << "Book added: " << title << endl;
    }

    void removeBook() {
        int bookId;
        cout << "Enter Book ID to remove: ";
        cin >> bookId;

        books.erase(remove_if(books.begin(), books.end(),
            [bookId](Book &b) { return b.getId() == bookId; }), books.end());
        cout << "Book removed: " << bookId << endl;
    }

    void updateBook() {
        int bookId;
        string newTitle, newAuthor, newGenre;
        cout << "Enter Book ID to update: ";
        cin >> bookId;
        cout << "Enter new Book Title: ";
        cin.ignore();
        getline(cin, newTitle);
        cout << "Enter new Book Author: ";
        getline(cin, newAuthor);
        cout << "Enter new Book Genre: ";
        getline(cin, newGenre);

        for (auto &book : books) {
            if (book.getId() == bookId) {
                book.updateDetails(newTitle, newAuthor, newGenre);
                cout << "Book updated: " << book.getTitle() << endl;
            }
        }
    }

    // Member Services
    void addMember() {
        int id;
        string name;
        cout << "Enter Member ID: ";
        cin >> id;
        cout << "Enter Member Name: ";
        cin.ignore();
        getline(cin, name);

        members.push_back(Member(id, name));
        cout << "Member added: " << name << endl;
    }

    void borrowBook() {
        int memberId, bookId;
        cout << "Enter Member ID: ";
        cin >> memberId;
        cout << "Enter Book ID to borrow: ";
        cin >> bookId;

        for (auto &book : books) {
            if (book.getId() == bookId && book.getAvailability()) {
                for (auto &member : members) {
                    if (member.getId() == memberId) {
                        book.setAvailability(false);
                        member.borrowBook(bookId);
                        cout << "Book borrowed: " << book.getTitle() << endl;
                        return;
                    }
                }
            }
        }
        cout << "Book not available or Member not found." << endl;
    }

    void returnBook() {
        int memberId, bookId;
        cout << "Enter Member ID: ";
        cin >> memberId;
        cout << "Enter Book ID to return: ";
        cin >> bookId;

        for (auto &book : books) {
            if (book.getId() == bookId && !book.getAvailability()) {
                for (auto &member : members) {
                    if (member.getId() == memberId) {
                        book.setAvailability(true);
                        member.returnBook(bookId);
                        cout << "Book returned: " << book.getTitle() << endl;
                        return;
                    }
                }
            }
        }
        cout << "Book not found or was not borrowed by this member." << endl;
    }

    void viewBorrowedBooks() {
        int memberId;
        cout << "Enter Member ID: ";
        cin >> memberId;

        for (const auto &member : members) {
            if (member.getId() == memberId) {
                cout << "Books borrowed by " << member.getName() << ": ";
                for (const auto &bookId : member.getBorrowedBooks()) {
                    for (const auto &book : books) {
                        if (book.getId() == bookId) {
                            cout << book.getTitle() << " ";
                        }
                    }
                }
                cout << endl;
                return;
            }
        }
        cout << "Member not found." << endl;
    }

    // Search Functionality
    void searchBook() {
        string searchTerm;
        cout << "Enter search term (Title, Author, or Genre): ";
        cin.ignore();
        getline(cin, searchTerm);

        for (const auto &book : books) {
            if (book.getTitle().find(searchTerm) != string::npos ||
                book.getAuthor().find(searchTerm) != string::npos ||
                book.getGenre().find(searchTerm) != string::npos) {
                cout << "Book found: " << book.getTitle() << " by " << book.getAuthor() << endl;
            }
        }
    }

    void displayAvailableBooks() {
        cout << "Available books: " << endl;
        for (const auto &book : books) {
            if (book.getAvailability()) {
                cout << book.getTitle() << " by " << book.getAuthor() << endl;
            }
        }
    }
};

int main() {
    Library myLibrary;
    int choice;

    while (true) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Remove Book\n";
        cout << "3. Update Book\n";
        cout << "4. Add Member\n";
        cout << "5. Borrow Book\n";
        cout << "6. Return Book\n";
        cout << "7. View Borrowed Books\n";
        cout << "8. Search Book\n";
        cout << "9. Display Available Books\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                myLibrary.addBook();
                break;
            case 2:
                myLibrary.removeBook();
                break;
            case 3:
                myLibrary.updateBook();
                break;
            case 4:
                myLibrary.addMember();
                break;
            case 5:
                myLibrary.borrowBook();
                break;
            case 6:
                myLibrary.returnBook();
                break;
            case 7:
                myLibrary.viewBorrowedBooks();
                break;
            case 8:
                myLibrary.searchBook();
                break;
            case 9:
                myLibrary.displayAvailableBooks();
                break;
            case 10:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

