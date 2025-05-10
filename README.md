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
