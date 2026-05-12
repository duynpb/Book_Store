#include <stdio.h>

#include "books.h"
#include "customers.h"
#include "invoices.h"
#include "menu.h"

void customerMenu(void) {  // Menu quan ly khach hang
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

        if (choice == 1) {
            listCustomers();
        } else if (choice == 2) {
            addCustomer();
        } else if (choice == 3) {
            editCustomer();
        } else if (choice == 4) {
            deleteCustomer();
        } else if (choice == 5) {
            searchCustomerByPhone();
        } else if (choice == 6) {
            searchCustomerByName();
        }
    } while (choice != 0);
}

void bookMenu(void) {  // Menu quan ly sach
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

        if (choice == 1) {
            listBooks();
        } else if (choice == 2) {
            addBook();
        } else if (choice == 3) {
            editBook();
        } else if (choice == 4) {
            deleteBook();
        } else if (choice == 5) {
            searchBookByISBN();
        } else if (choice == 6) {
            searchBookByTitle();
        }
    } while (choice != 0);
}

void mainMenu(void) {  // Menu chinh
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

        if (choice == 1) {
            customerMenu();
        } else if (choice == 2) {
            bookMenu();
        } else if (choice == 3) {
            createInvoice();
        } else if (choice == 4) {
            updateStock();
        } else if (choice == 5) {
            statistics();
        }
    } while (choice != 0);
}
