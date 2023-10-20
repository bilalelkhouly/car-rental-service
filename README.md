# Car Rental System in C

## Introduction
This C program is a simple car rental system that allows you to perform various transactions related to renting and managing cars. It includes functionalities for adding new cars to the available-for-rent list, adding returned cars to either the available-for-rent list or the repair list, transferring a car from the repair list to the available-for-rent list, renting the first available car, printing the lists, and quitting the program. The system also calculates income based on mileage when cars are returned.

## Features
- **Add New Car to Available List (Transaction Code 1):** You can add a new car to the list of cars available for rent. The program prompts you to enter the plate number (up to 7 characters or numbers) and the car's mileage.

- **Add Returned Car to Available List (Transaction Code 2):** You can add a car that has been returned to the available-for-rent list. The program calculates the charge based on the mileage driven and removes the car from the rented list.

- **Add Returned Car to Repair List (Transaction Code 3):** If a returned car requires maintenance, you can add it to the repair list. Like in transaction code 2, the program calculates the charge and removes the car from the rented list.

- **Transfer Car from Repair List to Available List (Transaction Code 4):** If a car in the repair list is ready for rent, you can transfer it to the available-for-rent list.

- **Rent the First Available Car (Transaction Code 5):** You can rent the first available car, and the program will prompt you to enter the expected return date (in YYMMDD format).

- **Print All Lists (Transaction Code 6):** This option allows you to print the available-for-rent, rented, and repair lists to see the current status of the cars.

- **Quitting the Program (Transaction Code 7):** When you decide to quit the program, it will save the updated lists to corresponding files and display the total income.

## How to Use
1. Compile the C program.
2. Run the program. It will load the car lists from existing files if they exist (e.g., `Available.txt`, `Rented.txt`, and `inRepair.txt`).

3. Choose a transaction code (1-7) based on the desired action.
4. Follow the prompts for each transaction, such as entering plate numbers, mileage, and expected return dates.
5. View the available lists by selecting Transaction Code 6.
6. Quit the program and check the total income and updated lists.

## Files
- `car_rental.c`: The main C program that manages car rental transactions.
- `Available.txt`: A file that stores the list of cars available for rent.
- `Rented.txt`: A file that stores the list of rented cars.
- `inRepair.txt`: A file that stores the list of cars under repair.
- `README.md`: This documentation file.

## Notes
- This program includes a simple mechanism to calculate charges based on mileage when a car is returned. The charges are $80 for the first 200 km and $0.15 per km for any additional distance.
- Plate numbers are limited to 7 characters or numbers.
- When adding a car, the mileage for new cars in the available list is set to 0.
- The program sorts the lists by return date for rented cars and by mileage for available and repair lists.
- The program ensures that duplicate cars with the same plate number are not added to the lists.

## Author
- Bilal Elkhouly

This car rental system was created as part of an assignment and serves as a basic example of file handling and linked list management in C. It can be further expanded and improved as needed.
