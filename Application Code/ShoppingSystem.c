#include "ShoppingSystem.h"


// Strings
char* copyString(char* string)
{
    // Allocates the given string into a new string with initialized needed size of memory
    char* memoryAllocateString = (char*) malloc(sizeof(char) * (strlen(string) + 1));
    if (memoryAllocateString == NULL)
        exit(true);

    strcpy_s(memoryAllocateString, strlen(string) + 1, string);
    return memoryAllocateString;
}
int initializeInt()
{
    // Initialize string from the user and convert it into an Integer
    // Note: if the input isn't an Integer the return value will be -1 ("Failed")
    char string[500] = { '\0' };

    scanf_s(" %[^\n]", string, (unsigned)sizeof(string));
    return convertStringToInt(string);
}
int convertStringToInt(char* string)
{
    // Converting the given string into an Integer
    // Note: if the input isn't an Integer the return value will be -1 ("Failed")
    int sum = 0;

    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] < '0' || string[i] > '9')
            return -1;

        else
            sum = sum * 10 + (string[i] - '0');
    }
    return sum;
}
float initializeFloat()
{
    // Initialize string from the user and convert it into a Float
    // Note: if the input isn't a Float the return value will be -1 ("Failed")
    char string[500] = { '\0' };

    scanf_s(" %[^\n]", string, (unsigned)sizeof(string));
    return convertStringToFloat(string);
}
float convertStringToFloat(char* string)
{
    // Converting the given string into a Float
    // Note: if the input isn't a Float the return value will be -1 ("Failed")
    int dividePower = 1;
    int sum = 0;

    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] >= '0' && string[i] <= '9')
            sum = sum * 10 + (string[i] - '0');

        else if (string[i] == '.')
            for (int j = 1; j < strlen(string) - i; j++)
                dividePower = dividePower * 10;

        else
            return -1;
    }
    return (float)sum / (float)dividePower;
}

// Folders And Files
void checkFolder()
{
    // Checking if the folders exist, else create them
    if (doesFileExists(FOLDER_DATA) == false)
        createFolder(FOLDER_DATA);

    if (doesFileExists(FOLDER_DATA_USERS) == false)
        createFolder(FOLDER_DATA_USERS);

    if (doesFileExists(FOLDER_DATA_ORDERS) == false)
        createFolder(FOLDER_DATA_ORDERS);

    if (doesFileExists(FOLDER_DATA_TICKETS) == false)
        createFolder(FOLDER_DATA_TICKETS);

    if (doesFileExists(FOLDER_DATA_CATALOGS) == false)
        createFolder(FOLDER_DATA_CATALOGS);

    if (doesFileExists(FOLDER_DATA_ORDERS_SUMMARY) == false)
        createFolder(FOLDER_DATA_ORDERS_SUMMARY);

    if (doesFileExists(FOLDER_DATA_TICKETS_SUMMARY) == false)
        createFolder(FOLDER_DATA_TICKETS_SUMMARY);
}
void checkFiles()
{
    // Checking if the files exist, else create them
    if (doesFileExists(FILE_TEMP) == false)
        writeFile(FILE_TEMP, "");

    if (doesFileExists(FILE_MANAGERS) == false)
        writeFile(FILE_MANAGERS, "ID,Name,Password,Phone");

    if (doesFileExists(FILE_CUSTOMERS) == false)
        writeFile(FILE_CUSTOMERS, "ID,Name,Password,Phone,Points");

    if (doesFileExists(FILE_CATALOGS) == false)
        writeFile(FILE_CATALOGS, "Name,Company,Category,Price,Quantity");

    if (doesFileExists(FILE_TICKETS_SUMMARY) == false)
        writeFile(FILE_TICKETS_SUMMARY, "Ticket No.,Customer ID,Date,Status");

    if (doesFileExists(FILE_ORDERS_SUMMARY) == false)
        writeFile(FILE_ORDERS_SUMMARY, "Order No.,Customer ID,Total,Date,Status");
}
void createFolder(char* folderName)
{
    // Creating new folder with the sent name
    if (mkdir(folderName))
        exit(true);
}
void resetFile(char* fileName)
{
    // Reset the sent file
    FILE* file;
    errno_t err;

    if ((err = fopen_s(&file, fileName, "w")))
        exit(true);

    fclose(file);
}
