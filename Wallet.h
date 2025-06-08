#pragma once
#include <string>
#include <vector>
#include <ctime>

/**
 * @brief Cấu trúc để ghi nhận lại thông tin của một giao dịch.
 */
struct Transaction {
    std::string transactionId;
    std::string fromWalletId;
    std::string toWalletId;
    double amount = 0.0;      // Khởi tạo giá trị
    time_t timestamp = 0;       // Khởi tạo giá trị
    std::string status;
};

/**
 * @brief Lớp quản lý thông tin của một ví điểm thưởng.
 */
class Wallet {
public:
    // --- Thuộc tính ---
    std::string walletId;       // Mã số định danh duy nhất
    std::string ownerUsername;  // Tên đăng nhập của chủ sở hữu
    double balance;
    std::vector<Transaction> transactionHistory;

    // --- Phương thức ---
    /**
     * @brief Hàm khởi tạo cho một đối tượng Wallet mới.
     * @param id Mã định danh của ví.
     * @param owner Tên đăng nhập của chủ sở hữu.
     * @param bal Số dư ban đầu, mặc định là 0.0.
     */
    Wallet(std::string id, std::string owner, double bal = 0.0);

    /**
     * @brief In lịch sử giao dịch của ví ra màn hình.
     */
    void printHistory();
};