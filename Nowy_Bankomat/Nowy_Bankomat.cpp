#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Class representing an ATM user
class User {
public:
    string name;
    string pin;
    double balance;

    User(const string& n, const string& p, double b) {
        name = n;
        pin = p;
        balance = b;
    }
};

void CreateUser() {
    string name;
    string pin;

    cout << "Enter user name: ";
    cin >> name;

    cout << "Enter PIN code: ";
    cin >> pin;

    User newUser(name, pin, 0.0);

    ofstream outputFile("users.txt", ios::app);
    if (outputFile.is_open()) {
        outputFile << newUser.name << "," << newUser.pin << "," << newUser.balance << "\n";
        outputFile.close();
        cout << "User created successfully.\n";
    }
    else {
        cout << "Unable to create the user.\n";
    }
}

bool Login(User& loggedInUser) {
    string name;
    string pin;

    cout << "Enter user name: ";
    cin >> name;

    cout << "Enter PIN code: ";
    cin >> pin;

    ifstream inputFile("users.txt");
    if (inputFile.is_open()) {
        string line;
        User tempUser("", "", 0.0);

        while (getline(inputFile, line)) {
            string savedName;
            string savedPin;
            double savedBalance;
            size_t delimiterPos1 = line.find(',');
            size_t delimiterPos2 = line.find(',', delimiterPos1 + 1);

            if (delimiterPos1 != string::npos && delimiterPos2 != string::npos) {
                savedName = line.substr(0, delimiterPos1);
                savedPin = line.substr(delimiterPos1 + 1, delimiterPos2 - delimiterPos1 - 1);
                savedBalance = stod(line.substr(delimiterPos2 + 1));

                if (name == savedName && pin == savedPin) {
                    tempUser = User(savedName, savedPin, savedBalance);
                }
            }
        }

        inputFile.close();

        if (!tempUser.name.empty()) {
            loggedInUser = tempUser;
            cout << "Login successful.\n";
            return true;
        }
    }
    else {
        cout << "No users found. Please create a user first.\n";
    }

    cout << "Login failed. Please try again.\n";
    return false;
}

void DeleteUser(const string& username) {
    ifstream inputFile("users.txt");
    ofstream tempFile("temp.txt");

    if (inputFile.is_open() && tempFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            string savedName;
            string savedPin;
            double savedBalance;
            size_t delimiterPos1 = line.find(',');
            size_t delimiterPos2 = line.find(',', delimiterPos1 + 1);

            if (delimiterPos1 != string::npos && delimiterPos2 != string::npos) {
                savedName = line.substr(0, delimiterPos1);
                savedPin = line.substr(delimiterPos1 + 1, delimiterPos2 - delimiterPos1 - 1);
                savedBalance = stod(line.substr(delimiterPos2 + 1));

                if (savedName != username) {
                    tempFile << savedName << "," << savedPin << "," << savedBalance << "\n";
                }
            }
        }

        inputFile.close();
        tempFile.close();

        remove("users.txt");
        rename("temp.txt", "users.txt");

        cout << "User deleted successfully.\n";
    }
    else {
        cout << "Unable to delete the user.\n";
    }
}

void Withdraw(User& user) {
    double amount;
    cout << "Enter the amount to withdraw: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount.\n";
        return;
    }

    if (user.balance < amount) {
        cout << "Insufficient balance.\n";
        return;
    }

    user.balance -= amount;

    // Update user's balance in the file
    ifstream inputFile("users.txt");
    ofstream tempFile("temp.txt");

    if (inputFile.is_open() && tempFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            string savedName;
            string savedPin;
            double savedBalance;
            size_t delimiterPos1 = line.find(',');
            size_t delimiterPos2 = line.find(',', delimiterPos1 + 1);

            if (delimiterPos1 != string::npos && delimiterPos2 != string::npos) {
                savedName = line.substr(0, delimiterPos1);
                savedPin = line.substr(delimiterPos1 + 1, delimiterPos2 - delimiterPos1 - 1);
                savedBalance = stod(line.substr(delimiterPos2 + 1));

                if (savedName == user.name && savedPin == user.pin) {
                    tempFile << savedName << "," << savedPin << "," << user.balance << "\n";
                }
                else {
                    tempFile << line << "\n";
                }
            }
        }

        inputFile.close();
        tempFile.close();

        remove("users.txt");
        rename("temp.txt", "users.txt");

        cout << "Withdrawal successful. New balance: " << user.balance << "\n";
    }
    else {
        cout << "Unable to process the withdrawal.\n";
    }
}

void Deposit(User& user) {
    double amount;
    cout << "Enter the amount to deposit: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount.\n";
        return;
    }

    user.balance += amount;

    // Update user's balance in the file
    ifstream inputFile("users.txt");
    ofstream tempFile("temp.txt");

    if (inputFile.is_open() && tempFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            string savedName;
            string savedPin;
            double savedBalance;
            size_t delimiterPos1 = line.find(',');
            size_t delimiterPos2 = line.find(',', delimiterPos1 + 1);

            if (delimiterPos1 != string::npos && delimiterPos2 != string::npos) {
                savedName = line.substr(0, delimiterPos1);
                savedPin = line.substr(delimiterPos1 + 1, delimiterPos2 - delimiterPos1 - 1);
                savedBalance = stod(line.substr(delimiterPos2 + 1));

                if (savedName == user.name && savedPin == user.pin) {
                    tempFile << savedName << "," << savedPin << "," << user.balance << "\n";
                }
                else {
                    tempFile << line << "\n";
                }
            }
        }

        inputFile.close();
        tempFile.close();

        remove("users.txt");
        rename("temp.txt", "users.txt");

        cout << "Deposit successful. New balance: " << user.balance << "\n";
    }
    else {
        cout << "Unable to process the deposit.\n";
    }
}

void ExitProgram() {
    cout << "Goodbye\n";
    exit(0);
}

void MainMenu() {
    int choice;
    User loggedInUser("", "", 0.0);

    while (true) {
        cout << "\n=== Main Menu ===\n";
        cout << "1. Create User\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            CreateUser();
            break;
        case 2:
            if (Login(loggedInUser)) {
                bool loggedIn = true;
                while (loggedIn) {
                   
                    cout << "Hello " << loggedInUser.name << ", your balance is: " << loggedInUser.balance << "\n";
                    cout << "\n1. Withdraw\n";
                    cout << "2. Deposit\n";
                    cout << "3. Delete User\n";
                    cout << "4. Logout\n";
                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice) {
                    case 1:
                        Withdraw(loggedInUser);
                        break;
                    case 2:
                        Deposit(loggedInUser);
                        break;
                    case 3:
                        DeleteUser(loggedInUser.name);
                        loggedIn = false;
                        break;
                    case 4:
                        loggedIn = false;
                        break;
                    default:
                        cout << "Invalid choice.\n";
                        break;
                    }
                }
            }
            break;
        case 3:
            ExitProgram();
            break;
        default:
            cout << "Invalid choice.\n";
            break;
        }
    }
}

int main() {
    MainMenu();
    return 0;
}