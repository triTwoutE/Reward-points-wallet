#pragma once
#include "User.h"
#include "Wallet.h"
#include "OTPManager.h"
#include <vector>
#include <string>

class AuthManager {
private:
    std::vector<User>& users;
    OTPManager& otpManager;

public:
    AuthManager(std::vector<User>& user_list, OTPManager& otp_manager);
    
    // Trả về một con trỏ tới người dùng nếu đăng nhập thành công, ngược lại trả về nullptr
    User* login();

    // Xử lý việc đăng ký người dùng mới
    bool registerUser();

    // Thay đổi mật khẩu cho người dùng đã đăng nhập
    void changePassword(User& currentUser);

    // Thay đổi thông tin cá nhân (tên, email, sđt) cho người dùng
    void updateUserInfo(User& currentUser);

    // Chức năng của admin: tạo tài khoản cho người dùng
    bool adminCreateUser();

    // Chức năng của admin: chỉnh sửa thông tin người dùng khác
    void adminUpdateUser();
};