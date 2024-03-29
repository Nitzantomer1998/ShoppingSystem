#include "ShoppingSystem.h"


// Folders & Files
void checkFolder() {
    // Checking if the folders exist, else create them
    if (doesFileExists(FOLDER_DATA) == False)
        createFolder(FOLDER_DATA);

    if (doesFileExists(FOLDER_DATA_USERS) == False)
        createFolder(FOLDER_DATA_USERS);

    if (doesFileExists(FOLDER_DATA_ORDERS) == False)
        createFolder(FOLDER_DATA_ORDERS);

    if (doesFileExists(FOLDER_DATA_TICKETS) == False)
        createFolder(FOLDER_DATA_TICKETS);

    if (doesFileExists(FOLDER_DATA_CATALOGS) == False)
        createFolder(FOLDER_DATA_CATALOGS);

    if (doesFileExists(FOLDER_DATA_ORDERS_SUMMARY) == False)
        createFolder(FOLDER_DATA_ORDERS_SUMMARY);

    if (doesFileExists(FOLDER_DATA_TICKETS_SUMMARY) == False)
        createFolder(FOLDER_DATA_TICKETS_SUMMARY);
}

void checkFiles() {
    // Checking if the files exist, else create them
    if (doesFileExists(FILE_TEMP) == False)
        writeFile(FILE_TEMP, "");

    if (doesFileExists(FILE_MANAGERS) == False)
        writeFile(FILE_MANAGERS, "ID,Name,Password,Phone");

    if (doesFileExists(FILE_CUSTOMERS) == False)
        writeFile(FILE_CUSTOMERS, "ID,Name,Password,Phone,Points");

    if (doesFileExists(FILE_CATALOGS) == False)
        writeFile(FILE_CATALOGS, "Name,Company,Category,Price,Quantity");

    if (doesFileExists(FILE_TICKETS_SUMMARY) == False)
        writeFile(FILE_TICKETS_SUMMARY, "Ticket No.,Customer ID,sDate,Status");

    if (doesFileExists(FILE_ORDERS_SUMMARY) == False)
        writeFile(FILE_ORDERS_SUMMARY, "Order No.,Customer ID,Total,sDate,Status");
}

void createFolder(char *folderName) {
    // Creating new folder with the sent name
    int ret = mkdir(folderName);
    if (ret == -1)
        exit(True);
}

void resetFile(char *fileName) {
    // Reset the sent file
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, fileName, "w")))
        exit(True);

    fclose(file);
}

void writeFile(char *fileName, char *data) {
    // Saving the sent data into the desirable file
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, fileName, "a+")))
        exit(True);

    else
        fprintf(file, "%s\n", data);

    fclose(file);
}

void copyFile(char *destinationFileName, char *sourceFileName) {
    // Copy source file content into destination file
    char buffer[500] = {'\0'};
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, sourceFileName, "r")))
        exit(True);

    else {
        resetFile(destinationFileName);

        while (fscanf_s(file, " %[^\n]", buffer, (unsigned) sizeof(buffer)) == 1)
            writeFile(destinationFileName, buffer);
    }
    fclose(file);
}

eBool doesFileExists(char *fileName) {
    // Checking if the sent file exist and return accordingly
    struct stat buffer;
    return stat(fileName, &buffer) == False;
}


// Strings
char *copyString(char *string) {
    if (string == NULL) return NULL;
    // Allocates the given string into a new string with initialized needed size of memory
    size_t stringLen = strlen(string);
    char *memoryAllocateString = (char *) malloc(sizeof(char) * (stringLen + 1));
    if (memoryAllocateString == NULL)
        return NULL;

    memcpy(memoryAllocateString, string, stringLen + 1);
    return memoryAllocateString;
}

int initializeInt() {
    // Initialize string from the user and convert it into an Integer
    // Note: if the input isn't an Integer the return value will be -1 ("Failed")
    char string[500] = {'\0'};

    scanf_s(" %[^\n]", string, (unsigned) sizeof(string));
    return convertStringToInt(string);
}

int convertStringToInt(char *string) {
    // Converting the given string into an Integer
    // Note: if the input isn't an Integer the return value will be -1 ("Failed")
    int sum = 0;

    for (int i = 0; i < strlen(string); i++) {
        if (string[i] < '0' || string[i] > '9')
            return -1;

        else
            sum = sum * 10 + (string[i] - '0');
    }
    return sum;
}

float initializeFloat() {
    // Initialize string from the user and convert it into a Float
    // Note: if the input isn't a Float the return value will be -1 ("Failed")
    char string[500] = {'\0'};

    scanf_s(" %[^\n]", string, (unsigned) sizeof(string));
    return convertStringToFloat(string);
}

float convertStringToFloat(char *string) {
    // Converting the given string into a Float
    // Note: if the input isn't a Float the return value will be -1 ("Failed")
    int dividePower = 1;
    int sum = 0;

    for (int i = 0; i < strlen(string); i++) {
        if (string[i] >= '0' && string[i] <= '9')
            sum = sum * 10 + (string[i] - '0');

        else if (string[i] == '.')
            for (int j = 1; j < strlen(string) - i; j++)
                dividePower = dividePower * 10;

        else
            return -1;
    }
    return (float) sum / (float) dividePower;
}


// sUser
void verifyUserId(sUser *user) {
    // Initialize the user ID till its valid
    // Note: the ID check is according to Israel ID's
    char userId[100] = {'\0'};
    eBool isIdValid = False;

    while (isIdValid == False) {
        isIdValid = True;

        printf("sUser ID -->");
        scanf_s(" %[^\n]", userId, (unsigned) sizeof(userId));

        gIdentity = copyString(userId);

        long idVal = strtol(userId, NULL, 10);
        int digit1 = 0, digit2 = 0, digit3 = 0, digit4 = 0, digit5 = 0, digit6 = 0, digit7 = 0, digit8 = 0, digit9 = 0;

        if (idVal < 10000000 || idVal > 999999999) {
            printf("Error: sUser ID Contains Eight To Nine Digits\n");
            isIdValid = False;
        }

        digit1 = idVal / 100000000 * 1;
        digit2 = idVal / 10000000 % 10 * 2;
        digit3 = idVal / 1000000 % 10 * 1;
        digit4 = idVal / 100000 % 10 * 2;
        digit5 = idVal / 10000 % 10 * 1;
        digit6 = idVal / 1000 % 10 * 2;
        digit7 = idVal / 100 % 10 * 1;
        digit8 = idVal / 10 % 10 * 2;
        digit9 = idVal % 10;

        if (digit1 > 9 || digit2 > 9 || digit3 > 9 || digit4 > 9 || digit5 > 9 || digit6 > 9 || digit7 > 9 ||
            digit8 > 9 || digit9 > 9) {
            digit1 = (digit1 / 10) + (digit1 % 10);
            digit2 = (digit2 / 10) + (digit2 % 10);
            digit3 = (digit3 / 10) + (digit3 % 10);
            digit4 = (digit4 / 10) + (digit4 % 10);
            digit5 = (digit5 / 10) + (digit5 % 10);
            digit6 = (digit6 / 10) + (digit6 % 10);
            digit7 = (digit7 / 10) + (digit7 % 10);
            digit8 = (digit8 / 10) + (digit8 % 10);
            digit9 = (digit9 / 10) + (digit9 % 10);
        }

        if ((digit1 + digit2 + digit3 + digit4 + digit5 + digit6 + digit7 + digit8 + digit9) % 10 != 0) {
            printf("Error: Incorrect ID\n");
            isIdValid = False;
        }

        if (isIdValid == False)
            printf("\n");
    }
    if (user->id)
        free(user->id);

    user->id = copyString(userId);
}

void verifyUserName(sUser *user) {
    // Initialize the username till its valid
    char userName[100] = {'\0'};
    eBool isNameValid = False;

    while (isNameValid == False) {
        isNameValid = True;

        printf("sUser Name -->");
        scanf_s(" %[^\n]", userName, (unsigned) sizeof(userName));

        for (int i = 0; i < strlen(userName); i++) {
            if (((userName[i] >= 'a' && userName[i] <= 'z') || (userName[i] >= 'A' && userName[i] <= 'Z') ||
                 userName[i] == ' ') == False) {
                printf("Error: sUser Name Contain Only English Alphabet\n\n");
                isNameValid = False;
                break;
            }
        }
    }
    if (user->name)
        free(user->name);

    user->name = copyString(userName);
}

void verifyUserPassword(sUser *user) {
    // Initialize the user password till its valid
    int lettersCounter = 0;
    int numbersCounter = 0;
    char userPassword[100] = {'\0'};
    eBool isPasswordValid = False;

    while (isPasswordValid == False) {
        lettersCounter = 0;
        numbersCounter = 0;
        isPasswordValid = True;

        printf("sUser Password -->");
        scanf_s(" %[^\n]", userPassword, (unsigned) sizeof(userPassword));

        if (strlen(userPassword) < MIN_PASSWORD_LENGTH) {
            printf("Error: sUser Password Contain At Least Six Characters\n");
            isPasswordValid = False;
        }

        for (int i = 0; i < strlen(userPassword); i++) {
            if ((userPassword[i] >= 'a' && userPassword[i] <= 'z') ||
                (userPassword[i] >= 'A' && userPassword[i] <= 'Z'))
                lettersCounter++;

            else if (userPassword[i] >= '0' && userPassword[i] <= '9')
                numbersCounter++;

            else {
                printf("Error: sUser Password Contain Only English Alphabet And Digits\n");
                isPasswordValid = False;
                break;
            }
        }

        if (lettersCounter < MIN_PASSWORD_LETTERS) {
            printf("Error: sUser Password Contain At Least One English Alphabet\n");
            isPasswordValid = False;
        }

        if (numbersCounter < MIN_PASSWORD_DIGITS) {
            printf("Error: sUser Password Contain At Least One Digit\n");
            isPasswordValid = False;
        }

        if (isPasswordValid == False)
            printf("\n");
    }
    if (user->password)
        free(user->password);

    user->password = copyString(userPassword);
}

