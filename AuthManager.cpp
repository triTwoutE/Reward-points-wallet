#include "AuthManager.h"
#include "Utils.h"
#include <iostream>
#include <string>
#include <vector>

AuthManager::AuthManager(std::vector<User>& user_list, OTPManager& otp_manager)
    : users(user_list), otpManager(otp_manager) {
}

User* AuthManager::login() {
    std::string username, password;
    std::cout << "--- DANG NHAP ---\n";
    std::cout << "Ten dang nhap: ";
    std::cin >> username;
    std::cout << "Mat khau: ";
    std::cin >> password;

    std::string hashed_password = Utils::hashPassword(password);

    for (User& user : users) {
        if (user.username == username && user.hashedPassword == hashed_password) {
            std::cout << "Dang nhap thanh cong!\n";

            if (user.isTempPassword) {
                std::cout << "\n[CANH BAO] Ban dang su dung mat khau tam. Vui long doi mat khau moi.\n";
                changePassword(user);
            }
            return &user;
        }
    }

    std::cout << "Loi: Ten dang nhap hoac mat khau khong dung.\n";
    return nullptr;
}

bool AuthManager::registerUser() {
    std::cout << "--- DANG KY TAI KHOAN ---\n";
    std::string username, password, fullName, email, phone;

    std::cout << "Ten dang nhap: ";
    std::cin >> username;

    for (const auto& user : users) {
        if (user.username == username) {
            std::cout << "Loi: Ten dang nhap nay da ton tai.\n";
            return false;
        }
    }

    std::cout << "Mat khau: ";
    std::cin >> password;
    std::cout << "Ho va ten: ";
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, fullName);
    std::cout << "Email: ";
    std::cin >> email;
    std::cout << "So dien thoai: ";
    std::cin >> phone;

    users.emplace_back(username, Utils::hashPassword(password), fullName, email, phone, UserRole::NORMAL, false);
    std::cout << "Dang ky thanh cong!\n";
    return true;
}

void AuthManager::changePassword(User& currentUser) {
    std::string oldPassword, newPassword, confirmPassword;
    std::cout << "--- THAY DOI MAT KHAU ---\n";
    std::cout << "Nhap mat khau cu: ";
    std::cin >> oldPassword;

    if (Utils::hashPassword(oldPassword) != currentUser.hashedPassword) {
        std::cout << "Loi: Mat khau cu khong dung.\n";
        return;
    }

    std::cout << "Nhap mat khau moi: ";
    std::cin >> newPassword;
    std::cout << "Xac nhan mat khau moi: ";
    std::cin >> confirmPassword;

    if (newPassword != confirmPassword) {
        std::cout << "Loi: Mat khau moi khong khop.\n";
        return;
    }

    currentUser.hashedPassword = Utils::hashPassword(newPassword);
    currentUser.isTempPassword = false;
    std::cout << "Doi mat khau thanh cong!\n";
}

// <<< HÀM ĐÃ ĐƯỢC NÂNG CẤP LOGIC OTP >>>
void AuthManager::updateUserInfo(User& currentUser) {
    std::cout << "--- CAP NHAT THONG TIN CA NHAN ---\n";
    std::string newFullName, newEmail, newPhone;

    std::cout << "Nhap Ho ten moi (hien tai: " << currentUser.fullName << "): ";
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, newFullName);

    std::cout << "Nhap Email moi (hien tai: " << currentUser.email << "): ";
    std::cin >> newEmail;

    std::cout << "Nhap SĐT moi (hien tai: " << currentUser.phone << "): ";
    std::cin >> newPhone;

    // Nâng cấp: Thêm vòng lặp cho phép thử lại OTP 3 lần
    otpManager.generateOTP(currentUser.username);
    bool otpVerified = false;
    for (int attempt = 0; attempt < 3; ++attempt) {
        std::string otpCode;
        std::cout << "Vui long nhap ma OTP de xac nhan thay doi (con " << 3 - attempt << " lan thu): ";
        std::cin >> otpCode;
        if (otpManager.validateOTP(currentUser.username, otpCode)) {
            otpVerified = true;
            break;
        }
        else {
            std::cout << "Ma OTP sai. ";
            if (attempt < 2) {
                std::cout << "Vui long thu lai.\n";
            }
        }
    }

    if (!otpVerified) {
        std::cout << "\nBan da nhap sai OTP 3 lan. Thao tac bi huy.\n";
        return;
    }

    currentUser.fullName = newFullName;
    currentUser.email = newEmail;
    currentUser.phone = newPhone;
    std::cout << "Cap nhat thong tin thanh cong!\n";
}

