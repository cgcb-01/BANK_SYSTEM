# 🏦 State Bank of India – Socket-Based Banking System

This is a **multithreaded C++ server application** that simulates an **automated banking system** for the *State Bank of India*. It supports real-time client connections, account access, balance checks, transaction history, and secure data file handling using CSV-based storage. The server broadcasts its availability over UDP and accepts multiple TCP connections for concurrent clients.

---

## 📌 Features

- 📡 **UDP Broadcasting** to advertise server IP and port
- 🔐 **TCP Server for Client Connections**
- 📂 **File Handling** (Read, Write, Update CSV files)
- 📱 **Phone Number Validation** before login
- 👤 **User Authentication** via Linked Mobile Number
- 📊 **Account Features (Planned/Partial)**
  - Account Details
  - Send Money
  - Check Balance
  - Transaction History
- 🧵 **Multithreaded Handling** of multiple clients
- 📋 **CSV-safe I/O formatting** for file operations

---

## ⚙️ Technologies Used

- **C++ STL**
- **POSIX Sockets (TCP & UDP)**
- **Multithreading (`std::thread`)**
- **File I/O with CSV formatting**
- **Linux system calls (UNIX sockets)**

---

## 📁 Project Structure

```plaintext
|-- main.cpp                # Entry point – socket setup and client handling
|-- data/
|   |-- users.csv           # Example user data storage (to be created)
|   |-- transactions.csv    # Example transaction history (planned)
|-- README.md               # Project documentation
```
---
# 🚀 How It Works
UDP Broadcast: Server announces its IP and TCP port (8050) on port 9000.

TCP Connection: Clients connect via TCP and are prompted to enter their linked phone number.

Validation: Phone number is verified for correctness and existence in the user database (CSV).

Client Menu (Planned): After successful verification, users can:

View account details

Transfer funds

Check balance

View transaction history

# ✅ To-Do / In Progress
 Complete accountDetails(), sendmoney(), checkBalance(), transactionHistory() functions

 Implement searchUser() to retrieve account based on phone number

 Create robust error handling and validation

 Encrypt sensitive data (future improvement)

 Develop a client-side app (optional)

 Unit tests and logging

# 🔧 Build & Run
## Prerequisites
Linux OS (for socket support)

C++11 or later

g++
### compile server
```
g++ -std=c++11 -pthread main.cpp -o bank_server
```
### Run Server
```
./bank_server
```

# 📝 Notes
Ensure you have the data files like users.csv in the working directory.

This is a work in progress project and intended for academic or prototype use.

Use CTRL+C to exit the server gracefully.
