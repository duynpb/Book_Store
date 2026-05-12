#include <stdio.h>
#include <string.h>

#include "data.h"
#include "invoices.h"
#include "utils.h"

void createInvoice(void) {  // Lap hoa don moi
    int i, n, customerIndex;

    if (invoiceCount >= MAX_INVOICES) {
        printf("Danh sach hoa don da day.\n");
        return;
    }

    printf("Ma hoa don: ");
    readLine(invoiceId[invoiceCount], LEN_ID);
    printf("Ma khach hang: ");
    readLine(invoiceCustomerId[invoiceCount], LEN_ID);

    customerIndex = findCustomerById(invoiceCustomerId[invoiceCount]);
    if (customerIndex == -1) {
        printf("Khach hang khong ton tai.\n");
        return;
    }

    printf("Ngay lap: ");
    readLine(invoiceDate[invoiceCount], LEN_DATE);

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

        if (invoiceItemQty[invoiceCount][i] <= 0 ||
            invoiceItemQty[invoiceCount][i] > bookStock[bi]) {
            printf("So luong khong hop le hoac vuot ton kho.\n");
            return;
        }

        invoiceItemUnitPrice[invoiceCount][i] = bookSellPrice[bi];
        invoiceItemLineTotal[invoiceCount][i] =
            invoiceItemUnitPrice[invoiceCount][i] * invoiceItemQty[invoiceCount][i];

        if (invoiceItemQty[invoiceCount][i] > 5) {
            invoiceItemLineTotal[invoiceCount][i] *= 0.95;
        }

        invoiceSubtotal[invoiceCount] += invoiceItemLineTotal[invoiceCount][i];
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

void updateStock(void) {  // Cap nhat ton kho sach
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

void statistics(void) {  // Thong ke
    char keyword[LEN_DATE];
    int choice, i;
    int totalStock = 0;
    int outOfStock = 0;
    int vipCount = 0;
    int normalCount = 0;
    double revenue = 0;

    char categoryList[MAX_BOOKS][LEN_CATEGORY];
    int categoryCount[MAX_BOOKS];
    int categoryTypes = 0;

    for (i = 0; i < bookCount; i++) {
        if (bookActive[i] == 1) {
            totalStock += bookStock[i];
            if (bookStock[i] == 0) {
                outOfStock++;
            }

            int found = 0;
            int j;
            for (j = 0; j < categoryTypes; j++) {
                if (strcmp(categoryList[j], bookCategory[i]) == 0) {
                    categoryCount[j] += bookStock[i];
                    found = 1;
                    break;
                }
            }

            if (!found) {
                strcpy(categoryList[categoryTypes], bookCategory[i]);
                categoryCount[categoryTypes] = bookStock[i];
                categoryTypes++;
            }
        }
    }

    for (i = 0; i < customerCount; i++) {
        if (customerActive[i] == 1) {
            if (customerTypeVIP[i] == 1) {
                vipCount++;
            } else {
                normalCount++;
            }
        }
    }

    printf("\nChon kieu thong ke doanh thu:\n");
    printf("1. Tong tat ca hoa don\n");
    printf("2. Theo ngay (vi du 08/05/2026)\n");
    printf("3. Theo thang/nam (vi du 05/2026)\n");
    printf("Chon: ");
    scanf("%d", &choice);
    getchar();

    keyword[0] = '\0';
    if (choice == 2) {
        printf("Nhap ngay: ");
        readLine(keyword, LEN_DATE);
    } else if (choice == 3) {
        printf("Nhap thang/nam: ");
        readLine(keyword, LEN_DATE);
    }

    for (i = 0; i < invoiceCount; i++) {
        if (invoiceActive[i] == 1 &&
            (choice == 1 || containsText(invoiceDate[i], keyword))) {
            revenue += invoiceTotal[i];
        }
    }

    printf("\n--- THONG KE ---\n");
    printf("Tong so luong sach trong kho: %d\n", totalStock);
    printf("So dau sach het hang: %d\n", outOfStock);
    printf("So KH Thuong: %d\n", normalCount);
    printf("So KH VIP: %d\n", vipCount);

    if (categoryTypes > 0) {
        printf("\nSo luong sach theo the loai:\n");
        for (i = 0; i < categoryTypes; i++) {
            printf("- %s: %d\n", categoryList[i], categoryCount[i]);
        }
    }

    if (choice == 2) {
        printf("Doanh thu ngay %s: %.2f\n", keyword, revenue);
    } else if (choice == 3) {
        printf("Doanh thu thang/nam %s: %.2f\n", keyword, revenue);
    } else {
        printf("Tong doanh thu: %.2f\n", revenue);
    }
}
