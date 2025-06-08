#include "user.h"

// Constructor
user::user() {}

void user::setfullname() {
    cout << "Fullname: ";
    getline(cin, fullname);
}

void user::setemail() {
    cout << "Email: ";
    getline(cin, email);
}

void user::setusername() {
    while (true) {
        cout << "Username (lowercase letters and digits only): ";
        getline(cin, username);
        if (checkusername(username)) break;
        cout << "Invalid username. Press Enter to try again.";
        getchar();
    }
}

void user::setpwd() {
    string pwd;
    while (true) {
        cout << "Password (at least 8 characters, no spaces): ";
        getline(cin, pwd);
        if (checkpassword(pwd)) break;
        cout << "Invalid password. Press Enter to try again.";
        getchar();
    }
    passwordHash = hashstring(pwd);
}

void user::setwalletID(string id) {
    walletID = id;
}

void user::setrole() {
    cout << "Role (admin/user): ";
    getline(cin, role);
    role = trim(role);
    if (role != "admin") role = "user";
}

void user::setrole(string r) {
    r = trim(r);
    if (r == "admin") role = "admin";
    else role = "user";
}

void user::setusername(string u) { username = u; }
void user::setfullname(string f) { fullname = f; }
void user::setemail(string e) { email = e; }
void user::setwalletID_direct(string id) { walletID = id; }

void user::save() {
    string sf = "userdata.txt";
    while (search_username(username, sf) > 0) {
        cout << "That username is already taken. Please try another!" << endl;
        setusername();
        setpwd();
    }
    fstream savefile(sf, ios::out | ios::app);
    savefile << username << "|" << passwordHash << "|" << fullname << "|" << email << "|" << walletID << "|" << role << endl;
    savefile.close();
}

void user::updateUserInfo() {
    cout << "Enter username of the account to update: ";
    string uname;
    getline(cin, uname);

    ifstream infile("userdata.txt");
    ofstream tempfile("temp.txt");
    string line;
    bool found = false;

    while (getline(infile, line)) {
        stringstream ss(line);
        string u, p, f, e, w, r;
        getline(ss, u, '|');
        getline(ss, p, '|');
        getline(ss, f, '|');
        getline(ss, e, '|');
        getline(ss, w, '|');
        getline(ss, r, '|');

        if (u == uname) {
            found = true;
            cout << "Current Fullname: " << f << endl;
            cout << "Current Email: " << e << endl;
            string newf, newe, newpwd;
            cout << "Enter new Fullname: ";
            getline(cin, newf);
            cout << "Enter new Email: ";
            getline(cin, newe);
            cout << "Enter new Password: ";
            getline(cin, newpwd);
            string newhash = hashstring(newpwd);
            tempfile << u << "|" << newhash << "|" << newf << "|" << newe << "|" << w << "|" << r << endl;
        } else {
            tempfile << line << endl;
        }
    }

    infile.close();
    tempfile.close();

    remove("userdata.txt");
    rename("temp.txt", "userdata.txt");

    if (found) cout << "Update complete.\n";
    else cout << "User not found.\n";
}

void user::listAllUsers() {
    ifstream infile("userdata.txt");
    string line;
    cout << left << setw(15) << "Username" << setw(25) << "Fullname" << setw(25) << "Email" << setw(10) << "Role" << endl;
    cout << string(75, '-') << endl;
    while (getline(infile, line)) {
        stringstream ss(line);
        string u, p, f, e, w, r;
        getline(ss, u, '|');
        getline(ss, p, '|');
        getline(ss, f, '|');
        getline(ss, e, '|');
        getline(ss, w, '|');
        getline(ss, r, '|');
        r = trim(r);
        cout << left << setw(15) << u << setw(25) << f << setw(25) << e << setw(10) << r << endl;
    }
    infile.close();
}

string hashstring(string s) {
    return "Hash" + s;
}

bool checkusername(string s) {
    for (char c : s) {
        if (!islower(c) && !isdigit(c)) return false;
    }
    return true;
}

bool checkpassword(string s) {
    return s.length() >= 8 && s.find(' ') == string::npos;
}

bool login(user &currentUser) {
    string u, p;
    cout << "Username: ";
    getline(cin, u);
    cout << "Password: ";
    getline(cin, p);
    string hashpwd = hashstring(p);

    ifstream infile("userdata.txt");
    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string username, password, fullname, email, wallet, role;
        getline(ss, username, '|');
        getline(ss, password, '|');
        getline(ss, fullname, '|');
        getline(ss, email, '|');
        getline(ss, wallet, '|');
        getline(ss, role, '|');

        role = trim(role);

        if (username == u && password == hashpwd) {
            currentUser.setusername(username);
            currentUser.setfullname(fullname);
            currentUser.setemail(email);
            currentUser.setwalletID_direct(wallet);
            currentUser.setrole(role);
            return true;
        }
    }
    return false;
}

void backupdata() {
    ifstream infile("userdata.txt", ios::binary);
    if (!infile) {
        cerr << "Can't find data file to back up\n";
        return;
    }
    time_t timestamp = time(NULL);
    struct tm now = *localtime(&timestamp);
    char buffer[50];
    strftime(buffer, 50, "%Y%m%d_%H%M%S", &now);
    string backupPath = "backup/" + string(buffer) + ".txt";

    ofstream outfile(backupPath, ios::binary);
    outfile << infile.rdbuf();
    infile.close();
    outfile.close();

    cout << "\u2705 Backup saved to: " << backupPath << endl;
}

int search_username(string usernamecheck, string sf) {
    fstream datafile(sf, ios::in);
    int row = 1;
    string line;
    while (getline(datafile, line)) {
        stringstream ss(line);
        string username;
        getline(ss, username, '|');
        if (usernamecheck == username) return row;
        row++;
    }
    return 0;
}

// Helper function to trim trailing spaces and newlines
string trim(const string& str) {
    size_t start = str.find_first_not_of(" \r\n\t");
    size_t end = str.find_last_not_of(" \r\n\t");
    return (start == string::npos) ? "" : str.substr(start, end - start + 1);
}
