#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// ==================================================================================
// التعريفات الأساسية والهياكل (Structures)
// ==================================================================================

const string ClientsFileName = "File_Database/Clients.txt";
const string UsersFileName = "File_Database/Users.txt";

struct stInfoClient {
    string Account_Number;
    string PIN_Code;
    string Client_Name;
    string Client_Phone_Number;
    double Account_Balance = 0;
    bool MarkForDelete = false;
};

struct stInfoUser {
    string UserName;
    string Password;
    int Permission;
    bool MarkForDelete = false;
};

// الإعلانات المسبقة للدوال الرئيسية
void Start();
void Transaction();
void ManageUsers();
bool Login();


// ==================================================================================
// دالة القراءة للنصوص
// ==================================================================================

string ReadString(string TEXT) {
    string Text;
    cout << TEXT;
    getline(cin >> ws, Text);
    return Text;
}

// دالة مساعدة لقراءة الأرقام الموجبة
short ReadPositiveNumber(string Message) {
    short Number = 0;
    do {
        cout << Message;
        cin >> Number;
    } while (Number <= 0);
    return Number;
}

// ==================================================================================
// دوال معالجة النصوص وتحويل البيانات (Data Transformation)
// ==================================================================================

/**
 * تقسم النص إلى ناقل (vector) من الكلمات بناءً على فاصل محدد.
 */
vector<string> SplitString(string& Text, string Delim) {
    vector<string> vValues;
    size_t pos = 0;
    string Word;

    while ((pos = Text.find(Delim)) != std::string::npos) {
        Word = Text.substr(0, pos);
        if (Word != "") {
            vValues.push_back(Word);
        }
        Text.erase(0, pos + Delim.length());
    }

    if (Text != "") {
        vValues.push_back(Text);
    }
    return vValues;
}

/**
 * تحول سطراً نصياً من الملف إلى هيكل بيانات العميل (struct).
 */
stInfoClient ConvertLineToRecord(string& Line, string Seperator = "/##/") {
    stInfoClient Client;
    vector<string> vClientInfo = SplitString(Line, Seperator);

    Client.Account_Number = vClientInfo[0];
    Client.PIN_Code = vClientInfo[1];
    Client.Client_Name = vClientInfo[2];
    Client.Client_Phone_Number = vClientInfo[3];
    Client.Account_Balance = stod(vClientInfo[4]);

    return Client;
}

/**
 * تحول سطراً نصياً من الملف إلى هيكل بيانات المستخدم (struct).
 */
stInfoUser ConvertLineToRecord2(string& Line, string Seperator = "#//#") {
    stInfoUser User;
    vector<string> vUserInfo = SplitString(Line, Seperator);

    User.UserName = vUserInfo[0];
    User.Password = vUserInfo[1];
    User.Permission =stoi(vUserInfo[2]);

    return User;
}


/**
 * تحول بيانات العميل من هيكل البيانات إلى سطر نصي مهيأ للحفظ في الملف.
 */
string ConvertRecordToLine(stInfoClient Client, string Seperator = "/##/") {
    string Line = "";
    Line += Client.Account_Number + Seperator;
    Line += Client.PIN_Code + Seperator;
    Line += Client.Client_Name + Seperator;
    Line += Client.Client_Phone_Number + Seperator;
    Line += to_string(Client.Account_Balance);
    return Line;
}

/**
 * تحول بيانات المستخدم من هيكل البيانات إلى سطر نصي مهيأ للحفظ في الملف.
 */
string ConvertRecordToLine(stInfoUser User, string Seperator = "#//#") {
    string Line = "";
    Line += User.UserName + Seperator;
    Line += User.Password + Seperator;
    Line += to_string(User.Permission);
    return Line;
}

// ==================================================================================
// دوال إدارة الملفات وقاعدة البيانات (File Management)
// ==================================================================================

/**
 * تحمل كافة بيانات العملاء من الملف إلى ذاكرة البرنامج (vector).
 */
vector<stInfoClient> LoadClientsDataFromFile(string FileName) {
    vector<stInfoClient> vClient;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open()) {
        string Line;
        stInfoClient Client;
        while (getline(MyFile, Line)) {
            Client = ConvertLineToRecord(Line);
            vClient.push_back(Client);
        }
        MyFile.close();
    }
    return vClient;
}

/**
 * تحمل كافة بيانات المستخدمين من الملف إلى ذاكرة البرنامج (vector).
 */
