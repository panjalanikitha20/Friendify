# Friendify - A Terminal-Based Social Network in C

**Friendify** is a mini social networking simulation program written in the C programming language. Designed to run in the terminal, it allows users to create profiles, log in, manage their friend list, send and receive messages, and simulate basic social media interactions — all with persistent file-based storage.

This project demonstrates fundamental programming concepts such as linked lists, file I/O, dynamic memory allocation, and user-defined data structures in C.

---

##  Features

-  **User Registration**  
  Create a new profile by entering a username and password. Each profile is stored in a separate file.

-  **Login System**  
  Authenticate users using stored credentials. Only one user can be logged in at a time.

-  **Friend Management**  
  Add other registered users as friends and maintain an in-memory linked list of friends per session.

- ✉ **Messaging**  
  Send messages to other users. Messages are stored in a shared file (`messages.txt`) and can be viewed upon login.

-  **Logout Functionality**  
  Switch between users during the same session.

-  **File-Based Storage**  
  - User profiles are stored in individual text files (`<username>.txt`).
  - All messages are appended to a common file (`messages.txt`) for simplicity.

---

## 📁 Project Structure
friendify/
├── frendify.c # Main source code file
├── README.md # Project documentation (this file)

Files generated at runtime:
- `messages.txt` – Stores all sent messages.
- `<username>` – A file for each user to save their credentials.

---


