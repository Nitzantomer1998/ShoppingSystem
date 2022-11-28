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

// User Authentication
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

// User
void registerUser(UserType userType)
{
    // Register the user to the users system database
    char buffer[500] = { '\0' };
    User user = { NULL, NULL, NULL, NULL, 0 };

    printf("\n[User Registration]\n");
    verifyUserId(&user);
    verifyUserName(&user);
    verifyUserPassword(&user);
    verifyUserPhone(&user);
    verifyUserAge();
    verifyUserTermsAndConditions();

    if (retrieveUserType())
    {
        printf("Error: User Already Exist In The System\n\n");
        return;
    }

    if (userType == customer)
        sprintf_s(buffer, (unsigned)sizeof(buffer), "%s,%s,%s,%s,%.2f", user.ID, user.name, user.password, user.phone, 0.0);

    else
        sprintf_s(buffer, (unsigned)sizeof(buffer), "%s,%s,%s,%s", user.ID, user.name, user.password, user.phone);

    writeFile(userType == customer ? FILE_CUSTOMERS : FILE_MANAGERS, buffer);


    printf("\n[Registered User]\n");
    printf("ID --> %s\n", user.ID);
    printf("Name --> %s\n", user.name);
    printf("Password --> %s\n", user.password);
    printf("Phone --> %s\n", user.phone);
    printf("User Have Been Successfully Registered To The System\n\n");
}
void printUserProfile()
{
    // Printing the current logged-in user information
    UserType userType = retrieveUserType();
    User user = retrieveUser(userType == customer ? FILE_CUSTOMERS : FILE_MANAGERS, userType);

    printf("\n[User Information]\n");
    printf("ID --> %s\n", user.ID);
    printf("Name --> %s\n", user.name);
    printf("Password --> %s\n", user.password);
    printf("Phone --> %s\n", user.phone);

    if (userType == customer)
        printf("Online Shopping Points --> %.2f\n", user.points);

    printf("User Information Have Been Successfully Printed\n");
}
void updateUserProfile()
{
    // Updating the user information as he desires
    char userID[100] = { '\0' };
    char userName[100] = { '\0' };
    char userPassword[100] = { '\0' };
    char userPhone[100] = { '\0' };
    char userPoints[100] = { '\0' };
    char buffer[500] = { '\0' };
    UserType userType = retrieveUserType();
    User user = { NULL, NULL, NULL, NULL, 0 };
    FILE* file;
    errno_t err;

    if ((err = fopen_s(&file, userType == customer ? FILE_CUSTOMERS : FILE_MANAGERS, "r")))
        exit(true);

    else
    {
        resetFile(FILE_TEMP);

        while (fscanf_s(file, " %[^\n]", buffer, (unsigned)sizeof(buffer)) == 1)
        {
            sscanf_s(buffer, " %[^,],%[^,],%[^,],%[^,],%[^,]", userID, (unsigned)sizeof(userID), userName, (unsigned)sizeof(userName), userPassword, (unsigned)sizeof(userPassword), userPhone, (unsigned)sizeof(userPhone), userPoints, (unsigned)sizeof(userPoints));

            if (strcmp(userID, IDENTITY) == 0)
            {
                user.ID = copyString(userID);
                user.name = copyString(userName);
                user.password = copyString(userPassword);
                user.phone = copyString(userPhone);

                userProfileUpdateMenu(&user);

                if (userType == customer)
                    sprintf_s(buffer, (unsigned)sizeof(buffer), "%s,%s,%s,%s,%s", user.ID, user.name, user.password, user.phone, userPoints);

                else
                    sprintf_s(buffer, (unsigned)sizeof(buffer), "%s,%s,%s,%s", user.ID, user.name, user.password, user.phone);
            }
            writeFile(FILE_TEMP, buffer);
        }
    }
    fclose(file);
    copyFile(userType == customer ? FILE_CUSTOMERS : FILE_MANAGERS, FILE_TEMP);


    printf("\n[Updated User]\n");
    printf("ID --> %s\n", user.ID);
    printf("Name --> %s\n", user.name);
    printf("Password --> %s\n", user.password);
    printf("Phone --> %s\n", user.phone);

    if (userType == customer)
        printf("Online Shopping Points --> %.2f\n", user.points);

    printf("User Have Been Successfully Updated\n");
}
void userLogin()
{
    // Login the user into the system
    char userID[100] = { '\0' };
    char userPassword[100] = { '\0' };
    bool isLoggedIn = true;

    printf("\n[User Login]\n");

    printf("User ID -->");
    scanf_s(" %[^\n]", userID, (unsigned)sizeof(userID));

    printf("User Password -->");
    scanf_s(" %[^\n]", userPassword, (unsigned)sizeof(userPassword));

    IDENTITY = copyString(userID);
    UserType userType = retrieveUserType();

    if (userType != none)
    {
        User user = retrieveUser(userType == customer ? FILE_CUSTOMERS : FILE_MANAGERS, userType);

        if (strcmp(userPassword, user.password) == 0)
        {
            printf("User Have Been Successfully Logged In To The System\n");

            if (userType == customer)
                customerMenu();

            else
                managerMenu();
        }

        else
            isLoggedIn = false;
    }

    if (userType == none || isLoggedIn == false)
        printf("Error: Invalid Input, Have Not Found Match Data In Our System\n\n");
}
void updateUserPoints(float decreasePoints)
{
    // Updating the user shopping points by decreasing from the sent parameter
    char userID[100] = { '\0' };
    char userName[100] = { '\0' };
    char userPassword[100] = { '\0' };
    char userPhone[100] = { '\0' };
    char userPoints[100] = { '\0' };
    char buffer[500] = { '\0' };
    FILE* file;
    errno_t err;

    if ((err = fopen_s(&file, FILE_CUSTOMERS, "r")))
        exit(true);

    else
    {
        resetFile(FILE_TEMP);

        while (fscanf_s(file, " %[^\n]", buffer, (unsigned)sizeof(buffer)) == 1)
        {
            sscanf_s(buffer, " %[^,],%[^,],%[^,],%[^,],%[^,]", userID, (unsigned)sizeof(userID), userName, (unsigned)sizeof(userName), userPassword, (unsigned)sizeof(userPassword), userPhone, (unsigned)sizeof(userPhone), userPoints, (unsigned)sizeof(userPoints));

            if (strcmp(userID, IDENTITY) == 0)
            {
                printf("\nUser Current Amount Of Online Shopping System --> %.2f\n", convertStringToFloat(userPoints) - decreasePoints);
                sprintf_s(buffer, (unsigned)sizeof(buffer), "%s,%s,%s,%s,%.2f", userID, userName, userPassword, userPhone, convertStringToFloat(userPoints) - decreasePoints);
            }
            writeFile(FILE_TEMP, buffer);
        }
    }
    fclose(file);
    copyFile(FILE_CUSTOMERS, FILE_TEMP);
}
User retrieveUser(char *fileName, UserType userType) {
    // Returning User with the current logged-in user information
    char userID[100] = {'\0'};
    char userName[100] = {'\0'};
    char userPassword[100] = {'\0'};
    char userPhone[100] = {'\0'};
    char userPoints[100] = {'\0'};
    char buffer[500] = {'\0'};
    User user = {NULL, NULL, NULL, NULL, 0};
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, fileName, "r")))
        exit(true);

    else {
        while (fscanf_s(file, " %[^\n]", buffer, (unsigned) sizeof(buffer)) == 1) {
            sscanf_s(buffer, " %[^,],%[^,],%[^,],%[^,],%[^,]", userID, (unsigned) sizeof(userID), userName,
                     (unsigned) sizeof(userName), userPassword, (unsigned) sizeof(userPassword), userPhone,
                     (unsigned) sizeof(userPhone), userPoints, (unsigned) sizeof(userPoints));

            if (strcmp(userID, IDENTITY) == 0) {
                user.ID = copyString(userID);
                user.name = copyString(userName);
                user.password = copyString(userPassword);
                user.phone = copyString(userPhone);
                user.points = userType == customer ? convertStringToFloat(userPoints) : 0;
            }
        }
    }
    fclose(file);
    return user;
}
UserType retrieveUserType() {
    // Returning the current logged-in user his user type
    User user = retrieveUser(FILE_CUSTOMERS, customer);
    if (user.ID)
        return customer;

    user = retrieveUser(FILE_MANAGERS, manager);
    if (user.ID)
        return manager;

    return none;
}


