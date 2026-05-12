#ifndef DATA_H
#define DATA_H

#include "config.h"
/* Du lieu khach hang */
extern int customerCount;
extern char customerId[MAX_CUSTOMERS][LEN_ID];
extern char customerName[MAX_CUSTOMERS][LEN_NAME];
extern char customerPhone[MAX_CUSTOMERS][LEN_PHONE];
extern char customerEmail[MAX_CUSTOMERS][LEN_EMAIL];
extern char customerAddress[MAX_CUSTOMERS][LEN_ADDRESS];
extern char customerRegisterDate[MAX_CUSTOMERS][LEN_DATE];
extern int customerTypeVIP[MAX_CUSTOMERS];
extern int customerActive[MAX_CUSTOMERS];

/* Du lieu sach */
extern int bookCount;
extern char bookISBN[MAX_BOOKS][LEN_ID];
extern char bookTitle[MAX_BOOKS][LEN_NAME];
extern char bookAuthor[MAX_BOOKS][LEN_NAME];
extern char bookPublisher[MAX_BOOKS][LEN_NAME];
extern int bookYear[MAX_BOOKS];
extern char bookCategory[MAX_BOOKS][LEN_CATEGORY];
extern double bookImportPrice[MAX_BOOKS];
extern double bookSellPrice[MAX_BOOKS];
extern int bookStock[MAX_BOOKS];
extern int bookActive[MAX_BOOKS];

/* Du lieu hoa don */
extern int invoiceCount;
extern char invoiceId[MAX_INVOICES][LEN_ID];
extern char invoiceCustomerId[MAX_INVOICES][LEN_ID];
extern char invoiceDate[MAX_INVOICES][LEN_DATE];
extern int invoiceItemCount[MAX_INVOICES];
extern double invoiceSubtotal[MAX_INVOICES];
extern double invoiceDiscount[MAX_INVOICES];
extern double invoiceVAT[MAX_INVOICES];
extern double invoiceTotal[MAX_INVOICES];
extern int invoiceActive[MAX_INVOICES];

/* Chi tiet hoa don */
extern char invoiceItemISBN[MAX_INVOICES][MAX_ITEMS_PER_INVOICE][LEN_ID];
extern int invoiceItemQty[MAX_INVOICES][MAX_ITEMS_PER_INVOICE];
extern double invoiceItemUnitPrice[MAX_INVOICES][MAX_ITEMS_PER_INVOICE];
extern double invoiceItemLineTotal[MAX_INVOICES][MAX_ITEMS_PER_INVOICE];

#endif
