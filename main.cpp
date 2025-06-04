#include "user.h"
#include <cstdlib>

using namespace std;

void menu(){
    cout << "Please select an option from menu bellow: " << endl;
    cout << "1. Create new account" << endl;
    cout << "2. Log in"<< endl;
    cout << "q. Quit" << endl;
    cout << endl << ">";
}

void clearScreen(){
    #ifndef _Win32
        system("cls");
    #else
        system("clear");
    #endif
}

int main(){
    backupdata();
    string userinput = "";
    clearScreen();
    menu();
    getline(cin,userinput);
    while (userinput != "q" && userinput != "Q"){
        if (userinput == "1") {
            clearScreen();
            //Create new account:
            user x;
            x.save();
        }
        else if (userinput == "2"){
            //Log in:
            clearScreen();
        }
        else {
            clearScreen();
            cout << "Input not valid. Try again!";
        }
        cout << endl;
        menu();
        getline(cin,userinput);

    }
    
    return 0;
}