// Product Authentication
void verifyProductName(Product *product) {
    // Initialize the product name till its valid
    char productName[100] = {'\0'};
    bool isNameValid = false;

    while (isNameValid == false) {
        isNameValid = true;

        printf("Product Name -->");
        scanf_s(" %[^\n]", productName, (unsigned) sizeof(productName));

        for (int i = 0; i < strlen(productName); i++) {
            if (((productName[i] >= 'a' && productName[i] <= 'z') || (productName[i] >= 'A' && productName[i] <= 'Z') ||
                 productName[i] == ' ') == false) {
                printf("Error: Product Name Contain Only English Alphabet\n\n");
                isNameValid = false;
                break;
            }
        }
    }
    product->name = copyString(productName);
}
void verifyProductCompany(Product *product) {
    // Initialize the product company name till its valid
    char productCompany[100] = {'\0'};
    bool isCompanyValid = false;

    while (isCompanyValid == false) {
        isCompanyValid = true;

        printf("Product Company -->");
        scanf_s(" %[^\n]", productCompany, (unsigned) sizeof(productCompany));

        for (int i = 0; i < strlen(productCompany); i++) {
            if (((productCompany[i] >= 'a' && productCompany[i] <= 'z') ||
                 (productCompany[i] >= 'A' && productCompany[i] <= 'Z') || productCompany[i] == ' ') == false) {
                printf("Error: Product Company Name Contain Only English Alphabet\n\n");
                isCompanyValid = false;
                break;
            }
        }
    }
    product->company = copyString(productCompany);
}
void verifyProductCategory(Product *product) {
    // Initialize the product category name till its valid
    char productCategory[100] = {'\0'};
    bool isCategoryValid = false;

    while (isCategoryValid == false) {
        isCategoryValid = true;

        printf("Product Category -->");
        scanf_s(" %[^\n]", productCategory, (unsigned) sizeof(productCategory));

        for (int i = 0; i < strlen(productCategory); i++) {
            if (((productCategory[i] >= 'a' && productCategory[i] <= 'z') ||
                 (productCategory[i] >= 'A' && productCategory[i] <= 'Z') || productCategory[i] == ' ') == false) {
                printf("Error: Product Category Name Contain Only English Alphabet\n\n");
                isCategoryValid = false;
                break;
            }
        }
    }
    product->category = copyString(productCategory);
}
void verifyProductPrice(Product *product) {
    // Initialize the product price till its valid
    float productPrice = 0;

    while (productPrice <= 0) {
        printf("Product Price -->");
        productPrice = initializeFloat();

        if (productPrice <= 0)
            printf("Error: Product Price Must Be Greater Than Zero\n\n");
    }
    product->price = productPrice;
}
void verifyProductQuantity(Product *product) {
    // Initialize the product quantity till its valid
    int productQuantity = 0;

    while (productQuantity < 1) {
        printf("Product Quantity -->");
        productQuantity = initializeInt();

        if (productQuantity < 1)
            printf("Error: Product Quantity Must Be Integer Greater Than Zero\n\n");
    }
    product->quantity = productQuantity;
}

