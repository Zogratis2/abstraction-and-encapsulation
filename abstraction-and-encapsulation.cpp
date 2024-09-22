#include <iostream>
#include <string>
#include <limits>  
#include <algorithm>  

using namespace std;

// Function to convert a string to uppercase
string to_upper(const string& str) {
    string upperStr = str;
    transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
    return upperStr;
}

// Function to convert a string to lowercase
string to_lower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

class Account {
private:
    string Name;
    double Money;

protected:
    Account(string accName, double accMoney) : Name(accName), Money(accMoney) {}

public:
    virtual void calculateSavings() = 0;

    string getName() const {
        return Name;
    }

    double getMoney() const {
        return Money;
    }

    void setMoney(double accMoney) {
        if (accMoney >= 0) {
            Money = accMoney;
        }
    }

    void deposit(double amount) {
        if (amount > 0) {
            Money += amount;
            cout << "Deposit successful! New balance: $" << Money << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    virtual bool withdraw(double amount) = 0;  
};

class SavingsAccount : public Account {
public:
    SavingsAccount(string name, double money) : Account(name, money) {}

    void calculateSavings() override {
        double bonus = getMoney() * 1.0;
        cout << "Savings Account of " << getName() << " with a money of: $" << bonus << endl;
    }

    bool withdraw(double amount) override {
        if (amount > 0 && (getMoney() - amount) >= 1000) {  
            setMoney(getMoney() - amount);
            cout << "Withdrawal successful! New balance: $" << getMoney() << endl;
            return true;
        } else {
            cout << "Invalid amount or minimum balance not maintained (Min: $1000)." << endl;
            return false;
        }
    }
};

class CurrentAccount : public Account {
public:
    CurrentAccount(string name, double money) : Account(name, money) {}

    void calculateSavings() override {
        double bonus = getMoney() * 1.0;
        cout << "Current Account of " << getName() << " with a money of: $" << bonus << endl;
    }

    bool withdraw(double amount) override {
        if (amount > 0 && amount <= getMoney()) {
            setMoney(getMoney() - amount);
            cout << "Withdrawal successful! New balance: $" << getMoney() << endl;
            return true;
        } else {
            cout << "Invalid amount or insufficient funds!" << endl;
            return false;
        }
    }
};

// Validate input for numeric values (deposit and withdraw amounts)
double getValidAmount() {
    double amount;
    while (!(cin >> amount) || amount < 0) {
        cout << "Invalid input! Please enter a valid positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return amount;
}

void savingsMenu(SavingsAccount &acc) {
    int choice;
    do {
        cout << "\nSavings Account Sub Menu\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Check Balance\n";
        cout << "4. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Enter amount to deposit: ";
            double amount = getValidAmount();
            acc.deposit(amount);
            break;
        }
        case 2: {
            cout << "Enter amount to withdraw: ";
            double amount = getValidAmount();
            acc.withdraw(amount);
            break;
        }
        case 3:
            cout << "Current balance: $" << acc.getMoney() << endl;
            break;
        case 4:
            cout << "Returning to Main Menu...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);
}

void currentMenu(CurrentAccount &acc) {
    int choice;
    do {
        cout << "\nCurrent Account Sub Menu\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Check Balance\n";
        cout << "4. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Enter amount to deposit: ";
            double amount = getValidAmount();
            acc.deposit(amount);
            break;
        }
        case 2: {
            cout << "Enter amount to withdraw: ";
            double amount = getValidAmount();
            acc.withdraw(amount);
            break;
        }
        case 3:
            cout << "Current balance: $" << acc.getMoney() << endl;
            break;
        case 4:
            cout << "Returning to Main Menu...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);
}

int main() {
    SavingsAccount acc1("Sarah Kaibigan", 50000);
    CurrentAccount acc2("Ikaw at Ako", 30000);

    int mainChoice;
    do {
        cout << "\nMain Menu\n";
        cout << "1. Savings Account\n";
        cout << "2. Current Account\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;

        switch (mainChoice) {
        case 1:
            savingsMenu(acc1);
            break;
        case 2:
            currentMenu(acc2);
            break;
        case 3:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (mainChoice != 3);

    return 0;
}
