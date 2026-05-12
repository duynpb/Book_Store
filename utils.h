#ifndef UTILS_H
#define UTILS_H

#include "config.h"


void readLine(char s[], int maxLen);


int findCustomerById(const char id[]);


int findBookByISBN(const char isbn[]);


int containsText(const char text[], const char keyword[]);

#endif
