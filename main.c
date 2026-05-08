#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_CUSTOMERS 300
#define MAX_BOOKS 500
#define MAX_INVOICE_ITEMS 100
#define MAX_INVOICES 500
#define STR_SMALL 32
#define STR_MED 64
#define STR_LARGE 128
#define PHONE_LEN 20
#define DATE_LEN 16

typedef struct {
    char id[STR_SMALL];
    char name[STR_MED];
    char phone[PHONE_LEN];
    char email[STR_MED];
    char address[STR_LARGE];
    char regDate[DATE_LEN];
    int isVIP; /* 0: Thuong, 1: VIP */
    int active;
} Customer;

typedef struct {
    char isbn[STR_SMALL];
    char title[STR_LARGE];
    char author[STR_MED];
    char publisher[STR_MED];
    int year;
    char category[STR_MED];
    double importPrice;
    double sellPrice;
    int stock;
    int active;
} Book;

typedef struct {
    char isbn[STR_SMALL];
    int quantity;
    double unitPrice;
    double lineTotal;
} InvoiceItem;

typedef struct {
    char invoiceId[STR_SMALL];
    char customerId[STR_SMALL];
    char date[DATE_LEN];
    InvoiceItem items[MAX_INVOICE_ITEMS];
    int itemCount;
    double subTotal;
    double discount;
    double vat;
    double total;
    int active;
} Invoice;

Customer customers[MAX_CUSTOMERS];
Book books[MAX_BOOKS];
Invoice invoices[MAX_INVOICES];

int customerCount = 0;
int bookCount = 0;
int invoiceCount = 0;

