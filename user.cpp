#include "user.h"

using namespace std;

//Constructor:
user :: user(){
    //Set Fullname
    setfullname();
    //Set Email:
    setemail();
    //Set Username;
    setusername();
    //Set password
    setpwd();
}

void user::save (){
    string sf = "userdata.txt";
    while (search_username(username,sf) > 0){
        cout << "That username is taken. Try another!" << endl;
        this->setusername();
        this->setpwd();
    }    
        fstream savefile(sf,ios::out | ios::app);
        savefile << username << "|" << passwordHash << "|" << fullname << "|" << email  
        << "|" << walletID << endl;
        savefile.close();
    }

void user::setfullname(){
    //Set Fullname
    cout << "Fullname: ";
    getline(cin,fullname);
}

void user::setemail(){
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
}

void user::setusername(){
    //Set Username;
    while(true){
        cout << "Username (just contain lowcase character and num): ";
        getline(cin,username);
        if (checkusername(username)) break;
        cout << "Username not valid. Press Enter and try again!";
        getchar();
    }
}

void user::setpwd(){
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

void setwalletID(){

};

//Function
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




void backupdata(){
    ifstream datafile("userdata.txt",ios::binary);
    if (!datafile) cerr << "Can't find data file to back up";
    time_t timestamp = time(NULL);
    time(&timestamp);
    struct tm currenttime = *localtime(&timestamp);
    char thoigian[50];
    strftime(thoigian, 50, "%y_%b_%d_%I_%M_%p",&currenttime);
    string tg = thoigian;
    string out = "backup/" + tg + ".txt";
    ofstream backupfile(out, ios::binary);
    backupfile << datafile.rdbuf();
    
}


int search_username(string usernamecheck,string sf){
    fstream datafile(sf,ios::in);
    int row = 1;
    string line;
    while (getline(datafile,line)){
        stringstream ss(line);
        string username;
        getline(ss, username, '|');
        if (usernamecheck == username) return row;
        row++;
    }
    return 0;

}

void login(){

}