bool AuthManager::adminCreateUser() {
    std::cout << "--- (Admin) TAO TAI KHOAN MOI ---\n";
    std::string username, fullName, email, phone;

    std::cout << "Ten dang nhap: ";
    std::cin >> username;

    for (const auto& user : users) {
        if (user.username == username) {
            std::cout << "Loi: Ten dang nhap nay da ton tai.\n";
            return false;
        }
    }

    std::cout << "Ho va ten: ";
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, fullName);
    std::cout << "Email: ";
    std::cin >> email;
    std::cout << "So dien thoai: ";
    std::cin >> phone;

    int roleChoice = 1;
    std::cout << "Chon vai tro cho tai khoan (1: NORMAL, 2: ADMIN): ";
    std::cin >> roleChoice;
    UserRole role = (roleChoice == 2) ? UserRole::ADMIN : UserRole::NORMAL;

    std::string tempPassword = Utils::generateRandomPassword();
    std::cout << "Mat khau tam da duoc tao: " << tempPassword << std::endl;

    users.emplace_back(username, Utils::hashPassword(tempPassword), fullName, email, phone, role, true);
    std::cout << "Tao tai khoan cho nguoi dung '" << username << "' voi vai tro " << (role == UserRole::ADMIN ? "ADMIN" : "NORMAL") << " thanh cong!\n";
    return true;
}

// <<< HÀM ĐÃ ĐƯỢC NÂNG CẤP LOGIC OTP >>>
void AuthManager::adminUpdateUser() {
    std::cout << "--- (Admin) CAP NHAT THONG TIN NGUOI DUNG ---\n";
    std::string username;
    std::cout << "Nhap ten dang nhap cua nguoi dung can chinh sua: ";
    std::cin >> username;

    User* targetUser = nullptr;
    for (User& u : users) {
        if (u.username == username) {
            targetUser = &u;
            break;
        }
    }

    if (targetUser == nullptr) {
        std::cout << "Loi: Khong tim thay nguoi dung.\n";
        return;
    }

    std::cout << "Ban dang sua thong tin cho: " << targetUser->username << std::endl;
    std::string newFullName, newEmail, newPhone;

    std::cout << "Nhap Ho ten moi (hien tai: " << targetUser->fullName << "): ";
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, newFullName);
    std::cout << "Nhap Email moi (hien tai: " << targetUser->email << "): ";
    std::cin >> newEmail;
    std::cout << "Nhap SĐT moi (hien tai: " << targetUser->phone << "): ";
    std::cin >> newPhone;

    int roleChoice = 0;
    std::cout << "Thay doi vai tro? (1: NORMAL, 2: ADMIN, 0: Khong doi): ";
    std::cin >> roleChoice;

    // Nâng cấp: Thêm vòng lặp cho phép thử lại OTP 3 lần
    otpManager.generateOTP(targetUser->username);
    bool otpVerified = false;
    for (int attempt = 0; attempt < 3; ++attempt) {
        std::string otpCode;
        std::cout << "Vui long nhap ma OTP (da gui cho nguoi dung) (con " << 3 - attempt << " lan thu): ";
        std::cin >> otpCode;
        if (otpManager.validateOTP(targetUser->username, otpCode)) {
            otpVerified = true;
            break;
        }
        else {
            std::cout << "Ma OTP sai. ";
            if (attempt < 2) {
                std::cout << "Vui long thu lai.\n";
            }
        }
    }

    if (!otpVerified) {
        std::cout << "\nBan da nhap sai OTP 3 lan. Thao tac bi huy.\n";
        return;
    }

    targetUser->fullName = newFullName;
    targetUser->email = newEmail;
    targetUser->phone = newPhone;

    if (roleChoice == 1) {
        targetUser->role = UserRole::NORMAL;
        std::cout << "Da cap nhat vai tro thanh NORMAL.\n";
    }
    else if (roleChoice == 2) {
        targetUser->role = UserRole::ADMIN;
        std::cout << "Da cap nhat vai tro thanh ADMIN.\n";
    }

    std::cout << "Cap nhat thong tin cho '" << username << "' thanh cong!\n";
}