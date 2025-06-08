#include "DatabaseManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <ctime>

// Thư viện cần thiết để lấy đường dẫn AppData và tạo thư mục
#include <filesystem> 
#include <ShlObj.h> 

// Yêu cầu Linker liên kết với thư viện Shell32.lib
#pragma comment(lib, "Shell32.lib")

const std::string MASTER_WALLET_ID = "MASTER_WALLET";
const std::string MASTER_WALLET_OWNER = "system";

// Hàm lấy đường dẫn đến thư mục AppData và tạo thư mục con cho ứng dụng
std::string getAppDataPath() {
    CHAR szPath[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, szPath))) {
        std::string appDataPath(szPath);
        std::string appFolderPath = appDataPath + "\\QuanLyViDiem";

        if (!std::filesystem::exists(appFolderPath)) {
            std::filesystem::create_directory(appFolderPath);
        }
        return appFolderPath;
    }
    else {
        throw std::runtime_error("Loi: Khong the truy cap thu muc AppData.");
    }
}

void DatabaseManager::loadUsers(std::vector<User>& users) {
    std::string filePath = getAppDataPath() + "\\" + userFile;
    std::ifstream file(filePath);
    if (!file.is_open()) return;

    users.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string username, pass, fname, email, phone, role_str, is_temp_str;

        std::getline(ss, username, ',');
        std::getline(ss, pass, ',');
        std::getline(ss, fname, ',');
        std::getline(ss, email, ',');
        std::getline(ss, phone, ',');
        std::getline(ss, role_str, ',');
        std::getline(ss, is_temp_str, ',');

        UserRole role = (role_str == "ADMIN") ? UserRole::ADMIN : UserRole::NORMAL;
        bool is_temp = (is_temp_str == "1");

        users.emplace_back(username, pass, fname, email, phone, role, is_temp);
    }
    file.close();
}

void DatabaseManager::saveUsers(const std::vector<User>& users) {
    std::string filePath = getAppDataPath() + "\\" + userFile;
    std::ofstream file(filePath);
    for (const auto& user : users) {
        file << user.username << ","
            << user.hashedPassword << ","
            << user.fullName << ","
            << user.email << ","
            << user.phone << ","
            << (user.role == UserRole::ADMIN ? "ADMIN" : "NORMAL") << ","
            << (user.isTempPassword ? "1" : "0") << "\n";
    }
    file.close();
}

void DatabaseManager::loadWallets(std::vector<Wallet>& wallets) {
    std::string filePath = getAppDataPath() + "\\" + walletFile;
    std::ifstream file(filePath);

    wallets.clear();
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string id, owner, balance_str;
            std::getline(ss, id, ',');
            std::getline(ss, owner, ',');
            std::getline(ss, balance_str, ',');

            double balance = 0.0;
            if (!balance_str.empty()) {
                balance = std::stod(balance_str);
            }
            wallets.emplace_back(id, owner, balance);
        }
        file.close();
    }

    bool masterWalletExists = false;
    for (const auto& w : wallets) {
        if (w.walletId == MASTER_WALLET_ID) {
            masterWalletExists = true;
            break;
        }
    }

    if (!masterWalletExists) {
        std::cout << "[He Thong] Phat hien Vi Tong chua ton tai. Dang khoi tao Vi Tong...\n";
        wallets.emplace_back(MASTER_WALLET_ID, MASTER_WALLET_OWNER, 1000000.0);
    }
}

void DatabaseManager::saveWallets(const std::vector<Wallet>& wallets) {
    std::string filePath = getAppDataPath() + "\\" + walletFile;
    std::ofstream file(filePath);
    for (const auto& wallet : wallets) {
        file << wallet.walletId << ","
            << wallet.ownerUsername << ","
            << wallet.balance << "\n";
    }
    file.close();
}

// <<< HÀM BACKUPDATA ĐÃ ĐƯỢC KÍCH HOẠT LẠI VÀ HOÀN THIỆN >>>
void DatabaseManager::backupData() {
    try {
        std::string dataFolderPath = getAppDataPath();
        std::string backupFolderPath = dataFolderPath + "\\backup";

        // Tạo thư mục backup nếu chưa có
        if (!std::filesystem::exists(backupFolderPath)) {
            std::filesystem::create_directory(backupFolderPath);
        }

        // Lấy thời gian hiện tại để đặt tên cho tệp sao lưu
        time_t now = time(nullptr);
        char buf[20];
        strftime(buf, sizeof(buf), "%Y%m%d_%H%M%S", localtime(&now));

        std::string userSourcePath = dataFolderPath + "\\" + userFile;
        std::string walletSourcePath = dataFolderPath + "\\" + walletFile;

        std::string userBackupPath = backupFolderPath + "\\users_" + std::string(buf) + ".csv";
        std::string walletBackupPath = backupFolderPath + "\\wallets_" + std::string(buf) + ".csv";

        // Thực hiện sao chép, chỉ sao chép nếu tệp nguồn tồn tại
        if (std::filesystem::exists(userSourcePath)) {
            std::filesystem::copy_file(userSourcePath, userBackupPath, std::filesystem::copy_options::overwrite_existing);
        }

        if (std::filesystem::exists(walletSourcePath)) {
            std::filesystem::copy_file(walletSourcePath, walletBackupPath, std::filesystem::copy_options::overwrite_existing);
        }

        std::cout << "[He Thong] Da tao ban sao luu du lieu thanh cong.\n";

    }
    catch (const std::exception& e) {
        std::cerr << "Loi sao luu: " << e.what() << std::endl;
    }
}