#include "data.h"

/* -------- Khach hang -------- */
int customerCount = 0;
char customerId[MAX_CUSTOMERS][LEN_ID];
char customerName[MAX_CUSTOMERS][LEN_NAME];
char customerPhone[MAX_CUSTOMERS][LEN_PHONE];
char customerEmail[MAX_CUSTOMERS][LEN_EMAIL];
char customerAddress[MAX_CUSTOMERS][LEN_ADDRESS];
char customerRegisterDate[MAX_CUSTOMERS][LEN_DATE];
int customerTypeVIP[MAX_CUSTOMERS];
int customerActive[MAX_CUSTOMERS];

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

char invoiceItemISBN[MAX_INVOICES][MAX_ITEMS_PER_INVOICE][LEN_ID];
int invoiceItemQty[MAX_INVOICES][MAX_ITEMS_PER_INVOICE];
double invoiceItemUnitPrice[MAX_INVOICES][MAX_ITEMS_PER_INVOICE];
double invoiceItemLineTotal[MAX_INVOICES][MAX_ITEMS_PER_INVOICE];
