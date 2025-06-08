#include "User.h"

User::User(std::string uname, std::string pass, std::string fname, std::string mail, std::string p, UserRole r, bool is_temp)
    : username(uname), hashedPassword(pass), fullName(fname), email(mail), phone(p), role(r), isTempPassword(is_temp) {}