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
    if (ret == -1) {
        printf("Error creating folder %s: %s\n", folderName, strerror(errno));
        exit(EXIT_FAILURE);
    }
}
void resetFile(char *fileName) {
    // Reset the sent file
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, fileName, "w"))) {
        printf("Error opening file %s: %s\n", fileName, strerror(err));
        exit(EXIT_FAILURE);
    }

    fclose(file);
}
void writeFile(char *fileName, char *data) {
    // Saving the sent data into the desirable file
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, fileName, "a+"))) {
        printf("Error creating file %s: %s\n", fileName, strerror(err));
        exit(EXIT_FAILURE);
    } else
        fprintf(file, "%s\n", data);

    fclose(file);
}
void copyFile(char *destinationFileName, char *sourceFileName) {
    // Copy source file content into destination file
    char buffer[500] = {'\0'};
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, sourceFileName, "r"))) {
        printf("Error creating file %s: %s\n", sourceFileName, strerror(err));
        exit(EXIT_FAILURE);
    } else {
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
    // Allocates the given string into a new string with initialized needed size of memory
    char *memoryAllocateString = (char *) malloc(sizeof(char) * (strlen(string) + 1));
    if (memoryAllocateString == NULL)
        exit(True);

    strcpy_s(memoryAllocateString, strlen(string) + 1, string);
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


// User
void verifyUserId(User *user) {
    // Initialize the user ID till its valid
    // Note: the ID check is according to Israel ID's
    char userID[100] = {'\0'};
    Bool isIdValid = False;

    while (isIdValid == False) {
        isIdValid = True;

        printf("User ID -->");
        scanf_s(" %[^\n]", userID, (unsigned) sizeof(userID));

        IDENTITY = copyString(userID);

        long idVal = strtol(userID, NULL, 10);
        int digit1 = 0, digit2 = 0, digit3 = 0, digit4 = 0, digit5 = 0, digit6 = 0, digit7 = 0, digit8 = 0, digit9 = 0;

        if (idVal < 10000000 || idVal > 999999999) {
            printf("Error: User ID Contains Eight To Nine Digits\n");
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
    user->ID = copyString(userID);
}
void verifyUserName(User *user) {
    // Initialize the username till its valid
    char userName[100] = {'\0'};
    Bool isNameValid = False;

    while (isNameValid == False) {
        isNameValid = True;

        printf("User Name -->");
        scanf_s(" %[^\n]", userName, (unsigned) sizeof(userName));

        for (int i = 0; i < strlen(userName); i++) {
            if (((userName[i] >= 'a' && userName[i] <= 'z') || (userName[i] >= 'A' && userName[i] <= 'Z') ||
                 userName[i] == ' ') == False) {
                printf("Error: User Name Contain Only English Alphabet\n\n");
                isNameValid = False;
                break;
            }
        }
    }
    user->name = copyString(userName);
}
void verifyUserPassword(User *user) {
    // Initialize the user password till its valid
    int lettersCounter = 0;
    int numbersCounter = 0;
    char userPassword[100] = {'\0'};
    Bool isPasswordValid = False;

    while (isPasswordValid == False) {
        lettersCounter = 0;
        numbersCounter = 0;
        isPasswordValid = True;

        printf("User Password -->");
        scanf_s(" %[^\n]", userPassword, (unsigned) sizeof(userPassword));

        if (strlen(userPassword) < MIN_PASSWORD_LENGTH) {
            printf("Error: User Password Contain At Least Six Characters\n");
            isPasswordValid = False;
        }

        for (int i = 0; i < strlen(userPassword); i++) {
            if ((userPassword[i] >= 'a' && userPassword[i] <= 'z') ||
                (userPassword[i] >= 'A' && userPassword[i] <= 'Z'))
                lettersCounter++;

            else if (userPassword[i] >= '0' && userPassword[i] <= '9')
                numbersCounter++;

            else {
                printf("Error: User Password Contain Only English Alphabet And Digits\n");
                isPasswordValid = False;
                break;
            }
        }

        if (lettersCounter < MIN_PASSWORD_LETTERS) {
            printf("Error: User Password Contain At Least One English Alphabet\n");
            isPasswordValid = False;
        }

        if (numbersCounter < MIN_PASSWORD_DIGITS) {
            printf("Error: User Password Contain At Least One Digit\n");
            isPasswordValid = False;
        }

        if (isPasswordValid == False)
            printf("\n");
    }
    user->password = copyString(userPassword);
}
void verifyUserPhone(User *user) {
    // Initialize the user phone number till its valid
    // Note: the Phone check is according to Israel Phone's
    char userPhone[100] = {'\0'};
    Bool isPhoneValid = False;

    while (isPhoneValid == False) {
        isPhoneValid = True;

        printf("User Phone -->");
        scanf_s(" %[^\n]", userPhone, (unsigned) sizeof(userPhone));

        for (int i = 0; i < strlen(userPhone); i++) {
            if (userPhone[i] < '0' || userPhone[i] > '9') {
                printf("Error: User Phone Number Contain Only Digits\n");
                isPhoneValid = False;
                break;
            }

            if (strlen(userPhone) != PHONE_LENGTH) {
                printf("Error: User Phone Number Contain Ten Digits\n");
                isPhoneValid = False;
                break;
            }
        }

        if (isPhoneValid == False)
            printf("\n");
    }
    user->phone = copyString(userPhone);
}
void verifyUserAge() {
    // Checking the user age, in order to determine if he is allowed to own an account
    printf("User Age -->");
    int userAge = initializeInt();

    if (userAge < MIN_AGE) {
        printf("Error: We Are Sorry, The Minimum User Age Is Sixteen\n");
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
void registerUser(UserType userType) {
    // Register the user to the users system database
    char buffer[500] = {'\0'};
    User user = {NULL, NULL, NULL, NULL, 0};

    printf("\n[User Registration]\n");
    verifyUserId(&user);
    verifyUserName(&user);
    verifyUserPassword(&user);
    verifyUserPhone(&user);
    verifyUserAge();
    verifyUserTermsAndConditions();

    if (retrieveUserType()) {
        printf("Error: User Already Exist In The System\n\n");
        return;
    }

    if (userType == Customer)
        sprintf_s(buffer, (unsigned) sizeof(buffer), "%s,%s,%s,%s,%.2f", user.ID, user.name, user.password, user.phone,
                  0.0);

    else
        sprintf_s(buffer, (unsigned) sizeof(buffer), "%s,%s,%s,%s", user.ID, user.name, user.password, user.phone);

    writeFile(userType == Customer ? FILE_CUSTOMERS : FILE_MANAGERS, buffer);


    printf("\n[Registered User]\n");
    printf("ID --> %s\n", user.ID);
    printf("Name --> %s\n", user.name);
    printf("Password --> %s\n", user.password);
    printf("Phone --> %s\n", user.phone);
    printf("User Have Been Successfully Registered To The System\n\n");
}
void printUserProfile() {
    // Printing the current logged-in user information
    UserType userType = retrieveUserType();
    User user = retrieveUser(userType == Customer ? FILE_CUSTOMERS : FILE_MANAGERS, userType);

    printf("\n[User Information]\n");
    printf("ID --> %s\n", user.ID);
    printf("Name --> %s\n", user.name);
    printf("Password --> %s\n", user.password);
    printf("Phone --> %s\n", user.phone);

    if (userType == Customer)
        printf("Online Shopping Points --> %.2f\n", user.points);

    printf("User Information Have Been Successfully Printed\n");
}
void updateUserProfile() {
    // Updating the user information as he desires
    char userID[100] = {'\0'};
    char userName[100] = {'\0'};
    char userPassword[100] = {'\0'};
    char userPhone[100] = {'\0'};
    char userPoints[100] = {'\0'};
    char buffer[500] = {'\0'};
    UserType userType = retrieveUserType();
    User user = {NULL, NULL, NULL, NULL, 0};
    FILE *file;
    errno_t err;

    if ((err = fopen_s(&file, userType == Customer ? FILE_CUSTOMERS : FILE_MANAGERS, "r")))
        exit(True);

    else {
        resetFile(FILE_TEMP);

        while (fscanf_s(file, " %[^\n]", buffer, (unsigned) sizeof(buffer)) == 1) {
            sscanf_s(buffer, " %[^,],%[^,],%[^,],%[^,],%[^,]", userID, (unsigned) sizeof(userID), userName,
                     (unsigned) sizeof(userName), userPassword, (unsigned) sizeof(userPassword), userPhone,
                     (unsigned) sizeof(userPhone), userPoints, (unsigned) sizeof(userPoints));

            if (strcmp(userID, IDENTITY) == 0) {
                user.ID = copyString(userID);
                user.name = copyString(userName);
                user.password = copyString(userPassword);
                user.phone = copyString(userPhone);

                userProfileUpdateMenu(&user);

                if (userType == Customer)
                    sprintf_s(buffer, (unsigned) sizeof(buffer), "%s,%s,%s,%s,%s", user.ID, user.name, user.password,
                              user.phone, userPoints);

                else
                    sprintf_s(buffer, (unsigned) sizeof(buffer), "%s,%s,%s,%s", user.ID, user.name, user.password,
                              user.phone);
            }
            writeFile(FILE_TEMP, buffer);
        }
    }
    fclose(file);
    copyFile(userType == Customer ? FILE_CUSTOMERS : FILE_MANAGERS, FILE_TEMP);


    printf("\n[Updated User]\n");
    printf("ID --> %s\n", user.ID);
    printf("Name --> %s\n", user.name);
    printf("Password --> %s\n", user.password);
    printf("Phone --> %s\n", user.phone);

    if (userType == Customer)
        printf("Online Shopping Points --> %.2f\n", user.points);

    printf("User Have Been Successfully Updated\n");
}
void userLogin() {
    // Login the user into the system
    char userID[100] = {'\0'};
    char userPassword[100] = {'\0'};
    Bool isLoggedIn = True;

    printf("\n[User Login]\n");

    printf("User ID -->");
    scanf_s(" %[^\n]", userID, (unsigned) sizeof(userID));

    printf("User Password -->");
    scanf_s(" %[^\n]", userPassword, (unsigned) sizeof(userPassword));

    IDENTITY = copyString(userID);
    UserType userType = retrieveUserType();

    if (userType != None) {
        User user = retrieveUser(userType == Customer ? FILE_CUSTOMERS : FILE_MANAGERS, userType);

        if (strcmp(userPassword, user.password) == 0) {
            printf("User Have Been Successfully Logged In To The System\n");

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
    char userID[100] = {'\0'};
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
            sscanf_s(buffer, " %[^,],%[^,],%[^,],%[^,],%[^,]", userID, (unsigned) sizeof(userID), userName,
                     (unsigned) sizeof(userName), userPassword, (unsigned) sizeof(userPassword), userPhone,
                     (unsigned) sizeof(userPhone), userPoints, (unsigned) sizeof(userPoints));

            if (strcmp(userID, IDENTITY) == 0) {
                printf("\nUser Current Amount Of Online Shopping System --> %.2f\n",
                       convertStringToFloat(userPoints) - decreasePoints);
                sprintf_s(buffer, (unsigned) sizeof(buffer), "%s,%s,%s,%s,%.2f", userID, userName, userPassword,
                          userPhone, convertStringToFloat(userPoints) - decreasePoints);
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
        exit(True);

    else
        while (fscanf_s(file, " %[^\n]", buffer, (unsigned) sizeof(buffer)) == 1) {
            sscanf_s(buffer, " %[^,],%[^,],%[^,],%[^,],%[^,]", userID, (unsigned) sizeof(userID), userName,
                     (unsigned) sizeof(userName), userPassword, (unsigned) sizeof(userPassword), userPhone,
                     (unsigned) sizeof(userPhone), userPoints, (unsigned) sizeof(userPoints));

            if (strcmp(userID, IDENTITY) == 0) {
                user.ID = copyString(userID);
                user.name = copyString(userName);
                user.password = copyString(userPassword);
                user.phone = copyString(userPhone);
                user.points = userType == Customer ? convertStringToFloat(userPoints) : 0;
            }
        }

    fclose(file);
    return user;
}
UserType retrieveUserType() {
    // Returning the current logged-in user his user type
    User user = retrieveUser(FILE_CUSTOMERS, Customer);
    if (user.ID)
        return Customer;

    user = retrieveUser(FILE_MANAGERS, Manager);
    if (user.ID)
        return Manager;

    return None;
}


// Product
void verifyProductName(Product *product) {
    // Initialize the product name till its valid
    char productName[100] = {'\0'};
    Bool isNameValid = False;

    while (isNameValid == False) {
        isNameValid = True;

        printf("Product Name -->");
        scanf_s(" %[^\n]", productName, (unsigned) sizeof(productName));

        for (int i = 0; i < strlen(productName); i++) {
            if (((productName[i] >= 'a' && productName[i] <= 'z') || (productName[i] >= 'A' && productName[i] <= 'Z') ||
                 productName[i] == ' ') == False) {
                printf("Error: Product Name Contain Only English Alphabet\n\n");
                isNameValid = False;
                break;
            }
        }
    }
    product->name = copyString(productName);
}
void verifyProductCompany(Product *product) {
    // Initialize the product company name till its valid
    char productCompany[100] = {'\0'};
    Bool isCompanyValid = False;

    while (isCompanyValid == False) {
        isCompanyValid = True;

        printf("Product Company -->");
        scanf_s(" %[^\n]", productCompany, (unsigned) sizeof(productCompany));

        for (int i = 0; i < strlen(productCompany); i++) {
            if (((productCompany[i] >= 'a' && productCompany[i] <= 'z') ||
                 (productCompany[i] >= 'A' && productCompany[i] <= 'Z') || productCompany[i] == ' ') == False) {
                printf("Error: Product Company Name Contain Only English Alphabet\n\n");
                isCompanyValid = False;
                break;
            }
        }
    }
    product->company = copyString(productCompany);
}
void verifyProductCategory(Product *product) {
    // Initialize the product category name till its valid
    char productCategory[100] = {'\0'};
    Bool isCategoryValid = False;

    while (isCategoryValid == False) {
        isCategoryValid = True;

        printf("Product Category -->");
        scanf_s(" %[^\n]", productCategory, (unsigned) sizeof(productCategory));

        for (int i = 0; i < strlen(productCategory); i++) {
            if (((productCategory[i] >= 'a' && productCategory[i] <= 'z') ||
                 (productCategory[i] >= 'A' && productCategory[i] <= 'Z') || productCategory[i] == ' ') == False) {
                printf("Error: Product Category Name Contain Only English Alphabet\n\n");
                isCategoryValid = False;
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


    printf("\n[Updated Product]\n");
    printf("Name --> %s\n", product.name);
    printf("Company --> %s\n", product.company);
    printf("Category --> %s\n", product.category);
    printf("Price --> %.2f\n", product.price);
    printf("Quantity --> %d\n", product.quantity);
    printf("Product Have Been Successfully Updated In The Catalog\n");
}
Bool doesProductExist(char *fileName, char *productName, char *productCompany) {
    // Checking if the product exist in the catalog system database and return accordingly
    char nameString[100] = {'\0'};
    char companyString[100] = {'\0'};
    char buffer[200] = {'\0'};
    Bool isProductExist = False;
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
        exit(True);

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
    Bool isCountryValid = False;

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
    Bool isCityValid = False;

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
    Bool isStreetValid = False;

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
    Bool isCardValid = False;

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
void verifyCreditCardCVC() {
    // Initialize the credit card CVC till its valid
    // Note: the Credit Cart CVC checks are according to Israel Credit Card CVC
    int creditCardCVC = 0;

    while (creditCardCVC < 100 || creditCardCVC > 999) {
        printf("Credit Card CVC -->");
        creditCardCVC = initializeInt();

        if (creditCardCVC < 100 || creditCardCVC > 999)
            printf("Error: Invalid Input, Try Between [100 To 999]\n\n");
    }
}
void verifyCreditCardDate() {
    // Initialize the credit card date till its valid
    int creditCardMonthDate = 0;
    int creditCardYearDate = 0;
    Bool isDateValid = False;
    Date currentDate = getCurrentDate();

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
    User user = retrieveUser(FILE_CUSTOMERS, Customer);

    printf("\n[Payment Process: Total Of --> %.2f]", totalCartPrice);
    verifyCreditCard();
    verifyCreditCardCVC();
    verifyCreditCardDate();

    updateUserPoints(
            (user.points > 0 ? shoppingPointsMenu(user, totalCartPrice) : 0) - (float) (totalCartPrice * 0.05));
}


// Orders
void writeOrder(Cart *cart) {
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
    Date currentDate = getCurrentDate();

    sprintf_s(buffer, (unsigned) sizeof(buffer), "%d,%s,%.2f,%d/%d/%d,%s", getOrderFileName(), IDENTITY,
              totalOrderPrice, currentDate.day, currentDate.month, currentDate.year, "WAITING");
    writeFile(FILE_ORDERS_SUMMARY, buffer);
}
void printOrdersSummary(int **ordersHistory, char ***customersID, Bool onlyWaitingOrders) {
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
        *customersID = NULL;

        while (fscanf_s(file, " %[^\n]", buffer, (unsigned) sizeof(buffer)) == 1) {
            sscanf_s(buffer, " %[^,],%[^,],%[^,],%[^,],%[^,]", orderId, (unsigned) sizeof(orderId), orderCustomerId,
                     (unsigned) sizeof(orderCustomerId), orderPrice, (unsigned) sizeof(orderPrice), orderDate,
                     (unsigned) sizeof(orderDate), orderStatus, (unsigned) sizeof(orderStatus));

            if (onlyWaitingOrders == False || (onlyWaitingOrders && strcmp(orderStatus, "WAITING") == 0)) {
                if (onlyWaitingOrders == True && index == 0)
                    printf("%-15s%-15s%-15s%-15s%-15s\n", "Order No.", "Customer ID", "Price", "Date", "Status");

                printf("%-15s%-15s%-15s%-15s%-15s\n", orderId, orderCustomerId, orderPrice, orderDate, orderStatus);

                *ordersHistory = (int *) realloc(*ordersHistory, sizeof(int) * (index));
                (*ordersHistory)[index] = convertStringToInt(orderId);

                *customersID = (char **) realloc(*customersID, sizeof(char *) * (strlen(orderCustomerId) + 1));
                (*customersID)[index] = copyString(orderCustomerId);

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
    char **customersID = NULL;

    if (ordersAmount == 1) {
        printf("Error: Did Not Had Orders Yet\n");
        return;
    }

    while (selection < 1 || selection > ordersAmount - 1) {
        printf("\n[Orders Summarize]\n");
        printOrdersSummary(&ordersHistory, &customersID, False);

        printf("Select Order -->");
        selection = initializeInt();

        if (selection < 1 || selection > ordersAmount - 1)
            printf("Error: Invalid Input, Try Between [1 To %d]\n\n", ordersAmount - 1);
    }
    printOrder(ordersHistory[selection], customersID[selection]);
}
void selectOrderConfirmation() {
    // Manager accepting waiting in queue orders
    int selection = 0;
    int arraySize = 0;
    int intSize = 0;
    int *waitingConfirmationOrders = NULL;
    char **customersID = NULL;

    if (getOrderFileName() == 1) {
        printf("Error: Did Not Had Orders Yet\n");
        return;
    }

    while (True) {
        printf("\n[Confirm / Unconfirmed Orders]\n");
        printOrdersSummary(&waitingConfirmationOrders, &customersID, True);

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
                printOrder(waitingConfirmationOrders[i], customersID[i]);
                changeOrderStatus(waitingConfirmationOrders[i]);
                return;
            }
        }
        printf("Error: Invalid Input, Try Available Order ID\n\n");
    }
}
void printOrder(int orderNumber, char *orderID) {
    // Printing the order with the sent parameters
    printf("\n[Order No. --> %d From %s]\n", orderNumber, orderID);

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
              IDENTITY);
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
    Date currentDate = getCurrentDate();

    sprintf_s(buffer, (unsigned) sizeof(buffer), "%d,%s,%d/%d/%d,%s", getTicketFileName(), IDENTITY, currentDate.day,
              currentDate.month, currentDate.year, "WAITING");
    writeFile(FILE_TICKETS_SUMMARY, buffer);
}
void printTicketsSummary(int **ticketsHistory, char ***customersID, Bool onlyWaitingTickets) {
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
        *customersID = NULL;

        while (fscanf_s(file, " %[^\n]", buffer, (unsigned) sizeof(buffer)) == 1) {
            sscanf_s(buffer, " %[^,],%[^,],%[^,],%[^,]", ticketId, (unsigned) sizeof(ticketId), ticketCustomerId,
                     (unsigned) sizeof(ticketCustomerId), ticketDate, (unsigned) sizeof(ticketDate), ticketStatus,
                     (unsigned) sizeof(ticketStatus));

            if (onlyWaitingTickets == False || (onlyWaitingTickets && strcmp(ticketStatus, "WAITING") == 0)) {
                if (onlyWaitingTickets == True && index == 0)
                    printf("%-15s%-15s%-15s%-15s\n", "Ticket No.", "Customer ID", "Date", "Status");

                printf("%-15s%-15s%-15s%-15s\n", ticketId, ticketCustomerId, ticketDate, ticketStatus);

                *ticketsHistory = (int *) realloc(*ticketsHistory, sizeof(int) * (index));
                (*ticketsHistory)[index] = convertStringToInt(ticketId);

                *customersID = (char **) realloc(*customersID, sizeof(char *) * (strlen(ticketCustomerId) + 1));
                (*customersID)[index] = copyString(ticketCustomerId);

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
    char **customersID = NULL;

    if (ticketsAmount == 1) {
        printf("Error: Did Not Had Tickets Yet\n");
        return;
    }

    while (selection < 1 || selection > ticketsAmount - 1) {
        printf("\n[Tickets Summarize]\n");
        printTicketsSummary(&ticketsHistory, &customersID, False);

        printf("Select Ticket -->");
        selection = initializeInt();

        if (selection < 1 || selection > ticketsAmount - 1)
            printf("Error: Invalid Input, Try Between [1 To %d]\n", ticketsAmount - 1);
    }
    printTicket(ticketsHistory[selection], customersID[selection]);
}
void selectTicketConfirmation() {
    // Accepting waiting in queue tickets
    int selection = 0;
    int arraySize = 0;
    int intSize = 0;
    int *waitingConfirmationTickets = NULL;
    char **customersID = NULL;

    if (getTicketFileName() == 1) {
        printf("Error: Did Not Had Tickets Yet\n");
        return;
    }

    while (True) {
        printf("\n[Confirm / Unconfirmed Tickets]\n");
        printTicketsSummary(&waitingConfirmationTickets, &customersID, True);

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
                printTicket(waitingConfirmationTickets[i], customersID[i]);
                changeTicketStatus(waitingConfirmationTickets[i]);
                return;
            }
        }
        printf("Error: Invalid Input, Try Available Ticket ID\n");
    }
}
void printTicket(int ticketNumber, char *ticketID) {
    // Printing the ticket with the sent parameters
    printf("\n[Ticket No. --> %d From %s]\n", ticketNumber, ticketID);

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


// Date
Date getCurrentDate() {
    // Getting the date of the current day (Today)
    char dayString[100] = {'\0'};
    char monthString[100] = {'\0'};
    char yearString[100] = {'\0'};
    char strDate[100];
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    Date date = {0, 0, 0};

    strftime(strDate, sizeof(strDate), "%d %m %Y", tm);
    sscanf_s(strDate, " %s %s %s", dayString, (unsigned) sizeof(dayString), monthString, (unsigned) sizeof(monthString),
             yearString, (unsigned) sizeof(yearString));

    date.day = convertStringToInt(dayString);
    date.month = convertStringToInt(monthString);
    date.year = convertStringToInt(yearString);
    return date;
}
int calculateDateDiff(Date date) {
    // Returning the amount of days between the current date and the received one
    int currentDateInDays = 0;
    int dateInDays = 0;
    int daysInEveryMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    Date currentDate = getCurrentDate();

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
        printf("1' Print User Profile    '2' Update User Profile    '3' Return\nInput -->");

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
void userProfileUpdateMenu(User *user) {
    // The update profile menu
    int selection = 0;

    while (selection < 1 || selection > 5) {
        printf("\n[User Profile Update Menu]\n");
        printf("'1' User ID    '2' User Name    '3' User Password    '4' User Phone    '5' Return\nInput -->");

        selection = initializeInt();
        switch (selection) {
            case 1:
                printf("\n[User ID Update]\n");
                verifyUserId(user);
                break;

            case 2:
                printf("\n[User Name Update]\n");
                verifyUserName(user);
                break;

            case 3:
                printf("\n[User Password Update]\n");
                verifyUserPassword(user);
                break;

            case 4:
                printf("\n[User Phone Update]\n");
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
        Bool isFilterWordValid = False;

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
        printf("'1' Add Product    '2' Delete Product    '3' Update Product    '4' Return\nInput -->");

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
void productUpdateMenu(Product *product) {
    // The Manager product update menu
    int selection = 0;

    while (selection < 1 || selection > 2) {
        printf("\n[Product Update Menu]\n");
        printf("'1' Product Price    '2' Product Quantity\nInput -->");
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
    Cart cart = {0, NULL};

    while (True) {
        printf("\n[Customer Menu]\n");
        printf("'1' Store Menu    '2' Profile Menu    '3' Cart Menu    '4' Submit Ticket    '5' Log Out\nInput -->");

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
                return;

            default:
                printf("Error: Invalid Input, Try Between [1 To 5]\n");
                break;
        }
    }
}
void customerStoreMenu(Cart *cart) {
    // The Customer store menu
    while (True) {
        printf("\n[Customer Store Menu]\n");
        printf("'1' Add Product    '2' Delete Product    '3' Update Product    '4' Return\nInput -->");

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
void cartMenu(Cart *cart) {
    // The Customer Cart menu
    while (True) {
        printf("\n[Cart Menu]\n");
        printf("'1' Print Cart    '2' Purchase Cart    '3' Return\nInput -->");

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

            Date orderDate = {convertStringToInt(dayString), convertStringToInt(monthString),
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
int selectProductQuantity(Product product) {
    // Selecting product quantity menu
    int productQuantity = 0;

    while (productQuantity < 1 || productQuantity > product.quantity) {
        printf("Product Quantity -->");
        productQuantity = initializeInt();

        if (productQuantity < 1 || productQuantity > product.quantity)
            printf("Error: Invalid Input, Try Between [1 To %d]\n\n", product.quantity);
    }
    return productQuantity;
}
int purchaseCartMenu(Cart cart) {
    // The Customer purchase menu
    int selection = 0;

    while (selection < 1 || selection > 2) {
        printf("\n[Purchase Cart Menu]");
        printCart(cart);
        printf("\nAre You Sure You Would Like To Finish Your Order?\n'1' Yes    '2' No\nInput -->");
        selection = initializeInt();

        if (selection < 1 || selection > 2)
            printf("Error: Invalid Input, Try Between [1 To 2]\n");
    }
    return selection;
}
float shoppingPointsMenu(User user, float totalPrice) {
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