void verifyUserPhone(sUser *user) {
    // Initialize the user phone number till its valid
    // Note: the Phone check is according to Israel Phone's
    char userPhone[100] = {'\0'};
    eBool isPhoneValid = False;

    while (isPhoneValid == False) {
        isPhoneValid = True;

        printf("sUser Phone -->");
        scanf_s(" %[^\n]", userPhone, (unsigned) sizeof(userPhone));

        for (int i = 0; i < strlen(userPhone); i++) {
            if (userPhone[i] < '0' || userPhone[i] > '9') {
                printf("Error: sUser Phone Number Contain Only Digits\n");
                isPhoneValid = False;
                break;
            }

            if (strlen(userPhone) != PHONE_LENGTH) {
                printf("Error: sUser Phone Number Contain Ten Digits\n");
                isPhoneValid = False;
                break;
            }
        }

        if (isPhoneValid == False)
            printf("\n");
    }
    if (user->phone)
        free(user->phone);

    user->phone = copyString(userPhone);
}

void verifyUserAge() {
    // Checking the user age, in order to determine if he is allowed to own an account
    printf("sUser Age -->");
    int userAge = initializeInt();

    if (userAge < MIN_AGE) {
        printf("Error: We Are Sorry, The Minimum sUser Age Is Sixteen\n");
        exit(True);
    } else if (userAge > MAX_AGE) {
        printf("Error: Sorry If You Are Truly %d Years Old You Probably Death, Goodbye\n", userAge);
        exit(True);
    }
}

void verifyUserTermsAndConditions() {
    // Checking if the user agreed to the system term and condition in order to create an account
    int selection = 0;

    while (selection < 1 || selection > 2) {
        printf("\n[Terms and Conditions]\n");
        printf("Blah Blah Blah ...\n");
        printf("\nDo You Agree To The Terms And Conditions\n'1' Yes    '2' No\nInput -->");

        selection = initializeInt();
        if (selection < 1 || selection > 2)
            printf("Error: Invalid Input, Try Between [1 To 2]\n");
    }

    if (selection == 2) {
        printf("Error: We Are Sorry To Hear, Goodbye\n");
        exit(True);
    }
}

void registerUser(eUserType userType) {
    // Register the user to the users system database
    char buffer[500] = {'\0'};
    sUser user = {NULL, NULL, NULL, NULL, 0};

    printf("\n[sUser Registration]\n");
    verifyUserId(&user);
    verifyUserName(&user);
    verifyUserPassword(&user);
    verifyUserPhone(&user);
    verifyUserAge();
    verifyUserTermsAndConditions();

    if (retrieveUserType()) {
        printf("Error: sUser Already Exist In The System\n\n");
        return;
    }

    if (userType == Customer)
        sprintf_s(buffer, (unsigned) sizeof(buffer), "%s,%s,%s,%s,%.2f", user.id, user.name, user.password, user.phone,
                  0.0);

    else
        sprintf_s(buffer, (unsigned) sizeof(buffer), "%s,%s,%s,%s", user.id, user.name, user.password, user.phone);

    writeFile(userType == Customer ? FILE_CUSTOMERS : FILE_MANAGERS, buffer);


    printf("\n[Registered sUser]\n");
    printf("ID --> %s\n", user.id);
    printf("Name --> %s\n", user.name);
    printf("Password --> %s\n", user.password);
    printf("Phone --> %s\n", user.phone);
    printf("sUser Have Been Successfully Registered To The System\n\n");
}

void printUserProfile() {
    // Printing the current logged-in user information
    eUserType userType = retrieveUserType();
    sUser user = retrieveUser(userType == Customer ? FILE_CUSTOMERS : FILE_MANAGERS, userType);

    printf("\n[sUser Information]\n");
    printf("ID --> %s\n", user.id);
    printf("Name --> %s\n", user.name);
    printf("Password --> %s\n", user.password);
    printf("Phone --> %s\n", user.phone);

    if (userType == Customer)
        printf("Online Shopping Points --> %.2f\n", user.points);

    printf("sUser Information Have Been Successfully Printed\n");
}

void updateUserProfile() {
    // Updating the user information as he desires
    char userId[100] = {'\0'};
    char userName[100] = {'\0'};
    char userPassword[100] = {'\0'};
    char userPhone[100] = {'\0'};
    char userPoints[100] = {'\0'};
    char buffer[500] = {'\0'};
    eUserType userType = retrieveUserType();
    sUser user = {NULL, NULL, NULL, NULL, 0};
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, userType == Customer ? FILE_CUSTOMERS : FILE_MANAGERS, "r")))
        exit(True);

    else {
        resetFile(FILE_TEMP);

        while (fscanf_s(file, " %[^\n]", buffer, (unsigned) sizeof(buffer)) == 1) {
            sscanf_s(buffer, " %[^,],%[^,],%[^,],%[^,],%[^,]", userId, (unsigned) sizeof(userId), userName,
                     (unsigned) sizeof(userName), userPassword, (unsigned) sizeof(userPassword), userPhone,
                     (unsigned) sizeof(userPhone), userPoints, (unsigned) sizeof(userPoints));

            if (strcmp(userId, gIdentity) == 0) {
                user.id = copyString(userId);
                user.name = copyString(userName);
                user.password = copyString(userPassword);
                user.phone = copyString(userPhone);

                userProfileUpdateMenu(&user);

                if (userType == Customer)
                    sprintf_s(buffer, (unsigned) sizeof(buffer), "%s,%s,%s,%s,%s", user.id, user.name, user.password,
                              user.phone, userPoints);

                else
                    sprintf_s(buffer, (unsigned) sizeof(buffer), "%s,%s,%s,%s", user.id, user.name, user.password,
                              user.phone);
            }
            writeFile(FILE_TEMP, buffer);
        }
    }
    fclose(file);
    copyFile(userType == Customer ? FILE_CUSTOMERS : FILE_MANAGERS, FILE_TEMP);


    printf("\n[Updated sUser]\n");
    printf("ID --> %s\n", user.id);
    printf("Name --> %s\n", user.name);
    printf("Password --> %s\n", user.password);
    printf("Phone --> %s\n", user.phone);

    if (userType == Customer)
        printf("Online Shopping Points --> %.2f\n", user.points);

    printf("sUser Have Been Successfully Updated\n");
}

void userLogin() {
    // Login the user into the system
    char userId[100] = {'\0'};
    char userPassword[100] = {'\0'};
    eBool isLoggedIn = True;

    printf("\n[sUser Login]\n");

    printf("sUser ID -->");
    scanf_s(" %[^\n]", userId, (unsigned) sizeof(userId));

    printf("sUser Password -->");
    scanf_s(" %[^\n]", userPassword, (unsigned) sizeof(userPassword));

    if (gIdentity)
        free(gIdentity);

    gIdentity = copyString(userId);
    eUserType userType = retrieveUserType();

    if (userType != None) {
        sUser user = retrieveUser(userType == Customer ? FILE_CUSTOMERS : FILE_MANAGERS, userType);

        if (strcmp(userPassword, user.password) == 0) {
            printf("sUser Have Been Successfully Logged In To The System\n");

            if (userType == Customer)
                customerMenu();

            else
                managerMenu();
        } else
            isLoggedIn = False;
    }

    if (userType == None || isLoggedIn == False)
        printf("Error: Invalid Input, Have Not Found Match Data In Our System\n\n");
}

void updateUserPoints(float decreasePoints) {
    // Updating the user shopping points by decreasing from the sent parameter
    char userId[100] = {'\0'};
    char userName[100] = {'\0'};
    char userPassword[100] = {'\0'};
    char userPhone[100] = {'\0'};
    char userPoints[100] = {'\0'};
    char buffer[500] = {'\0'};
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, FILE_CUSTOMERS, "r")))
        exit(True);

    else {
        resetFile(FILE_TEMP);

        while (fscanf_s(file, " %[^\n]", buffer, (unsigned) sizeof(buffer)) == 1) {
            sscanf_s(buffer, " %[^,],%[^,],%[^,],%[^,],%[^,]", userId, (unsigned) sizeof(userId), userName,
                     (unsigned) sizeof(userName), userPassword, (unsigned) sizeof(userPassword), userPhone,
                     (unsigned) sizeof(userPhone), userPoints, (unsigned) sizeof(userPoints));

            if (strcmp(userId, gIdentity) == 0) {
                printf("\nsUser Current Amount Of Online Shopping System --> %.2f\n",
                       convertStringToFloat(userPoints) - decreasePoints);
                sprintf_s(buffer, (unsigned) sizeof(buffer), "%s,%s,%s,%s,%.2f", userId, userName, userPassword,
                          userPhone, convertStringToFloat(userPoints) - decreasePoints);
            }
            writeFile(FILE_TEMP, buffer);
        }
    }
    fclose(file);
    copyFile(FILE_CUSTOMERS, FILE_TEMP);
}