vector<stInfoUser> LoadUsersDataFromFile(string FileName) {
    vector<stInfoUser> vUser;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open()) {
        string Line;
        stInfoUser User;
        while (getline(MyFile, Line)) {
            User = ConvertLineToRecord2(Line);
            vUser.push_back(User);
        }
        MyFile.close();
    }
    return vUser;
}

/**
 * تعيد كتابة بيانات العميل في الملف (تستخدم للتحديث أو الحذف).
 */
void SaveClientsDataToFile(string FileName, vector<stInfoClient>& vClients) {
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    if (MyFile.is_open()) {
        for (stInfoClient& C : vClients) {
            if (!C.MarkForDelete) {
                MyFile << ConvertRecordToLine(C) << endl;
            }
        }
        MyFile.close();
    }
}

/**
 * تعيد كتابة بيانات المستخدم في الملف (تستخدم للتحديث أو الحذف).
 */
void SaveUsersDataToFile(string FileName, vector<stInfoUser>& vUsers) {
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    if (MyFile.is_open()) {
        for (stInfoUser& U : vUsers) {
            if (!U.MarkForDelete) {
                MyFile << ConvertRecordToLine(U) << endl;
            }
        }
        MyFile.close();
    }
}


/**
 * تضيف سطر بيانات جديد في نهاية الملف مباشرة.
 */
void AddDataLineToFile(string FileName, string DataLine) {
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open()) {
        MyFile << DataLine << endl;
        MyFile.close();
    }
}

// ==================================================================================
// دوال البحث والتحقق (Search & Validation)
// ==================================================================================

/**
 * تتحقق مما إذا كان رقم حساب العميل موجوداً مسبقاً في النظام.
 */
bool ClientExistsByAccountNumber(string AccountNumber, string ClientsFileName) {
    fstream MyFile;
    MyFile.open(ClientsFileName, ios::in);
    if (MyFile.is_open()) {
        string Line;
        stInfoClient Client;
        while (getline(MyFile, Line)) {
            Client = ConvertLineToRecord(Line);
            if (Client.Account_Number == AccountNumber) {
                MyFile.close();
                return true;
            }
        }
        MyFile.close();
    }
    return false;
}

/**
 * تتحقق مما إذا كان رقم حساب المستخدم موجوداً مسبقاً في النظام.
 */
bool UsersExistsByUserName(string UserName, string UsersFileName) {
    fstream MyFile;
    MyFile.open(UsersFileName, ios::in);
    if (MyFile.is_open()) {
        string Line;
        stInfoUser User;
        while (getline(MyFile, Line)) {
            User = ConvertLineToRecord2(Line);
            if (User.UserName == UserName) {
                MyFile.close();
                return true;
            }
        }
        MyFile.close();
    }
    return false;
}

/**
 * تبحث عن متسخدم محدد داخل المتجه وتعيد بياناته بالمرجع.
 */
bool FindUserByUserName(stInfoUser& User, vector<stInfoUser> vUser, string UserName) {
    for (stInfoUser U : vUser) {
        if (U.UserName == UserName) {
            User = U;
            return true;
        }
    }
    return false;
}

/**
 * تبحث عن عميل محدد داخل المتجه وتعيد بياناته بالمرجع.
 */
bool FindClientByAccountNumber(stInfoClient& Client, vector<stInfoClient> vClient, string AccountNumber) {
    for (stInfoClient C : vClient) {
        if (C.Account_Number == AccountNumber) {
            Client = C;
            return true;
        }
    }
    return false;
}

bool FindUserByUsernameAndPassword(string UserName, string Password, stInfoUser& User) {
    vector<stInfoUser> vUsers = LoadUsersDataFromFile(UsersFileName);

    for (stInfoUser& U : vUsers) {
        if (U.UserName == UserName && U.Password == Password) {
            User = U;
            return true;
        }
    }
    return false;
}

// ==================================================================================
// دوال الإدخال والطباعة الأساسية (Base UI)
// ==================================================================================

void PrintHeader(string Text) {
    cout << "====================================================================================================\n";
    cout << "\t\t\t\t\t" << Text << "\n";
    cout << "====================================================================================================\n";
}

