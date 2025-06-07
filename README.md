# Reward Points Wallet - Quản lý tài khoản và ví điểm tích lũy

A. 📌 Giới thiệu dự án
Ứng dụng quản lý tài khoản người dùng và ví điểm tích lũy, cho phép đăng ký, đăng nhập, cập nhật thông tin và phân quyền. Dành cho người dùng thông thường và quản trị viên (admin).

B. 👨‍💻 Thành viên và công việc

| Thành viên              | Vai trò chính                     | Nội dung công việc cụ thể |
|-------------------------|-----------------------------------|----------------------------|
| Trần Tiến Thành_K24DTCN673 | Thiết kế lớp và xử lý dữ liệu tài khoản | Đăng ký, lưu và đọc dữ liệu từ file, hash mật khẩu, đề xuất cách lưu, sao lưu dữ liệu |
| Nguyễn Xuân Hoàng_K24DTCN599 | Đăng nhập, đổi mật khẩu, OTP | Tạo mật khẩu khi cần, OTP khi cập nhật thông tin |
| Thùy Dinh | Giao dịch điểm và ví người dùng | Thiết kế ví, kiểm tra điều kiện, lưu lịch sử giao dịch, OTP xác nhận chuyển điểm |
| Đoàn Thùy Dương_K24DTCN581 | Quản lý người dùng & viết báo cáo | Tạo tài khoản hộ, cập nhật hộ, hiển thị danh sách người dùng, viết README, tài liệu phân công |

C. 📋 Đặc tả chức năng

C.1. Chức năng chính
- Đăng ký tài khoản
- Tạo tài khoản cho người khác (admin)
- Đăng nhập (kiểm tra thông tin + phân quyền)
- Cập nhật thông tin của chính mình
- Cập nhật thông tin người khác (admin)
- Quản lý thông tin cá nhân
- Quản lý danh sách người dùng (admin)
- Chuyển điểm cho người khác & Theo dõi lịch sử giao dịch
- Lưu trữ thông tin vào file `userdata.txt`
- Phân quyền `admin` và `user`
- Sao lưu dữ liệu vào thư mục `backup/`
- Xác thực OTP

D. ⚙️ Cách tải và dịch chương trình

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

1. Chọn `1` để tự đăng ký tài khoản mới
2. Chọn `2` để đăng nhập
3. Sau khi đăng nhập (nếu là admin), bạn có thể:
   - Tạo tài khoản hộ người khác
   - Cập nhật thông tin người dùng
   - Xem danh sách tất cả tài khoản

## 📚 Tài liệu tham khảo

- Tài liệu cấu trúc dữ liệu & thuật toán cơ bản
- Hướng dẫn C++ trên GeeksForGeeks và Cplusplus.com
- Mẫu phân công và README từ các đồ án trước năm học

---

✔️ Dự án hoàn thành bởi nhóm sinh viên Khoa CNTT PTIT lớp D24TXCN15-K, với mục tiêu mô phỏng một hệ thống quản lý người dùng đơn giản nhưng có đầy đủ quyền và chức năng cơ bản.