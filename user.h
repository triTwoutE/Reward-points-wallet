#ifndef user_h_
#define user_h_h
#include <bits/stdc++.h>
#include <fstream> //FILE
#include <ctime> //TIME
#include <sstream> //string

using namespace std;

class user {
    private:
        string username, passwordHash, fullname, email, walletID;
    public:
        user();
        void save();
        void setfullname();
        void setemail();
        void setusername();
        void setpwd();
        void setwalletID();

};

string hashstring (string);
bool checkusername(string);
bool checkpassword(string);
bool checkemail(string);
void createuser();
void backupdata();
int search_username(string,string);
void login();

#endif