void PrintClientInfo(stInfoClient& ClientInfo) {
    cout << "\nClient Information : \n";
    cout << "---------------------------------------------\n";
    cout << "Account Number  : " << ClientInfo.Account_Number << endl;
    cout << "Pin Code        : " << ClientInfo.PIN_Code << endl;
    cout << "Client Name     : " << ClientInfo.Client_Name << endl;
    cout << "Phone Number    : " << ClientInfo.Client_Phone_Number << endl;
    cout << "Account Balance : " << ClientInfo.Account_Balance << " $" << endl;
}

void PrintUserInfo(stInfoUser& UserInfo) {
    cout << "\nUser Information : \n";
    cout << "---------------------------------------------\n";
    cout << "User Name       : " << UserInfo.UserName << endl;
    cout << "Password        : " << UserInfo.Password << endl;
    cout << "Permissions     : " << UserInfo.Permission << endl;
}

void PrintClientRecord(stInfoClient ClientInfo) {
    cout << "| " << left << setw(15) << ClientInfo.Account_Number;
    cout << "| " << left << setw(15) << ClientInfo.PIN_Code;
    cout << "| " << left << setw(25) << ClientInfo.Client_Name;
    cout << "| " << left << setw(25) << ClientInfo.Client_Phone_Number;
    cout << "| " << left << setw(12) << (to_string(ClientInfo.Account_Balance) + " $");
}

void PrintUserRecord(stInfoUser UserInfo) {
    cout << "| " << left << setw(15) << UserInfo.UserName;
    cout << "| " << left << setw(15) << UserInfo.Password;
    cout << "| " << left << setw(12) << (to_string(UserInfo.Permission));
}

stInfoClient ReadInfoClient() {
    stInfoClient New_Client;
    cout << "Please Enter a New Clinet Data :\n\n";
    cout << "Enter Account Number : ";
    getline(cin >> ws, New_Client.Account_Number);

    while (ClientExistsByAccountNumber(New_Client.Account_Number, ClientsFileName)) {
        cout << "\nClient With [" << New_Client.Account_Number << "] Already exists , Enter Anouther Account Number : ";
        getline(cin >> ws, New_Client.Account_Number);
        cout << endl;
    }

    cout << "Enter PIN Code : ";
    getline(cin, New_Client.PIN_Code);
    cout << "Enter Client Name : ";
    getline(cin, New_Client.Client_Name);
    cout << "Enter Client Phone Number : ";
    getline(cin, New_Client.Client_Phone_Number);
    cout << "Enter Your Account Balance : ";
    cin >> New_Client.Account_Balance;

    return New_Client;
}

stInfoUser ReadInfoUser() {
    stInfoUser New_User;
    cout << "Please Enter a New User Data :\n\n";
    cout << "Enter User Name : ";
    getline(cin >> ws, New_User.UserName);

    while (UsersExistsByUserName(New_User.UserName, UsersFileName)) {
        cout << "\nUser With [" << New_User.UserName << "] Already exists , Enter Anouther Account Number : ";
        getline(cin >> ws, New_User.UserName);
        cout << endl;
    }

    cout << "Enter Password : ";
    getline(cin, New_User.Password);

    cout << "Enter Your Permission : ";
    cin >> New_User.Permission;

    return New_User;
}

stInfoClient UpdateClient(stInfoClient& Client) {
    cout << "Enter Pin Code : ";
    getline(cin >> ws, Client.PIN_Code);
    cout << "Enter Client Name : ";
    getline(cin, Client.Client_Name);
    cout << "Enter Client Phone: ";
    getline(cin, Client.Client_Phone_Number);
    cout << "Enter Client Balance : ";
    cin >> Client.Account_Balance;
    return Client;
}

stInfoUser UpdateUser(stInfoUser& User) {

    cout << "Enter New Password : ";
    getline(cin, User.Password);
    cout << "Enter Permission : ";
    cin >> User.Permission;
    return User;
}

// ==================================================================================
// دوال العمليات الرئيسية (Core Operations)
// ==================================================================================

void AddNewClient() {
    stInfoClient Client;
    Client = ReadInfoClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client,"/##/"));
}

void AddNewUser() {
    stInfoUser User;
    User = ReadInfoUser();
    AddDataLineToFile(UsersFileName, ConvertRecordToLine(User));
}

void AddNewClients() {
    char AddMore = 'Y';
    do {
        AddNewClient();
        cout << "\n\n\aAdd Client Successfully , Do you want add more client ? Y/N : ";
        cin >> AddMore;
        cout << "\n\n";
    } while (toupper(AddMore) == 'Y');
}

