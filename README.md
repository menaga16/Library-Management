# Library Management System (LMS)

The **Library Management System (LMS)** is a simple yet effective C++ application designed to handle the core operations of a library. This system helps manage library books, user registration and login, book borrowing and returning, and fine calculation for overdue books.

---

## Key Features

### 1. User Authentication
- Allows **user registration** and **login** for both **regular users** and an **admin**.
- Provides role-based access, ensuring admins have exclusive privileges to manage books.

### 2. Book Management
- **Admins**:
  - Add new books to the system.
  - Maintain the library's catalog.
- **Users**:
  - Search for books by title or author.
  - Borrow and return books seamlessly.

### 3. Fine Calculation
- Implements an automated fine calculation system for overdue books:
  - A standard borrowing period of **14 days** is allowed.
  - Overdue returns are charged a fine based on the number of late days.

### 4. Persistent Storage
- Stores:
  - **Book data**: All details of books in the library.
  - **User data**: User information, including borrowed books and return status.
- Uses text files to retain data between application sessions.

---

## Getting Started

### Prerequisites
- A **C++ compiler** such as GCC.
- Basic knowledge of how to run C++ programs in your preferred environment.

### Installation
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/your-username/library-management-system.git
   cd library-management-system
