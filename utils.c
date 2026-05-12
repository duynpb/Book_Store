#include <stdio.h>
#include <string.h>

#include "data.h"
#include "utils.h"

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
    if (strstr(text, keyword) != NULL) {
        return 1;
    }
    return 0;
}