void AddNewUsers() {
    char AddMore = 'Y';
    do {
        AddNewUser();
        cout << "\n\n\aAdd User Successfully , Do you want add more User ? Y/N : ";
        cin >> AddMore;
        cout << "\n\n";
    } while (toupper(AddMore) == 'Y');
}

bool DeleteClientByAccountNumber(vector<stInfoClient>& vClient, string AccountNumber) {
    char Answer = 'n';
    for (stInfoClient& C : vClient) {
        if (C.Account_Number == AccountNumber) {
            PrintClientInfo(C);
            cout << "\n\nAre You Sure you want delete this client? Y/N: ";
            cin >> Answer;
            if (toupper(Answer) == 'Y') {
                C.MarkForDelete = true;
                SaveClientsDataToFile(ClientsFileName, vClient);
                vClient = LoadClientsDataFromFile(ClientsFileName);
                cout << "\n\nClient Delete Successfully!";
                return true;
            }
        }
    }
    return false;
}

bool DeleteUserByUserName(vector<stInfoUser>& vUser, string UserName) {
    char Answer = 'n';
    for (stInfoUser& V : vUser) {
        if (V.UserName == UserName) {
            PrintUserInfo(V);
            cout << "\n\nAre You Sure you want delete this User? Y/N: ";
            cin >> Answer;
            if (toupper(Answer) == 'Y') {
                V.MarkForDelete = true;
                SaveUsersDataToFile(UsersFileName, vUser);
                vUser = LoadUsersDataFromFile(UsersFileName);
                cout << "\n\nUser Delete Successfully!";
                return true;
            }
        }
    }
    return false;
}

bool UpdateClientByAccountNumber(vector<stInfoClient>& vClient, string AccountNumber) {
    char Answer = 'n';
    for (stInfoClient& C : vClient) {
        if (C.Account_Number == AccountNumber) {
            PrintClientInfo(C);
            cout << "\n\nAre You Sure You Want Update This Client? Y/N: ";
            cin >> Answer;
            if (toupper(Answer) == 'Y') {
                UpdateClient(C);
                SaveClientsDataToFile(ClientsFileName, vClient);
                cout << "\n\nUpdate Client Successfully!";
                return true;
            }
        }
    }
    return false;
}

bool UpdateUserByUserName(vector<stInfoUser>& vUser, string UserName) {
    char Answer = 'n';
    for (stInfoUser& V : vUser) {
        if (V.UserName == UserName) {
            PrintUserInfo(V);
            cout << "\n\nAre You Sure You Want Update This User? Y/N: ";
            cin >> Answer;
            if (toupper(Answer) == 'Y') {
                UpdateUser(V);
                SaveUsersDataToFile(UsersFileName, vUser);
                cout << "\n\nUpdate User Successfully!";
                return true;
            }
        }
    }
    return false;
}

bool DepositeClientByAccountNumber(double Amount, vector<stInfoClient>& vClient, string AccountNumber) {
    for (stInfoClient& Client : vClient) {
        if (Client.Account_Number == AccountNumber) {
            Client.Account_Balance += Amount;
            SaveClientsDataToFile(ClientsFileName, vClient);
            cout << "\n\nDone Successfully. New Balance is: " << Client.Account_Balance << " $ " << endl;
            return true;
        }
    }
    return false;
}

// ==================================================================================
// شاشات العرض (Screens)
// ==================================================================================

void PrintAllClientsData() {
    vector<stInfoClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    cout << "\n\t\t\t\t Client List (" << vClients.size() << ")" << " Client(s).";
    cout << "\n---------------------------------------------------------------------------------------------------" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(15) << "Pin Code";
    cout << "| " << left << setw(25) << "Client Name";
    cout << "| " << left << setw(25) << "phone Number";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n---------------------------------------------------------------------------------------------------" << endl;

    for (stInfoClient Client : vClients) {
        PrintClientRecord(Client);
        cout << endl;
    }
}

void PrintAllUsersData() {
    vector<stInfoUser> vUsers = LoadUsersDataFromFile(UsersFileName);
    cout << "\n\t\t\t\t Users List (" << vUsers.size() << ")" << " User(s).";
    cout << "\n---------------------------------------------------------------------------------------------------" << endl;
    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(15) << "Password";
    cout << "| " << left << setw(25) << "Permission";
    cout << "\n---------------------------------------------------------------------------------------------------" << endl;

    for (stInfoUser User : vUsers) {
        PrintUserRecord(User);
        cout << endl;
    }
}