sUser retrieveUser(char *fileName, eUserType userType) {
    // Returning sUser with the current logged-in user information
    char userId[100] = {'\0'};
    char userName[100] = {'\0'};
    char userPassword[100] = {'\0'};
    char userPhone[100] = {'\0'};
    char userPoints[100] = {'\0'};
    char buffer[500] = {'\0'};
    sUser user = {NULL, NULL, NULL, NULL, 0};
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, fileName, "r")))
        exit(True);

    else
        while (fscanf_s(file, " %[^\n]", buffer, (unsigned) sizeof(buffer)) == 1) {
            sscanf_s(buffer, " %[^,],%[^,],%[^,],%[^,],%[^,]", userId, (unsigned) sizeof(userId), userName,
                     (unsigned) sizeof(userName), userPassword, (unsigned) sizeof(userPassword), userPhone,
                     (unsigned) sizeof(userPhone), userPoints, (unsigned) sizeof(userPoints));

            if (strcmp(userId, gIdentity) == 0) {
                user.id = copyString(userId);
                user.name = copyString(userName);
                user.password = copyString(userPassword);
                user.phone = copyString(userPhone);
                user.points = userType == Customer ? convertStringToFloat(userPoints) : 0;
            }
        }

    fclose(file);
    return user;
}

eUserType retrieveUserType() {
    // Returning the current logged-in user his user type
    sUser user = retrieveUser(FILE_CUSTOMERS, Customer);
    if (user.id)
        return Customer;

    user = retrieveUser(FILE_MANAGERS, Manager);
    if (user.id)
        return Manager;

    return None;
}


// sProduct
void verifyProductName(sProduct *product) {
    // Initialize the product name till its valid
    char productName[100] = {'\0'};
    eBool isNameValid = False;

    while (isNameValid == False) {
        isNameValid = True;

        printf("sProduct Name -->");
        scanf_s(" %[^\n]", productName, (unsigned) sizeof(productName));

        for (int i = 0; i < strlen(productName); i++) {
            if (((productName[i] >= 'a' && productName[i] <= 'z') || (productName[i] >= 'A' && productName[i] <= 'Z') ||
                 productName[i] == ' ') == False) {
                printf("Error: sProduct Name Contain Only English Alphabet\n\n");
                isNameValid = False;
                break;
            }
        }
    }
    if (product->name)
        free(product->name);

    product->name = copyString(productName);
}

void verifyProductCompany(sProduct *product) {
    // Initialize the product company name till its valid
    char productCompany[100] = {'\0'};
    eBool isCompanyValid = False;

    while (isCompanyValid == False) {
        isCompanyValid = True;

        printf("sProduct Company -->");
        scanf_s(" %[^\n]", productCompany, (unsigned) sizeof(productCompany));

        for (int i = 0; i < strlen(productCompany); i++) {
            if (((productCompany[i] >= 'a' && productCompany[i] <= 'z') ||
                 (productCompany[i] >= 'A' && productCompany[i] <= 'Z') || productCompany[i] == ' ') == False) {
                printf("Error: sProduct Company Name Contain Only English Alphabet\n\n");
                isCompanyValid = False;
                break;
            }
        }
    }
    if (product->company)
        free(product->company);

    product->company = copyString(productCompany);
}

void verifyProductCategory(sProduct *product) {
    // Initialize the product category name till its valid
    char productCategory[100] = {'\0'};
    eBool isCategoryValid = False;

    while (isCategoryValid == False) {
        isCategoryValid = True;

        printf("sProduct Category -->");
        scanf_s(" %[^\n]", productCategory, (unsigned) sizeof(productCategory));

        for (int i = 0; i < strlen(productCategory); i++) {
            if (((productCategory[i] >= 'a' && productCategory[i] <= 'z') ||
                 (productCategory[i] >= 'A' && productCategory[i] <= 'Z') || productCategory[i] == ' ') == False) {
                printf("Error: sProduct Category Name Contain Only English Alphabet\n\n");
                isCategoryValid = False;
                break;
            }
        }
    }
    if (product->category)
        free(product->category);

    product->category = copyString(productCategory);
}

void verifyProductPrice(sProduct *product) {
    // Initialize the product price till its valid
    float productPrice = 0;

    while (productPrice <= 0) {
        printf("sProduct Price -->");
        productPrice = initializeFloat();

        if (productPrice <= 0)
            printf("Error: sProduct Price Must Be Greater Than Zero\n\n");
    }
    product->price = productPrice;
}

void verifyProductQuantity(sProduct *product) {
    // Initialize the product quantity till its valid
    int productQuantity = 0;

    while (productQuantity < 1) {
        printf("sProduct Quantity -->");
        productQuantity = initializeInt();

        if (productQuantity < 1)
            printf("Error: sProduct Quantity Must Be Integer Greater Than Zero\n\n");
    }
    product->quantity = productQuantity;
}

void addProductToCatalog() {
    // Adding product to the system catalog database
    char buffer[500] = {'\0'};
    sProduct product = {NULL, NULL, NULL, 0, 0};

    printf("\n[Adding sProduct]\n");
    verifyProductName(&product);
    verifyProductCompany(&product);
    verifyProductCategory(&product);
    verifyProductPrice(&product);
    verifyProductQuantity(&product);

    if (doesProductExist(FILE_CATALOGS, product.name, product.company)) {
        printf("Error: sProduct Already Exist In The System\n");
        return;
    }

    sprintf_s(buffer, (unsigned) sizeof(buffer), "%s,%s,%s,%.2f,%d", product.name, product.company, product.category,
              product.price, product.quantity);
    writeFile(FILE_CATALOGS, buffer);


    printf("\n[Added sProduct]\n");
    printf("Name --> %s\n", product.name);
    printf("Company --> %s\n", product.company);
    printf("Category --> %s\n", product.category);
    printf("Price --> %.2f\n", product.price);
    printf("Quantity --> %d\n", product.quantity);
    printf("sProduct Have Been Successfully Added To The Catalog\n");
}

void deleteProductFromCatalog() {
    // Deleting product from the system catalog database
    char productName[100] = {'\0'};
    char productCompany[100] = {'\0'};
    char productCategory[100] = {'\0'};
    char productPrice[100] = {'\0'};
    char productQuantity[100] = {'\0'};
    char buffer[500] = {'\0'};
    sProduct product = {NULL, NULL, NULL, 0, 0};
    FILE *file;
    errno_t err;

    printf("\n[Deleting sProduct]");
    product = selectProduct(retrieveRequestedCatalog());
    if (product.name == NULL)
        return;

    if ((err = fopen_s(&file, FILE_CATALOGS, "r")))
        exit(True);

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


    printf("\n[Deleted sProduct]\n");
    printf("Name --> %s\n", product.name);
    printf("Company --> %s\n", product.company);
    printf("Category --> %s\n", product.category);
    printf("Price --> %.2f\n", product.price);
    printf("Quantity --> %d\n", product.quantity);
    printf("sProduct Have Been Successfully Deleted From The Catalog\n");

    free(product.name);
    free(product.company);
    free(product.category);
}

void updateProductInCatalog() {
    // Updating product from the system catalog database
    char productName[100] = {'\0'};
    char productCompany[100] = {'\0'};
    char productCategory[100] = {'\0'};
    char productPrice[100] = {'\0'};
    char productQuantity[100] = {'\0'};
    char buffer[500] = {'\0'};
    sProduct product = {NULL, NULL, NULL, 0, 0};
    FILE *file;
    errno_t err;

    printf("\n[Updating sProduct]");
    product = selectProduct(retrieveRequestedCatalog());
    if (product.name == NULL)
        return;

    if ((err = fopen_s(&file, FILE_CATALOGS, "r")))
        exit(True);

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


    printf("\n[Updated sProduct]\n");
    printf("Name --> %s\n", product.name);
    printf("Company --> %s\n", product.company);
    printf("Category --> %s\n", product.category);
    printf("Price --> %.2f\n", product.price);
    printf("Quantity --> %d\n", product.quantity);
    printf("sProduct Have Been Successfully Updated In The Catalog\n");

    free(product.name);
    free(product.company);
    free(product.category);
}

eBool doesProductExist(char *fileName, char *productName, char *productCompany) {
    // Checking if the product exist in the catalog system database and return accordingly
    char nameString[100] = {'\0'};
    char companyString[100] = {'\0'};
    char buffer[200] = {'\0'};
    eBool isProductExist = False;
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, fileName, "r")))
        exit(True);

    else {
        while (fscanf_s(file, " %[^\n]", buffer, (unsigned) sizeof(buffer)) == 1) {
            sscanf_s(buffer, " %[^,],%[^,],%*[^,],%*[^,],%*[^,]", nameString, (unsigned) sizeof(nameString),
                     companyString, (unsigned) sizeof(companyString));

            if (strcmp(nameString, productName) == 0 && strcmp(companyString, productCompany) == 0) {
                isProductExist = True;
                break;
            }
        }
    }
    fclose(file);
    return isProductExist;
}

sProduct selectProduct(sCart cart) {
    // Printing the available catalog, selecting product from it and retrieve the selected product
    if (cart.itemsCounter == 0) {
        printf("Error: There Are No Available Products\n");
        sProduct product = {NULL, NULL, NULL, 0, 0};
        return product;
    }

    int selection = 0;
    while (selection < 1 || selection > cart.itemsCounter) {
        printCart(cart);
        printf("Select sProduct -->");
        selection = initializeInt();

        if (selection < 1 || selection > cart.itemsCounter)
            printf("Error: Invalid Input, Try Between [1 To %d]\n", cart.itemsCounter);
    }
    return cart.products[selection - 1];
}

