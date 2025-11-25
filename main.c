#include <stdio.h>      // Thư viện chuẩn để nhập/xuất dữ liệu
#include <stdlib.h>     // Thư viện chuẩn cho việc cấp phát bộ nhớ và các hàm khác
#include <string.h>     // Thư viện chuẩn để làm việc với chuỗi ký tự

// Định nghĩa cấu trúc Book lưu thông tin sách
typedef struct {
    char ten[30];   // Tên sách
    char bid[12];   // Mã số sách
    int pb;         // Giá sách
    int qre;        // Số lượng còn lại
} Book;

// Định nghĩa cấu trúc Node cho danh sách liên kết đơn
typedef struct Node {
    Book book;           // Dữ liệu sách
    struct Node *n;      // Con trỏ đến Node tiếp theo
} Node;

// Hàm tạo một Node mới với dữ liệu sách được truyền vào
Node *tao(Book b) {
    Node *nn = (Node*)malloc(sizeof(Node));  // Cấp phát bộ nhớ cho Node mới
    if(!nn) {  // Kiểm tra nếu cấp phát thất bại
        printf("Khong the cap phat bo nho"); // Thông báo lỗi
        return NULL;
    }
    nn->book = b;  // Gán dữ liệu sách vào Node
    nn->n = NULL;  // Khởi tạo con trỏ tiếp theo là NULL
    return nn;     // Trả về Node mới được tạo
}

// Hàm đọc dữ liệu sách từ file và tạo danh sách liên kết
void docfile(const char *filename, Node **h, int *n) {
    FILE *f = fopen(filename, "r");  // Mở file ở chế độ đọc
    if(f == NULL) {  // Kiểm tra nếu mở file thất bại
        printf("Khong the doc duoc file\n\n");  // Thông báo lỗi
        return;
    } else {
        printf("Doc file thanh cong\n\n");  // Thông báo đọc file thành công
    }
    *n = 0;  // Khởi tạo số lượng sách đọc được là 0
    Book b;
    // Đọc từng dòng trong file cho đến khi hết dữ liệu
    while(fscanf(f, "%s\t%[^\t]\t%d\t%d\n", b.bid, b.ten, &b.pb, &b.qre) == 4) {
        Node *nn = tao(b);  // Tạo Node mới cho sách vừa đọc
        if (*h == NULL) {   // Nếu danh sách trống, gán Node này làm đầu danh sách
            *h = nn;
        } else {
            Node *temp = *h;  // Di chuyển đến cuối danh sách
            while (temp->n != NULL) {
                temp = temp->n;
            }
            temp->n = nn;  // Thêm Node mới vào cuối danh sách
        }
        (*n)++;  // Tăng số lượng sách
    }
    fclose(f);  // Đóng file sau khi đọc xong
}

// Hàm in danh sách sách ra màn hình
void Inds(Node *h) {
    printf("\n+--------------------+------------------------------+-------------+------------------+\n");
    printf("|     Ma so sach     |           Ten sach           |     Gia     | So luong con lai |\n");
    printf("+--------------------+------------------------------+-------------+------------------+\n");
    while(h != NULL) {  // Duyệt qua từng Node trong danh sách
        printf("|%-20s|%-30s|%-13d|      %-6d      |\n", h->book.bid, h->book.ten, h->book.pb, h->book.qre);
        h = h->n;  // Di chuyển đến Node tiếp theo
    }
    printf("+--------------------+------------------------------+-------------+------------------+\n\n");
}

// Hàm xuất danh sách sách ra file
void xuatfile(const char *filename, Node *h) {
    FILE *f = fopen(filename, "w");  // Mở file ở chế độ ghi
    if(f == NULL) {  // Kiểm tra nếu mở file thất bại
        printf("Khong ghi duoc file\n\n");  // Thông báo lỗi
        return;
    } else {
        printf("Ghi file thanh cong\n\n");  // Thông báo ghi file thành công
    }

    // In tiêu đề bảng ra file
    fprintf(f, "+--------------------+------------------------------+-------------+------------------+\n");
    fprintf(f, "|     Ma so sach     |           Ten sach           |     Gia     | So luong con lai |\n");
    fprintf(f, "+--------------------+------------------------------+-------------+------------------+\n");
    while(h != NULL) {  // Duyệt qua từng Node trong danh sách
        fprintf(f, "|%-20s|%-30s|%-13d|      %-6d      |\n", h->book.bid, h->book.ten, h->book.pb, h->book.qre);
        h = h->n;  // Di chuyển đến Node tiếp theo
    }
    fprintf(f, "+--------------------+------------------------------+-------------+------------------+\n\n");
    fclose(f);  // Đóng file sau khi ghi xong
}

