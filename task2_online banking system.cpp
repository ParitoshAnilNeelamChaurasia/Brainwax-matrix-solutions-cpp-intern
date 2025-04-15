#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Account {
public:
    string name;
    int accountNumber;
    int pin;
    double balance;

    Account(string n, int accNo, int p, double b) {
        name = n;
        accountNumber = accNo;
        pin = p;
        balance = b;
    }

    void showDetails() {
        cout << "\nAccount Holder: " << name;
        cout << "\nAccount Number: " << accountNumber;
        cout << "\nBalance: ₹" << balance << "\n";
    }
};

class BankSystem {
private:
    vector<Account> accounts;
    int accCounter = 1001;

    Account* findAccount(int accNo) {
        for (auto &acc : accounts) {
            if (acc.accountNumber == accNo) return &acc;
        }
        return nullptr;
    }

public:
    void createAccount() {
        string name;
        int pin;
        double deposit;

        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Set a 4-digit PIN: ";
        cin >> pin;
        cout << "Initial deposit amount: ₹";
        cin >> deposit;

        accounts.emplace_back(name, accCounter, pin, deposit);
        cout << "Account created successfully! Your Account Number is " << accCounter << "\n";
        accCounter++;
    }

    void login() {
        int accNo, pin;
        cout << "\nEnter Account Number: ";
        cin >> accNo;
        cout << "Enter PIN: ";
        cin >> pin;

        Account* acc = findAccount(accNo);
        if (acc && acc->pin == pin) {
            cout << "Login successful!\n";
            userMenu(acc);
        } else {
            cout << "Invalid account number or PIN.\n";
        }
    }

    void userMenu(Account* acc) {
        int choice;
        do {
            cout << "\n--- Online Banking Menu ---\n";
            cout << "1. Check Balance\n2. Deposit\n3. Withdraw\n4. Transfer\n5. Account Info\n6. Logout\nChoose: ";
            cin >> choice;

            switch (choice) {
                case 1: cout << "Balance: ₹" << acc->balance << "\n"; break;
                case 2: deposit(acc); break;
                case 3: withdraw(acc); break;
                case 4: transfer(acc); break;
                case 5: acc->showDetails(); break;
                case 6: cout << "Logging out...\n"; break;
                default: cout << "Invalid option.\n";
            }
        } while (choice != 6);
    }

    void deposit(Account* acc) {
        double amount;
        cout << "Enter deposit amount: ₹";
        cin >> amount;
        if (amount > 0) {
            acc->balance += amount;
            cout << "Deposited ₹" << amount << "\n";
        } else {
            cout << "Invalid amount.\n";
        }
    }

    void withdraw(Account* acc) {
        double amount;
        cout << "Enter withdrawal amount: ₹";
        cin >> amount;
        if (amount > 0 && amount <= acc->balance) {
            acc->balance -= amount;
            cout << "Withdrew ₹" << amount << "\n";
        } else {
            cout << "Insufficient balance or invalid amount.\n";
        }
    }

    void transfer(Account* sender) {
        int targetAccNo;
        double amount;
        cout << "Enter target account number: ";
        cin >> targetAccNo;
        cout << "Enter amount to transfer: ₹";
        cin >> amount;

        Account* receiver = findAccount(targetAccNo);
        if (!receiver) {
            cout << "Target account not found.\n";
            return;
        }

        if (amount > 0 && sender->balance >= amount) {
            sender->balance -= amount;
            receiver->balance += amount;
            cout << "Transferred ₹" << amount << " to account " << receiver->accountNumber << "\n";
        } else {
            cout << "Transfer failed. Check balance or amount.\n";
        }
    }
};

int main() {
    BankSystem bank;
    int choice;

    do {
        cout << "\n====== Online Banking System ======\n";
        cout << "1. Create Account\n2. Login\n3. Exit\nChoose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: bank.createAccount(); break;
            case 2: bank.login(); break;
            case 3: cout << "Thank you for using our banking system!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 3);

    return 0;
}
