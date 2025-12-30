Arbitrary Precision Calculator (APC) 

📌 Description
This project implements an Arbitrary Precision Calculator (APC) in DS, capable of performing arithmetic operations on very large integers that exceed the limits of built-in data types. The calculator represents numbers using doubly linked lists, enabling digit-by-digit operations similar to manual arithmetic.

The project supports addition, subtraction, multiplication, and division via command-line input and demonstrates strong fundamentals of data structures, pointers, and modular C programming.

⚙️ Features

Supports arbitrarily large integers

Operations supported:

Addition (+)

Subtraction (-)

Multiplication (* or x)

Division (/)

Uses Doubly Linked Lists for digit storage

Handles carry and borrow logic correctly

Sign handling for negative subtraction results

Modular, well-structured source files

Command-line based interface

🛠 Technologies Used

Language: C

Concepts:

Doubly Linked Lists

Dynamic Memory Allocation

Pointers & Structures

Command-line Arguments

Modular Programming

Platform: Linux

Compiler: GCC

📂 Project Structure

APC_Project_Shubham/
├── apc.h                 # Header file with structures & prototypes
├── main.c                # Main driver program
├── addition.c            # Addition logic
├── subtraction.c         # Subtraction logic
├── multiplication.c      # Multiplication logic
├── division.c            # Division logic
├── digit_to_list.c       # Convert input numbers to linked lists
├── list_operations.c     # Insert, delete, print list functions
└── README.md             # Project documentation


▶️ Usage

Compile the project
gcc *.c -o apc

Run the program
./apc <number1> <operator> <number2>

Examples
./apc 123456789123456789 + 987654321987654321
./apc 1000000000000 - 999999999999
./apc 12345 x 6789
./apc 1000000 / 25


📚 Learning Outcomes

Understanding arbitrary precision arithmetic

Implementing arithmetic operations using linked lists

Handling carry, borrow, and digit-wise computation

Working with command-line arguments

Memory management using dynamic allocation

Writing clean, modular, and maintainable C code

🚧 Limitations

Works only with non-floating (integer) numbers

No optimization for extremely large multiplication/division

Division uses basic logic (not optimized like long division)

Designed for educational purposes

👨‍💻 Author

Shubham Shinde
Embedded Systems & C Programmer

📜 License

This project is open-source and intended for educational and learning purposes.