void readLine(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

void toLowerStr(char *s) {
    int i;
    for (i = 0; s[i] != '\0'; i++) {
        s[i] = (char)tolower((unsigned char)s[i]);
    }
}

int containsIgnoreCase(const char *text, const char *keyword) {
    char a[STR_LARGE], b[STR_LARGE];
    strncpy(a, text, sizeof(a) - 1);
    a[sizeof(a) - 1] = '\0';
    strncpy(b, keyword, sizeof(b) - 1);
    b[sizeof(b) - 1] = '\0';
    toLowerStr(a);
    toLowerStr(b);
    return strstr(a, b) != NULL;
}

int findCustomerIndexById(const char *id) {
    int i;
    for (i = 0; i < customerCount; i++) {
        if (customers[i].active && strcmp(customers[i].id, id) == 0) return i;
    }
    return -1;
}

int findBookIndexByISBN(const char *isbn) {
    int i;
    for (i = 0; i < bookCount; i++) {
        if (books[i].active && strcmp(books[i].isbn, isbn) == 0) return i;
    }
    return -1;
}

void printCustomerHeader() {
    printf("%-10s %-20s %-15s %-22s %-8s\n", "MaKH", "Ho ten", "SDT", "Email", "Loai");
}

void viewCustomers() {
    int i, found = 0;
    printCustomerHeader();
    for (i = 0; i < customerCount; i++) {
        if (customers[i].active) {
            found = 1;
            printf("%-10s %-20s %-15s %-22s %-8s\n",
                   customers[i].id,
                   customers[i].name,
                   customers[i].phone,
                   customers[i].email,
                   customers[i].isVIP ? "VIP" : "Thuong");
        }
    }
    if (!found) printf("Khong co khach hang nao.\n");
}

void addCustomer() {
    Customer c;
    if (customerCount >= MAX_CUSTOMERS) {
        printf("Danh sach khach hang da day.\n");
        return;
    }
    printf("Nhap ma khach hang: "); readLine(c.id, STR_SMALL);
    if (findCustomerIndexById(c.id) != -1) {
        printf("Ma khach hang da ton tai.\n");
        return;
    }
    printf("Nhap ho ten: "); readLine(c.name, STR_MED);
    printf("Nhap so dien thoai: "); readLine(c.phone, PHONE_LEN);
    printf("Nhap email: "); readLine(c.email, STR_MED);
    printf("Nhap dia chi: "); readLine(c.address, STR_LARGE);
    printf("Nhap ngay dang ky (dd/mm/yyyy): "); readLine(c.regDate, DATE_LEN);
    printf("Loai thanh vien (0=Thuong, 1=VIP): "); scanf("%d", &c.isVIP); getchar();

    c.active = 1;
    customers[customerCount++] = c;
    printf("Them khach hang thanh cong.\n");
}

void editCustomer() {
    char id[STR_SMALL];
    int idx;
    printf("Nhap ma khach hang can sua: "); readLine(id, STR_SMALL);
    idx = findCustomerIndexById(id);
    if (idx == -1) {
        printf("Khong tim thay khach hang.\n");
        return;
    }
    printf("Nhap ho ten moi: "); readLine(customers[idx].name, STR_MED);
    printf("Nhap SDT moi: "); readLine(customers[idx].phone, PHONE_LEN);
    printf("Nhap email moi: "); readLine(customers[idx].email, STR_MED);
    printf("Nhap dia chi moi: "); readLine(customers[idx].address, STR_LARGE);
    printf("Nhap loai (0=Thuong, 1=VIP): "); scanf("%d", &customers[idx].isVIP); getchar();
    printf("Cap nhat khach hang thanh cong.\n");
}

void deleteCustomer() {
    char id[STR_SMALL];
    int idx;
    printf("Nhap ma khach hang can xoa: "); readLine(id, STR_SMALL);
    idx = findCustomerIndexById(id);
    if (idx == -1) {
        printf("Khong tim thay khach hang.\n");
        return;
    }
    customers[idx].active = 0;
    printf("Xoa khach hang thanh cong.\n");
}

void searchCustomerByPhone() {
    char phone[PHONE_LEN];
    int i, found = 0;
    printf("Nhap SDT can tim: "); readLine(phone, PHONE_LEN);
    printCustomerHeader();
    for (i = 0; i < customerCount; i++) {
        if (customers[i].active && strcmp(customers[i].phone, phone) == 0) {
            found = 1;
            printf("%-10s %-20s %-15s %-22s %-8s\n",
                   customers[i].id, customers[i].name, customers[i].phone,
                   customers[i].email, customers[i].isVIP ? "VIP" : "Thuong");
        }
    }
    if (!found) printf("Khong tim thay theo SDT.\n");
}

void searchCustomerByName() {
    char key[STR_MED];
    int i, found = 0;
    printf("Nhap ten can tim: "); readLine(key, STR_MED);
    printCustomerHeader();
    for (i = 0; i < customerCount; i++) {
        if (customers[i].active && containsIgnoreCase(customers[i].name, key)) {
            found = 1;
            printf("%-10s %-20s %-15s %-22s %-8s\n",
                   customers[i].id, customers[i].name, customers[i].phone,
                   customers[i].email, customers[i].isVIP ? "VIP" : "Thuong");
        }
    }
    if (!found) printf("Khong tim thay theo ten.\n");
}

void viewBooks() {
    int i, found = 0;
    printf("%-14s %-20s %-12s %-8s %-10s\n", "ISBN", "Ten sach", "The loai", "GiaBan", "TonKho");
    for (i = 0; i < bookCount; i++) {
        if (books[i].active) {
            found = 1;
            printf("%-14s %-20s %-12s %-8.2f %-10d\n",
                   books[i].isbn, books[i].title, books[i].category,
                   books[i].sellPrice, books[i].stock);
        }
    }
    if (!found) printf("Khong co sach nao.\n");
}

void addBook() {
    Book b;
    if (bookCount >= MAX_BOOKS) {
        printf("Danh sach sach da day.\n");
        return;
    }
    printf("Nhap ISBN: "); readLine(b.isbn, STR_SMALL);
    if (findBookIndexByISBN(b.isbn) != -1) {
        printf("ISBN da ton tai.\n");
        return;
    }
    printf("Nhap ten sach: "); readLine(b.title, STR_LARGE);
    printf("Nhap tac gia: "); readLine(b.author, STR_MED);
    printf("Nhap NXB: "); readLine(b.publisher, STR_MED);
    printf("Nhap nam xuat ban: "); scanf("%d", &b.year); getchar();
    printf("Nhap the loai: "); readLine(b.category, STR_MED);
    printf("Nhap gia nhap: "); scanf("%lf", &b.importPrice); getchar();
    printf("Nhap gia ban: "); scanf("%lf", &b.sellPrice); getchar();
    printf("Nhap so luong ton kho: "); scanf("%d", &b.stock); getchar();
    b.active = 1;
    books[bookCount++] = b;
    printf("Them sach thanh cong.\n");
}

void editBook() {
    char isbn[STR_SMALL];
    int idx;
    printf("Nhap ISBN can sua: "); readLine(isbn, STR_SMALL);
    idx = findBookIndexByISBN(isbn);
    if (idx == -1) {
        printf("Khong tim thay sach.\n");
        return;
    }
    printf("Nhap ten sach moi: "); readLine(books[idx].title, STR_LARGE);
    printf("Nhap tac gia moi: "); readLine(books[idx].author, STR_MED);
    printf("Nhap NXB moi: "); readLine(books[idx].publisher, STR_MED);
    printf("Nhap nam xuat ban moi: "); scanf("%d", &books[idx].year); getchar();
    printf("Nhap the loai moi: "); readLine(books[idx].category, STR_MED);
    printf("Nhap gia nhap moi: "); scanf("%lf", &books[idx].importPrice); getchar();
    printf("Nhap gia ban moi: "); scanf("%lf", &books[idx].sellPrice); getchar();
    printf("Nhap ton kho moi: "); scanf("%d", &books[idx].stock); getchar();
    printf("Cap nhat sach thanh cong.\n");
}

void deleteBook() {
    char isbn[STR_SMALL];
    int idx;
    printf("Nhap ISBN can xoa: "); readLine(isbn, STR_SMALL);
    idx = findBookIndexByISBN(isbn);
    if (idx == -1) {
        printf("Khong tim thay sach.\n");
        return;
    }
    if (books[idx].stock != 0) {
        printf("Chi duoc xoa khi ton kho bang 0.\n");
        return;
    }
    books[idx].active = 0;
    printf("Xoa sach thanh cong.\n");
}

void searchBookByISBN() {
    char isbn[STR_SMALL];
    int idx;
    printf("Nhap ISBN can tim: "); readLine(isbn, STR_SMALL);
    idx = findBookIndexByISBN(isbn);
    if (idx == -1) {
        printf("Khong tim thay sach.\n");
        return;
    }
    printf("Sach: %s | %s | Ton kho: %d | Gia ban: %.2f\n",
           books[idx].isbn, books[idx].title, books[idx].stock, books[idx].sellPrice);
}

void searchBookByTitle() {
    char key[STR_MED];
    int i, found = 0;
    printf("Nhap ten sach can tim: "); readLine(key, STR_MED);
    for (i = 0; i < bookCount; i++) {
        if (books[i].active && containsIgnoreCase(books[i].title, key)) {
            found = 1;
            printf("%s | %s | Ton kho: %d | Gia ban: %.2f\n",
                   books[i].isbn, books[i].title, books[i].stock, books[i].sellPrice);
        }
    }
    if (!found) printf("Khong tim thay sach theo ten.\n");
}

void createInvoice() {
    Invoice inv;
    int cIdx, n, i;

    if (invoiceCount >= MAX_INVOICES) {
        printf("Danh sach hoa don da day.\n");
        return;
    }
    printf("Nhap ma hoa don: "); readLine(inv.invoiceId, STR_SMALL);
    printf("Nhap ma khach hang: "); readLine(inv.customerId, STR_SMALL);
    cIdx = findCustomerIndexById(inv.customerId);
    if (cIdx == -1) {
        printf("Khach hang khong ton tai.\n");
        return;
    }
    printf("Nhap ngay lap (dd/mm/yyyy): "); readLine(inv.date, DATE_LEN);
    printf("Nhap so dong sach trong hoa don: "); scanf("%d", &n); getchar();
    if (n <= 0 || n > MAX_INVOICE_ITEMS) {
        printf("So dong khong hop le.\n");
        return;
    }

    inv.itemCount = n;
    inv.subTotal = 0.0;
    for (i = 0; i < n; i++) {
        int bIdx;
        printf("--- Dong %d ---\n", i + 1);
        printf("ISBN: "); readLine(inv.items[i].isbn, STR_SMALL);
        bIdx = findBookIndexByISBN(inv.items[i].isbn);
        if (bIdx == -1) {
            printf("ISBN khong ton tai.\n");
            return;
        }
        printf("So luong: "); scanf("%d", &inv.items[i].quantity); getchar();
        if (inv.items[i].quantity <= 0 || inv.items[i].quantity > books[bIdx].stock) {
            printf("So luong khong hop le / vuot ton kho.\n");
            return;
        }

        inv.items[i].unitPrice = books[bIdx].sellPrice;
        inv.items[i].lineTotal = inv.items[i].quantity * inv.items[i].unitPrice;

        if (inv.items[i].quantity > 5) {
            inv.items[i].lineTotal *= 0.95; /* giam 5% neu mua >5 cung dau sach */
        }

        inv.subTotal += inv.items[i].lineTotal;
        books[bIdx].stock -= inv.items[i].quantity;
    }

    inv.discount = 0.0;
    if (customers[cIdx].isVIP) {
        inv.discount += inv.subTotal * 0.10;
    }

    {
        double afterDiscount = inv.subTotal - inv.discount;
        inv.vat = afterDiscount * 0.10;
        inv.total = afterDiscount + inv.vat;
    }

    inv.active = 1;
    invoices[invoiceCount++] = inv;

    printf("\n===== HOA DON =====\n");
    printf("Ma HD: %s | Ma KH: %s | Ngay: %s\n", inv.invoiceId, inv.customerId, inv.date);
    for (i = 0; i < inv.itemCount; i++) {
        printf("%s | SL: %d | Don gia: %.2f | Thanh tien: %.2f\n",
               inv.items[i].isbn, inv.items[i].quantity, inv.items[i].unitPrice, inv.items[i].lineTotal);
    }
    printf("Tam tinh: %.2f\n", inv.subTotal);
    printf("Giam gia: %.2f\n", inv.discount);
    printf("VAT 10%%: %.2f\n", inv.vat);
    printf("Tong thanh toan: %.2f\n", inv.total);
}

void updateStock() {
    char isbn[STR_SMALL];
    int idx, addQty;
    printf("Nhap ISBN can cap nhat ton kho: "); readLine(isbn, STR_SMALL);
    idx = findBookIndexByISBN(isbn);
    if (idx == -1) {
        printf("Khong tim thay sach.\n");
        return;
    }
    printf("Nhap so luong nhap them (co the am neu can dieu chinh): "); scanf("%d", &addQty); getchar();
    if (books[idx].stock + addQty < 0) {
        printf("Khong the de ton kho am.\n");
        return;
    }
    books[idx].stock += addQty;
    printf("Cap nhat ton kho thanh cong. Ton moi: %d\n", books[idx].stock);
}

void basicStats() {
    int i;
    int totalStock = 0;
    int outOfStock = 0;
    int vip = 0, normal = 0;
    double revenue = 0;

    for (i = 0; i < bookCount; i++) {
        if (books[i].active) {
            totalStock += books[i].stock;
            if (books[i].stock == 0) outOfStock++;
        }
    }
    for (i = 0; i < customerCount; i++) {
        if (customers[i].active) {
            if (customers[i].isVIP) vip++;
            else normal++;
        }
    }
    for (i = 0; i < invoiceCount; i++) {
        if (invoices[i].active) revenue += invoices[i].total;
    }

    printf("\n===== THONG KE =====\n");
    printf("Tong so luong sach trong kho: %d\n", totalStock);
    printf("So sach het hang: %d\n", outOfStock);
    printf("So khach Thuong: %d\n", normal);
    printf("So khach VIP: %d\n", vip);
    printf("Tong doanh thu: %.2f\n", revenue);

    printf("Danh sach sach het hang:\n");
    for (i = 0; i < bookCount; i++) {
        if (books[i].active && books[i].stock == 0) {
            printf("- %s | %s\n", books[i].isbn, books[i].title);
        }
    }
}

void menuCustomers() {
    int choice;
    do {
        printf("\n=== QUAN LY KHACH HANG ===\n");
        printf("1. Xem danh sach\n2. Them\n3. Chinh sua\n4. Xoa\n5. Tim theo SDT\n6. Tim theo ten\n0. Quay lai\n");
        printf("Chon: "); scanf("%d", &choice); getchar();
        switch (choice) {
            case 1: viewCustomers(); break;
            case 2: addCustomer(); break;
            case 3: editCustomer(); break;
            case 4: deleteCustomer(); break;
            case 5: searchCustomerByPhone(); break;
            case 6: searchCustomerByName(); break;
            case 0: break;
            default: printf("Lua chon khong hop le.\n");
        }
    } while (choice != 0);
}

void menuBooks() {
    int choice;
    do {
        printf("\n=== QUAN LY SACH ===\n");
        printf("1. Xem danh sach\n2. Them\n3. Chinh sua\n4. Xoa\n5. Tim theo ISBN\n6. Tim theo ten\n0. Quay lai\n");
        printf("Chon: "); scanf("%d", &choice); getchar();
        switch (choice) {
            case 1: viewBooks(); break;
            case 2: addBook(); break;
            case 3: editBook(); break;
            case 4: deleteBook(); break;
            case 5: searchBookByISBN(); break;
            case 6: searchBookByTitle(); break;
            case 0: break;
            default: printf("Lua chon khong hop le.\n");
        }
    } while (choice != 0);
}

int main() {
    int choice;
    do {
        printf("\n===== CHUONG TRINH QUAN LY NHA SACH =====\n");
        printf("1. Quan ly khach hang\n");
        printf("2. Quan ly sach\n");
        printf("3. Lap hoa don ban hang\n");
        printf("4. Quan ly kho (cap nhat ton kho)\n");
        printf("5. Thong ke co ban\n");
        printf("0. Thoat\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice); getchar();

        switch (choice) {
            case 1: menuCustomers(); break;
            case 2: menuBooks(); break;
            case 3: createInvoice(); break;
            case 4: updateStock(); break;
            case 5: basicStats(); break;
            case 0: printf("Tam biet!\n"); break;
            default: printf("Lua chon khong hop le.\n");
        }
    } while (choice != 0);

    return 0;
}
