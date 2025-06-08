#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <iomanip> // <<< THÊM VÀO: Thư viện để định dạng bảng (setw)

#include "User.h"
#include "Wallet.h"
#include "DatabaseManager.h"
#include "AuthManager.h"
#include "WalletManager.h"
#include "OTPManager.h"

void showMainMenu() {
    std::cout << "\n--- HE THONG VI DIEM THUONG NHOM 3 ---\n";
    std::cout << "1. Dang Nhap\n";
    std::cout << "2. Dang Ky\n";
    std::cout << "3. Thoat\n";
    std::cout << "Lua chon cua ban: ";
}

void showUserMenu(const User& user) {
    std::cout << "\n--- XIN CHAO, " << user.fullName << " ---\n";
    std::cout << "1. Xem Thong Tin Vi & Lich Su Giao Dich\n";
    std::cout << "2. Chuyen Diem\n";
    std::cout << "3. Cap Nhat Thong Tin Ca Nhan\n";
    std::cout << "4. Doi Mat Khau\n";
    std::cout << "5. Dang Xuat\n";
    std::cout << "Lua chon cua ban: ";
}

void showAdminMenu(const User& user) {
    showUserMenu(user);
    std::cout << "--- CHUC NANG QUAN LY ---\n";
    std::cout << "6. Xem Danh Sach Tat Ca Nguoi Dung\n";
    std::cout << "7. Tao Tai Khoan Moi Cho Nguoi Dung\n";
    std::cout << "8. Chinh Sua Thong Tin Nguoi Dung Khac\n";
    std::cout << "9. Kiem Tra Vi Tong\n";
    std::cout << "10. Phat Diem Tu Vi Tong\n";
    std::cout << "11. Xem Lich Su Giao Dich Vi Tong\n";
    std::cout << "Lua chon cua ban: ";
}


int main() {
    try {
        std::vector<User> users;
        std::vector<Wallet> wallets;

        DatabaseManager dbManager;
        OTPManager otpManager;
        AuthManager authManager(users, otpManager);
        WalletManager walletManager(wallets, otpManager);

        dbManager.loadUsers(users);
        dbManager.loadWallets(wallets);

        User* currentUser = nullptr;
        int choice;

        while (true) {
            if (currentUser == nullptr) {
                showMainMenu();
                std::cin >> choice;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    choice = 0;
                }
                switch (choice) {
                case 1: currentUser = authManager.login(); break;
                case 2: {
                    bool success = authManager.registerUser();
                    if (success) { walletManager.createWalletForUser(users.back().username); }
                    break;
                }
                case 3:
                    std::cout << "Dang luu du lieu...\n";
                    dbManager.saveUsers(users);
                    dbManager.saveWallets(wallets);
                    dbManager.backupData();
                    std::cout << "Tam biet!\n";
                    system("pause");
                    return 0;
                default:
                    std::cout << "Lua chon khong hop le. Vui long chon lai.\n";
                    break;
                }
            }
            else {
                if (currentUser->role == UserRole::ADMIN) {
                    showAdminMenu(*currentUser);
                }
                else {
                    showUserMenu(*currentUser);
                }

                std::cin >> choice;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    choice = 0;
                }

                switch (choice) {
                case 1: walletManager.showWalletInfo(currentUser->username); break;
                case 2: walletManager.processTransfer(currentUser->username); break;
                case 3: authManager.updateUserInfo(*currentUser); break;
                case 4: authManager.changePassword(*currentUser); break;
                case 5: currentUser = nullptr; std::cout << "Da dang xuat.\n"; break;
                default:
                    if (currentUser->role == UserRole::ADMIN) {
                        switch (choice) {
                            // <<< CASE 6 ĐƯỢC THAY THẾ HOÀN TOÀN ĐỂ HIỂN THỊ BẢNG CHI TIẾT >>>
                        case 6:
                        {
                            std::cout << "\n--- DANH SACH NGUOI DUNG CHI TIET ---\n";
                            // In tiêu đề cho bảng
                            std::cout << std::left
                                << std::setw(15) << "Username"
                                << std::setw(25) << "Ho Ten"
                                << std::setw(25) << "Email"
                                << std::setw(15) << "So DT"
                                << std::setw(15) << "Ma Vi"
                                << std::setw(10) << "Vai Tro" << std::endl;
                            std::cout << std::string(105, '-') << std::endl;

                            // Duyệt qua từng người dùng để in thông tin
                            for (const auto& u : users) {
                                std::string walletId = "N/A";
                                // Tìm ví tương ứng để lấy ID
                                for (const auto& w : wallets) {
                                    if (w.ownerUsername == u.username) {
                                        walletId = w.walletId;
                                        break;
                                    }
                                }
                                std::cout << std::left
                                    << std::setw(15) << u.username
                                    << std::setw(25) << u.fullName
                                    << std::setw(25) << u.email
                                    << std::setw(15) << u.phone
                                    << std::setw(15) << walletId
                                    << std::setw(10) << (u.role == UserRole::ADMIN ? "ADMIN" : "NORMAL") << std::endl;
                            }
                        }
                        break;
                        case 7: {
                            bool success = authManager.adminCreateUser();
                            if (success) {
                                walletManager.createWalletForUser(users.back().username);
                            }
                            break;
                        }
                        case 8: authManager.adminUpdateUser(); break;
                        case 9: walletManager.adminCheckMasterWallet(*currentUser); break;
                        case 10: walletManager.adminDistributeFromMaster(*currentUser); break;
                        case 11: walletManager.adminShowMasterWalletHistory(*currentUser); break;
                        default: std::cout << "Lua chon khong hop le. Vui long chon lai.\n"; break;
                        }
                    }
                    else {
                        std::cout << "Lua chon khong hop le. Vui long chon lai.\n";
                    }
                    break;
                }
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "LOI NGHIEM TRONG: Mot loi runtime da xay ra: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "LOI NGHIEM TRONG: Mot loi khong xac dinh da xay ra." << std::endl;
    }

    std::cout << "Chuong trinh da ket thuc do loi. Nhan phim bat ky de dong cua so." << std::endl;
    system("pause");
    return 1;
}