sProduct retrieveProduct(char *nameString, char *companyString) {
    // Returning the product that match to the sent data
    char productName[100] = {'\0'};
    char productCompany[100] = {'\0'};
    char productCategory[100] = {'\0'};
    char productPrice[100] = {'\0'};
    char productQuantity[100] = {'\0'};
    char buffer[500] = {'\0'};
    sProduct product = {NULL, NULL, NULL, 0, 0};
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, FILE_CATALOGS, "r")))
        exit(True);

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


// sCart
void addProductToCart(sCart *cart) {
    // Adding product to the user cart
    printf("\n[Adding sProduct]");

    sProduct product = selectProduct(retrieveRequestedCatalog());
    if (product.name == NULL)
        return;

    cart->products = (sProduct *) realloc(cart->products, sizeof(sProduct) * (cart->itemsCounter + 1));
    cart->products[cart->itemsCounter].name = copyString(product.name);
    cart->products[cart->itemsCounter].company = copyString(product.company);
    cart->products[cart->itemsCounter].category = copyString(product.category);
    cart->products[cart->itemsCounter].price = product.price;
    cart->products[cart->itemsCounter].quantity = selectProductQuantity(product);
    cart->itemsCounter++;


    printf("\n[Added sProduct]\n");
    printf("Name --> %s\n", cart->products[cart->itemsCounter - 1].name);
    printf("Company --> %s\n", cart->products[cart->itemsCounter - 1].company);
    printf("Category --> %s\n", cart->products[cart->itemsCounter - 1].category);
    printf("Price --> %.2f\n", cart->products[cart->itemsCounter - 1].price);
    printf("Quantity --> %d\n", cart->products[cart->itemsCounter - 1].quantity);
    printf("sProduct Have Been Successfully Added To The sCart\n");
}

void deleteProductFromCart(sCart *cart) {
    // Deleting product from the user cart
    printf("\n[Deleting sProduct]");

    sProduct product = selectProduct(*cart);
    if (product.name == NULL)
        return;

    for (int i = 0; i < cart->itemsCounter; i++) {
        if (strcmp(cart->products[i].name, product.name) == 0 &&
            strcmp(cart->products[i].company, product.company) == 0) {

            if (i != cart->itemsCounter - 1) {
                free(cart->products[i].name);
                free(cart->products[i].company);
                free(cart->products[i].category);

                cart->products[i].name = copyString(cart->products[cart->itemsCounter - 1].name);
                cart->products[i].company = copyString(cart->products[cart->itemsCounter - 1].company);
                cart->products[i].category = copyString(cart->products[cart->itemsCounter - 1].category);
                cart->products[i].price = cart->products[cart->itemsCounter - 1].price;
                cart->products[i].quantity = cart->products[cart->itemsCounter - 1].quantity;
            }

            free(cart->products[cart->itemsCounter - 1].name);
            free(cart->products[cart->itemsCounter - 1].company);
            free(cart->products[cart->itemsCounter - 1].category);

            cart->itemsCounter--;

            if (cart->itemsCounter)
                cart->products = (sProduct *) realloc(cart->products, sizeof(sProduct) * cart->itemsCounter);
            else
                cart->products = NULL;

            break;
        }
    }


    printf("\n[Deleted sProduct]\n");
    printf("Name --> %s\n", product.name);
    printf("Company --> %s\n", product.company);
    printf("Category --> %s\n", product.category);
    printf("Price --> %.2f\n", product.price);
    printf("Quantity --> %d\n", product.quantity);
    printf("sProduct Have Been Successfully Deleted From The sCart\n");
}

void updateProductInCart(sCart *cart) {
    // Updating product from the user cart
    printf("\n[Updating sProduct Quantity]");

    sProduct product = selectProduct(*cart);
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

    printf("\n[Updated sProduct]\n");
    printf("Name --> %s\n", product.name);
    printf("Company --> %s\n", product.company);
    printf("Category --> %s\n", product.category);
    printf("Price --> %.2f\n", product.price);
    printf("Quantity --> %d\n", product.quantity);
    printf("sProduct Have Been Successfully Updated In The sCart\n");

    free(product.name);
    free(product.company);
    free(product.category);
}

void printCart(sCart cart) {
    // Printing the sent cart
    printf("\n[Available sCart]\n");

    if (cart.itemsCounter == 0) {
        printf("Error: Did Not Found Any Products In The sCart\n");
        return;
    }

    for (int i = 0; i < cart.itemsCounter; i++) {
        if (i == 0)
            printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "sProduct No.", "Name", "Company", "Category", "Price",
                   "Quantity");

        printf("%-15d%-15s%-15s%-15s%-15.2f%-15d\n", i + 1, cart.products[i].name, cart.products[i].company,
               cart.products[i].category, cart.products[i].price, cart.products[i].quantity);
    }
}

void purchaseCart(sCart *cart) {
    // Purchasing the sent user cart
    if (cart->itemsCounter == 0) {
        printf("Error: There's Noting To Purchase In Your sCart\n");
        return;
    }

    if (purchaseCartMenu(*cart) == 2)
        return;

    deliveryProcess();
    paymentProcess(calculateCartTotal(*cart));
    writeOrder(cart);
    updateCatalogAfterPurchase(cart);

    printf("You Have Successfully Purchase The sCart\n");
}

void updateCatalogAfterPurchase(sCart *cart) {
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
        exit(True);

    else {
        resetFile(FILE_TEMP);

        while (fscanf_s(file, " %[^\n]", buffer, (unsigned) sizeof(buffer)) == 1) {
            sscanf_s(buffer, " %[^,],%[^,],%[^,],%[^,],%[^,]", productName, (unsigned) sizeof(productName),
                     productCompany, (unsigned) sizeof(productCompany), productCategory,
                     (unsigned) sizeof(productCompany), productPrice, (unsigned) sizeof(productPrice), productQuantity,
                     (unsigned) sizeof(productQuantity));

            for (int i = 0; i < cart->itemsCounter; i++) {
                if (strcmp(productName, cart->products[i].name) == 0 &&
                    strcmp(productCompany, cart->products[i].company) == 0) {
                    sprintf_s(buffer, (unsigned) sizeof(buffer), "%s,%s,%s,%s,%d", productName, productCompany,
                              productCategory, productPrice,
                              convertStringToInt(productQuantity) - cart->products[i].quantity);

                    if (i != cart->itemsCounter - 1) {
                        free(cart->products[i].name);
                        free(cart->products[i].company);
                        free(cart->products[i].category);

                        cart->products[i].name = copyString(cart->products[cart->itemsCounter - 1].name);
                        cart->products[i].company = copyString(cart->products[cart->itemsCounter - 1].company);
                        cart->products[i].category = copyString(cart->products[cart->itemsCounter - 1].category);
                        cart->products[i].price = cart->products[cart->itemsCounter - 1].price;
                        cart->products[i].quantity = cart->products[cart->itemsCounter - 1].quantity;
                    }

                    free(cart->products[cart->itemsCounter - 1].name);
                    free(cart->products[cart->itemsCounter - 1].company);
                    free(cart->products[cart->itemsCounter - 1].category);

                    cart->itemsCounter--;

                    if (cart->itemsCounter > 0)
                        cart->products = (sProduct *) realloc(cart->products, sizeof(sProduct) * cart->itemsCounter);
                    else
                        cart->products = NULL;

                    break;
                }
            }
            writeFile(FILE_TEMP, buffer);
        }
    }
    fclose(file);
    copyFile(FILE_CATALOGS, FILE_TEMP);
}

float calculateCartTotal(sCart cart) {
    float totalPrice = 0;

    for (int i = 0; i < cart.itemsCounter; i++)
        totalPrice = totalPrice + cart.products[i].price * (float) cart.products[i].quantity;

    return totalPrice;
}

sCart retrieveRequestedCatalog() {
    // Returning sCart full of the items in the system according to the requested filter
    char productName[100] = {'\0'};
    char productCompany[100] = {'\0'};
    char productCategory[100] = {'\0'};
    char productPrice[100] = {'\0'};
    char productQuantity[100] = {'\0'};
    char buffer[500] = {'\0'};
    char *filterBy = NULL;
    char *filterWord = NULL;
    sCart cart = {0, NULL};
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, FILE_CATALOGS, "r")))
        exit(True);

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
                    cart.products = (sProduct *) realloc(cart.products, sizeof(sProduct) * (cart.itemsCounter + 1));
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
    eBool isCountryValid = False;

    while (isCountryValid == False) {
        isCountryValid = True;

        printf("Country Name -->");
        scanf_s(" %[^\n]", countryName, (unsigned) sizeof(countryName));

        for (int i = 0; i < strlen(countryName); i++) {
            if (((countryName[i] >= 'a' && countryName[i] <= 'z') || (countryName[i] >= 'A' && countryName[i] <= 'Z') ||
                 countryName[i] == ' ') == False) {
                printf("Error: Country Name Contain Only English Alphabet\n\n");
                isCountryValid = False;
                break;
            }
        }
    }
}

void verifyCity() {
    // Initialize the city name till its valid
    char cityName[100] = {'\0'};
    eBool isCityValid = False;

    while (isCityValid == False) {
        isCityValid = True;

        printf("City Name -->");
        scanf_s(" %[^\n]", cityName, (unsigned) sizeof(cityName));

        for (int i = 0; i < strlen(cityName); i++) {
            if (((cityName[i] >= 'a' && cityName[i] <= 'z') || (cityName[i] >= 'A' && cityName[i] <= 'Z') ||
                 cityName[i] == ' ') == False) {
                printf("City Name Contain Only English Alphabet\n\n");
                isCityValid = False;
                break;
            }
        }
    }
}

