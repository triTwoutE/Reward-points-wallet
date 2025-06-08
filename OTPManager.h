#pragma once
#include <string>
#include <map>
#include <chrono>

struct OTPData {
    std::string code;
    std::chrono::steady_clock::time_point expiry;
};

class OTPManager {
private:
    std::map<std::string, OTPData> otpStore;

public:
    // Tạo và "gửi" OTP cho người dùng
    std::string generateOTP(const std::string& username);
    
    // Xác thực OTP do người dùng nhập
    bool validateOTP(const std::string& username, const std::string& code);
};