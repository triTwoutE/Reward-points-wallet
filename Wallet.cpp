#include "Wallet.h"
#include <iostream>
#include <iomanip>

Wallet::Wallet(std::string id, std::string owner, double bal)
    : walletId(id), ownerUsername(owner), balance(bal) {}

void Wallet::printHistory() {
    std::cout << "--- Lich su Giao dich cho Vi " << walletId << " ---\n";
    if (transactionHistory.empty()) {
        std::cout << "Khong co giao dich nao.\n";
        return;
    }
    std::cout << std::left << std::setw(15) << "ID Giao Dich"
              << std::setw(15) << "Tu Vi"
              << std::setw(15) << "Den Vi"
              << std::setw(12) << "So Tien"
              << std::setw(12) << "Trang Thai" << std::endl;
    for (const auto& tx : transactionHistory) {
        std::cout << std::left << std::setw(15) << tx.transactionId.substr(0, 13)
                  << std::setw(15) << tx.fromWalletId
                  << std::setw(15) << tx.toWalletId
                  << std::fixed << std::setprecision(2) << std::setw(12) << tx.amount
                  << std::setw(12) << tx.status << std::endl;
    }
}