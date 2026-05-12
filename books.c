#include <stdio.h>

#include "books.h"
#include "data.h"
#include "utils.h"

void listBooks(void) {  // Danh sach sach dang co
    int i, found = 0;
    printf("\n--- Danh sach sach ---\n");
    for (i = 0; i < bookCount; i++) {
        if (bookActive[i] == 1) {
            found = 1;
            printf("%s | %s | %s | Gia %.2f | Ton %d\n",
                   bookISBN[i], bookTitle[i], bookCategory[i],
                   bookSellPrice[i], bookStock[i]);
        }
    }
    if (!found) {
        printf("Chua co sach nao.\n");
    }
}

void addBook(void) {  // Them sach moi
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

    printf("Ten sach: ");
    readLine(bookTitle[bookCount], LEN_NAME);
    printf("Tac gia: ");
    readLine(bookAuthor[bookCount], LEN_NAME);
    printf("NXB: ");
    readLine(bookPublisher[bookCount], LEN_NAME);
    printf("Nam XB: ");
    scanf("%d", &bookYear[bookCount]);
    getchar();
    printf("The loai: ");
    readLine(bookCategory[bookCount], LEN_CATEGORY);
    printf("Gia nhap: ");
    scanf("%lf", &bookImportPrice[bookCount]);
    getchar();
    printf("Gia ban: ");
    scanf("%lf", &bookSellPrice[bookCount]);
    getchar();
    printf("Ton kho: ");
    scanf("%d", &bookStock[bookCount]);
    getchar();

    bookActive[bookCount] = 1;
    bookCount++;
    printf("Them sach thanh cong.\n");
}

void editBook(void) {  // Sua thong tin sach
    char isbn[LEN_ID];
    int i;

    printf("Nhap ISBN can sua: ");
    readLine(isbn, LEN_ID);

    i = findBookByISBN(isbn);
    if (i == -1) {
        printf("Khong tim thay sach.\n");
        return;
    }

    printf("Ten moi: ");
    readLine(bookTitle[i], LEN_NAME);
    printf("Tac gia moi: ");
    readLine(bookAuthor[i], LEN_NAME);
    printf("NXB moi: ");
    readLine(bookPublisher[i], LEN_NAME);
    printf("Nam moi: ");
    scanf("%d", &bookYear[i]);
    getchar();
    printf("The loai moi: ");
    readLine(bookCategory[i], LEN_CATEGORY);
    printf("Gia nhap moi: ");
    scanf("%lf", &bookImportPrice[i]);
    getchar();
    printf("Gia ban moi: ");
    scanf("%lf", &bookSellPrice[i]);
    getchar();
    printf("Ton kho moi: ");
    scanf("%d", &bookStock[i]);
    getchar();

    printf("Da cap nhat sach.\n");
}

void deleteBook(void) {  // Xoa sach
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

void searchBookByISBN(void) {  // Tim sach theo ISBN
    char isbn[LEN_ID];
    int i;

    printf("Nhap ISBN can tim: ");
    readLine(isbn, LEN_ID);

    i = findBookByISBN(isbn);
    if (i == -1) {
        printf("Khong tim thay sach.\n");
        return;
    }

    printf("%s | %s | Ton %d | Gia %.2f\n",
           bookISBN[i], bookTitle[i], bookStock[i], bookSellPrice[i]);
}

void searchBookByTitle(void) {  // Tim sach theo ten
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

    if (!found) {
        printf("Khong tim thay sach.\n");
    }
}
