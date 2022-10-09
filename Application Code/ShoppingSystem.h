#ifndef SHOPPINGSYSTEM_SHOPPINGSYSTEM_H
#define SHOPPINGSYSTEM_SHOPPINGSYSTEM_H

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Folders
#define FOLDER_DATA "Data\\"
#define FOLDER_DATA_USERS "Data\\Users\\"
#define FOLDER_DATA_CATALOGS "Data\\Catalogs\\"
#define FOLDER_DATA_ORDERS "Data\\Orders\\"
#define FOLDER_DATA_TICKETS "Data\\Tickets\\"
#define FOLDER_DATA_ORDERS_SUMMARY "Data\\Orders\\Summary\\"
#define FOLDER_DATA_TICKETS_SUMMARY "Data\\Tickets\\Summary\\"

// Enums
typedef enum { false, true } bool;

// Strings
char* copyString(char* string);
int initializeInt();
int convertStringToInt(char* string);
float initializeFloat();
float convertStringToFloat(char* string);


#endif //SHOPPINGSYSTEM_SHOPPINGSYSTEM_H
