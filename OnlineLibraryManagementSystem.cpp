#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

class Book {
private:
	string title;
	string author;
	string ISBN;
	int publicationYear;
	bool isAvailable;

public:
	Book(string t, string a, string isbn, int year)
		: title(t), author(a), ISBN(isbn), publicationYear(year), isAvailable(true) { }

	string getTitle() const { return title; }
	string getAuthor() const { return author; }
	string getISBN() const { return ISBN; }
	int getYear() const { return publicationYear; }
	bool getAvailability() const { return isAvailable; }

	void setAvailability(bool availability) { isAvailable = availability; }

	void display() const {
		cout << "Title: " << title << "\nAuthor: " << author
			<< "\nISBN: " << ISBN << "\nYear: " << publicationYear
			<< "\nAvailable: " << (isAvailable ? "Yes!" : "No!") << endl;
	}

};

class User {
private:
	string name;
	string userID;
	vector<string> borrowedISBNs;

public:
	User(string n, string id) : name(n), userID(id) {}

	string getName() const { return name; }
	string getUserID() const { return userID; }
	const vector<string>& getBorrowedISBNs() const { return borrowedISBNs; }

	void borrowBook(const string& ISBN) { borrowedISBNs.push_back(ISBN); }

	void returnBook(const string& ISBN) {
		auto it = find(borrowedISBNs.begin(), borrowedISBNs.end(), ISBN);
		if (it != borrowedISBNs.end())
			borrowedISBNs.erase(it);
	}
};

class Library {
private:
	vector<Book> books;
	vector<User> users;

public:
	void addBook(const Book& book) {
		for (const auto& b : books) {
			if (b.getISBN() == book.getISBN()) {
				cout << "Error: Book with ISBN " << book.getISBN() << " already exists." << endl;
				return;
			}
		}
		books.push_back(book);
		cout << "Book succesxfully added!" << endl;
	}

	void removeBook(const string& ISBN) {
		auto it = find_if(books.begin(), books.end(), [&ISBN](const Book& b) {
			return b.getISBN() == ISBN;
			});

		if (it != books.end()) {
			if (!it->getAvailability()) {
				cout << "Error: Cannot remove book. It is currently borrowed." << endl;
				return;
			}
			books.erase(it);
			cout << "Book removed successfully!" << endl;
		}
		else {
			cout << "Error: Book not found!" << endl;
		}
	}

	void addUser(const User& user) {
		for (const auto& u : users) {
			if (u.getUserID() == user.getUserID()) {
				cout << "Error: User with ID " << user.getUserID() << " already exists." << endl;
				return;
			}
		}
		users.push_back(user);
		cout << "User added successfully." << endl;
	}

	void removeUser(const string& userID) {
		auto it = find_if(users.begin(), users.end(), [&userID](const User& u) {
			return u.getUserID() == userID;
			});
		if (it != users.end()) {
			if (!it->getBorrowedISBNs().empty()) {
				cout << "Error: Cannot remove user. They have borrowed books." << endl;
				return;
			}
			users.erase(it);
			cout << "User removed successfully!" << endl;
		}
		else {
			cout << "Error: User not found." << endl;
		}
	}

	vector<Book> searchByTitle(const string& title) const {
		vector<Book> results;
		for (const auto& book : books) {
			if (book.getTitle() == title)
				results.push_back(book);
		}
		return results;
	}

	vector<Book> searchByAuthor(const string& author) const {
		vector<Book> results;
		for (const auto& book : books) {
			if (book.getAuthor() == author)
				results.push_back(book);
		}
		return results;
	}

	Book* findBookByISBN(const string& ISBN) {
		for (auto& book : books) {
			if (book.getISBN() == ISBN)
				return &book;
		}
		return nullptr;
	}

	const Book* findBookByISBN(const string& ISBN) const {
		for (const auto& book : books) {
			if (book.getISBN() == ISBN)
				return &book;
		}
		return nullptr;
	}

	User* findUserByID(const string& userID) {
		for (auto& user : users) {
			if (user.getUserID() == userID)
				return &user;
		}
		return nullptr;
	}

	const User* findUserByID(const string& userID) const {
		for (const auto& user : users) {
			if (user.getUserID() == userID)
				return &user;
		}
		return nullptr;
	}

