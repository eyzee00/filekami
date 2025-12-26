# Filekami

A modular C project and static library designed for advanced file manipulation, featuring a router-based architecture and dynamic memory management.

## Overview
Filekami implements a centralized control flow where `main.c` acts as a router, dispatching user requests to specific handler functions. The core operational logic is encapsulated within a static library (`libfilekami.a`), allowing for clean, efficient, and reusable code.

## Key Features
* **Modular Architecture:** Clear separation of concerns between the entry point, handlers, and operating functions.
* **Static Library:** Logic compiled into `libfilekami.a` for global system accessibility.
* **Advanced Operations:** Includes algorithms for complex tasks, such as alphabetical line sorting using QuickSort (`subject6.c`).
* **Dynamic Memory:** Optimized use of `getline`, `malloc`, and `realloc` to handle variable file sizes.
* **Centralized Header:** `files.h` manages all prototypes, constants, and include guards.

## Installation
To build the library and install it to your system's standard paths:

1. **Compile Object Files:**
    gcc -c subject*.c

2. **Create Static Library:**
    ar rcs libfilekami.a subject*.o

3. **Install Headers and Library:**
    sudo cp files.h /usr/local/include/
    sudo cp libfilekami.a /usr/local/lib/

## Usage
Once installed, you can compile the project without referencing individual source files or full paths:

    gcc main.c subjecthandlers.c -o filekami -lfilekami 

*Note: The linker automatically resolves `libfilekami.a` and `files.h` from the standard system directories.*

## Project Structure
* `main.c`: Entry point, handles user menu and routing.
* `subjecthandlers.c`: Implementation of the subject handler/router functions, the linking point between the operating functions and the `main.c` file.
* `files.h`: Central header file (prototypes, macros, structs).
* `subject[1-6].c`: Implementation of specific file operations (filtering, sorting, processing).

## Acknowledgments
Special thanks to my instructor for the encouragement to expand the project scope beyond a single subject, allowing for a deeper exploration of C file handling and modular design.
