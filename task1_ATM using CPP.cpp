#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class ATM {
private:
    string userID = "paritosh";
    int pin = 1234;
    double balance = 10000.0;
    string accountHolder = "Paritosh Chaurasia";
    string accountNumber = "1234567890";

    vector<string> transactions;

    void addTransaction(const string& type, double amount) {
        time_t now = time(0);
        string timeStr = ctime(&now);
        timeStr.pop_back(); // remove trailing newline
        string record = type + ": ₹" + to_string(amount) + " on " + timeStr;
        if (transactions.size() == 5) {
            transactions.erase(transactions.begin()); // keep only last 5
        }
        transactions.push_back(record);
    }

public:
    bool login() {
        string inputID;
        int inputPIN;
        int attempts = 0;

        while (attempts < 3) {
            cout << "Enter User ID: ";
            cin >> inputID;
            cout << "Enter PIN: ";
            cin >> inputPIN;

            if (inputID == userID && inputPIN == pin) {
                cout << "\nLogin Successful!\n\n";
                return true;
            } else {
                cout << "Invalid credentials. Try again.\n";
                attempts++;
            }
        }
        cout << "Too many failed attempts. Exiting...\n";
        return false;
    }

    void showMenu() {
        int choice;
        do {
            cout << "\n===== ATM Menu =====\n";
            cout << "1. Check Balance\n";
            cout << "2. Deposit\n";
            cout << "3. Withdraw\n";
            cout << "4. Change PIN\n";
            cout << "5. Mini Statement\n";
            cout << "6. Account Info\n";
            cout << "7. Logout\n";
            cout << "Choose an option: ";
            cin >> choice;

            switch (choice) {
                case 1: checkBalance(); break;
                case 2: deposit(); break;
                case 3: withdraw(); break;
                case 4: changePIN(); break;
                case 5: miniStatement(); break;
                case 6: showAccountInfo(); break;
                case 7: cout << "Logging out...\n"; break;
                default: cout << "Invalid option. Try again.\n";
            }

        } while (choice != 7);
    }

    void checkBalance() {
        cout << "Your current balance is ₹" << balance << endl;
    }

    void deposit() {
        double amount;
        cout << "Enter amount to deposit: ₹";
        cin >> amount;
        if (amount > 0) {
            balance += amount;
            addTransaction("Deposit", amount);
            cout << "₹" << amount << " deposited successfully.\n";
        } else {
            cout << "Invalid deposit amount.\n";
        }
    }

    void withdraw() {
        double amount;
        cout << "Enter amount to withdraw: ₹";
        cin >> amount;
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            addTransaction("Withdrawal", amount);
            cout << "₹" << amount << " withdrawn successfully.\n";
        } else {
            cout << "Invalid or insufficient balance.\n";
        }
    }

    void changePIN() {
        int oldPIN, newPIN;
        cout << "Enter current PIN: ";
        cin >> oldPIN;

        if (oldPIN == pin) {
            cout << "Enter new PIN: ";
            cin >> newPIN;
            pin = newPIN;
            cout << "PIN changed successfully.\n";
        } else {
            cout << "Incorrect current PIN.\n";
        }
    }

    void miniStatement() {
        cout << "\n=== Mini Statement ===\n";
        if (transactions.empty()) {
            cout << "No transactions yet.\n";
        } else {
            for (const string& t : transactions) {
                cout << t << endl;
            }
        }
    }

    void showAccountInfo() {
        cout << "\n=== Account Information ===\n";
        cout << "Name: " << accountHolder << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Current Balance: ₹" << balance << endl;
    }
};

int main() {
    ATM atm;
    while (true) {
        if (atm.login()) {
            atm.showMenu();
        }
        char again;
        cout << "Would you like to login again? (y/n): ";
        cin >> again;
        if (again != 'y' && again != 'Y') {
            cout << "Exiting system. Have a great day!\n";
            break;
        }
    }
    return 0;
}
