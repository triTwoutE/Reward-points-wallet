#ifndef user_h_
#define user_h_h
#include <bits/stdc++.h>

using namespace std;

string hashstring (string);
bool checkusername(string);
bool checkpassword(string);
bool checkemail(string);
void createuser();

class user {
    private:
        string username, passwordHash, fullname, email, walletID;
    public:
        user();
        user(string, string, string);
        void save ();
        void login();


};
#endif