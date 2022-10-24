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
void writeFile(char* fileName, char* data)
{
    // Saving the sent data into the desirable file
    FILE* file;
    errno_t err;

    if ((err = fopen_s(&file, fileName, "a+")))
        exit(true);

    else
        fprintf(file, "%s\n", data);

    fclose(file);
}
void copyFile(char* destinationFileName, char* sourceFileName)
{
    // Copy source file content into destination file
    char buffer[500] = { '\0' };
    FILE* file;
    errno_t err;

    if ((err = fopen_s(&file, sourceFileName, "r")))
        exit(true);

    else
    {
        resetFile(destinationFileName);

        while (fscanf_s(file, " %[^\n]", buffer, (unsigned)sizeof(buffer)) == 1)
            writeFile(destinationFileName, buffer);
    }
    fclose(file);
}
bool doesFileExists(char* fileName)
{
    // Checking if the sent file exist and return accordingly
    struct stat buffer;
    return stat(fileName, &buffer) == false;
}

// User
void verifyUserId(User* user)
{
    // Initialize the user ID till its valid
    // Note: the ID check is according to Israel ID's
    char userID[100] = { '\0' };
    bool isIdValid = false;

    while (isIdValid == false)
    {
        isIdValid = true;

        printf("User ID -->");
        scanf_s(" %[^\n]", userID, (unsigned)sizeof(userID));

        IDENTITY = copyString(userID);

        long idVal = strtol(userID, NULL, 10);
        int Digit1 = 0, Digit2 = 0, Digit3 = 0, Digit4 = 0, Digit5 = 0, Digit6 = 0, Digit7 = 0, Digit8 = 0, Digit9 = 0;

        if (idVal < 10000000 || idVal > 999999999)
        {
            printf("Error: User ID Contains Eight To Nine Digits\n");
            isIdValid = false;
        }

        Digit1 = idVal / 100000000 * 1;
        Digit2 = idVal / 10000000 % 10 * 2;
        Digit3 = idVal / 1000000 % 10 * 1;
        Digit4 = idVal / 100000 % 10 * 2;
        Digit5 = idVal / 10000 % 10 * 1;
        Digit6 = idVal / 1000 % 10 * 2;
        Digit7 = idVal / 100 % 10 * 1;
        Digit8 = idVal / 10 % 10 * 2;
        Digit9 = idVal % 10;

        if (Digit1 > 9 || Digit2 > 9 || Digit3 > 9 || Digit4 > 9 || Digit5 > 9 || Digit6 > 9 || Digit7 > 9 || Digit8 > 9 || Digit9 > 9)
        {
            Digit1 = (Digit1 / 10) + (Digit1 % 10);
            Digit2 = (Digit2 / 10) + (Digit2 % 10);
            Digit3 = (Digit3 / 10) + (Digit3 % 10);
            Digit4 = (Digit4 / 10) + (Digit4 % 10);
            Digit5 = (Digit5 / 10) + (Digit5 % 10);
            Digit6 = (Digit6 / 10) + (Digit6 % 10);
            Digit7 = (Digit7 / 10) + (Digit7 % 10);
            Digit8 = (Digit8 / 10) + (Digit8 % 10);
            Digit9 = (Digit9 / 10) + (Digit9 % 10);
        }

        if ((Digit1 + Digit2 + Digit3 + Digit4 + Digit5 + Digit6 + Digit7 + Digit8 + Digit9) % 10 != 0)
        {
            printf("Error: Incorrect ID\n");
            isIdValid = false;
        }

        if (isIdValid == false)
            printf("\n");
    }
    user->ID = copyString(userID);
}
void verifyUserName(User* user)
{
    // Initialize the username till its valid
    char userName[100] = { '\0' };
    bool isNameValid = false;

    while (isNameValid == false)
    {
        isNameValid = true;

        printf("User Name -->");
        scanf_s(" %[^\n]", userName, (unsigned)sizeof(userName));

        for (int i = 0; i < strlen(userName); i++)
        {
            if (((userName[i] >= 'a' && userName[i] <= 'z') || (userName[i] >= 'A' && userName[i] <= 'Z') || userName[i] == ' ') == false)
            {
                printf("Error: User Name Contain Only English Alphabet\n\n");
                isNameValid = false;
                break;
            }
        }
    }
    user->name = copyString(userName);
}
void verifyUserPassword(User* user)
{
    // Initialize the user password till its valid
    int lettersCounter = 0;
    int numbersCounter = 0;
    char userPassword[100] = { '\0' };
    bool isPasswordValid = false;

    while (isPasswordValid == false)
    {
        lettersCounter = 0;
        numbersCounter = 0;
        isPasswordValid = true;

        printf("User Password -->");
        scanf_s(" %[^\n]", userPassword, (unsigned)sizeof(userPassword));

        if (strlen(userPassword) < MIN_PASSWORD_LENGTH)
        {
            printf("Error: User Password Contain At Least Six Characters\n");
            isPasswordValid = false;
        }

        for (int i = 0; i < strlen(userPassword); i++)
        {
            if ((userPassword[i] >= 'a' && userPassword[i] <= 'z') || (userPassword[i] >= 'A' && userPassword[i] <= 'Z'))
                lettersCounter++;

            else if (userPassword[i] >= '0' && userPassword[i] <= '9')
                numbersCounter++;

            else
            {
                printf("Error: User Password Contain Only English Alphabet And Digits\n");
                isPasswordValid = false;
                break;
            }
        }

        if (lettersCounter < MIN_PASSWORD_LETTERS)
        {
            printf("Error: User Password Contain At Least One English Alphabet\n");
            isPasswordValid = false;
        }

        if (numbersCounter < MIN_PASSWORD_DIGITS)
        {
            printf("Error: User Password Contain At Least One Digit\n");
            isPasswordValid = false;
        }

        if (isPasswordValid == false)
            printf("\n");
    }
    user->password = copyString(userPassword);
}
void verifyUserPhone(User* user)
{
    // Initialize the user phone number till its valid
    // Note: the Phone check is according to Israel Phone's
    char userPhone[100] = { '\0' };
    bool isPhoneValid = false;

    while (isPhoneValid == false)
    {
        isPhoneValid = true;

        printf("User Phone -->");
        scanf_s(" %[^\n]", userPhone, (unsigned)sizeof(userPhone));

        for (int i = 0; i < strlen(userPhone); i++)
        {
            if (userPhone[i] < '0' || userPhone[i] > '9')
            {
                printf("Error: User Phone Number Contain Only Digits\n");
                isPhoneValid = false;
                break;
            }

            if (strlen(userPhone) != PHONE_LENGTH)
            {
                printf("Error: User Phone Number Contain Ten Digits\n");
                isPhoneValid = false;
                break;
            }
        }

        if (isPhoneValid == false)
            printf("\n");
    }
    user->phone = copyString(userPhone);
}
void verifyUserAge()
{
    // Checking the user age, in order to determine if he is allowed to own an account
    printf("User Age -->");
    int userAge = initializeInt();

    if (userAge < MIN_AGE)
    {
        printf("Error: We Are Sorry, The Minimum User Age Is Sixteen\n");
        exit(true);
    }

    else if (userAge > MAX_AGE)
    {
        printf("Error: Sorry If You Are Truly %d Years Old You Probably Death, Goodbye\n", userAge);
        exit(true);
    }
}
void verifyUserTermsAndConditions()
{
    // Checking if the user agreed to the system term and condition in order to create an account
    int selection = 0;

    while (selection < 1 || selection > 2)
    {
        printf("\n[Terms and Conditions]\n");
        printf("Blah Blah Blah ...\n");
        printf("\nDo You Agree To The Terms And Conditions\n'1' Yes    '2' No\nInput -->");

        selection = initializeInt();
        if (selection < 1 || selection > 2)
            printf("Error: Invalid Input, Try Between [1 To 2]\n");
    }

    if (selection == 2)
    {
        printf("Error: We Are Sorry To Hear, Goodbye\n");
        exit(true);
    }
}