// Product
bool doesProductExist(char *fileName, char *productName, char *productCompany) {
    // Checking if the product exist in the catalog system database and return accordingly
    char nameString[100] = {'\0'};
    char companyString[100] = {'\0'};
    char buffer[200] = {'\0'};
    bool isProductExist = false;
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, fileName, "r")))
        exit(true);

    else {
        while (fscanf_s(file, " %[^\n]", buffer, (unsigned) sizeof(buffer)) == 1) {
            sscanf_s(buffer, " %[^,],%[^,],%*[^,],%*[^,],%*[^,]", nameString, (unsigned) sizeof(nameString),
                     companyString, (unsigned) sizeof(companyString));

            if (strcmp(nameString, productName) == 0 && strcmp(companyString, productCompany) == 0) {
                isProductExist = true;
                break;
            }
        }
    }
    fclose(file);
    return isProductExist;
}
void addProductToCatalog() {
    // Adding product to the system catalog database
    char buffer[500] = {'\0'};
    Product product = {NULL, NULL, NULL, 0, 0};

    printf("\n[Adding Product]\n");
    verifyProductName(&product);
    verifyProductCompany(&product);
    verifyProductCategory(&product);
    verifyProductPrice(&product);
    verifyProductQuantity(&product);

    if (doesProductExist(FILE_CATALOGS, product.name, product.company)) {
        printf("Error: Product Already Exist In The System\n");
        return;
    }

    sprintf_s(buffer, (unsigned) sizeof(buffer), "%s,%s,%s,%.2f,%d", product.name, product.company, product.category,
              product.price, product.quantity);
    writeFile(FILE_CATALOGS, buffer);


    printf("\n[Added Product]\n");
    printf("Name --> %s\n", product.name);
    printf("Company --> %s\n", product.company);
    printf("Category --> %s\n", product.category);
    printf("Price --> %.2f\n", product.price);
    printf("Quantity --> %d\n", product.quantity);
    printf("Product Have Been Successfully Added To The Catalog\n");
}
void deleteProductFromCatalog() {
    // Deleting product from the system catalog database
    char productName[100] = {'\0'};
    char productCompany[100] = {'\0'};
    char productCategory[100] = {'\0'};
    char productPrice[100] = {'\0'};
    char productQuantity[100] = {'\0'};
    char buffer[500] = {'\0'};
    Product product = {NULL, NULL, NULL, 0, 0};
    FILE *file;
    errno_t err;

    printf("\n[Deleting Product]");
    product = selectProduct(retrieveRequestedCatalog());
    if (product.name == NULL)
        return;

    if ((err = fopen_s(&file, FILE_CATALOGS, "r")))
        exit(true);

    else {
        resetFile(FILE_TEMP);

        while (fscanf_s(file, " %[^\n]", buffer, (unsigned) sizeof(buffer)) == 1) {
            sscanf_s(buffer, " %[^,],%[^,],%[^,],%[^,],%[^,]", productName, (unsigned) sizeof(productName),
                     productCompany, (unsigned) sizeof(productCompany), productCategory,
                     (unsigned) sizeof(productCompany), productPrice, (unsigned) sizeof(productPrice), productQuantity,
                     (unsigned) sizeof(productQuantity));

            if (strcmp(productName, product.name) != 0 || strcmp(productCompany, product.company) != 0)
                writeFile(FILE_TEMP, buffer);
        }
    }
    fclose(file);
    copyFile(FILE_CATALOGS, FILE_TEMP);


    printf("\n[Deleted Product]\n");
    printf("Name --> %s\n", product.name);
    printf("Company --> %s\n", product.company);
    printf("Category --> %s\n", product.category);
    printf("Price --> %.2f\n", product.price);
    printf("Quantity --> %d\n", product.quantity);
    printf("Product Have Been Successfully Deleted From The Catalog\n");
}
void updateProductInCatalog() {
    // Updating product from the system catalog database
    char productName[100] = {'\0'};
    char productCompany[100] = {'\0'};
    char productCategory[100] = {'\0'};
    char productPrice[100] = {'\0'};
    char productQuantity[100] = {'\0'};
    char buffer[500] = {'\0'};
    Product product = {NULL, NULL, NULL, 0, 0};
    FILE *file;
    errno_t err;

    printf("\n[Updating Product]");
    product = selectProduct(retrieveRequestedCatalog());
    if (product.name == NULL)
        return;

    if ((err = fopen_s(&file, FILE_CATALOGS, "r")))
        exit(true);

    else {
        productUpdateMenu(&product);

        resetFile(FILE_TEMP);

        while (fscanf_s(file, " %[^\n]", buffer, (unsigned) sizeof(buffer)) == 1) {
            sscanf_s(buffer, " %[^,],%[^,],%[^,],%[^,],%[^,]", productName, (unsigned) sizeof(productName),
                     productCompany, (unsigned) sizeof(productCompany), productCategory,
                     (unsigned) sizeof(productCompany), productPrice, (unsigned) sizeof(productPrice), productQuantity,
                     (unsigned) sizeof(productQuantity));

            if (strcmp(productName, product.name) == 0 && strcmp(productCompany, product.company) == 0)
                sprintf_s(buffer, (unsigned) sizeof(buffer), "%s,%s,%s,%.2f,%d", productName, productCompany,
                          productCategory, product.price, product.quantity);

            writeFile(FILE_TEMP, buffer);
        }
    }
    fclose(file);
    copyFile(FILE_CATALOGS, FILE_TEMP);


    printf("\n[Updated Product]\n");
    printf("Name --> %s\n", product.name);
    printf("Company --> %s\n", product.company);
    printf("Category --> %s\n", product.category);
    printf("Price --> %.2f\n", product.price);
    printf("Quantity --> %d\n", product.quantity);
    printf("Product Have Been Successfully Updated In The Catalog\n");
}
Product selectProduct(Cart cart) {
    // Printing the available catalog, selecting product from it and retrieve the selected product
    if (cart.itemsCounter == 0) {
        printf("Error: There Are No Available Products\n");
        Product product = {NULL, NULL, NULL, 0, 0};
        return product;
    }

    int selection = 0;
    while (selection < 1 || selection > cart.itemsCounter) {
        printCart(cart);
        printf("Select Product -->");
        selection = initializeInt();

        if (selection < 1 || selection > cart.itemsCounter)
            printf("Error: Invalid Input, Try Between [1 To %d]\n", cart.itemsCounter);
    }
    return cart.products[selection - 1];
}
Product retrieveProduct(char *nameString, char *companyString) {
    // Returning the product that match to the sent data
    char productName[100] = {'\0'};
    char productCompany[100] = {'\0'};
    char productCategory[100] = {'\0'};
    char productPrice[100] = {'\0'};
    char productQuantity[100] = {'\0'};
    char buffer[500] = {'\0'};
    Product product = {NULL, NULL, NULL, 0, 0};
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, FILE_CATALOGS, "r")))
        exit(true);

    else {
        while (fscanf_s(file, " %[^\n]", buffer, (unsigned) sizeof(buffer)) == 1) {
            sscanf_s(buffer, " %[^,],%[^,],%[^,],%[^,],%[^,]", productName, (unsigned) sizeof(productName),
                     productCompany, (unsigned) sizeof(productCompany), productCategory,
                     (unsigned) sizeof(productCategory), productPrice, (unsigned) sizeof(productPrice), productQuantity,
                     (unsigned) sizeof(productQuantity));

            if (strcmp(productName, nameString) == 0 && strcmp(productCompany, companyString) == 0) {
                product.name = copyString(productName);
                product.company = copyString(productCompany);
                product.category = copyString(productCategory);
                product.price = convertStringToFloat(productPrice);
                product.quantity = convertStringToInt(productQuantity);
                break;
            }
        }
    }
    fclose(file);
    return product;
}
// Cart
void addProductToCart(Cart *cart) {
    // Adding product to the user cart
    printf("\n[Adding Product]");

    Product product = selectProduct(retrieveRequestedCatalog());
    if (product.name == NULL)
        return;

    cart->products = (Product *) realloc(cart->products, sizeof(Product) * (cart->itemsCounter + 1));
    cart->products[cart->itemsCounter].name = copyString(product.name);
    cart->products[cart->itemsCounter].company = copyString(product.company);
    cart->products[cart->itemsCounter].category = copyString(product.category);
    cart->products[cart->itemsCounter].price = product.price;
    cart->products[cart->itemsCounter].quantity = selectProductQuantity(product);
    cart->itemsCounter++;


    printf("\n[Added Product]\n");
    printf("Name --> %s\n", cart->products[cart->itemsCounter - 1].name);
    printf("Company --> %s\n", cart->products[cart->itemsCounter - 1].company);
    printf("Category --> %s\n", cart->products[cart->itemsCounter - 1].category);
    printf("Price --> %.2f\n", cart->products[cart->itemsCounter - 1].price);
    printf("Quantity --> %d\n", cart->products[cart->itemsCounter - 1].quantity);
    printf("Product Have Been Successfully Added To The Cart\n");
}
void deleteProductFromCart(Cart *cart) {
    // Deleting product from the user cart
    printf("\n[Deleting Product]");

    Product product = selectProduct(*cart);
    if (product.name == NULL)
        return;

    for (int i = 0; i < cart->itemsCounter - 1; i++) {
        if (strcmp(cart->products[i].name, product.name) == 0 &&
            strcmp(cart->products[i].company, product.company) == 0) {
            cart->products[i].name = copyString(cart->products[cart->itemsCounter - 1].name);
            cart->products[i].company = copyString(cart->products[cart->itemsCounter - 1].company);
            cart->products[i].category = copyString(cart->products[cart->itemsCounter - 1].category);
            cart->products[i].price = cart->products[cart->itemsCounter - 1].price;
            cart->products[i].quantity = cart->products[cart->itemsCounter - 1].quantity;
            break;
        }
    }
    cart->itemsCounter--;
    cart->products = (Product *) realloc(cart->products, sizeof(Product) * cart->itemsCounter);


    printf("\n[Deleted Product]\n");
    printf("Name --> %s\n", product.name);
    printf("Company --> %s\n", product.company);
    printf("Category --> %s\n", product.category);
    printf("Price --> %.2f\n", product.price);
    printf("Quantity --> %d\n", product.quantity);
    printf("Product Have Been Successfully Deleted From The Cart\n");
}
void updateProductInCart(Cart *cart) {
    // Updating product from the user cart
    printf("\n[Updating Product Quantity]");

    Product product = selectProduct(*cart);
    if (product.name == NULL)
        return;

    for (int i = 0; i < cart->itemsCounter; i++) {
        if (strcmp(cart->products[i].name, product.name) == 0 &&
            strcmp(cart->products[i].company, product.company) == 0) {
            product.quantity = selectProductQuantity(retrieveProduct(product.name, product.company));
            cart->products[i].quantity = product.quantity;
            break;
        }
    }


    printf("\n[Updated Product]\n");
    printf("Name --> %s\n", product.name);
    printf("Company --> %s\n", product.company);
    printf("Category --> %s\n", product.category);
    printf("Price --> %.2f\n", product.price);
    printf("Quantity --> %d\n", product.quantity);
    printf("Product Have Been Successfully Updated In The Cart\n");
}
void printCart(Cart cart) {
    // Printing the sent cart
    printf("\n[Available Cart]\n");

    if (cart.itemsCounter == 0) {
        printf("Error: Did Not Found Any Products In The Cart\n");
        return;
    }

    for (int i = 0; i < cart.itemsCounter; i++) {
        if (i == 0)
            printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "Product No.", "Name", "Company", "Category", "Price",
                   "Quantity");

        printf("%-15d%-15s%-15s%-15s%-15.2f%-15d\n", i + 1, cart.products[i].name, cart.products[i].company,
               cart.products[i].category, cart.products[i].price, cart.products[i].quantity);
    }
}
void purchaseCart(Cart *cart) {
    // Purchasing the sent user cart
    if (cart->itemsCounter == 0) {
        printf("Error: There's Noting To Purchase In Your Cart\n");
        return;
    }

    if (purchaseCartMenu(*cart) == 2)
        return;

    deliveryProcess();
    paymentProcess(calculateCartTotal(*cart));
    writeOrder(cart);
    updateCatalogAfterPurchase(cart);

    printf("You Have Successfully Purchase The Cart\n");
}
void updateCatalogAfterPurchase(Cart *cart) {
    // Updating products from the system catalog database after user has made a purchase
    char productName[100] = {'\0'};
    char productCompany[100] = {'\0'};
    char productCategory[100] = {'\0'};
    char productPrice[100] = {'\0'};
    char productQuantity[100] = {'\0'};
    char buffer[500] = {'\0'};
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, FILE_CATALOGS, "r")))
        exit(true);

    else {
        resetFile(FILE_TEMP);

        while (fscanf_s(file, " %[^\n]", buffer, (unsigned) sizeof(buffer)) == 1) {
            sscanf_s(buffer, " %[^,],%[^,],%[^,],%[^,],%[^,]", productName, (unsigned) sizeof(productName),
                     productCompany, (unsigned) sizeof(productCompany), productCategory,
                     (unsigned) sizeof(productCompany), productPrice, (unsigned) sizeof(productPrice), productQuantity,
                     (unsigned) sizeof(productQuantity));

            for (int i = cart->itemsCounter - 1; i >= 0; i--) {
                if (strcmp(productName, cart->products[i].name) == 0 &&
                    strcmp(productCompany, cart->products[i].company) == 0) {
                    sprintf_s(buffer, (unsigned) sizeof(buffer), "%s,%s,%s,%s,%d", productName, productCompany,
                              productCategory, productPrice,
                              convertStringToInt(productQuantity) - cart->products[i].quantity);

                    cart->itemsCounter--;
                    cart->products = (Product *) realloc(cart->products, sizeof(Product) * cart->itemsCounter);
                }
            }
            writeFile(FILE_TEMP, buffer);
        }
    }
    fclose(file);
    copyFile(FILE_CATALOGS, FILE_TEMP);
}
float calculateCartTotal(Cart cart) {
    float totalPrice = 0;

    for (int i = 0; i < cart.itemsCounter; i++)
        totalPrice = totalPrice + cart.products[i].price * (float) cart.products[i].quantity;

    return totalPrice;
}
Cart retrieveRequestedCatalog() {
    // Returning Cart full of the items in the system according to the requested filter
    char productName[100] = {'\0'};
    char productCompany[100] = {'\0'};
    char productCategory[100] = {'\0'};
    char productPrice[100] = {'\0'};
    char productQuantity[100] = {'\0'};
    char buffer[500] = {'\0'};
    char *filterBy = NULL;
    char *filterWord = NULL;
    Cart cart = {0, NULL};
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, FILE_CATALOGS, "r")))
        exit(true);

    else {
        catalogFilterMenu(&filterBy, &filterWord);

        if (filterBy) {
            if (strcmp(filterBy, "Name") == 0)
                filterBy = productName;

            else if (strcmp(filterBy, "Company") == 0)
                filterBy = productCompany;

            else
                filterBy = productCategory;
        }

        while (fscanf_s(file, " %[^\n]", buffer, (unsigned) sizeof(buffer)) == 1) {
            sscanf_s(buffer, " %[^,],%[^,],%[^,],%[^,],%[^,]", productName, (unsigned) sizeof(productName),
                     productCompany, (unsigned) sizeof(productCompany), productCategory,
                     (unsigned) sizeof(productCompany), productPrice, (unsigned) sizeof(productPrice), productQuantity,
                     (unsigned) sizeof(productQuantity));

            if (convertStringToInt(productQuantity) > 0) {
                if (filterBy == NULL || (filterBy != NULL && strcmp(filterBy, filterWord) == 0)) {
                    cart.products = (Product *) realloc(cart.products, sizeof(Product) * (cart.itemsCounter + 1));
                    cart.products[cart.itemsCounter].name = copyString(productName);
                    cart.products[cart.itemsCounter].company = copyString(productCompany);
                    cart.products[cart.itemsCounter].category = copyString(productCategory);
                    cart.products[cart.itemsCounter].price = convertStringToFloat(productPrice);
                    cart.products[cart.itemsCounter].quantity = convertStringToInt(productQuantity);
                    cart.itemsCounter++;
                }
            }
        }
    }
    fclose(file);
    return cart;
}

// Delivery
void verifyCountry() {
    // Initialize the country name till its valid
    char countryName[100] = {'\0'};
    bool isCountryValid = false;

    while (isCountryValid == false) {
        isCountryValid = true;

        printf("Country Name -->");
        scanf_s(" %[^\n]", countryName, (unsigned) sizeof(countryName));

        for (int i = 0; i < strlen(countryName); i++) {
            if (((countryName[i] >= 'a' && countryName[i] <= 'z') || (countryName[i] >= 'A' && countryName[i] <= 'Z') ||
                 countryName[i] == ' ') == false) {
                printf("Error: Country Name Contain Only English Alphabet\n\n");
                isCountryValid = false;
                break;
            }
        }
    }
}
