#include "WalletManager.h"
#include "Utils.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>

const std::string MASTER_WALLET_ID = "MASTER_WALLET";

WalletManager::WalletManager(std::vector<Wallet>& wallet_list, OTPManager& otp_manager)
    : wallets(wallet_list), otpManager(otp_manager) {
}

Wallet* WalletManager::findWalletByUsername(const std::string& username) {
    for (auto& w : wallets) {
        if (w.ownerUsername == username) {
            return &w;
        }
    }
    return nullptr;
}

Wallet* WalletManager::findWalletById(const std::string& walletId) {
    for (auto& w : wallets) {
        if (w.walletId == walletId) {
            return &w;
        }
    }
    return nullptr;
}

void WalletManager::logTransaction(const std::string& fromId, const std::string& toId, double amount, const std::string& status) {
    Wallet* walletA = findWalletById(fromId);
    Wallet* walletB = findWalletById(toId);

    Transaction tx;
    tx.transactionId = Utils::generateRandomPassword(12);
    tx.fromWalletId = fromId;
    tx.toWalletId = toId;
    tx.amount = amount;
    tx.timestamp = time(nullptr);
    tx.status = status;

    if (walletA) walletA->transactionHistory.push_back(tx);
    if (walletB) walletB->transactionHistory.push_back(tx);
}

void WalletManager::createWalletForUser(const std::string& username) {
    std::string walletId = "W_" + username;
    wallets.emplace_back(walletId, username, 0.0);
    std::cout << "Da tao vi moi '" << walletId << "' cho nguoi dung '" << username << "'.\n";
}

void WalletManager::showWalletInfo(const std::string& username) {
    Wallet* wallet = findWalletByUsername(username);
    if (wallet) {
        std::cout << "\n--- THONG TIN VI ---\n";
        std::cout << "Chu so huu: " << wallet->ownerUsername << std::endl;
        std::cout << "Ma vi: " << wallet->walletId << std::endl;
        std::cout << "So du: " << std::fixed << std::setprecision(2) << wallet->balance << " diem\n";
        wallet->printHistory();
    }
    else {
        std::cout << "Loi: Khong tim thay vi cho nguoi dung nay.\n";
    }
}

// <<< HÀM ĐÃ ĐƯỢC NÂNG CẤP LOGIC OTP >>>
void WalletManager::processTransfer(const std::string& fromUsername) {
    std::cout << "\n--- CHUYEN DIEM ---\n";
    std::string toWalletId;
    double amount;

    std::cout << "Nhap ma vi nguoi nhan: ";
    std::cin >> toWalletId;
    std::cout << "Nhap so diem can chuyen: ";
    std::cin >> amount;

    if (amount <= 0) {
        std::cout << "So diem phai la so duong.\n";
        return;
    }

    // Nâng cấp: Thêm vòng lặp cho phép thử lại OTP 3 lần
    otpManager.generateOTP(fromUsername);
    bool otpVerified = false;
    for (int attempt = 0; attempt < 3; ++attempt) {
        std::string otpCode;
        std::cout << "Vui long nhap ma OTP (con " << 3 - attempt << " lan thu): ";
        std::cin >> otpCode;
        if (otpManager.validateOTP(fromUsername, otpCode)) {
            otpVerified = true;
            break; // Thoát khỏi vòng lặp nếu OTP đúng
        }
        else {
            std::cout << "Ma OTP sai. ";
            if (attempt < 2) {
                std::cout << "Vui long thu lai.\n";
            }
        }
    }

    if (!otpVerified) {
        std::cout << "\nBan da nhap sai OTP 3 lan. Giao dich bi huy.\n";
        return;
    }

    // Bắt đầu giao dịch
    Wallet* walletA = findWalletByUsername(fromUsername);
    Wallet* walletB = findWalletById(toWalletId);

    if (!walletA || !walletB) {
        std::cout << "Loi: Khong tim thay vi nguon hoac vi dich.\n";
        return;
    }

    if (walletA->walletId == walletB->walletId) {
        std::cout << "Loi: Khong the chuyen diem cho chinh minh.\n";
        return;
    }

    double initialBalanceA = walletA->balance;
    double initialBalanceB = walletB->balance;
    try {
        if (walletA->balance < amount) {
            throw std::runtime_error("So du khong du.");
        }
        walletA->balance -= amount;
        walletB->balance += amount;

        logTransaction(walletA->walletId, walletB->walletId, amount, "Completed");
        std::cout << "Giao dich thanh cong! So du moi cua ban: " << walletA->balance << " diem.\n";

    }
    catch (const std::runtime_error& e) {
        walletA->balance = initialBalanceA;
        walletB->balance = initialBalanceB;
        logTransaction(walletA->walletId, walletB->walletId, amount, "Failed");
        std::cout << "Giao dich that bai: " << e.what() << ". Da hoan lai trang thai vi.\n";
    }
}