void verifyStreet() {
    // Initialize the street name till its valid
    char streetName[100] = {'\0'};
    eBool isStreetValid = False;

    while (isStreetValid == False) {
        isStreetValid = True;

        printf("Street Name -->");
        scanf_s(" %[^\n]", streetName, (unsigned) sizeof(streetName));

        for (int i = 0; i < strlen(streetName); i++) {
            if (((streetName[i] >= 'a' && streetName[i] <= 'z') || (streetName[i] >= 'A' && streetName[i] <= 'Z') ||
                 streetName[i] == ' ') == False) {
                printf("Error: Street Name Contain Only English Alphabet\n\n");
                isStreetValid = False;
                break;
            }
        }
    }
}

void verifyHomeNumber() {
    // Initialize the home number till its valid
    int homeNumber = 0;

    while (homeNumber < 1 || homeNumber > 500) {
        printf("Home Number -->");
        homeNumber = initializeInt();

        if (homeNumber < 1 || homeNumber > 500)
            printf("Error: Invalid Input, Try Between [1 To 500]\n\n");
    }
}

void deliveryProcess() {
    // Process of the delivery
    printf("\n[Delivery Process]\n");
    verifyCountry();
    verifyCity();
    verifyStreet();
    verifyHomeNumber();
}


// Payment
void verifyCreditCard() {
    // Initialize the credit card till its valid
    // Note: the credit card checks are according to Israel Credit Card
    char creditCard[100] = {'\0'};
    eBool isCardValid = False;

    while (isCardValid == False) {
        isCardValid = True;

        printf("\nCredit Card -->");
        scanf_s(" %[^\n]", creditCard, (unsigned) sizeof(creditCard));

        for (int i = 0; i < strlen(creditCard); i++) {
            if (creditCard[i] < '0' || creditCard[i] > '9') {
                printf("Error: Credit Card Contain Only Digits\n");
                isCardValid = False;
                break;
            }
        }

        if (strlen(creditCard) != CREDIT_CARD_LENGTH) {
            printf("Error: Credit Card Must Contain Sixteen Digits\n");
            isCardValid = False;
        }
    }
}

void verifyCreditCardCvc() {
    // Initialize the credit card CVC till its valid
    // Note: the Credit sCart CVC checks are according to Israel Credit Card CVC
    int creditCardCvc = 0;

    while (creditCardCvc < 100 || creditCardCvc > 999) {
        printf("Credit Card CVC -->");
        creditCardCvc = initializeInt();

        if (creditCardCvc < 100 || creditCardCvc > 999)
            printf("Error: Invalid Input, Try Between [100 To 999]\n\n");
    }
}

void verifyCreditCardDate() {
    // Initialize the credit card date till its valid
    int creditCardMonthDate = 0;
    int creditCardYearDate = 0;
    eBool isDateValid = False;
    sDate currentDate = getCurrentDate();

    while (isDateValid == False) {
        creditCardMonthDate = 0;
        creditCardYearDate = 0;
        isDateValid = True;

        while (creditCardMonthDate < 1 || creditCardMonthDate > 12) {
            printf("Credit Card Expiration Month -->");
            creditCardMonthDate = initializeInt();

            if (creditCardMonthDate < 1 || creditCardMonthDate > 12)
                printf("Error: Invalid Input, Try Between [1 To 12]\n\n");
        }

        while (creditCardYearDate < currentDate.year || creditCardYearDate > CREDIT_CARD_MAX_EXPIRATION_YEAR) {
            printf("Credit Card Expiration Year -->");
            creditCardYearDate = initializeInt();

            if (creditCardYearDate < currentDate.year || creditCardYearDate > CREDIT_CARD_MAX_EXPIRATION_YEAR)
                printf("Error: Invalid Input, Try Between [%d To %d]\n\n", currentDate.year,
                       CREDIT_CARD_MAX_EXPIRATION_YEAR);
        }

        if (currentDate.year == creditCardYearDate) {
            if (currentDate.month >= creditCardMonthDate) {
                printf("Error: The Credit Card Is Expired\n\n");
                isDateValid = False;
            }
        }
    }
}

void paymentProcess(float totalCartPrice) {
    // Process of the payment
    sUser user = retrieveUser(FILE_CUSTOMERS, Customer);

    printf("\n[Payment Process: Total Of --> %.2f]", totalCartPrice);
    verifyCreditCard();
    verifyCreditCardCvc();
    verifyCreditCardDate();

    updateUserPoints(
            (user.points > 0 ? shoppingPointsMenu(user, totalCartPrice) : 0) - (float) (totalCartPrice * 0.05));
}


// Orders
void writeOrder(sCart *cart) {
    // Saving the purchase order in the system history purchases
    float totalOrderPrice = calculateCartTotal(*cart);
    char fileName[100] = {'\0'};
    char buffer[500] = {'\0'};

    for (int i = 0; i < cart->itemsCounter; i++) {
        if (i == 0) {
            sprintf_s(fileName, (unsigned) sizeof(fileName), "%s%d.csv", FOLDER_DATA_ORDERS, getOrderFileName());
            writeFile(fileName, "Name,Company,Category,Price,Quantity,Sum");
        }

        sprintf_s(buffer, (unsigned) sizeof(buffer), "%s,%s,%s,%.2f,%d,%.2f", cart->products[i].name,
                  cart->products[i].company, cart->products[i].category, cart->products[i].price,
                  cart->products[i].quantity, cart->products[i].price * (float) cart->products[i].quantity);
        writeFile(fileName, buffer);

        if (i == cart->itemsCounter - 1) {
            sprintf_s(buffer, (unsigned) sizeof(buffer), "\n%s,%.2f", "Total:", totalOrderPrice);
            writeFile(fileName, buffer);
        }
    }
    writeOrderSummary(totalOrderPrice);
}

void writeOrderSummary(float totalOrderPrice) {
    // Saving the purchase order in the summary orders history
    char buffer[500] = {'\0'};
    sDate currentDate = getCurrentDate();

    sprintf_s(buffer, (unsigned) sizeof(buffer), "%d,%s,%.2f,%d/%d/%d,%s", getOrderFileName(), gIdentity,
              totalOrderPrice, currentDate.day, currentDate.month, currentDate.year, "WAITING");
    writeFile(FILE_ORDERS_SUMMARY, buffer);
}

void printOrdersSummary(int **ordersHistory, char ***customersId, eBool onlyWaitingOrders) {
    // Printing the summarized of the orders
    int index = 0;
    char orderId[100] = {'\0'};
    char orderCustomerId[100] = {'\0'};
    char orderPrice[100] = {'\0'};
    char orderDate[100] = {'\0'};
    char orderStatus[100] = {'\0'};
    char buffer[500] = {'\0'};
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, FILE_ORDERS_SUMMARY, "r")))
        exit(True);

    else {
        *ordersHistory = NULL;
        *customersId = NULL;

        while (fscanf_s(file, " %[^\n]", buffer, (unsigned) sizeof(buffer)) == 1) {
            sscanf_s(buffer, " %[^,],%[^,],%[^,],%[^,],%[^,]", orderId, (unsigned) sizeof(orderId), orderCustomerId,
                     (unsigned) sizeof(orderCustomerId), orderPrice, (unsigned) sizeof(orderPrice), orderDate,
                     (unsigned) sizeof(orderDate), orderStatus, (unsigned) sizeof(orderStatus));

            if (onlyWaitingOrders == False || (onlyWaitingOrders && strcmp(orderStatus, "WAITING") == 0)) {
                if (onlyWaitingOrders == True && index == 0)
                    printf("%-15s%-15s%-15s%-15s%-15s\n", "Order No.", "Customer ID", "Price", "sDate", "Status");

                printf("%-15s%-15s%-15s%-15s%-15s\n", orderId, orderCustomerId, orderPrice, orderDate, orderStatus);

                *ordersHistory = (int *) realloc(*ordersHistory, sizeof(int) * (index));
                (*ordersHistory)[index] = convertStringToInt(orderId);

                *customersId = (char **) realloc(*customersId, sizeof(char *) * (strlen(orderCustomerId) + 1));
                (*customersId)[index] = copyString(orderCustomerId);

                index++;
            }
        }
    }
    fclose(file);
}

void selectOrdersSummary() {
    // Printing the summarized of the orders and selecting one in order to see the full order
    int selection = 0;
    int ordersAmount = getOrderFileName();
    int *ordersHistory = NULL;
    char **customersId = NULL;

    if (ordersAmount == 1) {
        printf("Error: Did Not Had Orders Yet\n");
        return;
    }

    while (selection < 1 || selection > ordersAmount - 1) {
        printf("\n[Orders Summarize]\n");
        printOrdersSummary(&ordersHistory, &customersId, False);

        printf("Select Order -->");
        selection = initializeInt();

        if (selection < 1 || selection > ordersAmount - 1)
            printf("Error: Invalid Input, Try Between [1 To %d]\n\n", ordersAmount - 1);
    }
    printOrder(ordersHistory[selection], customersId[selection]);

    for (int i = 0; i < ordersAmount - 1; i++) {
        free(customersId[i]);
    }
    free(customersId);
    free(ordersHistory);
}