// Hàm tìm kiếm sách theo mã số
void timsach(Node *h) {
    char maso[12];  // Khai báo biến chứa mã số sách cần tìm
    int k = 0;  // Biến kiểm tra tìm thấy sách hay không
    printf("\nNhap ma so sach can tim: ");
    scanf("%s", maso);  // Nhập mã số sách cần tìm từ bàn phím

    while(h != NULL) {  // Duyệt qua từng Node trong danh sách
        if(strcmp(maso, h->book.bid) == 0) {  // So sánh mã số sách
            // In thông tin sách nếu tìm thấy
            printf("\nMa so: %s\n", h->book.bid);
            printf("Ten sach: %s\n", h->book.ten);
            printf("Gia sach: %d\n", h->book.pb);
            printf("So luong con lai: %d\n\n", h->book.qre);
            k = 1;  // Đánh dấu đã tìm thấy sách
        }
        h = h->n;  // Di chuyển đến Node tiếp theo
    }
    if(k == 0) { printf("\nKhong tim thay\n\n"); }  // Thông báo nếu không tìm thấy sách
}

// Hàm chỉnh sửa thông tin sách theo mã số
void chinhsua(Node *h) {
    char maso[12];  // Khai báo biến chứa mã số sách cần sửa
    int k = 0, c = 0;  // Biến kiểm tra tìm thấy sách và lựa chọn thông tin cần sửa
    printf("\nNhap ma so sach can sua: ");
    scanf("%s", maso);  // Nhập mã số sách cần sửa từ bàn phím

    while(h != NULL) {  // Duyệt qua từng Node trong danh sách
        if(strcmp(maso, h->book.bid) == 0) {  // So sánh mã số sách
            // In thông tin sách hiện tại nếu tìm thấy
            printf("\nThong tin cu cua sach %s\n", h->book.bid);
            printf("Ma so: %s\n", h->book.bid);
            printf("Ten sach: %s\n", h->book.ten);
            printf("Gia sach: %d\n", h->book.pb);
            printf("So luong con lai: %d\n\n", h->book.qre);
            k = 1;  // Đánh dấu đã tìm thấy sách
            break;
        }
        h = h->n;  // Di chuyển đến Node tiếp theo
    }

    if(k == 0) { 
        printf("\nKhong tim thay\n\n");  // Thông báo nếu không tìm thấy sách
    } else {
        // Menu lựa chọn thông tin cần chỉnh sửa
        printf("1.Ma so sach\t2.Ten sach\t3.Gia sach\t4.So luong con lai\t5.Sua toan bo\t6.Thoat\n");
        printf("\nChon thong tin chinh sua (chon so tu: 1->6): ");
        scanf("%d", &c);  // Nhập lựa chọn từ bàn phím
        // Chỉnh sửa thông tin dựa trên lựa chọn
        if(c == 1 || c == 5) { printf("Nhap ma so sach: "); scanf("%s", h->book.bid); }
        if(c == 2 || c == 5) { printf("Nhap ten sach: "); scanf(" %[^\n]", h->book.ten); }
        if(c == 3 || c == 5) { printf("Nhap gia sach: "); scanf("%d", &h->book.pb); }
        if(c == 4 || c == 5) { printf("Nhap so luong con lai: "); scanf("%d", &h->book.qre); }
        if(c == 6) { printf("\nDa thoat\n"); return; }  // Thoát nếu chọn 6
    }
    printf("\n");
}

