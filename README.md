# Terminal Banking System

A terminal-based banking management system written in **C++** that simulates the core functionality of a real banking application. The project demonstrates object-oriented programming, file handling, data persistence, exception handling, and use of the C++ Standard Library.

---
## Project Highlights

- Developed a modular banking system using object-oriented C++
- Implemented persistent file-based storage for customers, accounts, and transactions
- Utilized STL containers (`unordered_map`, `vector`) for efficient data management
- Designed secure transaction workflows including deposits, withdrawals, and transfers
- Applied exception handling and comprehensive input validation throughout the application

## Features

### Customer Management
- Create new customers
- View customer information
- Update customer details
- Delete customers

### Account Management
- Create bank accounts
- View account details
- Close accounts
- PIN validation

### Banking Transactions
- Deposit money
- Withdraw money
- Transfer funds between accounts
- Automatic balance updates
- Transaction history logging

### Reports
- View customer accounts
- View account transaction history
- Display stored banking information

### Data Persistence
All data is stored locally using text files.

- Customers
- Accounts
- Transactions

Data is automatically loaded when the program starts and saved after changes.

---

# Technologies Used

- C++17
- Object-Oriented Programming
- Standard Template Library (STL)
  - `vector`
  - `unordered_map`
  - `string`
  - `fstream`
  - `sstream`
- Exception Handling
- File I/O

---

# Project Structure

```
Project/
│
├── main.cpp
├── Bank.cpp
├── Bank.h
├── Customer.cpp
├── Customer.h
├── Account.cpp
├── Account.h
│
├── customers.txt
├── accounts.txt
├── transactions.txt
│
└── README.md
```

---

# Concepts Demonstrated

This project demonstrates many core C++ concepts, including:

- Classes and Objects
- Encapsulation
- Constructors
- References
- STL Containers
- Iterators
- File Handling
- Exception Handling
- Input Validation
- Object Relationships
- Data Serialization
- Menu-Driven Applications

---

# Learning Outcomes

This project was developed as part of learning modern C++ and software engineering principles. It provided hands-on experience with:

- Designing multi-class applications
- Managing persistent data
- Using STL containers effectively
- Building maintainable C++ programs
- Applying exception handling
- Creating a complete command-line application

---

# Author

**Timothy Dan Hines**

Electrical Engineering Student  
Chulalongkorn University

GitHub: https://github.com/Timothyhsandbox

---

# License

This project is intended for educational purposes.