#include <stdio.h>
#include <string.h>

/* ================== Cau hinh ================== */
#define MAX_CUSTOMERS 100
#define MAX_BOOKS 200
#define MAX_INVOICES 100
#define MAX_ITEMS_PER_INVOICE 20

#define LEN_ID 30
#define LEN_NAME 60
#define LEN_PHONE 20
#define LEN_EMAIL 60
#define LEN_ADDRESS 100
#define LEN_DATE 20
#define LEN_CATEGORY 40

/* ==========================================================
   KHONG dung struct theo yeu cau -> dung mang song song
   Moi dong i cua cac mang la 1 ban ghi khach hang / sach / hoa don
   ========================================================== */

/* -------- Khach hang -------- */
int customerCount = 0;
char customerId[MAX_CUSTOMERS][LEN_ID];
char customerName[MAX_CUSTOMERS][LEN_NAME];
char customerPhone[MAX_CUSTOMERS][LEN_PHONE];
char customerEmail[MAX_CUSTOMERS][LEN_EMAIL];
char customerAddress[MAX_CUSTOMERS][LEN_ADDRESS];
char customerRegisterDate[MAX_CUSTOMERS][LEN_DATE];
int customerTypeVIP[MAX_CUSTOMERS]; /* 0: Thuong, 1: VIP */
int customerActive[MAX_CUSTOMERS];  /* 1: con ton tai, 0: da xoa */

/* -------- Sach -------- */
int bookCount = 0;
char bookISBN[MAX_BOOKS][LEN_ID];
char bookTitle[MAX_BOOKS][LEN_NAME];
char bookAuthor[MAX_BOOKS][LEN_NAME];
char bookPublisher[MAX_BOOKS][LEN_NAME];
int bookYear[MAX_BOOKS];
char bookCategory[MAX_BOOKS][LEN_CATEGORY];
double bookImportPrice[MAX_BOOKS];
double bookSellPrice[MAX_BOOKS];
int bookStock[MAX_BOOKS];
int bookActive[MAX_BOOKS];

/* -------- Hoa don -------- */
int invoiceCount = 0;
char invoiceId[MAX_INVOICES][LEN_ID];
char invoiceCustomerId[MAX_INVOICES][LEN_ID];
char invoiceDate[MAX_INVOICES][LEN_DATE];
int invoiceItemCount[MAX_INVOICES];
double invoiceSubtotal[MAX_INVOICES];
double invoiceDiscount[MAX_INVOICES];
double invoiceVAT[MAX_INVOICES];
double invoiceTotal[MAX_INVOICES];
int invoiceActive[MAX_INVOICES];

/* Chi tiet hoa don: [so_hoa_don][dong_hang] */
char invoiceItemISBN[MAX_INVOICES][MAX_ITEMS_PER_INVOICE][LEN_ID];
int invoiceItemQty[MAX_INVOICES][MAX_ITEMS_PER_INVOICE];
double invoiceItemUnitPrice[MAX_INVOICES][MAX_ITEMS_PER_INVOICE];
double invoiceItemLineTotal[MAX_INVOICES][MAX_ITEMS_PER_INVOICE];

/* ================== Ham ho tro ================== */
void readLine(char s[], int maxLen) {
    fgets(s, maxLen, stdin);
    s[strcspn(s, "\n")] = '\0';
}

int findCustomerById(const char id[]) {
    int i;
    for (i = 0; i < customerCount; i++) {
        if (customerActive[i] == 1 && strcmp(customerId[i], id) == 0) {
            return i;
        }
    }
    return -1;
}

int findBookByISBN(const char isbn[]) {
    int i;
    for (i = 0; i < bookCount; i++) {
        if (bookActive[i] == 1 && strcmp(bookISBN[i], isbn) == 0) {
            return i;
        }
    }
    return -1;
}

int containsText(const char text[], const char keyword[]) {
    /* Ban don gian: so khop dung chu hoa/thuong */
    if (strstr(text, keyword) != NULL) return 1;
    return 0;
}

/* ================== Khach hang ================== */
void listCustomers() {
    int i, found = 0;
    printf("\n--- Danh sach khach hang ---\n");
    for (i = 0; i < customerCount; i++) {
        if (customerActive[i] == 1) {
            found = 1;
            printf("%s | %s | %s | %s | %s\n",
                   customerId[i], customerName[i], customerPhone[i],
                   customerEmail[i], customerTypeVIP[i] ? "VIP" : "Thuong");
        }
    }
    if (!found) printf("Chua co khach hang nao.\n");
}

