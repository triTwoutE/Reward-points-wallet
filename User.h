#pragma once
#include <string>

// Phân chia người dùng
enum class UserRole { NORMAL, ADMIN };

// Cấu trúc dữ liệu quản lý thông tin tài khoản người dùng 
class User {
public:
    std::string username;
    std::string hashedPassword;
    std::string fullName;
    std::string email;
    std::string phone;
    UserRole role;
    bool isTempPassword;

    User(std::string uname, std::string pass, std::string fname, std::string mail, std::string p, UserRole r, bool is_temp);
};