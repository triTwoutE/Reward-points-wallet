# Reward Points Wallet - Quản lý tài khoản và ví điểm tích lũy

## A. 📌 Giới thiệu dự án
Ứng dụng quản lý tài khoản người dùng và ví điểm tích lũy, cho phép đăng ký, đăng nhập, cập nhật thông tin và phân quyền. Dành cho người dùng thông thường và quản trị viên (admin).

## B. 👨‍💻 Thành viên và công việc

| Thành viên              | Vai trò chính                     | Nội dung công việc cụ thể |
|-------------------------|-----------------------------------|----------------------------|
| Trần Tiến Thành_K24DTCN637 | Thiết kế lớp và xử lý dữ liệu tài khoản | Đăng ký, lưu và đọc dữ liệu từ file, hash mật khẩu, đề xuất cách lưu, sao lưu dữ liệu | Đăng nhập, đổi mật khẩu, OTP | Tạo tài khoản hộ |
| Nguyễn Xuân Hoàng_K24DTCN599 | Giao dịch điểm và ví người dùng, ví tổng | Thiết kế ví, kiểm tra, lưu lịch sử giao dịch, OTP xác nhận chuyển điểm | Ví tổng: kiểm tra, xem lịch sử giao dịch, phát điểm từ ví tổng |
| Đoàn Thùy Dương_K24DTCN581 | Cập nhật thông tin, quản lý thông tin và viết tài liệu |  Cập nhật thông tin cá nhân, cập nhật hộ & quản lý người dùng, cá nhân. Viết tài liệu README |

## C. 📋 Đặc tả chức năng, các chức năng chính:
- Đăng ký tài khoản
- Tạo tài khoản cho người khác (admin)
- Đăng nhập (kiểm tra thông tin + phân quyền)
- Cập nhật thông tin của chính mình
- Cập nhật thông tin người khác (admin)
- Quản lý thông tin cá nhân
- Quản lý danh sách người dùng (admin)
- Chuyển điểm cho người khác & Theo dõi lịch sử giao dịch
- Ví tổng: kiểm tra, xem lịch sử giao dịch, phát điểm từ ví tổng
- Lưu trữ thông tin vào file `userdata.txt`
- Phân quyền `admin` và `user`
- Sao lưu dữ liệu vào thư mục `backup/`
- Xác thực OTP

## D. ⚙️ Cách tải và dịch chương trình

**Yêu cầu:**
- Compiler hỗ trợ C++ (g++, mingw hoặc Linux g++)
- Visual Studio Code (nếu dùng giao diện đồ họa)

**Cách biên dịch (Windows):**
```bash
g++ main.cpp user.cpp -o app
```

**Cách chạy:**
```bash
./app  # hoặc app.exe trên Windows
```

E. 🕹️ Hướng dẫn sử dụng
1. Chọn `1` để đăng nhập
1.1. Sau khi đăng nhập, hệ thống kiểm tra:
**1.1.1. Nếu tài khoản là admin, bạn có quyền thực hiện các chứng năng sau:**

