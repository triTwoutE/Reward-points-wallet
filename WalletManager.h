#pragma once
#include "Wallet.h"
#include "OTPManager.h"
#include "User.h"
#include <vector>
#include <string>

class WalletManager {
private:
    std::vector<Wallet>& wallets;
    OTPManager& otpManager;

    Wallet* findWalletByUsername(const std::string& username);
    Wallet* findWalletById(const std::string& walletId);
    void logTransaction(const std::string& fromId, const std::string& toId, double amount, const std::string& status);

public:
    WalletManager(std::vector<Wallet>& wallet_list, OTPManager& otp_manager);

    void createWalletForUser(const std::string& username);
    void showWalletInfo(const std::string& username);
    void processTransfer(const std::string& fromUsername);

    // Chức năng Admin cho Ví tổng
    void adminCheckMasterWallet(const User& adminUser);
    void adminDistributeFromMaster(const User& adminUser);
    void adminShowMasterWalletHistory(const User& adminUser);
};