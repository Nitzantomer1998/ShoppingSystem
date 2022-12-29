#ifndef SHOPPINGSYSTEM_SHOPPINGSYSTEM_H
#define SHOPPINGSYSTEM_SHOPPINGSYSTEM_H


// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

// Folders
#define FOLDER_DATA "Data\\"
#define FOLDER_DATA_USERS "Data\\Users\\"
#define FOLDER_DATA_CATALOGS "Data\\Catalogs\\"
#define FOLDER_DATA_ORDERS "Data\\Orders\\"
#define FOLDER_DATA_TICKETS "Data\\Tickets\\"
#define FOLDER_DATA_ORDERS_SUMMARY "Data\\Orders\\Summary\\"
#define FOLDER_DATA_TICKETS_SUMMARY "Data\\Tickets\\Summary\\"

// Files
#define FILE_TEMP "Data\\Temp.csv"
#define FILE_MANAGERS "Data\\Users\\Managers.csv"
#define FILE_CUSTOMERS "Data\\Users\\Customers.csv"
#define FILE_CATALOGS "Data\\Catalogs\\Catalog.csv"
#define FILE_ORDERS_SUMMARY "Data\\Orders\\Summary\\OrdersSummary.csv"
#define FILE_TICKETS_SUMMARY "Data\\Tickets\\Summary\\TicketsSummary.csv"

// Consts
#define MIN_AGE 16
#define MAX_AGE 120
#define PHONE_LENGTH 10
#define CREDIT_CARD_LENGTH 16
#define MIN_PASSWORD_LENGTH 6
#define MIN_PASSWORD_DIGITS 1
#define MIN_PASSWORD_LETTERS 1
#define CREDIT_CARD_MAX_EXPIRATION_YEAR 2035

// Global Variable
char* IDENTITY = NULL;


// Enums
typedef enum { false, true } bool;
typedef enum { none, customer, manager } UserType;

// Structs
typedef struct User
{
    char* ID;
    char* name;
    char* password;
    char* phone;
    float points;
} User;
typedef struct Product {
    char *name;
    char *company;
    char *category;
    float price;
    int quantity;
} Product;
typedef struct Cart {
    int itemsCounter;
    Product *products;
} Cart;
typedef struct Date {
    int day;
    int month;
    int year;
} Date;


// Strings
char* copyString(char* string);
int initializeInt();
int convertStringToInt(char* string);
float initializeFloat();
float convertStringToFloat(char* string);

// Folders And Files
void checkFolder();
void checkFiles();
void createFolder(char* folderName);
void resetFile(char* fileName);
void writeFile(char* fileName, char* data);
void copyFile(char* destinationFileName, char* sourceFileName);
bool doesFileExists(char* fileName);

// User Authentication
void verifyUserId(User* user);
void verifyUserName(User* user);
void verifyUserPassword(User* user);
void verifyUserPhone(User* user);
void verifyUserAge();
void verifyUserTermsAndConditions();

// User
void registerUser(UserType userType);
void printUserProfile();
void updateUserProfile();
void userLogin();
void updateUserPoints(float decreasePoints);
User retrieveUser(char *fileName, UserType userType);
UserType retrieveUserType();

// Product Authentication
void verifyProductName(Product *product);
void verifyProductCompany(Product *product);
void verifyProductCategory(Product *product);
void verifyProductPrice(Product *product);
void verifyProductQuantity(Product *product);


// Product
bool doesProductExist(char *fileName, char *productName, char *productCompany);
void addProductToCatalog();
void deleteProductFromCatalog();
void updateProductInCatalog();
Product selectProduct(Cart cart);
Product retrieveProduct(char *nameString, char *companyString);

// Cart
void addProductToCart(Cart *cart);
void deleteProductFromCart(Cart *cart);
void updateProductInCart(Cart *cart);
void printCart(Cart cart);
void purchaseCart(Cart *cart);
void updateCatalogAfterPurchase(Cart *cart);
float calculateCartTotal(Cart cart);
Cart retrieveRequestedCatalog();


// Delivery
void verifyCountry();
void verifyCity();
void verifyStreet();
void verifyHomeNumber();
void deliveryProcess();

// Payment
void verifyCreditCard();
void verifyCreditCardCVC();
void verifyCreditCardDate();
void paymentProcess(float totalCartPrice);

// Orders
void writeOrder(Cart *cart);
void writeOrderSummary(float totalOrderPrice);
void printOrdersSummary(int **ordersHistory, char ***customersID, bool onlyWaitingOrders);
void selectOrdersSummary();
void selectOrderConfirmation();
void printOrder(int orderNumber, char *orderID);
void changeOrderStatus(int orderNumber);
int getOrderFileName();

// Tickets
void writeTicket();
void writeTicketSummary();
void printTicketsSummary(int **ticketsHistory, char ***customersID, bool onlyWaitingTickets);
void selectTicketsSummary();
void selectTicketConfirmation();
void printTicket(int ticketNumber, char *ticketID);
void changeTicketStatus(int ticketNumber);
int getTicketFileName();


// Date
Date getCurrentDate();
int calculateDateDiff(Date date);


// Menu's
void systemMenu();

#endif
