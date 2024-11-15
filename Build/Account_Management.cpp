#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// Base class representing a bank account
class Account {
private:
    string accountHolder;
    double balance;
    int accountNumber;

public:
    // Constructor to initialize account with account holder's name and initial balance
    Account(string name, double initialBalance, int accNum) {
        accountHolder = name;
        balance = initialBalance;
        accountNumber = accNum;
    }

    // Getter methods
    string getAccountHolder() const {
        return accountHolder;
    }

    double getBalance() const {
        return balance;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    // Method to deposit money into the account
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "$" << amount << " deposited successfully!\n";
        } else {
            cout << "Deposit amount must be positive!\n";
        }
    }

    // Method to withdraw money from the account
    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "Withdrawal amount must be positive!\n";
            return false;
        }
        if (amount <= balance) {
            balance -= amount;
            cout << "$" << amount << " withdrawn successfully!\n";
            return true;
        } else {
            cout << "Insufficient balance!\n";
            return false;
        }
    }

    // Method to display account details
    virtual void displayAccountInfo() const {
        cout << "Account Holder: " << accountHolder << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: $" << balance << endl;
    }
};

// Derived class for savings account
class SavingsAccount : public Account {
public:
    SavingsAccount(string name, double initialBalance, int accNum)
        : Account(name, initialBalance, accNum) {}

    void displayAccountInfo() const override {
        cout << "Savings Account Details:\n";
        Account::displayAccountInfo();
    }
};

// Derived class for checking account
class CheckingAccount : public Account {
public:
    CheckingAccount(string name, double initialBalance, int accNum)
        : Account(name, initialBalance, accNum) {}

    void displayAccountInfo() const override {
        cout << "Checking Account Details:\n";
        Account::displayAccountInfo();
    }
};

// Bank class to manage multiple accounts
class Bank {
private:
    vector<Account*> accounts;  // List of accounts in the bank
    int nextAccountNumber;      // Keeps track of the next account number

public:
    Bank() : nextAccountNumber(1000) {}

    // Method to create a new account
    void createAccount() {
        string name;
        double initialBalance;
        int accountType;
        cout << "Enter account holder's name: ";
        getline(cin, name);
        cout << "Enter initial deposit amount: $";
        cin >> initialBalance;
        cout << "Choose account type:\n";
        cout << "1. Savings Account\n";
        cout << "2. Checking Account\n";
        cout << "Enter choice (1 or 2): ";
        cin >> accountType;

        // Create the account based on type
        Account* newAccount = nullptr;
        if (accountType == 1) {
            newAccount = new SavingsAccount(name, initialBalance, nextAccountNumber++);
        } else if (accountType == 2) {
            newAccount = new CheckingAccount(name, initialBalance, nextAccountNumber++);
        } else {
            cout << "Invalid account type! Account creation failed.\n";
            return;
        }

        accounts.push_back(newAccount);
        cout << "Account created successfully!\n";
        newAccount->displayAccountInfo();
    }

    // Method to display all accounts
    void displayAllAccounts() const {
        if (accounts.empty()) {
            cout << "No accounts available.\n";
            return;
        }

        for (const auto& account : accounts) {
            account->displayAccountInfo();
            cout << "-----------------------\n";
        }
    }

    // Method to find an account by account number
    Account* findAccount(int accountNumber) {
        for (auto& account : accounts) {
            if (account->getAccountNumber() == accountNumber) {
                return account;
            }
        }
        return nullptr;
    }

    // Method to deposit money into an account
    void depositMoney() {
        int accountNumber;
        double amount;
        cout << "Enter account number: ";
        cin >> accountNumber;
        Account* account = findAccount(accountNumber);

        if (account) {
            cout << "Enter amount to deposit: $";
            cin >> amount;
            account->deposit(amount);
        } else {
            cout << "Account not found!\n";
        }
    }

    // Method to withdraw money from an account
    void withdrawMoney() {
        int accountNumber;
        double amount;
        cout << "Enter account number: ";
        cin >> accountNumber;
        Account* account = findAccount(accountNumber);

        if (account) {
            cout << "Enter amount to withdraw: $";
            cin >> amount;
            account->withdraw(amount);
        } else {
            cout << "Account not found!\n";
        }
    }

    // Method to transfer money between accounts
    void transferMoney() {
        int fromAccountNumber, toAccountNumber;
        double amount;
        cout << "Enter source account number: ";
        cin >> fromAccountNumber;
        Account* fromAccount = findAccount(fromAccountNumber);

        if (!fromAccount) {
            cout << "Source account not found!\n";
            return;
        }

        cout << "Enter destination account number: ";
        cin >> toAccountNumber;
        Account* toAccount = findAccount(toAccountNumber);

        if (!toAccount) {
            cout << "Destination account not found!\n";
            return;
        }

        cout << "Enter amount to transfer: $";
        cin >> amount;
        if (fromAccount->withdraw(amount)) {
            toAccount->deposit(amount);
            cout << "$" << amount << " transferred successfully!\n";
        }
    }
};

// Main function
int main() {
    Bank bank;
    int choice;

    do {
        cout << "\nBank Account Management System\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transfer Money\n";
        cout << "5. Display All Accounts\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // To consume the newline character

        switch (choice) {
            case 1:
                bank.createAccount();
                break;
            case 2:
                bank.depositMoney();
                break;
            case 3:
                bank.withdrawMoney();
                break;
            case 4:
                bank.transferMoney();
                break;
            case 5:
                bank.displayAllAccounts();
                break;
            case 6:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
 