// Hàm sắp xếp danh sách sách theo mã số sử dụng thuật toán Radix Sort
void xepsachradix(Node **head) {
    // Tìm độ dài lớn nhất của mã số sách
    int maxLength = 0;
    Node *temp = *head;
    while (temp != NULL) {
        int len = strlen(temp->book.bid);  // Tính độ dài mã số sách
        if (len > maxLength) {
            maxLength = len;  // Cập nhật độ dài lớn nhất
        }
        temp = temp->n;  // Di chuyển đến Node tiếp theo
    }

    // Tạo các bucket để sắp xếp
    Node *buckets[256] = {NULL};  // 256 bucket cho tất cả ký tự ASCII
    Node *bucketsTail[256] = {NULL};  // Tail cho từng bucket

    // Sắp xếp theo từng ký tự từ phải sang trái
    for (int exp = maxLength - 1; exp >= 0; exp--) {
        // Đưa các nút vào bucket dựa trên ký tự hiện tại
        temp = *head;
        while (temp != NULL) {
            int len = strlen(temp->book.bid);
            int index = (len > exp) ? (unsigned char)temp->book.bid[exp] : 0;  // Lấy ký tự hiện tại hoặc 0 nếu không có ký tự
            if (buckets[index] == NULL) {
                buckets[index] = temp;  // Thêm Node vào bucket tương ứng
                bucketsTail[index] = temp;  // Cập nhật tail của bucket
            } else {
                bucketsTail[index]->n = temp;  // Thêm Node vào cuối bucket
                bucketsTail[index] = temp;  // Cập nhật tail của bucket
            }
            temp = temp->n;  // Di chuyển đến Node tiếp theo
        }

        // Kết nối lại các bucket để tạo danh sách đã sắp xếp
        *head = NULL;
        Node *tail = NULL;
        for (int i = 0; i < 256; i++) {
            if (buckets[i] != NULL) {
                if (*head == NULL) {
                    *head = buckets[i];  // Đặt bucket đầu tiên làm head
                } else {
                    tail->n = buckets[i];  // Nối tiếp vào danh sách
                }
                tail = bucketsTail[i];  // Cập nhật tail của danh sách
                buckets[i] = NULL;  // Reset bucket
                bucketsTail[i] = NULL;  // Reset tail của bucket
            }
        }
        if (tail != NULL) {
            tail->n = NULL;  // Đặt NULL cho Node cuối cùng
        }
    }
}

void luufile(const char *filename, Node *h) { // Lưu thay đổi vào data.txt
    FILE *f = fopen(filename, "w");
    if(f == NULL) {
        printf("Loi ghi file!\n");
        return;
    }
    while(h != NULL) {
        fprintf(f, "%s\t%s\t%d\t%d\n", h->book.bid, h->book.ten, h->book.pb, h->book.qre); // Lưu dạng thô để lần sau có thể đọc
        h = h->n;
    }
    fclose(f);
    printf("Da luu du lieu vao %s\n", filename);
}

void giaiphong(Node *h) { //Giải phóng dung lượng
    Node *temp;
    while (h != NULL) {
        temp = h;
        h = h->n;
        free(temp); 
    }
}

// Hàm chính của chương trình
int main() {
    Node *h = NULL;  // Khởi tạo danh sách liên kết trống
    int n = 0, c = -1;  // Khởi tạo biến đếm số lượng sách và biến lựa chọn
    printf("Doc du lieu file data.txt\n");
    docfile("data.txt", &h, &n);  // Đọc dữ liệu từ file vào danh sách liên kết
    do {
        // Hiển thị menu lựa chọn
        printf("------------------------Nhap lua chon--------------------------\n");
        printf("1. In va xuat danh sach de kiem tra (file nhap)\n");
        printf("2. Tim sach theo ma so sach\n");
        printf("3. Chinh sua thong tin\n");
        printf("4. Sap xep thu tu tang dan theo ma so sach\n");
        printf("Nhap 0 de thoat va ghi file output.txt\n");
        printf("Moi nhap: ");
        scanf("%d", &c);  // Nhập lựa chọn từ bàn phím
        if(c == 0) {
            luufile("data.txt", h); // Lưu thay đổi vào data.txt (dạng thô)
            xuatfile("output.txt", h);  // Ghi danh sách ra file nếu chọn 0
            break;
        }
        if(c == 1) {
            Inds(h);  // In danh sách sách
            xuatfile("output.txt", h);  // Ghi danh sách ra file
        }
        if(c == 2) {
            timsach(h);  // Tìm sách theo mã số
        }
        if(c == 3) {
            chinhsua(h);  // Chỉnh sửa thông tin sách
        }
        if(c == 4) {
            xepsachradix(&h);  // Sắp xếp danh sách theo mã số sách
            Inds(h);  // In danh sách sau khi sắp xếp
        }
    } while(c != 0);  // Lặp lại menu cho đến khi chọn thoát
    giaiphong(h);
    printf("\nKet thuc\n");
    return 0;
}