void addCustomer() {
    if (customerCount >= MAX_CUSTOMERS) {
        printf("Danh sach khach hang da day.\n");
        return;
    }

    printf("Ma KH: ");
    readLine(customerId[customerCount], LEN_ID);

    if (findCustomerById(customerId[customerCount]) != -1) {
        printf("Ma KH da ton tai.\n");
        return;
    }

    printf("Ten KH: "); readLine(customerName[customerCount], LEN_NAME);
    printf("SDT: "); readLine(customerPhone[customerCount], LEN_PHONE);
    printf("Email: "); readLine(customerEmail[customerCount], LEN_EMAIL);
    printf("Dia chi: "); readLine(customerAddress[customerCount], LEN_ADDRESS);
    printf("Ngay dang ky: "); readLine(customerRegisterDate[customerCount], LEN_DATE);
    printf("Loai (0 Thuong, 1 VIP): "); scanf("%d", &customerTypeVIP[customerCount]); getchar();

    customerActive[customerCount] = 1;
    customerCount++;
    printf("Them khach hang thanh cong.\n");
}

void editCustomer() {
    char id[LEN_ID];
    int i;

    printf("Nhap ma KH can sua: ");
    readLine(id, LEN_ID);

    i = findCustomerById(id);
    if (i == -1) {
        printf("Khong tim thay KH.\n");
        return;
    }

    printf("Ten moi: "); readLine(customerName[i], LEN_NAME);
    printf("SDT moi: "); readLine(customerPhone[i], LEN_PHONE);
    printf("Email moi: "); readLine(customerEmail[i], LEN_EMAIL);
    printf("Dia chi moi: "); readLine(customerAddress[i], LEN_ADDRESS);
    printf("Loai moi (0 Thuong, 1 VIP): "); scanf("%d", &customerTypeVIP[i]); getchar();

    printf("Da cap nhat KH.\n");
}

void deleteCustomer() {
    char id[LEN_ID];
    int i;

    printf("Nhap ma KH can xoa: ");
    readLine(id, LEN_ID);

    i = findCustomerById(id);
    if (i == -1) {
        printf("Khong tim thay KH.\n");
        return;
    }

    customerActive[i] = 0;
    printf("Da xoa KH.\n");
}

void searchCustomerByPhone() {
    char phone[LEN_PHONE];
    int i, found = 0;

    printf("Nhap SDT can tim: ");
    readLine(phone, LEN_PHONE);

    for (i = 0; i < customerCount; i++) {
        if (customerActive[i] == 1 && strcmp(customerPhone[i], phone) == 0) {
            found = 1;
            printf("%s | %s | %s\n", customerId[i], customerName[i], customerPhone[i]);
        }
    }

    if (!found) printf("Khong tim thay.\n");
}

void searchCustomerByName() {
    char keyword[LEN_NAME];
    int i, found = 0;

    printf("Nhap ten can tim: ");
    readLine(keyword, LEN_NAME);

    for (i = 0; i < customerCount; i++) {
        if (customerActive[i] == 1 && containsText(customerName[i], keyword)) {
            found = 1;
            printf("%s | %s\n", customerId[i], customerName[i]);
        }
    }

    if (!found) printf("Khong tim thay.\n");
}

/* ================== Sach ================== */
void listBooks() {
    int i, found = 0;
    printf("\n--- Danh sach sach ---\n");
    for (i = 0; i < bookCount; i++) {
        if (bookActive[i] == 1) {
            found = 1;
            printf("%s | %s | %s | Gia %.2f | Ton %d\n",
                   bookISBN[i], bookTitle[i], bookCategory[i], bookSellPrice[i], bookStock[i]);
        }
    }
    if (!found) printf("Chua co sach nao.\n");
}

void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Danh sach sach da day.\n");
        return;
    }

    printf("ISBN: ");
    readLine(bookISBN[bookCount], LEN_ID);

    if (findBookByISBN(bookISBN[bookCount]) != -1) {
        printf("ISBN da ton tai.\n");
        return;
    }

    printf("Ten sach: "); readLine(bookTitle[bookCount], LEN_NAME);
    printf("Tac gia: "); readLine(bookAuthor[bookCount], LEN_NAME);
    printf("NXB: "); readLine(bookPublisher[bookCount], LEN_NAME);
    printf("Nam XB: "); scanf("%d", &bookYear[bookCount]); getchar();
    printf("The loai: "); readLine(bookCategory[bookCount], LEN_CATEGORY);
    printf("Gia nhap: "); scanf("%lf", &bookImportPrice[bookCount]); getchar();
    printf("Gia ban: "); scanf("%lf", &bookSellPrice[bookCount]); getchar();
    printf("Ton kho: "); scanf("%d", &bookStock[bookCount]); getchar();

    bookActive[bookCount] = 1;
    bookCount++;
    printf("Them sach thanh cong.\n");
}