void PrintBalanceClientRecord(stInfoClient ClientInfo) {
    cout << "| " << left << setw(15) << ClientInfo.Account_Number;
    cout << "| " << left << setw(25) << ClientInfo.Client_Name;
    cout << "| " << left << setw(12) << (to_string(ClientInfo.Account_Balance) + " $");
}

void PrintTotalBalanceClientsData() {
    vector<stInfoClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    double Total = 0;
    cout << "\n\t\t Client List (" << vClients.size() << ")" << " Client(s).";
    cout << "\n--------------------------------------------------------------" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(25) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n--------------------------------------------------------------" << endl;

    if (vClients.size() == 0) {
        cout << "\t\tNo Clients in System.";
    }
    else {
        for (stInfoClient Client : vClients) {
            Total += Client.Account_Balance;
            PrintBalanceClientRecord(Client);
            cout << endl;
        }
        cout << "\n--------------------------------------------------------------" << endl;
        cout << "\t\tTotal Balance : " << Total << " $" << endl;
    }
}

// ==================================================================================
// شاشات العمليات الفرعية (Operation Screens)
// ==================================================================================

void ShowAddNewClientsScreen() {
    PrintHeader("Add New Client Screen");
    AddNewClients();
}

void ShowDeleteClientScreen() {
    PrintHeader("Delete Client Page");
    vector<stInfoClient> vClient = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadString("Please Enter Account Number You Want Delete : ");
    DeleteClientByAccountNumber(vClient, AccountNumber);
}

void ShowUpdateClientScreen() {
    PrintHeader("Update Client Page");
    vector<stInfoClient> vClient = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadString("Please Enter Account Number You Want Update : ");
    UpdateClientByAccountNumber(vClient, AccountNumber);
}

void ShowFindClientScreen() {
    PrintHeader("Find Client Page");
    vector<stInfoClient> vClient = LoadClientsDataFromFile(ClientsFileName);
    stInfoClient Client;
    string AccountNumber = ReadString("Please Enter Account Number You Need Find : ");
    if (FindClientByAccountNumber(Client, vClient, AccountNumber)) {
        PrintClientInfo(Client);
    }
    else {
        cout << "\nClient Numebr (" << AccountNumber << ") Is Not found In System .";
    }
}


void ShowAddNewUsersScreen() {
    PrintHeader("Add New User Screen");
    AddNewUsers();
}

void ShowDeleteUserScreen() {
    PrintHeader("Delete User Page");
    vector<stInfoUser> vUser = LoadUsersDataFromFile(UsersFileName);

    string Username = ReadString("Please Enter User Name You Want Delete : ");

  
    while (Username == "Admin" || Username == "admin") {
        cout << "\nThis user cannot be deleted because it is the Admin account.\n";
        Username = ReadString("Please enter another User Name to delete: ");
    }
    if (DeleteUserByUserName(vUser, Username)) {

    }
    else {
        cout << "\nUser Name (" << Username << ") Is Not found In System.";
    }
}


void ShowUpdateUserScreen() {
        PrintHeader("Update User Page");
        vector<stInfoUser> vUser = LoadUsersDataFromFile(UsersFileName);

        string UserName = ReadString("Please Enter User Name You Want Update : ");

        while (UserName == "Admin" || UserName == "admin") {
            cout << "\n[Access Denied]: The [Admin] user cannot be updated from this screen for security reasons.\n";
            UserName = ReadString("Please Enter another User Name : ");
        }

        if (UpdateUserByUserName(vUser, UserName)) {
            
        }
        else {
            cout << "\nUser Name (" << UserName << ") Is Not found In System.";
        }
    }


void ShowFindUserScreen() {
    PrintHeader("Find User Page");
    vector<stInfoUser> vUser = LoadUsersDataFromFile(UsersFileName);
    stInfoUser User;
    string UserName = ReadString("Please Enter User Name You Need Find : ");
    if (FindUserByUserName(User, vUser, UserName)) {
        PrintUserInfo(User);
    }
    else {
        cout << "\nUser Name (" << UserName << ") Is Not found In System .";
    }
}


