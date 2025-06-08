#pragma once
#include "User.h"
#include "Wallet.h"
#include <vector>
#include <string>

class DatabaseManager {
private:
    const std::string userFile = "users.csv";
    const std::string walletFile = "wallets.csv";

public:
    // Đọc/Ghi dữ liệu người dùng 
    void loadUsers(std::vector<User>& users);
    void saveUsers(const std::vector<User>& users);

    // Đọc/Ghi dữ liệu ví
    void loadWallets(std::vector<Wallet>& wallets);
    void saveWallets(const std::vector<Wallet>& wallets);
    
    // Quy trình sao lưu 
    void backupData();
};