#include "OTPManager.h"
#include "Utils.h"
#include <iostream>

// Đề xuất giải pháp sử dụng OTP 
// OTP được dùng để xác thực các hoạt động thay đổi thông tin quan trọng 
std::string OTPManager::generateOTP(const std::string& username) {
    std::string code = Utils::generateRandomNumericString(6);
    // Lưu mã OTP và thời gian hết hạn (60 giây)
    otpStore[username] = {code, std::chrono::steady_clock::now() + std::chrono::seconds(60)};
    
    // Giả lập việc gửi OTP bằng cách in ra màn hình
    std::cout << "\n>>> [He Thong] Ma OTP cho '" << username << "' la: " << code << " (Hieu luc trong 60 giay)\n";
    return code;
}

bool OTPManager::validateOTP(const std::string& username, const std::string& code) {
    if (otpStore.count(username)) {
        auto& otpData = otpStore.at(username);
        // Kiểm tra mã và thời gian hiệu lực
        if (otpData.code == code && std::chrono::steady_clock::now() < otpData.expiry) {
            otpStore.erase(username); // OTP chỉ được dùng một lần
            return true;
        }
    }
    return false;
}