void editBook() {
    char isbn[LEN_ID];
    int i;

    printf("Nhap ISBN can sua: ");
    readLine(isbn, LEN_ID);

    i = findBookByISBN(isbn);
    if (i == -1) {
        printf("Khong tim thay sach.\n");
        return;
    }

    printf("Ten moi: "); readLine(bookTitle[i], LEN_NAME);
    printf("Tac gia moi: "); readLine(bookAuthor[i], LEN_NAME);
    printf("NXB moi: "); readLine(bookPublisher[i], LEN_NAME);
    printf("Nam moi: "); scanf("%d", &bookYear[i]); getchar();
    printf("The loai moi: "); readLine(bookCategory[i], LEN_CATEGORY);
    printf("Gia nhap moi: "); scanf("%lf", &bookImportPrice[i]); getchar();
    printf("Gia ban moi: "); scanf("%lf", &bookSellPrice[i]); getchar();
    printf("Ton kho moi: "); scanf("%d", &bookStock[i]); getchar();

    printf("Da cap nhat sach.\n");
}

void deleteBook() {
    char isbn[LEN_ID];
    int i;

    printf("Nhap ISBN can xoa: ");
    readLine(isbn, LEN_ID);

    i = findBookByISBN(isbn);
    if (i == -1) {
        printf("Khong tim thay sach.\n");
        return;
    }

    if (bookStock[i] != 0) {
        printf("Chi duoc xoa khi ton kho = 0.\n");
        return;
    }

    bookActive[i] = 0;
    printf("Da xoa sach.\n");
}

void searchBookByISBN() {
    char isbn[LEN_ID];
    int i;

    printf("Nhap ISBN can tim: ");
    readLine(isbn, LEN_ID);

    i = findBookByISBN(isbn);
    if (i == -1) {
        printf("Khong tim thay sach.\n");
        return;
    }

    printf("%s | %s | Ton %d | Gia %.2f\n", bookISBN[i], bookTitle[i], bookStock[i], bookSellPrice[i]);
}

void searchBookByTitle() {
    char keyword[LEN_NAME];
    int i, found = 0;

    printf("Nhap ten sach can tim: ");
    readLine(keyword, LEN_NAME);

    for (i = 0; i < bookCount; i++) {
        if (bookActive[i] == 1 && containsText(bookTitle[i], keyword)) {
            found = 1;
            printf("%s | %s\n", bookISBN[i], bookTitle[i]);
        }
    }

    if (!found) printf("Khong tim thay sach.\n");
}

/* ================== Hoa don + kho + thong ke ================== */
void createInvoice() {
    int i, n, customerIndex;

    if (invoiceCount >= MAX_INVOICES) {
        printf("Danh sach hoa don da day.\n");
        return;
    }

    printf("Ma hoa don: "); readLine(invoiceId[invoiceCount], LEN_ID);
    printf("Ma khach hang: "); readLine(invoiceCustomerId[invoiceCount], LEN_ID);

    customerIndex = findCustomerById(invoiceCustomerId[invoiceCount]);
    if (customerIndex == -1) {
        printf("Khach hang khong ton tai.\n");
        return;
    }

    printf("Ngay lap: "); readLine(invoiceDate[invoiceCount], LEN_DATE);

    printf("So dong sach: ");
    scanf("%d", &n);
    getchar();

    if (n <= 0 || n > MAX_ITEMS_PER_INVOICE) {
        printf("So dong khong hop le.\n");
        return;
    }

    invoiceItemCount[invoiceCount] = n;
    invoiceSubtotal[invoiceCount] = 0;

    for (i = 0; i < n; i++) {
        int bi;
        printf("\nDong %d\n", i + 1);

        printf("ISBN: ");
        readLine(invoiceItemISBN[invoiceCount][i], LEN_ID);

        bi = findBookByISBN(invoiceItemISBN[invoiceCount][i]);
        if (bi == -1) {
            printf("ISBN khong ton tai.\n");
            return;
        }

        printf("So luong: ");
        scanf("%d", &invoiceItemQty[invoiceCount][i]);
        getchar();

        if (invoiceItemQty[invoiceCount][i] <= 0 || invoiceItemQty[invoiceCount][i] > bookStock[bi]) {
            printf("So luong khong hop le hoac vuot ton kho.\n");
            return;
        }

        invoiceItemUnitPrice[invoiceCount][i] = bookSellPrice[bi];
        invoiceItemLineTotal[invoiceCount][i] = invoiceItemUnitPrice[invoiceCount][i] * invoiceItemQty[invoiceCount][i];

        if (invoiceItemQty[invoiceCount][i] > 5) {
            invoiceItemLineTotal[invoiceCount][i] = invoiceItemLineTotal[invoiceCount][i] * 0.95;
        }

        invoiceSubtotal[invoiceCount] += invoiceItemLineTotal[invoiceCount][i];

        /* Tru ton kho sau khi ban */
        bookStock[bi] -= invoiceItemQty[invoiceCount][i];
    }

    if (customerTypeVIP[customerIndex] == 1) {
        invoiceDiscount[invoiceCount] = invoiceSubtotal[invoiceCount] * 0.10;
    } else {
        invoiceDiscount[invoiceCount] = 0;
    }

    {
        double afterDiscount = invoiceSubtotal[invoiceCount] - invoiceDiscount[invoiceCount];
        invoiceVAT[invoiceCount] = afterDiscount * 0.10;
        invoiceTotal[invoiceCount] = afterDiscount + invoiceVAT[invoiceCount];
    }

    invoiceActive[invoiceCount] = 1;

    printf("\n--- HOA DON ---\n");
    printf("Ma HD: %s\n", invoiceId[invoiceCount]);
    printf("Tam tinh: %.2f\n", invoiceSubtotal[invoiceCount]);
    printf("Giam gia: %.2f\n", invoiceDiscount[invoiceCount]);
    printf("VAT: %.2f\n", invoiceVAT[invoiceCount]);
    printf("Tong thanh toan: %.2f\n", invoiceTotal[invoiceCount]);

    invoiceCount++;
}

