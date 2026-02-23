#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// ==================================================================================
// التعريفات الأساسية والهياكل (Structures)
// ==================================================================================

const string ClientsFileName = "Clients.txt";

struct stInfoClient {
    string Account_Number;
    string PIN_Code;
    string Client_Name;
    string Client_Phone_Number;
    double Account_Balance = 0;
    bool MarkForDelete = false;
};

// الإعلانات المسبقة للدوال الرئيسية
void Start();
void Transaction();

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
 * تعيد كتابة بيانات المتجه في الملف (تستخدم للتحديث أو الحذف).
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
 * تتحقق مما إذا كان رقم الحساب موجوداً مسبقاً في النظام.
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

void PrintClientRecord(stInfoClient ClientInfo) {
    cout << "| " << left << setw(15) << ClientInfo.Account_Number;
    cout << "| " << left << setw(15) << ClientInfo.PIN_Code;
    cout << "| " << left << setw(25) << ClientInfo.Client_Name;
    cout << "| " << left << setw(25) << ClientInfo.Client_Phone_Number;
    cout << "| " << left << setw(12) << (to_string(ClientInfo.Account_Balance) + " $");
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

// ==================================================================================
// دوال العمليات الرئيسية (Core Operations)
// ==================================================================================

void AddNewClient() {
    stInfoClient Client;
    Client = ReadInfoClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
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
    eLstClient = 1, eAddNewClient = 2, eDeleteClient = 3,
    eUpdateClient = 4, eFindClient = 5, eTransaction = 6, eExit = 7
};

enum enTransactionMenuOption {
    eDeposit = 1, ewithdraw = 2, eTotalBalance = 3, eMainMenu = 4
};

short ReadMainMenuOption() {
    short Select = ReadPositiveNumber("Choose What do You Want to Do ? [ 1 to 7 ] : ");
    while (Select > 7 || Select < 1) {
        Select = ReadPositiveNumber("Please Enter Number Between [ 1 to 7 ] : ");
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
    cout << "\t[7] Exit.\n";
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

void ReturnToMainMenu() {
    cout << "\n\nPress Any Key To Go Back To Main Menu...";
    system("Pause>0");
    Start();
}

void ReturnToTransactionMenu() {
    cout << "\n\nPress Any Key To Go Back To Transaction Menu...";
    system("Pause>0");
    Transaction();
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
    case eLstClient: system("Cls"); PrintAllClientsData(); ReturnToMainMenu(); break;
    case eAddNewClient: system("Cls"); ShowAddNewClientsScreen(); ReturnToMainMenu(); break;
    case eDeleteClient: system("Cls"); ShowDeleteClientScreen(); ReturnToMainMenu(); break;
    case eUpdateClient: system("Cls"); ShowUpdateClientScreen(); ReturnToMainMenu(); break;
    case eFindClient: system("Cls"); ShowFindClientScreen(); ReturnToMainMenu(); break;
    case eTransaction: system("Cls"); Transaction(); break;
    case eExit: ShowEndScreen(); break;
    }
}

void Start() {
    PrintMainMenuList();
    PerFromMainMenuOption((enMainMenuOption)ReadMainMenuOption());
}

// ==================================================================================
// نقطة انطلاق البرنامج (Main)
// ==================================================================================

int main() {
    Start();
    return 0;
}