void ShowDepositScreen() {
    system("Cls");
    PrintHeader("Deposite Screen Client Page");
    stInfoClient Client;
    vector<stInfoClient> vClient = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadString("\nPlease Enter Account Number : ");

    while (!FindClientByAccountNumber(Client, vClient, AccountNumber)) {
        cout << "\nClient With [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadString("\nPlease Enter Account Number : ");
    }
    PrintClientInfo(Client);
    double Amount = 0;
    cout << "\nPlease Enter Deposit Amount : ";
    cin >> Amount;

    char Confirmation = 'n';
    cout << "\nAre you sure you want to perform this transaction? y/n: ";
    cin >> Confirmation;

    if (toupper(Confirmation) == 'Y') {
        DepositeClientByAccountNumber(Amount, vClient, AccountNumber);
    }
    else {
        cout << "\nTransaction Cancelled.\n";
    }
}

void ShowWithdrawScreen() {
    system("Cls");
    PrintHeader("Withdraw Screen Client Page");
    stInfoClient Client;
    vector<stInfoClient> vClient = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadString("\nPlease Enter Account Number : ");

    while (!FindClientByAccountNumber(Client, vClient, AccountNumber)) {
        cout << "\nClient With [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadString("\nPlease Enter Account Number : ");
    }
    PrintClientInfo(Client);
    double Amount = 0;
    cout << "\nPlease Enter Withdraw Amount : ";
    cin >> Amount;

    while (Amount > Client.Account_Balance) {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.Account_Balance;
        cout << "\nPlease Enter another Amount : ";
        cin >> Amount;
    }

    char Confirmation = 'n';
    cout << "\nAre you sure you want to perform this transaction? y/n: ";
    cin >> Confirmation;

    if (toupper(Confirmation) == 'Y') {
        DepositeClientByAccountNumber(Amount * -1, vClient, AccountNumber);
    }
    else {
        cout << "\nTransaction Cancelled.\n";
    }
}

void ShowTotalBalanceScreen() {
    system("Cls");
    PrintHeader("Total Balance Screen Client`s Page");
    PrintTotalBalanceClientsData();
}

void ShowEndScreen() {
    system("Cls");
    cout << "\a";
    cout << "\n";
    cout << "==========================================================================" << endl;
    cout << "PROGRAM END\n";
    cout << "==========================================================================" << endl;
    cout << "\n";
    exit(0);
}

// ==================================================================================
// نظام القوائم والتحكم (Menu System)
// ==================================================================================

enum enMainMenuOption {
    eListClient = 1, eAddNewClient = 2, eDeleteClient = 3,
    eUpdateClient = 4, eFindClient = 5, eTransaction = 6, eManageUsers = 7,
    eLogout = 8,
};

enum enTransactionMenuOption {
    eDeposit = 1, ewithdraw = 2, eTotalBalance = 3, eMainMenu = 4,
};

enum enManageUsersMenuOption {
    eListUser = 1 , eAddNewUser = 2, eDeleteUser = 3,
    eUpdateUser = 4,eFindUser = 5, eMainMenu2 = 6,

};

short ReadMainMenuOption() {
    short Select = ReadPositiveNumber("Choose What do You Want to Do ? [ 1 to 8 ] : ");
    while (Select > 8 || Select < 1) {
        Select = ReadPositiveNumber("Please Enter Number Between [ 1 to 8 ] : ");
    }
    return Select;
}

short ReadTransactionMenuOption() {
    short Select = ReadPositiveNumber("Choose What do You Want to Do ? [ 1 to 4 ] : ");
    while (Select > 4 || Select < 1) {
        Select = ReadPositiveNumber("Please Enter Number Between [ 1 to 4 ] : ");
    }
    return Select;
}

short ReadManageUsersMenuOption() {
    short Select = ReadPositiveNumber("Choose What do You Want to Do ? [ 1 to 6 ] : ");
    while (Select > 6 || Select < 1) {
        Select = ReadPositiveNumber("Please Enter Number Between [ 1 to 6 ] : ");
    }
    return Select;
}

void PrintMainMenuList() {
    system("Cls");
    cout << "============================================\n";
    cout << "\t\tMain Menu List\n";
    cout << "============================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transaction.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "============================================\n";
}

void PrintTransactionList() {
    system("Cls");
    cout << "============================================\n";
    cout << "\t\tTransaction List\n";
    cout << "============================================\n";
    cout << "\t[1] Deposit .\n";
    cout << "\t[2] Withdraw .\n";
    cout << "\t[3] Total Balance .\n";
    cout << "\t[4] Return Main Menu .\n";
    cout << "============================================\n";

}