void updateStock() {
    char isbn[LEN_ID];
    int i, delta;

    printf("Nhap ISBN can cap nhat ton: ");
    readLine(isbn, LEN_ID);

    i = findBookByISBN(isbn);
    if (i == -1) {
        printf("Khong tim thay sach.\n");
        return;
    }

    printf("Nhap so luong thay doi (co the am): ");
    scanf("%d", &delta);
    getchar();

    if (bookStock[i] + delta < 0) {
        printf("Ton kho khong duoc am.\n");
        return;
    }

    bookStock[i] += delta;
    printf("Ton moi: %d\n", bookStock[i]);
}

void statistics() {
    int i;
    int totalStock = 0;
    int outOfStock = 0;
    int vipCount = 0;
    int normalCount = 0;
    double revenue = 0;

    for (i = 0; i < bookCount; i++) {
        if (bookActive[i] == 1) {
            totalStock += bookStock[i];
            if (bookStock[i] == 0) outOfStock++;
        }
    }

    for (i = 0; i < customerCount; i++) {
        if (customerActive[i] == 1) {
            if (customerTypeVIP[i] == 1) vipCount++;
            else normalCount++;
        }
    }

    for (i = 0; i < invoiceCount; i++) {
        if (invoiceActive[i] == 1) {
            revenue += invoiceTotal[i];
        }
    }

    printf("\n--- THONG KE ---\n");
    printf("Tong so luong sach trong kho: %d\n", totalStock);
    printf("So dau sach het hang: %d\n", outOfStock);
    printf("So KH Thuong: %d\n", normalCount);
    printf("So KH VIP: %d\n", vipCount);
    printf("Tong doanh thu: %.2f\n", revenue);
}

/* ================== Menu ================== */
void customerMenu() {
    int choice;
    do {
        printf("\n=== MENU KHACH HANG ===\n");
        printf("1. Xem danh sach\n");
        printf("2. Them\n");
        printf("3. Sua\n");
        printf("4. Xoa\n");
        printf("5. Tim theo SDT\n");
        printf("6. Tim theo ten\n");
        printf("0. Quay lai\n");
        printf("Chon: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) listCustomers();
        else if (choice == 2) addCustomer();
        else if (choice == 3) editCustomer();
        else if (choice == 4) deleteCustomer();
        else if (choice == 5) searchCustomerByPhone();
        else if (choice == 6) searchCustomerByName();
    } while (choice != 0);
}

void bookMenu() {
    int choice;
    do {
        printf("\n=== MENU SACH ===\n");
        printf("1. Xem danh sach\n");
        printf("2. Them\n");
        printf("3. Sua\n");
        printf("4. Xoa\n");
        printf("5. Tim theo ISBN\n");
        printf("6. Tim theo ten\n");
        printf("0. Quay lai\n");
        printf("Chon: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) listBooks();
        else if (choice == 2) addBook();
        else if (choice == 3) editBook();
        else if (choice == 4) deleteBook();
        else if (choice == 5) searchBookByISBN();
        else if (choice == 6) searchBookByTitle();
    } while (choice != 0);
}

int main() {
    int choice;

    do {
        printf("\n===== QUAN LY NHA SACH =====\n");
        printf("1. Quan ly khach hang\n");
        printf("2. Quan ly sach\n");
        printf("3. Lap hoa don\n");
        printf("4. Cap nhat ton kho\n");
        printf("5. Thong ke\n");
        printf("0. Thoat\n");
        printf("Nhap lua chon: ");

        scanf("%d", &choice);
        getchar();

        if (choice == 1) customerMenu();
        else if (choice == 2) bookMenu();
        else if (choice == 3) createInvoice();
        else if (choice == 4) updateStock();
        else if (choice == 5) statistics();

    } while (choice != 0);

    return 0;
}