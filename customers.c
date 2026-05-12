#include <stdio.h>
#include <string.h>

#include "customers.h"
#include "data.h"
#include "utils.h"

void listCustomers(void) {  // Danh sach khach hang dang co
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
    if (!found) {
        printf("Chua co khach hang nao.\n");
    }
}

void addCustomer(void) { // Them khach hang moi
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

    printf("Ten KH: ");
    readLine(customerName[customerCount], LEN_NAME);
    printf("SDT: ");
    readLine(customerPhone[customerCount], LEN_PHONE);
    printf("Email: ");
    readLine(customerEmail[customerCount], LEN_EMAIL);
    printf("Dia chi: ");
    readLine(customerAddress[customerCount], LEN_ADDRESS);
    printf("Ngay dang ky: ");
    readLine(customerRegisterDate[customerCount], LEN_DATE);
    printf("Loai (0 Thuong, 1 VIP): ");
    scanf("%d", &customerTypeVIP[customerCount]);
    getchar();

    customerActive[customerCount] = 1;
    customerCount++;
    printf("Them khach hang thanh cong.\n");
}

void editCustomer(void) {  // Sua thong tin khach hang
    char id[LEN_ID];
    int i;

    printf("Nhap ma KH can sua: ");
    readLine(id, LEN_ID);

    i = findCustomerById(id);
    if (i == -1) {
        printf("Khong tim thay KH.\n");
        return;
    }

    printf("Ten moi: ");
    readLine(customerName[i], LEN_NAME);
    printf("SDT moi: ");
    readLine(customerPhone[i], LEN_PHONE);
    printf("Email moi: ");
    readLine(customerEmail[i], LEN_EMAIL);
    printf("Dia chi moi: ");
    readLine(customerAddress[i], LEN_ADDRESS);
    printf("Loai moi (0 Thuong, 1 VIP): ");
    scanf("%d", &customerTypeVIP[i]);
    getchar();

    printf("Da cap nhat KH.\n");
}

void deleteCustomer(void) {  // Xoa khach hang
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

void searchCustomerByPhone(void) {  // Tim khach hang theo SDT
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

    if (!found) {
        printf("Khong tim thay.\n");
    }
}

void searchCustomerByName(void) {  // Tim khach hang theo ten
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

    if (!found) {
        printf("Khong tim thay.\n");
    }
}
