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
