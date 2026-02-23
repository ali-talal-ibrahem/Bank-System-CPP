# 🏦 Bank Management System (Core Engine)

A robust, **console-based** Bank Management System developed in **C++**. This project focuses on high-quality code architecture, efficient file handling, and a professional user interface. It is designed to simulate real-world banking operations with a focus on **data integrity** and **"Clean Code"** principles.

---

## 🌟 Key Features

- **Comprehensive Client Management**: Full **CRUD** operations (Create, Read, Update, Delete).
- **Transaction Engine**: Secure Deposit and Withdrawal operations with **real-time balance validation**.
- **Data Persistence**: Flat-file database system (`.txt`) using custom delimiters for structured data storage.
- **Total Liquidity Overview**: A dedicated dashboard to monitor the bank's total assets and individual balances.
- **Advanced Data Parsing**: Custom-built string manipulation and splitting logic for efficient data retrieval.
- **Professional UI/UX**: Well-organized console menus with **input validation** to prevent system crashes.

---

## 🛠 Technical Highlights

- **Clean Code Principles**: Adheres to **DRY** (Don't Repeat Yourself) and high modularity.
- **Memory Management**: Uses `std::vector` and `structs` for efficient in-memory data handling.
- **Input Shielding**: Implemented `cin >> ws` and custom validation to ensure robust user input handling.
- **Formatted Reporting**: Utilizes `std::setw` and `std::left/right` for clean, tabular data presentation.

---

## 📂 Project Structure

- `Main.cpp`: Contains the core logic, menu systems, and operational flows.
- `Clients.txt`: The system's database, pre-loaded with **50+ test records** for immediate evaluation.
- `MyLibInput.h` *(Optional)*: Modular input library for enhanced reusability.

---

## 🚀 How to Run

### 1. Clone the repository:
```Bash
git clone [https://github.com/ali-talal-ibrahem/Bank-System-CPP.git](https://github.com/ali-talal-ibrahem/Bank-System-CPP.git)
```

### 2. Compile:
Use any C++ compiler (e.g., g++):

```Bash
g++ Main.cpp -o BankSystem
```

### 3. Execute:
Run the generated file and ensure Clients.txt is in the same directory:

```Bash
./BankSystem
```

# 📝 Final Note & Future Aspirations

## This project marks a significant milestone in my journey toward mastering Software Engineering. While the current version provides a solid core for banking operations, my vision for the future of this system includes:

Database Integration: Transitioning from flat-file storage to SQL for enhanced data relational management.

Security Layers: Implementing advanced encryption for PIN codes and sensitive user data.

Graphical User Interface (GUI): Evolving from a console-based app to a modern desktop application using Qt or SFML.

Network Capabilities: Adding multi-user support with a client-server architecture.

"Coding is not just about writing lines of code; it's about building solutions that endure."

Best Regards, Ali Talal Ibrahem 📅 February 23, 2026