![image](https://github.com/user-attachments/assets/f630fa37-ad57-4514-a458-cbf78ed6c58c)

1.1.1.1. Chọn `1` để: Xem thông tin ví và lịch sử giao dịch
![image](https://github.com/user-attachments/assets/f215935e-6220-4cbc-8699-84c00754ff8d)

1.1.1.2. Chọn `2` để: Chuyển điểm cho người khác từ ví của mình
![image](https://github.com/user-attachments/assets/3eac5ab6-9198-4261-ae71-370aebe3cd88)
- Bạn cần nhập ID ví của người dùng bạn muốn chuyển điểm. Nếu nhập ID ví không tồn tại, hệ thống báo lỗi
- Sau khi nhập ID ví, bạn cần nhập số điểm muốn chuyển. Số điểm chuyển cần phải nhỏ hơn hoặc bằng số dư của ví của bạn, và không được là số âm

![image](https://github.com/user-attachments/assets/94666ef1-335f-4548-9229-842711580421)
- Sau đó hệ thống gửi mã OTP để xác thực giao dịch, cho phép nhập sai 3 lần, quá 3 lần -> giao dịch bị hủy, bạn cần thực hiện lại

![image](https://github.com/user-attachments/assets/55ad0863-bcef-4204-bc9d-baa235b4bb01)

1.1.1.3. Chọn `3` để: Cập nhật thông tin cá nhân
![image](https://github.com/user-attachments/assets/c005dc8d-3042-4d7d-ac61-364a7c460f39)
- Hệ thống cho phép cập nhật các thông tin sau: Họ và tên, Email, Số điện thoại
- Sau khi bạn nhập các thông tin mới, hệ thống gửi mã OTP để xác thực, sau khi nhập mã OTP thành công, thông tin mới được cập nhật trên hệ thống

1.1.1.4. Chọn `4` để: Đổi mật khẩu

![image](https://github.com/user-attachments/assets/863b4815-de85-43ca-b37b-0f921fdeab9a)
- Bạn cần nhập lại mật khẩu cũ, mật khẩu mới và xác nhận mật khẩu mới (2 trường thông tin này cần phải trùng nhau)
- Sau khi đổi thành công, hệ thống cập nhật mật khẩu mới -> session sau cần đăng nhập theo mật khẩu mới

1.1.1.5. Chọn `5` để: Đăng xuất

1.1.1.6. Chọn `6` để: Xem danh sách tất cả người dùng
![image](https://github.com/user-attachments/assets/681a0cf7-6362-4c50-a1dd-354e479c9794)

1.1.1.7. Chọn `7` để: Tạo tài khoản hộ người khác
![image](https://github.com/user-attachments/assets/692d9356-a885-4c1d-a0ae-0b20ba991b92)

Bạn cần nhập đủ các thông tin bắt buộc sau:
- Tên đăng nhập: không có khoảng trắng, không có ký tự đặc biệt
- Họ và tên
- Email
- Số điện thoại
- Vai trò: admin hoặc người dùng thông thường
-> bấm Enter bạn nhận được thông báo "Tạo tài khoản cho người dùng "Tên đăng nhập" với vai trò "ADMIN/NORMAL" thành công!"
-> Hệ thống tự sinh mật khẩu cho tài khoản này

Khi người dùng này đăng nhập lần đầu, hệ thống yêu cầu đổi mật khẩu để truy cập vào ứng dụng
![image](https://github.com/user-attachments/assets/984c4921-d288-4c93-8774-1d24ea7bed34)

1.1.1.8. Chọn `8` để: Cập nhật thông tin người dùng khác 
![image](https://github.com/user-attachments/assets/2d4811cf-f7b2-45ed-a21a-e88245b83e13)
- Hệ thống cho phép cập nhật các thông tin sau: Họ và tên, Email, Số điện thoại, thay đổi vai trò
- Sau khi bạn nhập các thông tin mới, hệ thống gửi mã OTP cho người dùng đang được cập nhật thông tin để xác thực, sau khi nhập mã OTP thành công, thông tin mới được cập nhật trên hệ thống

1.1.1.9. Chọn `9` để: Kiểm tra ví tổng

![image](https://github.com/user-attachments/assets/21cc44b7-5798-49e1-b1b1-caa341321401)

1.1.1.10. Chọn `10` để: Phát điểm từ ví tổng
![image](https://github.com/user-attachments/assets/8655452e-b296-4c78-8765-9c2b579df3ad)
- Bạn cần nhập ID ví của người dùng bạn muốn phát điểm. Nếu nhập ID ví không tồn tại, hệ thống báo lỗi
- Sau khi nhập ID ví, bạn cần nhập số điểm muốn phát. Số điểm chuyển cần phải nhỏ hơn hoặc bằng số dư của ví tổng, và không được là số âm

1.1.1.11. Chọn `11` để: Xem lịch sử giao dịch ví tổng
![image](https://github.com/user-attachments/assets/70103bb1-0992-4ccb-be04-6eda0b787404)

**1.1.2. Nếu tài khoản là người dùng thông thường, bạn có quyền thực hiện các chứng năng sau:**
![image](https://github.com/user-attachments/assets/6e376a7e-2c85-4729-9fbf-280b26e0212c)

1.1.2.1. Chọn `1` để: Xem thông tin ví và lịch sử giao dịch
![image](https://github.com/user-attachments/assets/8ef20dce-e660-43aa-8986-f5ffd04a9edf)

1.1.2.2. Chọn `2` để: Chuyển điểm cho người khác từ ví của mình
![image](https://github.com/user-attachments/assets/3eac5ab6-9198-4261-ae71-370aebe3cd88)
- Bạn cần nhập ID ví của người dùng bạn muốn chuyển điểm. Nếu nhập ID ví không tồn tại, hệ thống báo lỗi
- Sau khi nhập ID ví, bạn cần nhập số điểm muốn chuyển. Số điểm chuyển cần phải nhỏ hơn hoặc bằng số dư của ví của bạn, và không được là số âm

![image](https://github.com/user-attachments/assets/94666ef1-335f-4548-9229-842711580421)
- Sau đó hệ thống gửi mã OTP để xác thực giao dịch, cho phép nhập sai 3 lần, quá 3 lần -> giao dịch bị hủy, bạn cần thực hiện lại
![image](https://github.com/user-attachments/assets/e8b777cb-0d89-4076-b639-64d326f21452)

1.1.2.3. Chọn `3` để: Cập nhật thông tin cá nhân
![image](https://github.com/user-attachments/assets/c005dc8d-3042-4d7d-ac61-364a7c460f39)
- Hệ thống cho phép cập nhật các thông tin sau: Họ và tên, Email, Số điện thoại
- Sau khi bạn nhập các thông tin mới, hệ thống gửi mã OTP để xác thực, sau khi nhập mã OTP thành công, thông tin mới được cập nhật trên hệ thống

1.1.2.4. Chọn `4` để: Đổi mật khẩu

![image](https://github.com/user-attachments/assets/863b4815-de85-43ca-b37b-0f921fdeab9a)
- Bạn cần nhập lại mật khẩu cũ, mật khẩu mới và xác nhận mật khẩu mới (2 trường thông tin này cần phải trùng nhau)
- Sau khi đổi thành công, hệ thống cập nhật mật khẩu mới -> session sau cần đăng nhập theo mật khẩu mới
  
1.1.2.5. Chọn `5` để: Đăng xuất

2. Chọn `2` để tự đăng ký tài khoản mới
2.1. Chức năng này chỉ hỗ trợ người dùng thông thường
![image](https://github.com/user-attachments/assets/b582fa22-ae99-44ea-a9f7-215121b58fff)

Bạn cần nhập đủ các thông tin bắt buộc sau:
- Tên đăng nhập: không có khoảng trắng, không có ký tự đặc biệt
- Mật khẩu
- Họ và tên
- Email
- Số điện thoại
-> bấm Enter bạn nhận được thông báo "Đã tạo ví mới "ID ví" cho người dùng "Tên đăng nhâp"

3. Chọn `3` để đăng xuất

## F. 📚 Tài liệu tham khảo

- Tài liệu cấu trúc dữ liệu & thuật toán cơ bản
- Hướng dẫn C++ trên GeeksForGeeks và Cplusplus.com
- Mẫu phân công và README từ các đồ án trước năm học

---

## G. ✔️ Dự án hoàn thành bởi nhóm sinh viên Khoa CNTT PTIT lớp D24TXCN15-K, với mục tiêu mô phỏng một hệ thống quản lý người dùng đơn giản nhưng có đầy đủ quyền và chức năng cơ bản.
