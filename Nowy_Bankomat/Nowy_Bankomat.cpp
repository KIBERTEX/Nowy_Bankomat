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

    User(const string& n, const string& p) {
        name = n;
        pin = p;
    }

};


// Function for the menu with choices.
// Needs to have "Create User", "Login", "Exit".
// All of which need to be seperate functions that will be run in a Switch case statement.

void CreateUser() {
    string name;
    string pin;

    cout << "Enter user name: ";
        cin >> name;

    cout << "Enter PIN code: ";
        cin >> pin;

        User newUser(name, pin);

        //balance = 0.0;

        ofstream outputFile("users.txt", ios::app);
        if (outputFile.is_open()) {
            outputFile << newUser.name << "," << newUser.pin << "," << "0" << "\n";
            outputFile.close();
            cout << "User created successfully.\n";

        }
        else {
            cout << "Unable to create the user.\n";
        }
            
}

bool Login() {
    string name;
    string pin;

    bool loginSuccessful = false;

    cout << "Enter user name: ";
    cin >> name;

    cout << "Enter PIN code: ";
    cin >> pin;

    ifstream inputFile("users.txt");
    if (inputFile.is_open()) {
        string line;

        while (getline(inputFile, line)) {
            string savedName;
            string savedPin;
            size_t delimiterPos = line.find(',');

            if (delimiterPos != string::npos) {
                savedName = line.substr(0, delimiterPos);
                savedPin = line.substr(delimiterPos + 1, 4);

                if (name == savedName && pin == savedPin) {
                    inputFile.close();
                    return true;
                }
            }
        }

        inputFile.close();
    } else {
       cout << " No users found. Please create a user first.\n \n";
    }

    return false;
}

void ExitProgram() {
    cout << "Goodbye\n";
    exit(0);
}

int main() {
    int choice;
    bool isLoggedIn = false;

    while (true) {

        if (isLoggedIn == false) {
            cout << "\n=== Main Menu ===\n";
            cout << "1. Create User\n";
            cout << "2. Login\n";
            cout << "3. Exit\n";
            cout << "Select an option: ";
            cin >> choice;

            switch (choice) {
            case 1:
                CreateUser();
                break;
            case 2:
                if (Login()) {
                    isLoggedIn = true;
                    cout << "Login succsessful.\n";
                } else {
                    cout << "Login failed. Please try again.\n";
                }
                break;
            case 3:
                ExitProgram();
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
        else {
            string userName = "Diana";
            double balance = 100.0;

            switch (choice) {
                cout << "\n=== Menu ===\n";
                cout << "Hello ", userName, "your balance is: ", balance, "\n";
                cout << "1. Withdraw\n";
                cout << "2. Insert\n";
                cout << "3. Log out\n";
                cout << "Select an option: ";
                cin >> choice;
            }
        }

    }
    return 0;
}

// Function to create a new user and save the user in users.txt
// If users.txt does not exist create one.
// Needs to happen in the same function

// Function to login user.
// Checks the user input variables for user name and password/pin code and compares them to find any similarity in the users.txt file
// If yes then show a simple string of "Login successfull" otherwise show an error and prompt the user to try login again.
// Hint: While loop would be good here.

// Function to exit program.