void selectOrderConfirmation() {
    // Manager accepting waiting in queue orders
    int selection = 0;
    int arraySize = 0;
    int intSize = 0;
    int *waitingConfirmationOrders = NULL;
    char **customersId = NULL;

    if (getOrderFileName() == 1) {
        printf("Error: Did Not Had Orders Yet\n");
        return;
    }

    while (True) {
        printf("\n[Confirm / Unconfirmed Orders]\n");
        printOrdersSummary(&waitingConfirmationOrders, &customersId, True);

        if (waitingConfirmationOrders == NULL) {
            printf("Error: Did Not Had Unconfirmed Orders Yet\n");
            return;
        }

        arraySize = sizeof(waitingConfirmationOrders);
        intSize = sizeof(waitingConfirmationOrders[0]);

        printf("Select Order -->");
        selection = initializeInt();

        for (int i = 0; i < arraySize / intSize; i++) {
            if (waitingConfirmationOrders[i] == selection) {
                printOrder(waitingConfirmationOrders[i], customersId[i]);
                changeOrderStatus(waitingConfirmationOrders[i]);
                return;
            }
        }
        printf("Error: Invalid Input, Try Available Order ID\n\n");
    }

    for (int i = 0; i < arraySize / intSize - 1; i++) {
        free(customersId[i]);
    }
    free(customersId);
    free(waitingConfirmationOrders);
}

void printOrder(int orderNumber, char *orderId) {
    // Printing the order with the sent parameters
    printf("\n[Order No. --> %d From %s]\n", orderNumber, orderId);

    char productName[100] = {'\0'};
    char productCompany[100] = {'\0'};
    char productCategory[100] = {'\0'};
    char productPrice[100] = {'\0'};
    char productQuantity[100] = {'\0'};
    char buffer[500] = {'\0'};
    FILE *file;
    errno_t err;

    sprintf_s(buffer, (unsigned) sizeof(buffer), "%s%d.csv", FOLDER_DATA_ORDERS, orderNumber);

    if ((err = fopen_s(&file, buffer, "r")))
        exit(True);

    else {
        while (fscanf_s(file, " %[^\n]", buffer, (unsigned) sizeof(buffer)) == 1) {
            sscanf_s(buffer, " %[^,],%[^,],%[^,],%[^,],%[^,]", productName, (unsigned) sizeof(productName),
                     productCompany, (unsigned) sizeof(productCompany), productCategory,
                     (unsigned) sizeof(productCategory), productPrice, (unsigned) sizeof(productPrice), productQuantity,
                     (unsigned) sizeof(productQuantity));

            if (strcmp(productName, "Total:") == 0) {
                printf("%-15s%-15s\n", productName, productCompany);
                break;
            }

            printf("%-15s%-15s%-15s%-15s%-15s\n", productName, productCompany, productCategory, productPrice,
                   productQuantity);
        }
    }
    fclose(file);
}

void changeOrderStatus(int orderNumber) {
    // Confirm the sent order ID
    char orderId[100] = {'\0'};
    char orderCustomerId[100] = {'\0'};
    char orderPrice[100] = {'\0'};
    char orderDate[100] = {'\0'};
    char orderStatus[100] = {'\0'};
    char buffer[500] = {'\0'};
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, FILE_ORDERS_SUMMARY, "r")))
        exit(True);

    else {
        resetFile(FILE_TEMP);

        while (fscanf_s(file, " %[^\n]", buffer, (unsigned) sizeof(buffer)) == 1) {
            sscanf_s(buffer, " %[^,],%[^,],%[^,],%[^,],%[^,]", orderId, (unsigned) sizeof(orderId), orderCustomerId,
                     (unsigned) sizeof(orderCustomerId), orderPrice, (unsigned) sizeof(orderPrice), orderDate,
                     (unsigned) sizeof(orderDate), orderStatus, (unsigned) sizeof(orderStatus));

            if (orderNumber == convertStringToInt(orderId))
                sprintf_s(buffer, 500, "%s,%s,%s,%s,%s", orderId, orderCustomerId, orderPrice, orderDate, "CONFIRMED");

            writeFile(FILE_TEMP, buffer);
        }
    }
    fclose(file);
    copyFile(FILE_ORDERS_SUMMARY, FILE_TEMP);

    printf("Order Has Been Successfully Approved\n");
}

int getOrderFileName() {
    // Return the number of the current order
    char buffer[500] = {'\0'};
    int numberOrder = 0;
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, FILE_ORDERS_SUMMARY, "r")))
        exit(True);

    else
        while (fgets(buffer, (unsigned) sizeof(buffer), file))
            numberOrder++;

    fclose(file);
    return numberOrder;
}


// Tickets
void writeTicket() {
    // Saving the ticket in the system history tickets
    int ticketNumber = getTicketFileName();
    char ticketInformation[500] = {'\0'};
    char buffer[500] = {'\0'};
    char fileName[100] = {'\0'};

    sprintf_s(fileName, (unsigned) sizeof(fileName), "%s%d.csv", FOLDER_DATA_TICKETS, ticketNumber);

    sprintf_s(buffer, (unsigned) sizeof(buffer), "%s,%d\n%s,%s", "Ticket No: ", ticketNumber, "Customer ID: ",
              gIdentity);
    writeFile(fileName, buffer);

    printf("Ticket Title -->");
    scanf_s(" %[^\n]", ticketInformation, (unsigned) sizeof(ticketInformation));
    sprintf_s(buffer, (unsigned) sizeof(buffer), "%s,%s", "Title: ", ticketInformation);
    writeFile(fileName, buffer);

    printf("Ticket -->");
    scanf_s(" %[^\n]", ticketInformation, (unsigned) sizeof(ticketInformation));
    sprintf_s(buffer, (unsigned) sizeof(buffer), "%s,%s", "Ticket: ", ticketInformation);
    writeFile(fileName, buffer);

    writeTicketSummary();
}

void writeTicketSummary() {
    // Saving the submitted ticket in the summary tickets history
    char buffer[500] = {'\0'};
    sDate currentDate = getCurrentDate();

    sprintf_s(buffer, (unsigned) sizeof(buffer), "%d,%s,%d/%d/%d,%s", getTicketFileName(), gIdentity, currentDate.day,
              currentDate.month, currentDate.year, "WAITING");
    writeFile(FILE_TICKETS_SUMMARY, buffer);
}

void printTicketsSummary(int **ticketsHistory, char ***customersId, eBool onlyWaitingTickets) {
    // Printing the summarized tickets
    int index = 0;
    char ticketId[100] = {'\0'};
    char ticketCustomerId[100] = {'\0'};
    char ticketDate[100] = {'\0'};
    char ticketStatus[100] = {'\0'};
    char buffer[500] = {'\0'};
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, FILE_TICKETS_SUMMARY, "r")))
        exit(True);

    else {
        *ticketsHistory = NULL;
        *customersId = NULL;

        while (fscanf_s(file, " %[^\n]", buffer, (unsigned) sizeof(buffer)) == 1) {
            sscanf_s(buffer, " %[^,],%[^,],%[^,],%[^,]", ticketId, (unsigned) sizeof(ticketId), ticketCustomerId,
                     (unsigned) sizeof(ticketCustomerId), ticketDate, (unsigned) sizeof(ticketDate), ticketStatus,
                     (unsigned) sizeof(ticketStatus));

            if (onlyWaitingTickets == False || (onlyWaitingTickets && strcmp(ticketStatus, "WAITING") == 0)) {
                if (onlyWaitingTickets == True && index == 0)
                    printf("%-15s%-15s%-15s%-15s\n", "Ticket No.", "Customer ID", "sDate", "Status");

                printf("%-15s%-15s%-15s%-15s\n", ticketId, ticketCustomerId, ticketDate, ticketStatus);

                *ticketsHistory = (int *) realloc(*ticketsHistory, sizeof(int) * (index));
                (*ticketsHistory)[index] = convertStringToInt(ticketId);

                *customersId = (char **) realloc(*customersId, sizeof(char *) * (strlen(ticketCustomerId) + 1));
                (*customersId)[index] = copyString(ticketCustomerId);

                index++;
            }
        }
    }
    fclose(file);
}

void selectTicketsSummary() {
    // Printing the summarized of the tickets and selecting one in order to see the full ticket
    int selection = 0;
    int ticketsAmount = getTicketFileName();
    int *ticketsHistory = NULL;
    char **customersId = NULL;

    if (ticketsAmount == 1) {
        printf("Error: Did Not Had Tickets Yet\n");
        return;
    }

    while (selection < 1 || selection > ticketsAmount - 1) {
        printf("\n[Tickets Summarize]\n");
        printTicketsSummary(&ticketsHistory, &customersId, False);

        printf("Select Ticket -->");
        selection = initializeInt();

        if (selection < 1 || selection > ticketsAmount - 1)
            printf("Error: Invalid Input, Try Between [1 To %d]\n", ticketsAmount - 1);
    }
    printTicket(ticketsHistory[selection], customersId[selection]);

    for (int i = 0; i < ticketsAmount - 1; i++) {
        free(customersId[i]);
    }
    free(customersId);
    free(ticketsHistory);
}

