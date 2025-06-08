#include "Utils.h"
#include <random>
#include <functional>
#include <string>

// Hàm băm mật khẩu đơn giản cho mục đích học tập.
// Trong thực tế, hãy dùng các thư viện mạnh hơn như bcrypt hoặc Argon2.
std::string Utils::hashPassword(const std::string& password) {
    std::hash<std::string> hasher;
    // Thêm "salt" đơn giản để tránh rainbow table attack
    return std::to_string(hasher(password + "a_simple_salt_string"));
}

std::string Utils::generateRandomNumericString(int length) {
    const std::string chars = "0123456789";
    std::string result = "";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, chars.size() - 1);
    for (int i = 0; i < length; ++i) {
        result += chars[distribution(generator)];
    }
    return result;
}

std::string Utils::generateRandomPassword(int length) {
    const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string password = "";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, chars.size() - 1);
    for (int i = 0; i < length; ++i) {
        password += chars[distribution(generator)];
    }
    return password;
}