# 🏦 Bank Management System (Core Engine)

A robust, **console-based** Bank Management System developed in **C++**. This project focuses on high-quality code architecture, efficient file handling, and a professional user interface. It is designed to simulate real-world banking operations with a focus on **data integrity** and **"Clean Code"** principles.

---

## 🌟 Key Features

- **🔐 Secure Authentication**: Integrated **Login System** that validates credentials against the user database before granting access.
- **🛡️ Admin & User Protection**: Advanced UI constraints to prevent the deletion or modification of the **"Admin"** account, ensuring system stability.
- **👥 User Management**: A dedicated **Manage Users** dashboard for creating, updating, and deleting system operators with specific permissions.
- **📂 Structured Data Architecture**: Organized file system with a dedicated `File_Database/` directory for better project scalability.
- **Comprehensive Client Management**: Full **CRUD** operations (Create, Read, Update, Delete).
- **Transaction Engine**: Secure Deposit and Withdrawal operations with **real-time balance validation**.
- **Data Persistence**: Flat-file database system (`.txt`) using custom delimiters for structured data storage.
- **Total Liquidity Overview**: A dedicated dashboard to monitor the bank's total assets and individual balances.
- **Advanced Data Parsing**: Custom-built string manipulation and splitting logic for efficient data retrieval.
- **Professional UI/UX**: Well-organized console menus with **input validation** to prevent system crashes.

---

## 🛠 Technical Highlights

- **Clean Code Principles**: Adheres to **DRY** (Don't Repeat Yourself) and high modularity.
- **Defense in Depth**: Implemented validation loops in both UI and Logic layers to prevent unauthorized data manipulation.
- **Memory Management**: Uses `std::vector` and `structs` for efficient in-memory data handling.
- **Input Shielding**: Implemented `cin >> ws` and custom validation to ensure robust user input handling.
- **Formatted Reporting**: Utilizes `std::setw` and `std::left/right` for clean, tabular data presentation.

---

## 📂 Project Structure

- `Main.cpp`: The central engine containing the `Login`, `Start`, and `Menu` systems.
- `File_Database/`: Dedicated folder for persistence:
    - `Clients.txt`: Stores client profiles, PINs, and balances.
    - `Users.txt`: Stores system operator credentials and permission levels.
- `README.md`: Project documentation and roadmap.

---

## 🚀 How to Run

### 1. Clone the repository:
```Bash
git clone https://github.com/ali-talal-ibrahem/Bank-System-CPP.git
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

# 📝 Concluding Note and Future Aspirations

## This project marks a significant milestone in my journey toward mastering software engineering. Its recent evolution—transforming from a simple client management tool into a secure, multi-user system—reflects my growing proficiency in grasping the concepts of systems engineering and information security.

User permissions will be refined and fully implemented in an upcoming update.

##🔭 My Vision for the Future:
Database Integration: Transitioning from a flat-file storage approach to utilizing SQL databases (specifically MySQL/PostgreSQL).

Advanced Permissions: Implementing a precise and granular Access Control List , leveraging permissions to define specific user privileges.

"Programming is not merely about writing lines of code; it is about building solutions that are both enduring and secure."

Best regards, Ali Talal Ibrahem | 📅 Last Updated: April 4, 2026