void selectTicketConfirmation() {
    // Accepting waiting in queue tickets
    int selection = 0;
    int arraySize = 0;
    int intSize = 0;
    int *waitingConfirmationTickets = NULL;
    char **customersId = NULL;

    if (getTicketFileName() == 1) {
        printf("Error: Did Not Had Tickets Yet\n");
        return;
    }

    while (True) {
        printf("\n[Confirm / Unconfirmed Tickets]\n");
        printTicketsSummary(&waitingConfirmationTickets, &customersId, True);

        if (waitingConfirmationTickets == NULL) {
            printf("Error: Did Not Had Unconfirmed Tickets Yet\n");
            return;
        }

        arraySize = sizeof(waitingConfirmationTickets);
        intSize = sizeof(waitingConfirmationTickets[0]);

        printf("Select Ticket -->");
        selection = initializeInt();

        for (int i = 0; i < arraySize / intSize; i++) {
            if (waitingConfirmationTickets[i] == selection) {
                printTicket(waitingConfirmationTickets[i], customersId[i]);
                changeTicketStatus(waitingConfirmationTickets[i]);
                return;
            }
        }
        printf("Error: Invalid Input, Try Available Ticket ID\n");
    }

    for (int i = 0; i < arraySize / intSize; i++) {
        free(customersId[i]);
    }
    free(customersId);
    free(waitingConfirmationTickets);
}

void printTicket(int ticketNumber, char *ticketId) {
    // Printing the ticket with the sent parameters
    printf("\n[Ticket No. --> %d From %s]\n", ticketNumber, ticketId);

    char title[500] = {'\0'};
    char submit[500] = {'\0'};
    char buffer[1000] = {'\0'};
    FILE *file;
    errno_t err;

    sprintf_s(buffer, (unsigned) sizeof(buffer), "%s%d.csv", FOLDER_DATA_TICKETS, ticketNumber);

    if ((err = fopen_s(&file, buffer, "r")))
        exit(True);

    else {
        while (fscanf_s(file, " %[^\n]", buffer, (unsigned) sizeof(buffer)) == 1) {
            sscanf_s(buffer, " %[^,],%[^,]", title, (unsigned) sizeof(title), submit, (unsigned) sizeof(submit));
            printf("%-15s%-15s\n", title, submit);
        }
    }
    fclose(file);
}

void changeTicketStatus(int ticketNumber) {
    // Confirm the sent ticket ID
    char ticketId[100] = {'\0'};
    char ticketCustomerId[100] = {'\0'};
    char ticketDate[100] = {'\0'};
    char ticketStatus[100] = {'\0'};
    char buffer[500] = {'\0'};
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, FILE_TICKETS_SUMMARY, "r")))
        exit(True);

    else {
        resetFile(FILE_TEMP);

        while (fscanf_s(file, " %[^\n]", buffer, (unsigned) sizeof(buffer)) == 1) {
            sscanf_s(buffer, " %[^,],%[^,],%[^,],%[^,]", ticketId, (unsigned) sizeof(ticketId), ticketCustomerId,
                     (unsigned) sizeof(ticketCustomerId), ticketDate, (unsigned) sizeof(ticketDate), ticketStatus,
                     (unsigned) sizeof(ticketStatus));

            if (ticketNumber == convertStringToInt(ticketId))
                sprintf_s(buffer, (unsigned) sizeof(buffer), "%s,%s,%s,%s", ticketId, ticketCustomerId, ticketDate,
                          "CONFIRMED");

            writeFile(FILE_TEMP, buffer);
        }
    }
    fclose(file);
    copyFile(FILE_TICKETS_SUMMARY, FILE_TEMP);

    printf("Ticket Has Been Successfully Approved\n");
}

int getTicketFileName() {
    // Return the number of the current ticket
    char buffer[500] = {'\0'};
    int ticketNumber = 0;
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, FILE_TICKETS_SUMMARY, "r")))
        exit(True);

    else
        while (fgets(buffer, (unsigned) sizeof(buffer), file))
            ticketNumber++;

    fclose(file);
    return ticketNumber;
}


// sDate
sDate getCurrentDate() {
    // Getting the date of the current day (Today)
    char dayString[100] = {'\0'};
    char monthString[100] = {'\0'};
    char yearString[100] = {'\0'};
    char strDate[100];
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    sDate date = {0, 0, 0};

    strftime(strDate, sizeof(strDate), "%d %m %Y", tm);
    sscanf_s(strDate, " %s %s %s", dayString, (unsigned) sizeof(dayString), monthString, (unsigned) sizeof(monthString),
             yearString, (unsigned) sizeof(yearString));

    date.day = convertStringToInt(dayString);
    date.month = convertStringToInt(monthString);
    date.year = convertStringToInt(yearString);
    return date;
}

int calculateDateDiff(sDate date) {
    // Returning the amount of days between the current date and the received one
    int currentDateInDays = 0;
    int dateInDays = 0;
    int daysInEveryMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    sDate currentDate = getCurrentDate();

    currentDateInDays = currentDate.year * 365 + currentDate.day;
    for (int i = 0; i < currentDate.month; i++)
        currentDateInDays = currentDateInDays + daysInEveryMonth[i];

    dateInDays = date.year * 365 + date.day;
    for (int i = 0; i < date.month; i++)
        dateInDays = dateInDays + daysInEveryMonth[i];

    return currentDateInDays - dateInDays;
}


// Menu's
void systemMenu() {
    // The system menu
    while (True) {
        printf("[Online Shopping System Menu]\n");
        printf("'1' Register    '2' Login    '3' Exit\nInput -->");

        int selection = initializeInt();
        switch (selection) {
            case 1:
                registrationMenu();
                break;

            case 2:
                userLogin();
                break;

            case 3:
                printf("You Have Successfully Exit From The System\n");
                return;

            default:
                printf("Error: Invalid Input, Try Between [1 To 3]\n\n");
                break;
        }
    }
}

void registrationMenu() {
    // The registration menu
    while (True) {
        printf("\n[Register As]\n");
        printf("'1' Customer    '2' Manager    '3' Return\nInput -->");

        int managerCode = 0;
        int selection = initializeInt();
        switch (selection) {
            case 1:
                registerUser(Customer);
                return;

            case 2:
                printf("Manager Code -->");
                managerCode = initializeInt();

                if (managerCode == MANAGER_CODE)
                    registerUser(Manager);

                else
                    printf("Error: Wrong Code, GoodBye\n\n");

                return;

            case 3:
                printf("\n");
                return;

            default:
                printf("Error: Invalid Input, Try Between [1 To 3]\n");
                break;
        }
    }
}

void userProfileMenu() {
    // The profile menu
    while (True) {
        printf("\n[Profile Menu]\n");
        printf("1' Print sUser Profile    '2' Update sUser Profile    '3' Return\nInput -->");

        int selection = initializeInt();
        switch (selection) {
            case 1:
                printUserProfile();
                return;

            case 2:
                updateUserProfile();
                return;

            case 3:
                return;

            default:
                printf("Error: Invalid Input, Try Between [1 To 3]\n");
                break;
        }
    }
}

void userProfileUpdateMenu(sUser *user) {
    // The update profile menu
    int selection = 0;

    while (selection < 1 || selection > 5) {
        printf("\n[sUser Profile Update Menu]\n");
        printf("'1' sUser ID    '2' sUser Name    '3' sUser Password    '4' sUser Phone    '5' Return\nInput -->");

        selection = initializeInt();
        switch (selection) {
            case 1:
                printf("\n[sUser ID Update]\n");
                verifyUserId(user);
                break;

            case 2:
                printf("\n[sUser Name Update]\n");
                verifyUserName(user);
                break;

            case 3:
                printf("\n[sUser Password Update]\n");
                verifyUserPassword(user);
                break;

            case 4:
                printf("\n[sUser Phone Update]\n");
                verifyUserPhone(user);
                break;

            case 5:
                break;

            default:
                printf("Error: Invalid Input, Try Between [1 To 5]\n");
                break;
        }
    }
}

void catalogFilterMenu(char **filterBy, char **filterWord) {
    // The filter catalog menu
    int selection = 0;

    while (selection < 1 || selection > 4) {
        printf("\n[Catalog Filter Menu]\n");
        printf("'1' Filter By Name    '2' Filter By Company    '3' Filter By Category    '4' Show All\nInput -->");

        selection = initializeInt();
        switch (selection) {
            case 1:
                *filterBy = "Name";
                break;

            case 2:
                *filterBy = "Company";
                break;

            case 3:
                *filterBy = "Category";
                break;

            case 4:
                break;

            default:
                printf("Invalid Input, Try Between [1 To 4]\n");
                break;
        }
    }

    if (*filterBy) {
        char insertedFilterWord[100] = {'\0'};
        eBool isFilterWordValid = False;

        while (isFilterWordValid == False) {
            isFilterWordValid = True;

            printf("\n[Filter Word]\n");

            printf("Filter Word -->");
            scanf_s(" %[^\n]", insertedFilterWord, (unsigned) sizeof(insertedFilterWord));

            for (int i = 0; i < strlen(insertedFilterWord); i++) {
                if (((insertedFilterWord[i] >= 'a' && insertedFilterWord[i] <= 'z') ||
                     (insertedFilterWord[i] >= 'A' && insertedFilterWord[i] <= 'Z') || insertedFilterWord[i] == ' ') ==
                    False) {
                    printf("Error: Filter Contain Only English Alphabet\n");
                    isFilterWordValid = False;
                    break;
                }
            }
        }
        *filterWord = copyString(insertedFilterWord);
    }
}

