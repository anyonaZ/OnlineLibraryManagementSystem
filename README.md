# Online Library Management System

A C++ Object-Oriented Programming (OOP) implementation of an online library system for managing books and users, with borrowing/returning functionality and robust testing.

---

## Table of Contents
- [Design Choices](#design-choices)
- [How to Run](#how-to-run)
- [Testing](#testing)
- [Dependencies](#dependencies)

---

## Design Choices

### Class Structure
1. **`Book` Class**:
   - Encapsulates book attributes: `title`, `author`, `ISBN`, `publicationYear`, and `isAvailable`.
   - Methods: Getters/setters for availability, and a `display()` method to print book details.

2. **`User` Class**:
   - Manages user details: `name`, `userID`, and a list of borrowed books (tracked by ISBN).
   - Methods: `borrowBook()` and `returnBook()` to update borrowed books.

3. **`Library` Class**:
   - Core system managing collections of `Book` and `User` objects.
   - Functionality:
     - Add/remove books (with ISBN uniqueness and availability checks).
     - Add/remove users (with ID uniqueness and borrowed-book checks).
     - Search books by title, author, or ISBN.
     - Borrow/return books with validation (e.g., user/book existence, availability).

### Key Principles
- **Encapsulation**: All class data is private, with controlled access via methods.
- **Modularity**: Separation of concerns (e.g., `Library` handles logic, `Book`/`User` manage their own data).
- **Error Handling**: Comprehensive checks (e.g., duplicate ISBNs, removing borrowed books).

---

## How to Run

### Prerequisites
- **Visual Studio 2022** (or any C++17-compatible compiler).
- Git (optional, for cloning).

### Steps
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/anyonaZ/OnlineLibraryManagementSystem
   cd OnlineLibraryManagementSystem