void PrintManageUsersMenuList() {
    system("Cls");
    cout << "============================================\n";
    cout << "\t\tManage Users List\n";
    cout << "============================================\n";
    cout << "\t[1] List Users .\n";
    cout << "\t[2] Add New User .\n";
    cout << "\t[3] Delete User .\n";
    cout << "\t[4] Update User .\n";
    cout << "\t[5] Find User .\n";
    cout << "\t[6] Return Main Menu .\n";
    cout << "============================================\n";

}

void ReturnToMainMenu() {
    cout << "\n\nPress Any Key To Go Back To Main Menu ...";
    system("Pause>0");
    Start();
}

void ReturnToTransactionMenu() {
    cout << "\n\nPress Any Key To Go Back To Transaction Menu ...";
    system("Pause>0");
    Transaction();
}

void ReturnToManageUsersMenu() {
    cout << "\n\nPress Any Key To Go Back To Manage Users Menu ...";
    system("Pause>0");
    ManageUsers();
}

void PerFromManageUsersList(enManageUsersMenuOption ManageUsersMenuOption) {
    switch (ManageUsersMenuOption) {
    case eListUser: system("Cls"); PrintAllUsersData(); ReturnToManageUsersMenu(); break;
    case eAddNewUser: system("Cls"); ShowAddNewUsersScreen(); ReturnToManageUsersMenu(); break;
    case eDeleteUser: system("Cls"); ShowDeleteUserScreen(); ReturnToManageUsersMenu(); break;
    case eUpdateUser: system("Cls"); ShowUpdateUserScreen(); ReturnToManageUsersMenu(); break;
    case eFindUser: system("Cls"); ShowFindUserScreen(); ReturnToManageUsersMenu(); break;
    case eMainMenu2: Start(); break;
    }
}

void ManageUsers() {
    PrintManageUsersMenuList();
    PerFromManageUsersList((enManageUsersMenuOption)ReadManageUsersMenuOption());
}

void PerFromTransactionList(enTransactionMenuOption TransactionMenuOption) {
    switch (TransactionMenuOption) {
    case eDeposit: ShowDepositScreen(); ReturnToTransactionMenu(); break;
    case ewithdraw: ShowWithdrawScreen(); ReturnToTransactionMenu(); break;
    case eTotalBalance: ShowTotalBalanceScreen(); ReturnToTransactionMenu(); break;
    case eMainMenu: Start(); break;
    }
}

void Transaction() {
    PrintTransactionList();
    PerFromTransactionList((enTransactionMenuOption)ReadTransactionMenuOption());
}

void PerFromMainMenuOption(enMainMenuOption MainMenuOption) {
    switch (MainMenuOption) {
    case eListClient: system("Cls"); PrintAllClientsData(); ReturnToMainMenu(); break;
    case eAddNewClient: system("Cls"); ShowAddNewClientsScreen(); ReturnToMainMenu(); break;
    case eDeleteClient: system("Cls"); ShowDeleteClientScreen(); ReturnToMainMenu(); break;
    case eUpdateClient: system("Cls"); ShowUpdateClientScreen(); ReturnToMainMenu(); break;
    case eFindClient: system("Cls"); ShowFindClientScreen(); ReturnToMainMenu(); break;
    case eTransaction: system("Cls"); Transaction(); break;
    case eManageUsers: system("Cls"); ManageUsers(); break;
    case eLogout: Login(); break;
    }
}

void Start() {
    PrintMainMenuList();
    PerFromMainMenuOption((enMainMenuOption)ReadMainMenuOption());
}

bool Login() {
    string UserName, Password;
    bool LoginFailed = false;

    do {
        system("Cls");
        PrintHeader("Login Screen");

        if (LoginFailed) {
            cout << "\aInvalid Username/Password!\n";
        }

        cout << "Enter Username: ";
        getline(cin >> ws, UserName);
        cout << "Enter Password: ";
        getline(cin, Password);

        stInfoUser CurrentUser; 
        if (FindUserByUsernameAndPassword(UserName, Password, CurrentUser)) {
          
            Start();
            return true;
        }
        else {
            LoginFailed = true;
        }

    } while (LoginFailed); 

    return false;
}

// ==================================================================================
// نقطة انطلاق البرنامج (Main)
// ==================================================================================

int main() {
    Login();
    return 0;
}