void managerMenu() {
    // The Manager menu
    while (True) {
        printf("\n[Manager Menu]\n");
        printf("'1' Store Menu    '2' Profile Menu    '3' Orders Menu    '4' Revenue Menu    '5' Tickets Menu    '6' Log Out\nInput -->");

        int selection = initializeInt();
        switch (selection) {
            case 1:
                managerStoreMenu();
                break;

            case 2:
                userProfileMenu();
                break;

            case 3:
                ordersMenu();
                break;

            case 4:
                revenueMenu();
                break;

            case 5:
                ticketsMenu();
                break;

            case 6:
                printf("You Have Successfully Logged Out\n\n");
                return;

            default:
                printf("Error: Invalid Input, Try Between [1 To 6]\n");
                break;
        }
    }
}

void managerStoreMenu() {
    // The Manager store menu
    while (True) {
        printf("\n[Manager Store Menu]\n");
        printf("'1' Add sProduct    '2' Delete sProduct    '3' Update sProduct    '4' Return\nInput -->");

        int selection = initializeInt();
        switch (selection) {
            case 1:
                addProductToCatalog();
                return;

            case 2:
                deleteProductFromCatalog();
                return;

            case 3:
                updateProductInCatalog();
                return;

            case 4:
                return;

            default:
                printf("Error: Invalid Input, Try Between [1 To 4]\n");
                break;
        }
    }
}

void revenueMenu() {
    // The Manager revenue menu
    if (getOrderFileName() == 1) {
        printf("Error: Did Not Had Orders Yet\n");
        return;
    }

    while (True) {
        printf("\n[Revenue Menu]\n");
        printf("'1' Current Day    '2' Last 7 Days    '3' Last 30 Days    '4' Insert Amount    '5' Return\nInput -->");

        int selection = initializeInt();
        switch (selection) {
            case 1:
                printAskedRevenue(0);
                return;

            case 2:
                printAskedRevenue(7);
                return;

            case 3:
                printAskedRevenue(30);
                return;

            case 4:
                selection = -1;

                while (selection < 0) {
                    printf("Insert Amount Of Days -->");
                    selection = initializeInt();

                    if (selection < 0)
                        printf("Error: Invalid Input, Try Non Negative Integer\n\n");
                }
                printAskedRevenue(selection);
                return;

            case 5:
                return;

            default:
                printf("Error: Invalid Input, Try Between [1 To 5]\n");
                break;
        }
    }
}

void ordersMenu() {
    // The Manager orders menu
    while (True) {
        printf("\n[Orders Menu]\n");
        printf("1' Print Order    '2' Confirm / Unconfirmed Order    '3' Return\nInput -->");

        int selection = initializeInt();
        switch (selection) {
            case 1:
                selectOrdersSummary();
                return;

            case 2:
                selectOrderConfirmation();
                return;

            case 3:
                return;

            default:
                printf("Error: Invalid Input, Try Between [1 To 3]\n");
                break;
        }
    }
}

void ticketsMenu() {
    // The Manager tickets menu
    while (True) {
        printf("\n[Tickets Menu]\n");
        printf("1' Print Ticket    '2' Confirm / Unconfirmed Ticket    '3' Return\nInput -->");

        int selection = initializeInt();
        switch (selection) {
            case 1:
                selectTicketsSummary();
                return;

            case 2:
                selectTicketConfirmation();
                return;

            case 3:
                return;

            default:
                printf("Error: Invalid Input, Try Between [1 To 3]\n");
                break;
        }
    }
}

void productUpdateMenu(sProduct *product) {
    // The Manager product update menu
    int selection = 0;

    while (selection < 1 || selection > 2) {
        printf("\n[sProduct Update Menu]\n");
        printf("'1' sProduct Price    '2' sProduct Quantity\nInput -->");
        selection = initializeInt();

        if (selection < 1 || selection > 2)
            printf("Error: Invalid Input, Try Between [1 To 2]\n");
    }

    if (selection == 1)
        verifyProductPrice(product);

    else
        verifyProductQuantity(product);
}

void customerMenu() {
    // The Customer menu
    sCart cart = {0, NULL};

    while (True) {
        printf("\n[Customer Menu]\n");
        printf("'1' Store Menu    '2' Profile Menu    '3' sCart Menu    '4' Submit Ticket    '5' Log Out\nInput -->");

        int selection = initializeInt();
        switch (selection) {
            case 1:
                customerStoreMenu(&cart);
                break;

            case 2:
                userProfileMenu();
                break;

            case 3:
                cartMenu(&cart);
                break;

            case 4:
                writeTicket();
                break;

            case 5:
                printf("You Have Successfully Logged Out From The System\n\n");

                for (int i = cart.itemsCounter - 1; i >= 0; i--) {
                    free(cart.products[i].name);
                    free(cart.products[i].company);
                    free(cart.products[i].category);

                    cart.itemsCounter--;
                    if (cart.itemsCounter)
                        cart.products = (sProduct *) realloc(cart.products, sizeof(sProduct) * cart.itemsCounter);
                    else
                        cart.products = NULL;
                }
                return;

            default:
                printf("Error: Invalid Input, Try Between [1 To 5]\n");
                break;
        }
    }
}

void customerStoreMenu(sCart *cart) {
    // The Customer store menu
    while (True) {
        printf("\n[Customer Store Menu]\n");
        printf("'1' Add sProduct    '2' Delete sProduct    '3' Update sProduct    '4' Return\nInput -->");

        int selection = initializeInt();
        switch (selection) {
            case 1:
                addProductToCart(cart);
                return;

            case 2:
                deleteProductFromCart(cart);
                return;

            case 3:
                updateProductInCart(cart);
                return;

            case 4:
                return;

            default:
                printf("Error: Invalid Input, Try Between [1 To 4]\n");
                break;
        }
    }
}

void cartMenu(sCart *cart) {
    // The Customer sCart menu
    while (True) {
        printf("\n[sCart Menu]\n");
        printf("'1' Print sCart    '2' Purchase sCart    '3' Return\nInput -->");

        int selection = initializeInt();
        switch (selection) {
            case 1:
                printCart(*cart);
                return;

            case 2:
                purchaseCart(cart);
                return;

            case 3:
                return;

            default:
                printf("Error: Invalid Input, Try Between [1 To 3]\n");
                break;
        }
    }
}

void printAskedRevenue(int revenueDays) {
    // Printing the system revenue in the sent amount of days
    int ordersCounter = 0;
    float totalRevenue = 0;
    float totalPrice = 0;
    char dayString[100] = {'\0'};
    char monthString[100] = {'\0'};
    char yearString[100] = {'\0'};
    char priceString[100] = {'\0'};
    char buffer[500] = {'\0'};
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, FILE_ORDERS_SUMMARY, "r")))
        exit(True);

    else {
        while (fscanf_s(file, " %[^\n]", buffer, (unsigned) sizeof(buffer)) == 1) {
            sscanf_s(buffer, " %*[^,],%*[^,],%[^,],%[^/]/%[^/]/%[^,],%*[^,]", priceString,
                     (unsigned) sizeof(priceString), dayString, (unsigned) sizeof(dayString), monthString,
                     (unsigned) sizeof(monthString), yearString, (unsigned) sizeof(yearString));

            sDate orderDate = {convertStringToInt(dayString), convertStringToInt(monthString),
                               convertStringToInt(yearString)};
            totalPrice = convertStringToFloat(priceString);

            if (calculateDateDiff(orderDate) <= revenueDays) {
                totalRevenue = totalRevenue + totalPrice;
                ordersCounter++;
            }
        }
        printf("[Revenue In %d Days]\n", revenueDays);
        printf("Revenue --> %.2f In %d Orders]\n", totalRevenue, ordersCounter);
    }
    fclose(file);
}

int main() {
    checkFolder();
    checkFiles();
    systemMenu();
}

int selectProductQuantity(sProduct product) {
    // Selecting product quantity menu
    int productQuantity = 0;

    while (productQuantity < 1 || productQuantity > product.quantity) {
        printf("sProduct Quantity -->");
        productQuantity = initializeInt();

        if (productQuantity < 1 || productQuantity > product.quantity)
            printf("Error: Invalid Input, Try Between [1 To %d]\n\n", product.quantity);
    }
    return productQuantity;
}

int purchaseCartMenu(sCart cart) {
    // The Customer purchase menu
    int selection = 0;

    while (selection < 1 || selection > 2) {
        printf("\n[Purchase sCart Menu]");
        printCart(cart);
        printf("\nAre You Sure You Would Like To Finish Your Order?\n'1' Yes    '2' No\nInput -->");
        selection = initializeInt();

        if (selection < 1 || selection > 2)
            printf("Error: Invalid Input, Try Between [1 To 2]\n");
    }
    return selection;
}

float shoppingPointsMenu(sUser user, float totalPrice) {
    // The Customer shopping points menu
    int selection = 0;
    float shoppingPoints = 0;

    while (selection < 1 || selection > 2) {
        printf("\n[Shopping Points Menu]\n");
        printf("Available Shopping Points --> %.2f\n", user.points);
        printf("Would You Like To Use Them?\n'1' Yes    '2' No\nInput -->");
        selection = initializeInt();

        if (selection < 1 || selection > 2)
            printf("Error: Invalid Input, Try Between [1 To 2]\n");
    }

    if (selection == 1) {
        while (shoppingPoints < 0 || shoppingPoints > totalPrice || shoppingPoints > user.points) {
            printf("\nInput Shopping Points Amount -->");
            shoppingPoints = initializeFloat();

            if (shoppingPoints < 0 || shoppingPoints > totalPrice || shoppingPoints > user.points)
                printf("Error: Invalid Input, Try Between [0 To %.2f]\n",
                       user.points > totalPrice ? totalPrice : user.points);
        }
    }
    return shoppingPoints;
}
