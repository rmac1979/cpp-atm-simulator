/*
Author: Ryan McCamy
Assignment: ATM Simulator
Description: Program simulates an ATM*/

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Function prototypes
void displayMenu();
bool authenticate();
double checkBalance(double balance);
void deposit(double &balance, double amount, vector<string> &history);
void withdraw(double &balance, double amount, vector<string> &history, double &dailyLimit);
void displayHistory(const vector<string> &history);

int main() {
    double balance = 1000.00;  // Default balance
    double dailyLimit = 500.00;  // Daily withdrawal limit
    vector<string> history;  // Transaction history
    
    if (!authenticate()) {
        cout << "Too many failed attempts. Exiting...\n";
        return 1;
    }

    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number between 1 and 5.\n";
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Your balance is: $" << checkBalance(balance) << endl;
                break;
            case 2: {
                double amount;
                cout << "Enter deposit amount: $";
                cin >> amount;
                deposit(balance, amount, history);
                break;
            }
            case 3: {
                double amount;
                cout << "Enter withdrawal amount: $";
                cin >> amount;
                withdraw(balance, amount, history, dailyLimit);
                break;
            }
            case 4:
                displayHistory(history);
                break;
            case 5:
                cout << "Thank you for using the ATM. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please select a valid option.\n";
        }
    } while (choice != 5);

    return 0;
}

// Function to display ATM menu
void displayMenu() {
    cout << "\n===== ATM Menu =====\n";
    cout << "1. Check Balance\n";
    cout << "2. Deposit Money\n";
    cout << "3. Withdraw Money\n";
    cout << "4. View Transaction History\n";
    cout << "5. Exit\n";
}

// Function for PIN authentication
bool authenticate() {
    const int PIN = 1234;
    int attempts = 0, enteredPin;
    
    while (attempts < 3) {
        cout << "Enter your 4-digit PIN: ";
        cin >> enteredPin;
        
        if (enteredPin == PIN) {
            cout << "Authentication successful!\n";
            return true;
        } else {
            cout << "Incorrect PIN. Try again.\n";
            attempts++;
        }
    }
    
    return false;
}

// Function to check balance
double checkBalance(double balance) {
    return balance;
}

// Function to deposit money
void deposit(double &balance, double amount, vector<string> &history) {
    if (amount > 0) {
        balance += amount;
        history.push_back("Deposited: $" + to_string(amount));
        cout << "Deposit successful! New balance: $" << balance << endl;
    } else {
        cout << "Invalid deposit amount.\n";
    }
}

// Function to withdraw money
void withdraw(double &balance, double amount, vector<string> &history, double &dailyLimit) {
    if (amount <= 0) {
        cout << "Invalid withdrawal amount.\n";
    } else if (amount > balance) {
        cout << "Insufficient funds.\n";
    } else if (amount > dailyLimit) {
        cout << "Withdrawal amount exceeds daily limit of $" << dailyLimit << ".\n";
    } else {
        balance -= amount;
        dailyLimit -= amount;
        history.push_back("Withdrew: $" + to_string(amount));
        cout << "Withdrawal successful! New balance: $" << balance << endl;
    }
}

// Function to display transaction history
void displayHistory(const vector<string> &history) {
    if (history.empty()) {
        cout << "No transactions recorded.\n";
    } else {
        cout << "Transaction History:\n";
        for (const auto &transaction : history) {
            cout << "- " << transaction << endl;
        }
    }
}
