# SGPA Calculator with User Authentication

## Overview

This C program is designed to calculate the Semester Grade Point Average (SGPA) for a student's semester based on their subject grades. It includes user authentication, allowing registered users to log in and use the calculator. User data is stored in the `userdata.txt` file for future logins.

## Features

- User Registration: New users can register with unique usernames and passwords.
- User Authentication: Registered users can log in to access the SGPA calculator.
- SGPA Calculation: Users can input their personal information and subject details to calculate their SGPA.
- Progress Report: A detailed progress report is generated in `report.txt`, including personal information, subject details, total marks, and SGPA.

## Usage

1. Run the program.
2. Choose an option:
   - Login (1): Registered users can log in with their username and password.
   - Register (2): New users can register with a unique username and password.
3. If you log in successfully, input your personal information and subject details.
4. A progress report is generated in `report.txt`, displaying your SGPA.

## Notes

- Maximum of 100 users can be registered.
- Maximum username and password length is 20 characters.
- User data is stored in `userdata.txt`.
- Subject maximum marks are assumed to be 100.

## File Structure

- `sgpa_calculator.c`: The main program source code.
- `userdata.txt`: File for storing user registration data.
- `report.txt`: Generated progress report.

## Requirements

- C Compiler (GCC recommended)

## Author

shashank s dengi
uday hiremath