	bool borrowBook(const string& userID, const string& ISBN) {
		User* user = findUserByID(userID);
		Book* book = findBookByISBN(ISBN);
		if (!user) {
			cout << "Error: User not found." << endl;
			return false;
		}
		if (!book) {
			cout << "Error: Book not found." << endl;
			return false;
		}
		if (!book->getAvailability()) {
			cout << "Error: Book is not available." << endl;
			return false;
		}
		const vector<string>& borrowed = user->getBorrowedISBNs();
		if (find(borrowed.begin(), borrowed.end(), ISBN) != borrowed.end()) {
			cout << "Error: User already borrowed this book." << endl;
			return false;
		}
		book->setAvailability(false);
		user->borrowBook(ISBN);
		cout << "Book borrowed successfully!" << endl;
		return true;
	}

	bool returnBook(const string& userID, const string& ISBN) {
		User* user = findUserByID(userID);
		Book* book = findBookByISBN(ISBN);
		if (!user) {
			cout << "Error: User not found." << endl;
			return false;
		}
		if (!book) {
			cout << "Error: Book not found." << endl;
			return false;
		}
		vector<string> borrowed = user->getBorrowedISBNs();
		auto it = find(borrowed.begin(), borrowed.end(), ISBN);
		if (it == borrowed.end()) {
			cout << "Error: User did not borrow this book." << endl;
			return false;
		}
		book->setAvailability(true);
		user->returnBook(ISBN);
		cout << "Book returned successfully." << endl;
		return true;
	}

	void displayAllBooks() const {
		if (books.empty()) {
			cout << "No books in the library." << endl;
			return;
		}
		for (const auto& book : books) {
			book.display();
			cout << "___________" << endl;
		}
	}

	void displayUserBorrowedBooks(const string& userID) const {
		const User* user = findUserByID(userID);
		if (!user) {
			cout << "Error: User not found." << endl;
			return;
		}
		cout << "Books borrowed by " << user->getName() << ":" << endl;
		const vector<string>& borrowed = user->getBorrowedISBNs();
		if (borrowed.empty()) {
			cout << "No books borrowed." << endl;
			return;
		}
		for (const auto& isbn : borrowed) {
			const Book* book = findBookByISBN(isbn);
			if (book)
				cout << "Title: " << book->getTitle() << ", ISBN: " << isbn << endl;
			else
				cout << "Error: Book with ISBN " << isbn << "not found." << endl;
		}
	}
};


int main() {
	Library lib;

	cout << "=== Testing Library Management ===" << endl;
	lib.addBook(Book("The Catcher in the Rye", "J.D. Salinger", "ISBN001", 1951));
	lib.addBook(Book("To Kill a Mockingbird", "Harper Lee", "ISBN002", 1960));
	lib.addBook(Book("1984", "George Orwell", "ISBN003", 1949));
	lib.addBook(Book("Duplicate", "Author", "ISBN001", 2020));

	lib.removeBook("ISBN002");
	lib.removeBook("ISBN000");

	cout << "\n=== Testing User Management ===" << endl;
	lib.addUser(User("Alice Smith", "USER001"));
	lib.addUser(User("Bob Johnson", "USER002"));
	lib.addUser(User("Alice Smith", "USER001"));

	cout << "\n=== Testing Borrowing and Returning ===" << endl;
	lib.borrowBook("USER001", "ISBN003");
	lib.borrowBook("USER001", "ISBN003");
	lib.borrowBook("USER002", "ISBN002");
	lib.borrowBook("USER003", "ISBN001");

	lib.returnBook("USER001", "ISBN003");
	lib.returnBook("USER001", "ISBN003");

	cout << "\n=== Testing search functionality" << endl;
	vector<Book> results = lib.searchByTitle("1984");
	cout << "Search for '1984': " << results.size() << " results." << endl;

	results = lib.searchByAuthor("J.D. Salinger");
	cout << "Search by J.D. Salinger: " << results.size() << " results." << endl;

	Book* book = lib.findBookByISBN("ISBN001");
	if (book)
		cout << "Found book with ISBN001: " << book->getTitle() << endl;

	cout << "\n=== All Books in Library ===" << endl;
	lib.displayAllBooks();

	cout << "\n=== Testing User removal with borrowed books ===" << endl;
	lib.borrowBook("USER001", "ISBN001");
	lib.removeUser("USER001");

	cout << "\n=== Testing Book removal when borrowed ===" << endl;
	lib.removeBook("ISBN001");

	return 0;
}