#pragma once
#include <string>

namespace Utils {
    // Gợi ý: dùng hàm băm (hash function) để lưu mật khẩu 
    std::string hashPassword(const std::string& password);

    std::string generateRandomNumericString(int length);
    
    // Sinh mật khẩu tự động 
    std::string generateRandomPassword(int length = 10);
}