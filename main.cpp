#include "user.h"
#include <cstdlib>

using namespace std;

void menu(const user& currentUser) {
    cout << "\n===== MAIN MENU =====\n";
    cout << "1. Create new account (self-registration)\n";
    cout << "2. Log in\n";
    if (currentUser.getrole() == "admin") {
        cout << "3. Create account for someone else (admin only)\n";
        cout << "4. Update user info for someone else (admin only)\n";
        cout << "5. View all users\n";
    }
    cout << "q. Quit\n> ";
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    backupdata();

    user currentUser;
    string userinput = "";
    clearScreen();
    menu(currentUser);
    getline(cin, userinput);

    while (userinput != "q" && userinput != "Q") {
        clearScreen();

        if (userinput == "1") {
            cout << "\n=== Self Registration ===\n";
            user newUser;
            newUser.setfullname();
            newUser.setemail();
            newUser.setusername();
            newUser.setpwd();
            newUser.setwalletID("user" + to_string(time(NULL)));
            newUser.setrole("user"); // luôn là user
            newUser.save();
        } else if (userinput == "2") {
            cout << "\n=== Login ===\n";
            if (login(currentUser)) {
                cout << "Logged in successfully as: " << currentUser.getusername()
                     << " (" << currentUser.getrole() << ")\n";
            } else {
                cout << "Login failed. Try again.\n";
            }
        } else if (userinput == "3" && currentUser.getrole() == "admin") {
            cout << "\n=== Create Account for Another User ===\n";
            user newUser;
            newUser.setfullname();
            newUser.setemail();
            newUser.setusername();
            newUser.setpwd();
            newUser.setwalletID("user" + to_string(time(NULL)));
            newUser.setrole();  // cho phép chọn admin/user
            newUser.save();
        } else if (userinput == "4" && currentUser.getrole() == "admin") {
            cout << "\n=== Update User Info (Admin Input) ===\n";
            currentUser.updateUserInfo();
        } else if (userinput == "5" && currentUser.getrole() == "admin") {
            currentUser.listAllUsers();
        } else {
            cout << "Invalid option or insufficient permission.\n";
        }

        cout << endl;
        menu(currentUser);
        getline(cin, userinput);
    }

    return 0;
}
