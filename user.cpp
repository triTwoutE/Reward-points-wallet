#include <bits/stdc++.h>
#include "user.h"
#include <fstream>

using namespace std;

//Constructor:
user :: user(){
    //Set Fullname
    cout << "Fullname: ";
    getline(cin,fullname);
    //Set Email:
    cout << "Email: ";
    getline(cin,email);
    /* string mail;
    while(true){
        cout << "Email: ";
        getline(cin,mail);
        if (checkemail(mail)) {
            email = mail;
            break;
        }
        cout << "Email not valid. Press any key and try again!";
        getchar();
    } */
    //Set Username;
    while(true){
        cout << "Username (just contain lowcase character and num): ";
        getline(cin,username);
        if (checkusername(username)) break;
        cout << "Username not valid. Press Enter and try again!";
        getchar();
    }
    //Set password
    string pwd;
    while(true){
        cout << "Password (8 digit not contain space): ";
        getline(cin,pwd);
        if (checkpassword(pwd)) break;
        else {
            cout << "Password not valid. Press Enter and try again!";
            getchar();
        }
    }
    this->passwordHash = hashstring(pwd);


}


//Function:
string hashstring(string s){
    return "Hash" + s;  //Tamthoi
}

bool checkusername(string s){
    for (char x:s){
        if ((x >= 97 && x <= 126) || (x >= 48 && x <= 57)) continue;
        else return false;
    }
    return true;
}

bool checkpassword(string s){
    for (char x:s){
        if ((x >= 97 && x <= 126) || (x >= 48 && x <=57)) continue;
        else return false;
    }
    return true;
}

// bool checkemail(string s){
//     for (char x:s) {
//         if (/* (x >= 97 && x <= 126) || (x >= 48 && x <=57) || */ 
//         (x == 64)/*@*/ || (x == 46) /*dot(.)*/)
//             continue;
//         else return false;
//         return true;
//     }
// }

void user::save (){
    fstream savefile("userdata.txt",ios::out | ios::app);
    savefile << fullname << "|" << email 
    << "|" << username << "|" << passwordHash << endl;
    savefile.close();

}

void login(){}
