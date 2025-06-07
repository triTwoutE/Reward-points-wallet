#ifndef user_h_
#define user_h_

#include <bits/stdc++.h>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

class user {
private:
    string username, passwordHash, fullname, email, walletID;

public:
    string role = "user";

    // Constructor
    user();

    // Setters
    void setfullname();
    void setfullname(string);
    void setemail();
    void setemail(string);
    void setusername();
    void setusername(string);
    void setpwd();
    void setwalletID(string);
    void setwalletID_direct(string);
    void setrole();             // nhập từ người dùng
    void setrole(string);       // gán trực tiếp

    // Getters
    string getusername() const { return username; }
    string getrole() const { return role; }

    // Core methods
    void save();
    void updateUserInfo();
    void listAllUsers();
};

// Global functions
string hashstring(string);
bool checkusername(string);
bool checkpassword(string);
bool login(user &currentUser);
void backupdata();
int search_username(string, string);

#endif
