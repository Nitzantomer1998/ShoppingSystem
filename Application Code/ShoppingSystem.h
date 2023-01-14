#ifndef SHOPPINGSYSTEM_SHOPPINGSYSTEM_H
#define SHOPPINGSYSTEM_SHOPPINGSYSTEM_H


// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>


// Folders
#define FOLDER_DATA "..\\Data\\"
#define FOLDER_DATA_USERS "..\\Data\\Users\\"
#define FOLDER_DATA_ORDERS "..\\Data\\Orders\\"
#define FOLDER_DATA_TICKETS "..\\Data\\Tickets\\"
#define FOLDER_DATA_CATALOGS "..\\Data\\Catalogs\\"
#define FOLDER_DATA_ORDERS_SUMMARY "..\\Data\\orders\\Summary\\"
#define FOLDER_DATA_TICKETS_SUMMARY "..\\Data\\Tickets\\Summary\\"


// Files
#define FILE_TEMP "..\\Data\\Temp.csv"
#define FILE_MANAGERS "..\\Data\\Users\\Managers.csv"
#define FILE_CUSTOMERS "..\\Data\\Users\\Customers.csv"
#define FILE_CATALOGS "..\\Data\\Catalogs\\Catalog.csv"
#define FILE_ORDERS_SUMMARY "..\\Data\\Orders\\Summary\\OrdersSummary.csv"
#define FILE_TICKETS_SUMMARY "..\\Data\\Tickets\\Summary\\TicketsSummary.csv"


// Constants
#define MIN_AGE 16
#define MAX_AGE 120
#define PHONE_LENGTH 10
#define MANAGER_CODE 1111
#define CREDIT_CARD_LENGTH 16
#define MIN_PASSWORD_LENGTH 6
#define MIN_PASSWORD_DIGITS 1
#define MIN_PASSWORD_LETTERS 1
#define CREDIT_CARD_MAX_EXPIRATION_YEAR 2035


// Enums
typedef enum {
    False, True
} eBool;
typedef enum {
    None, Customer, Manager
} eUserType;


// Structs
typedef struct {
    char *id;
    char *name;
    char *password;
    char *phone;
    float points;
} sUser;
typedef struct {
    char *name;
    char *company;
    char *category;
    float price;
    int quantity;
} sProduct;
typedef struct {
    int itemsCounter;
    sProduct *products;
} sCart;
typedef struct {
    int day;
    int month;
    int year;
} sDate;


// Global Variable
char *gIdentity = NULL;


// Folders & Files
void checkFolder();
void checkFiles();
void createFolder(char *folderName);
void resetFile(char *fileName);
void writeFile(char *fileName, char *data);
void copyFile(char *destinationFileName, char *sourceFileName);
eBool doesFileExists(char *fileName);


// Strings
char *copyString(char *string);
int initializeInt();
int convertStringToInt(char *string);
float initializeFloat();
float convertStringToFloat(char *string);


// sUser
void verifyUserId(sUser *user);
void verifyUserName(sUser *user);
void verifyUserPassword(sUser *user);
void verifyUserPhone(sUser *user);
void verifyUserAge();
void verifyUserTermsAndConditions();
void registerUser(eUserType userType);
void printUserProfile();
void updateUserProfile();
void userLogin();
void updateUserPoints(float decreasePoints);
sUser retrieveUser(char *fileName, eUserType userType);
eUserType retrieveUserType();


// sProduct
void verifyProductName(sProduct *product);
void verifyProductCompany(sProduct *product);
void verifyProductCategory(sProduct *product);
void verifyProductPrice(sProduct *product);
void verifyProductQuantity(sProduct *product);
void addProductToCatalog();
void deleteProductFromCatalog();
void updateProductInCatalog();
eBool doesProductExist(char *fileName, char *productName, char *productCompany);
sProduct selectProduct(sCart cart);
sProduct retrieveProduct(char *nameString, char *companyString);


// sCart
void addProductToCart(sCart *cart);
void deleteProductFromCart(sCart *cart);
void updateProductInCart(sCart *cart);
void printCart(sCart cart);
void purchaseCart(sCart *cart);
void updateCatalogAfterPurchase(sCart *cart);
float calculateCartTotal(sCart cart);
sCart retrieveRequestedCatalog();


// Delivery
void verifyCountry();
void verifyCity();
void verifyStreet();
void verifyHomeNumber();
void deliveryProcess();


// Payment
void verifyCreditCard();
void verifyCreditCardCvc();
void verifyCreditCardDate();
void paymentProcess(float totalCartPrice);


// Orders
void writeOrder(sCart *cart);
void writeOrderSummary(float totalOrderPrice);
void printOrdersSummary(int **ordersHistory, char ***customersId, eBool onlyWaitingOrders);
void selectOrdersSummary();
void selectOrderConfirmation();
void printOrder(int orderNumber, char *orderId);
void changeOrderStatus(int orderNumber);
int getOrderFileName();


// Tickets
void writeTicket();
void writeTicketSummary();
void printTicketsSummary(int **ticketsHistory, char ***customersId, eBool onlyWaitingTickets);
void selectTicketsSummary();
void selectTicketConfirmation();
void printTicket(int ticketNumber, char *ticketId);
void changeTicketStatus(int ticketNumber);
int getTicketFileName();


// sDate
sDate getCurrentDate();
int calculateDateDiff(sDate date);


// Menu's
void systemMenu();
void registrationMenu();
void userProfileMenu();
void userProfileUpdateMenu(sUser *user);
void catalogFilterMenu(char **filterBy, char **filterWord);
void managerMenu();
void managerStoreMenu();
void revenueMenu();
void ordersMenu();
void ticketsMenu();
void productUpdateMenu(sProduct *product);
void customerMenu();
void customerStoreMenu(sCart *cart);
void cartMenu(sCart *cart);
void printAskedRevenue(int revenueDays);
int main();
int selectProductQuantity(sProduct product);
int purchaseCartMenu(sCart cart);
float shoppingPointsMenu(sUser user, float totalPrice);


#endif