void WalletManager::adminCheckMasterWallet(const User& adminUser) {
    if (adminUser.role != UserRole::ADMIN) {
        std::cout << "Loi: Ban khong co quyen thuc hien chuc nang nay.\n";
        return;
    }

    Wallet* masterWallet = findWalletById(MASTER_WALLET_ID);
    if (masterWallet) {
        std::cout << "\n--- THONG TIN VI TONG ---\n";
        std::cout << "Ma vi: " << masterWallet->walletId << std::endl;
        std::cout << "So du hien tai: " << std::fixed << std::setprecision(2) << masterWallet->balance << " diem.\n";
    }
    else {
        std::cout << "Loi: Khong tim thay Vi Tong trong he thong.\n";
    }
}

void WalletManager::adminDistributeFromMaster(const User& adminUser) {
    if (adminUser.role != UserRole::ADMIN) {
        std::cout << "Loi: Ban khong co quyen thuc hien chuc nang nay.\n";
        return;
    }

    std::cout << "\n--- PHAT DIEM TU VI TONG ---\n";
    std::string toWalletId;
    std::cout << "Nhap ma vi (Wallet ID) cua nguoi nhan: ";
    std::cin >> toWalletId;

    double amount;
    std::cout << "Nhap so diem can phat: ";
    std::cin >> amount;

    if (amount <= 0) {
        std::cout << "So diem phai la so duong.\n";
        return;
    }

    Wallet* masterWallet = findWalletById(MASTER_WALLET_ID);
    Wallet* userWallet = findWalletById(toWalletId);

    if (!masterWallet || !userWallet) {
        std::cout << "Loi: Khong tim thay Vi Tong hoac ma vi cua nguoi dung.\n";
        return;
    }

    if (masterWallet->walletId == userWallet->walletId) {
        std::cout << "Loi: Khong the phat diem cho chinh Vi Tong.\n";
        return;
    }

    if (masterWallet->balance < amount) {
        std::cout << "Loi: Vi Tong khong du diem de phat.\n";
        return;
    }

    masterWallet->balance -= amount;
    userWallet->balance += amount;

    logTransaction(masterWallet->walletId, userWallet->walletId, amount, "Completed");
    std::cout << "Phat diem thanh cong! " << amount << " diem da duoc chuyen den vi '"
        << userWallet->walletId << "' (cua nguoi dung '" << userWallet->ownerUsername << "').\n";
    std::cout << "So du con lai cua Vi Tong: " << masterWallet->balance << " diem.\n";
}

void WalletManager::adminShowMasterWalletHistory(const User& adminUser) {
    if (adminUser.role != UserRole::ADMIN) {
        std::cout << "Loi: Ban khong co quyen thuc hien chuc nang nay.\n";
        return;
    }

    Wallet* masterWallet = findWalletById(MASTER_WALLET_ID);
    if (masterWallet) {
        masterWallet->printHistory();
    }
    else {
        std::cout << "Loi: Khong tim thay Vi Tong trong he thong.\n";
    }
}