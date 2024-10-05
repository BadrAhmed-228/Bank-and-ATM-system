#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cctype>
#include <fstream>

using namespace std;

string ClientsFileName = "Clients data file Extension2.text";
string UsersFileName = "Users data file";

void Login();

enum enTransactions
{
	eDeposite = 1,
	eWithdraw = 2,
	eTotalBalances = 3,
	eMainMenue = 4
}; //new

enum enUsersMenue
{
	eUsersList = 1,
	eAddUsers = 2,
	eDeleteUser = 3,
	eUpdateUser = 4,
	eFindUser = 5,
	eMainMenueFromUsers = 6
};

enum enMainMenue
{
	eShowCLientsList = 1,
	eAddNewClient = 2,
	eDeleteClient = 3,
	eUpdateClientInfo = 4,
	eFindClint = 5,
	eTransactoins = 6, //new
	eUsers = 7,
	eExit = 8
};

enum enPermessions
{
	// main menue permissions

	pAll = -1,
	pShowClientList = 1,
	pAddNewClient = 2,
	pDeleteClient = 4,
	pUpdateClientInfo = 8,
	pFindClient = 16,
	pTransactions = 32,
	pUsers = 64
};

struct stClientData
{
	string AccountNumber = "";
	string pinCode = "";
	string clientName = "";
	string phoneNumber = "";
	double balance = 0;
	bool markForDelete = false;
};

struct stUserData
{
	string userName = "";
	string password = "";
	short permissions = 0;
	bool markForDelete = false;
};

stUserData currentUser;

void showMainMenue()
{
	system("cls");

	cout << "--------------------------------------------------------------\n";
	cout << "\t\t\tMain Menue\n";
	cout << "--------------------------------------------------------------\n\n";
	cout << "====================================\n";
	cout << "\t[1] Show Client List\n";
	cout << "\t[2] Add New Client\n";
	cout << "\t[3] Delete Client\n";
	cout << "\t[4] Update Client info\n";
	cout << "\t[5] Find Client\n";
	cout << "\t[6] Transactions\n";
	cout << "\t[7] Users\n";
	cout << "\t[8] Log Out\n";
	cout << "====================================\n\n";
}

enMainMenue readChoiceFromMainMenue()
{
	short Choice = 0;

	do
	{
		cout << "Enter your choice [1 to 7] ? ";
		cin >> Choice;

	} while (Choice > 8 || Choice < 1);

	return enMainMenue(Choice);
}

void goToMainMenue()
{
	cout << "\n\nPress any key to go to main Menue...";
	system("pause > 0");

	showMainMenue();
}

void showTransactionsMenue()
{
	system("cls");

	cout << "-------------------------------------------\n";
	cout << "\tTransaction Menue";
	cout << "\n-------------------------------------------\n\n";

	cout << "====================================\n";
	cout << "\t[1] Deposite.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menue\n";
	cout << "====================================\n" << endl;
} //new

enTransactions readTransaction()
{
	short choice = 0;

	do
	{
		cout << "Enter your choice [1 to 4] : ";
		cin >> choice;

	} while (choice > 4 || choice < 1);

	return enTransactions(choice);

} //new

void goToTransactionMenue()
{
	cout << "\n\nPress any key to go to Transaction Menue...";
	system("pause > 0");

	showTransactionsMenue();
} //new

void showUsersMenue()
{
	system("cls");

	cout << "-----------------------------------------------\n";
	cout << "\t\tUsers Menue";
	cout << "\n-----------------------------------------------\n\n";
	cout << "======================================\n";
	cout << "\t[1] Users List.\n";
	cout << "\t[2] Add Users.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menue.\n";
	cout << "======================================\n";
}

enUsersMenue readChoiceFromUsersMenue()
{
	short choice = 0;

	do
	{
		cout << "\nEnter you choice [1 to 6] : ";
		cin >> choice;

	} while (choice > 6 || choice < 1);

	return enUsersMenue(choice);
}

void goToUsersMenue()
{
	cout << "\n\npress any key to go to Users Menue...";
	system("pause > 0");

	showUsersMenue();
}

short readForPermissions()
{
	short totalPermissions = 0;
	char YN = 'y';

	cout << "\nDo you want to full access Y/N ? ";
	cin >> YN;
	if (tolower(YN) == 'y')
	{
		return -1;
	}
	cout << "\nDo you want to give access to : \n";
	
	cout << "\nShow client list Y/N ? ";
	cin >> YN;
	if (tolower(YN) == 'y')
	{
		totalPermissions += enPermessions::pShowClientList;
	}

	cout << "\nAdd new client Y/N ? ";
	cin >> YN;
	if (tolower(YN) == 'y')
	{
		totalPermissions += enPermessions::pAddNewClient;
	}

	cout << "\nDelete client Y/N ? ";
	cin >> YN;
	if (tolower(YN) == 'y')
	{
		totalPermissions += enPermessions::pDeleteClient;
	}

	cout << "\nFind client Y/N ? ";
	cin >> YN;
	if (tolower(YN) == 'y')
	{
		totalPermissions += enPermessions::pFindClient;
	}

	cout << "\nUpdate client Y/N ? ";
	cin >> YN;
	if (tolower(YN) == 'y')
	{
		totalPermissions += enPermessions::pUpdateClientInfo;
	}

	cout << "\nTransactions Y/N ? ";
	cin >> YN;
	if (tolower(YN) == 'y')
	{
		totalPermissions += enPermessions::pTransactions;
	}

	cout << "\nUsers Y/N ? ";
	cin >> YN;
	if (tolower(YN) == 'y')
	{
		totalPermissions += enPermessions::pUsers;
	}

	return totalPermissions;
}

string convertStUserToString(stUserData userData)
{
	string sUserData = "";

	sUserData += userData.userName + "#//#";
	sUserData += userData.password + "#//#";
	sUserData += to_string(userData.permissions);

	return sUserData;
}

string convertStClientToString(stClientData ClientData, string delimeter)
{
	string DataInOneLine = "";

	DataInOneLine += ClientData.AccountNumber + delimeter;
	DataInOneLine += ClientData.pinCode + delimeter;
	DataInOneLine += ClientData.clientName + delimeter;
	DataInOneLine += ClientData.phoneNumber + delimeter;
	DataInOneLine += to_string(ClientData.balance);

	return DataInOneLine;
}

vector<string> splitString(string s, string delimeter)
{
	vector<string> vSplit;

	short position = 0;

	string word = "";

	while ((position = s.find(delimeter)) != std::string::npos)
	{
		word = s.substr(0, position);

		if (word != "") {

			vSplit.push_back(word);
		}

		s.erase(0, position + delimeter.length());

		position = s.find(delimeter);
	}

	if (s != "")
	{
		vSplit.push_back(s);
	}

	return vSplit;
}

stUserData convertStringToStUserData(string sUserData)
{
	stUserData userData;

	vector<string> vUsers = splitString(sUserData, "#//#");

	userData.userName = vUsers[0];
	userData.password = vUsers[1];
	userData.permissions = stoi(vUsers[2]);

	return userData;
}

stClientData convertStringToStClientData(string DataInOneLine, string delimeter)
{
	vector<string> vClientData = splitString(DataInOneLine, "#//#");

	stClientData ClientData;

	ClientData.AccountNumber = vClientData[0];
	ClientData.pinCode = vClientData[1];
	ClientData.clientName = vClientData[2];
	ClientData.phoneNumber = vClientData[3];
	ClientData.balance = stod(vClientData[4]);

	return ClientData;
}

vector<stUserData> loadUsersDataFromFile(string fileName)
{
	fstream file;

	vector<stUserData> vUsersData;

	file.open(fileName, ios::in); //read mode

	if (file.is_open())
	{
		string line;
		stUserData userData;

		while (getline(file, line))
		{
			userData = convertStringToStUserData(line);

			vUsersData.push_back(userData);
		}

		file.close();
	}

	return vUsersData;
}

vector<stClientData> loadClientsDataFromFile(string fileName)
{
	fstream File;

	vector<stClientData> vClientsData;

	File.open(fileName, ios::in); //read mode

	if (File.is_open())
	{
		stClientData ClientData;
		string line = "";

		while (getline(File, line))
		{
			ClientData = convertStringToStClientData(line, "#//#");

			vClientsData.push_back(ClientData);
		}

		File.close();
	}

	return vClientsData;
}

void printStUserData(stUserData userData)
{
	cout << "| " << left << setw(17) << userData.userName;
	cout << "| " << left << setw(17) << userData.password;
	cout << "| " << left << setw(17) << userData.permissions;
}

void printStClientData(stClientData ClientData)
{
	cout << "| " << left << setw(15) << ClientData.AccountNumber;
	cout << "| " << left << setw(15) << ClientData.pinCode;
	cout << "| " << left << setw(30) << ClientData.clientName;
	cout << "| " << left << setw(20) << ClientData.phoneNumber;
	cout << "| " << left << setw(15) << ClientData.balance;
}

void printUserCard(stUserData userData)
{
	cout << "------------------------------------";
	cout << "\nUser Name : " << userData.userName;
	cout << "\nPassword : " << userData.password;
	cout << "\nPermissions : " << userData.permissions;
	cout << "\n------------------------------------\n";
}

void printClientCard(stClientData ClientData)
{
	cout << "--------------------------------------------------\n";
	cout << "Account Number : " << ClientData.AccountNumber << endl;
	cout << "PinCode        : " << ClientData.pinCode << endl;
	cout << "Client Name    : " << ClientData.clientName << endl;
	cout << "Phone Number   : " << ClientData.phoneNumber << endl;
	cout << "Balance        : " << ClientData.balance << endl;
	cout << "--------------------------------------------------\n";
}

void showUserList()
{
	vector<stUserData> vUsersData = loadUsersDataFromFile(UsersFileName);

	cout << "\n\t\t\t\tUser List (" << vUsersData.size() << ") User(s)\n" << endl;
	cout << "-----------------------------------------------------------------\n";
	cout << "| " << left << setw(17) << "User Name";
	cout << "| " << left << setw(17) << "Password";
	cout << "| " << left << setw(17) << "Permessions";
	cout << "\n-----------------------------------------------------------------\n";

	for (stUserData userData : vUsersData)
	{
		printStUserData(userData);
		cout << endl;
	}

	goToUsersMenue();
}

bool checkPermissions(enPermessions function)
{
	if (currentUser.permissions == enPermessions::pAll)
		return true;
	else
		return ((currentUser.permissions & function) == function);
}

void AccessDeniedMessage()
{
	cout << "------------------------------------\n";
	cout << "Access Denied,\nYou dont't have permission to do this,\nPlease contact your admin.";
	cout << "\n------------------------------------\n";
}

void showClientList()
{
	if (!checkPermissions(enPermessions::pShowClientList))
	{
		AccessDeniedMessage();
		goToMainMenue();
		return;
	}

	vector<stClientData> vClientsData = loadClientsDataFromFile(ClientsFileName);

	cout << "\n\t\t\t\tClinet List (" << vClientsData.size() << ")" << "Client(s)\n" << endl;
	cout << "---------------------------------------------------------------------------------------------------\n";
	cout << "| " << setw(15) << left << "Account Number";
	cout << "| " << setw(15) << left << "PinCode";
	cout << "| " << setw(30) << left << "Client Name";
	cout << "| " << setw(20) << left << "Phone Number";
	cout << "| " << setw(15) << left << "Balance";
	cout << "\n---------------------------------------------------------------------------------------------------\n";

	for (stClientData& ClientData : vClientsData)
	{
		printStClientData(ClientData);
		cout << endl;
	}

	goToMainMenue();
}

bool isUserExist(string userName)
{
	vector<stUserData> vUsersData = loadUsersDataFromFile(UsersFileName);

	for (stUserData userData : vUsersData)
	{
		if (userData.userName == userName)
		{
			return true;
		}
	}

	return false;
}

bool searchForUserByUserName(string userName, vector<stUserData>& vUsersData, stUserData& userData, string fileName)
{
	vUsersData = loadUsersDataFromFile(fileName);

	for (stUserData U : vUsersData)
	{
		if (userName == U.userName) 
		{
			userData = U;
			
			return true;
		}
	}

	return false;
}

bool searchForAccountNumber(string AccountNumber, vector<stClientData>& vClientsData, stClientData& ClientData, string fileName)
{
	vClientsData = loadClientsDataFromFile(fileName);

	for (stClientData& C : vClientsData)
	{
		if (AccountNumber == C.AccountNumber) {

			ClientData = C;

			return true;
		}
	}

	return false;
}

stClientData readClientData()
{
	stClientData ClientData;

	vector<stClientData> vClientsData;

	cout << "Enter account number : ";
	getline(cin >> ws, ClientData.AccountNumber);

	do
	{
		if (!searchForAccountNumber(ClientData.AccountNumber, vClientsData, ClientData, ClientsFileName))
		{
			cout << "Enter PinCode : ";
			getline(cin, ClientData.pinCode);

			cout << "Enter client name : ";
			getline(cin, ClientData.clientName);

			cout << "Enter phone number : ";
			getline(cin, ClientData.phoneNumber);

			cout << "Enter balance : ";
			cin >> ClientData.balance;

			return ClientData;
		}
		else
		{
			cout << "\nAccount Number [" << ClientData.AccountNumber << "] is already exists\n\n";
			cout << "Enter another Account Number : ";
			getline(cin, ClientData.AccountNumber);
		}

	} while (true);
}

stUserData readUserData()
{
	stUserData userData;

	do
	{
		cout << "\nEnter User Name : ";
		getline(cin >> ws, userData.userName);

		if(isUserExist(userData.userName))
			cout << "\nUser with [" << userData.userName << "] is already exist, Enter another user name.\n";
	
	} while (isUserExist(userData.userName));

	cout << "Enter Password : ";
	getline(cin, userData.password);

	userData.permissions = readForPermissions();

	return userData;
}

void AddUserData(string fileName)
{
	fstream file;

	file.open(fileName, ios::out | ios::app); //write mode

	if (file.is_open())
	{
		stUserData userData;
		string line;

		userData = readUserData();

		line = convertStUserToString(userData);

		file << line << endl;
	}

	file.close();
}

void AddUsersData()
{
	cout << "-------------------------------------\n";
	cout << "\tAdd Users Screen";
	cout << "\n-------------------------------------\n\n";

	char YN = 'y';

	do
	{
		cout << "\nAdding New User : \n\n";

		AddUserData(UsersFileName);

		cout << "\nDo you want to add more users Y/N ? ";
		cin >> YN;

	} while (tolower(YN) == 'y');

	goToUsersMenue();
}

void AddClientData(string fileName)
{
	fstream File;

	stClientData ClientData;

	string dataInOneLine;

	cout << "Adding new Client...\n\n";
	ClientData = readClientData();
	dataInOneLine = convertStClientToString(ClientData, "#//#");

	File.open(fileName, ios::out | ios::app);

	if (File.is_open())
	{
		File << dataInOneLine << endl;
	}

	cout << "\nClient added successfully...";
}

void AddClientsData(string fileName)
{
	if (!checkPermissions(enPermessions::pAddNewClient))
	{
		AccessDeniedMessage();
		goToMainMenue();
		return;
	}

	string header = "--------------------------------------------\n\tAdd New Client Screen\n"
		"--------------------------------------------\n\n";

	char YN = 'y';

	cout << header;

	do
	{
		AddClientData(fileName);

		cout << "\n\nDo you want to add more client Y/N ? ";
		cin >> YN;

		if (tolower(YN) == 'y') {

			system("cls");
			cout << header;
		}

	} while (tolower(YN) == 'y');

	goToMainMenue();
}

void markForDeleteUserData(string userName, vector<stUserData>& vUsersData, string fileName)
{
	vUsersData = loadUsersDataFromFile(fileName);

	for (stUserData& userData : vUsersData)
	{
		if (userData.userName == userName)
		{
			userData.markForDelete = true;
			break;
		}
	}
}

void markForDeleteClientData(string AccountNumber, vector<stClientData>& vClientsData, string fileName)
{
	vClientsData = loadClientsDataFromFile(fileName);

	for (stClientData& C : vClientsData)
	{
		if (AccountNumber == C.AccountNumber) {

			C.markForDelete = true;

			break; // updated after abu-hadhoude solution
		}
	}
}

void saveVectorStUserDataToFile(string fileName, vector<stUserData>& vUsersData)
{
	fstream file;

	file.open(fileName, ios::out);

	if (file.is_open())
	{
		string line = "";

		for (stUserData userData : vUsersData)
		{
			if (userData.markForDelete == false)
			{
				line = convertStUserToString(userData);

				file << line << endl;
			}
		}

		file.close();
	}

	// refresh data in vector

	loadUsersDataFromFile(fileName);
}

void saveVectorStClientDatatoFile(string fileName, vector<stClientData>& vClientsData)
{
	fstream File;

	string DataInOneLine = "";

	File.open(fileName, ios::out); //write mode

	if (File.is_open())
	{
		for (stClientData C : vClientsData)
		{
			if (C.markForDelete == false) {

				DataInOneLine = convertStClientToString(C, "#//#");

				File << DataInOneLine << endl;
			}
		}

		File.close();
	}

	//refresh vector
	vClientsData = loadClientsDataFromFile(fileName);
}

void DeleteUser()
{
	vector<stUserData> vUsersData;

	string userName = "";

	stUserData userData;

	cout << "---------------------------------------------\n";
	cout << "\tDelete User Screen";
	cout << "\n---------------------------------------------\n\n";

	cout << "Enter User Name : ";
	getline(cin >> ws, userName);

	if (searchForUserByUserName(userName, vUsersData, userData, UsersFileName))
	{
		char YN = 'y';

		cout << "\nUser Data : \n\n";
		printUserCard(userData);
		
		cout << "\nAre you sure you want to delete this user Y/N ? ";
		cin >> YN;

		if (tolower(YN) == 'y')
		{
			markForDeleteUserData(userName, vUsersData, UsersFileName);
			
			saveVectorStUserDataToFile(UsersFileName, vUsersData);

			cout << "\n\nUser Deleted successfully...";

			goToUsersMenue();
		}
	}
	else
	{
		cout << "User with User Name [" << userName << "] is not found";

		goToUsersMenue();
	}
}

void DeleteClient()
{
	if (!checkPermissions(enPermessions::pDeleteClient))
	{
		AccessDeniedMessage();
		goToMainMenue();
		return;
	}

	vector<stClientData> vClientsData = loadClientsDataFromFile(ClientsFileName);

	string AccountNumber;

	stClientData ClientData;

	cout << "-----------------------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n-----------------------------------------------\n\n";

	cout << "Enter Account Number : ";
	getline(cin >> ws, AccountNumber);

	if (searchForAccountNumber(AccountNumber, vClientsData, ClientData, ClientsFileName))
	{
		cout << "\nClient Data : \n\n";

		printClientCard(ClientData);

		char YN = 'y';

		cout << "\nAre you sure you want to delete Y/N ? ";
		cin >> YN;

		if (tolower(YN) == 'y') {

			markForDeleteClientData(AccountNumber, vClientsData, ClientsFileName);

			saveVectorStClientDatatoFile(ClientsFileName, vClientsData);

			cout << "\n\nClient deleted successfully...";
		}

		goToMainMenue();
	}
	else
	{
		cout << "\nAccount Number [" << AccountNumber << "] is not found";

		goToMainMenue();
	}
}

void readUpdatedUser(string userName, vector<stUserData>& vUsersData)
{
	vUsersData = loadUsersDataFromFile(UsersFileName);

	for (stUserData& U : vUsersData)
	{
		if (userName == U.userName)
		{
			U = readUserData();

			break;
		}
	}
}

void updateUser()
{
	system("cls");

	cout << "---------------------------------------------\n";
	cout << "\tUpdate User Screen";
	cout << "\n---------------------------------------------\n\n";

	string userName;

	cout << "Enter User Name : ";
	getline(cin >> ws, userName);

	vector<stUserData> vUsersData;

	stUserData userData;

	if (searchForUserByUserName(userName, vUsersData, userData, UsersFileName))
	{
		char YN = 'y';

		cout << "\n\nUser Data : \n\n";
		printUserCard(userData);

		cout << "\nAre you sure you want to update this user YN ? ";
		cin >> YN;

		if (tolower(YN) == 'y')
		{
			readUpdatedUser(userName, vUsersData);

			saveVectorStUserDataToFile(UsersFileName, vUsersData);

			cout << "\n\nUser Updated successfully...";

			goToUsersMenue();
		}
	}
	else
	{
		cout << "\n\nuser with user name [" << userName << "] is not exist.\n";

		goToUsersMenue();
	}
}

void readUpdateClientData(string AccountNumber, vector<stClientData>& vClientsData)
{
	vClientsData = loadClientsDataFromFile(ClientsFileName);

	for (stClientData& C : vClientsData)
	{
		if (AccountNumber == C.AccountNumber)
		{
			cout << "\nEnter PinCode : ";
			getline(cin >> ws, C.pinCode);

			cout << "Enter client name : ";
			getline(cin, C.clientName);

			cout << "Enter phone number : ";
			getline(cin, C.phoneNumber);

			cout << "Enter balance : ";
			cin >> C.balance;

			break; // updated after abu-hadhoude solution
		}
	}
}

void updateClientData()
{
	if (!checkPermissions(enPermessions::pUpdateClientInfo))
	{
		AccessDeniedMessage();
		goToMainMenue();
		return;
	}

	vector<stClientData> vClientsData = loadClientsDataFromFile(ClientsFileName);

	string AccountNumber;

	stClientData ClientData;

	cout << "-----------------------------------------------\n";
	cout << "\tUpdate Client Screen";
	cout << "\n-----------------------------------------------\n\n";

	cout << "Enter Account Number : ";
	getline(cin >> ws, AccountNumber);

	if (searchForAccountNumber(AccountNumber, vClientsData, ClientData, ClientsFileName))
	{
		char YN = 'y';

		cout << "\nClient Data : \n\n";

		printClientCard(ClientData);

		cout << "\nAre you sure you want to update Client Data Y/N ? ";
		cin >> YN;

		if (tolower(YN) == 'y')
		{
			readUpdateClientData(AccountNumber, vClientsData);

			saveVectorStClientDatatoFile(ClientsFileName, vClientsData);

			cout << "\nClient updated successfully...";
		}

		goToMainMenue();
	}
	else
	{
		cout << "\nAccount Number [" << AccountNumber << "] is not found";

		goToMainMenue();
	}
}

void findUser(string fileName)
{
	cout << "----------------------------------------------\n";
	cout << "\tFind User Screen";
	cout << "\n----------------------------------------------\n\n";

	vector<stUserData> vUsersData;

	stUserData userData;

	string userName = "";

	cout << "Enter User Name : ";
	cin >> userName;

	if (searchForUserByUserName(userName, vUsersData, userData, UsersFileName))
	{
		cout << "\nUser Data : \n\n";
		printUserCard(userData);

		goToUsersMenue();
	}
	else
	{
		cout << "\nUser with user name [" << userName << "] is not found";

		goToUsersMenue();
	}
}

void findClientUsingAccountNumber(string fileName)
{
	if (!checkPermissions(enPermessions::pFindClient))
	{
		AccessDeniedMessage();
		goToMainMenue();
		return;
	}

	cout << "-----------------------------------------------\n";
	cout << "\tFind Client Screen";
	cout << "\n-----------------------------------------------\n\n";

	vector<stClientData> vClientsData;

	string AccountNumber;

	stClientData ClientData;

	cout << "Enter Account Number : ";
	getline(cin >> ws, AccountNumber);

	if (searchForAccountNumber(AccountNumber, vClientsData, ClientData, fileName))
	{
		cout << "\nClient details : \n\n";
		printClientCard(ClientData);

		goToMainMenue();
	}
	else
	{
		cout << "\nAccount Number [" << AccountNumber << "] is not found\n";

		goToMainMenue();
	}
}

double readAmmount(string message)
{
	double Ammount = 0;

	cout << message;
	cin >> Ammount;

	return Ammount;
}

void updateAmmountInVector(vector<stClientData>& vClientsData, string AccountNumber, double Ammount)
{
	for (stClientData& C : vClientsData)
	{
		if (AccountNumber == C.AccountNumber)
		{
			C.balance += Ammount;

			break;
		}
	}
}

double Deposite(vector<stClientData>& vClientsData, string& AccountNumber, stClientData& ClientData, string message)
{
	vClientsData = loadClientsDataFromFile(ClientsFileName);

	do
	{
		cout << "\nEnter Account Number : ";
		cin >> AccountNumber;

		if (searchForAccountNumber(AccountNumber, vClientsData, ClientData, ClientsFileName))
		{
			char YN = 'y';

			cout << "\nClient Details : \n\n";
			printClientCard(ClientData);

			double Ammount = readAmmount(message);

			cout << "\nAre you sure you want to make this transaction Y/N ? ";
			cin >> YN;

			if (tolower(YN) == 'y')
			{
				return Ammount;
			}
			else
			{
				Ammount = 0;

				return Ammount;
			}
		}
		else
		{
			cout << "\nAccount Number [" << AccountNumber << "] is not exist\n";
		}

	} while (true);
}

bool validateWithdrawalAmmount(double& Ammount, stClientData ClientData)
{
	if (Ammount > ClientData.balance)
	{
		char YN = 'y';

		while (Ammount > ClientData.balance)
		{
			cout << "\n\nAmmount Exceeds the balance, you can withdraw up to : " << ClientData.balance;
			cout << "\nEnter Withdrawal Ammount : ";
			cin >> Ammount;
		}

		cout << "\n\nAre you sure you want perform this transaction Y/N ? ";
		cin >> YN;

		if (tolower(YN) == 'y')
		{
			return true;
		}

		return false;
	}

	return true;
}

double withdraw(vector<stClientData>& vClientsData, string& AccountNumber, stClientData& ClientData, string message)
{
	double withdrawalAmmount = Deposite(vClientsData, AccountNumber, ClientData, message);

	if (validateWithdrawalAmmount(withdrawalAmmount, ClientData))
	{
		return withdrawalAmmount * -1;
	}
	else
	{
		withdrawalAmmount = 0;

		return withdrawalAmmount;
	}
}

void printTotalBalances(vector<stClientData>& vClientsData)
{
	vClientsData = loadClientsDataFromFile(ClientsFileName);

	double TotalBalances = 0;

	cout << "\t\tBalance List (" << vClientsData.size() << ") Client(s)\n" << endl;

	cout << "-------------------------------------------------------------\n";
	cout << "| " << setw(15) << left << "Account Number";
	cout << "| " << setw(30) << left << "Client Name";
	cout << "| " << setw(15) << left << "Balance";
	cout << "\n-------------------------------------------------------------\n";

	for (stClientData C : vClientsData)
	{
		cout << "| " << setw(15) << left << C.AccountNumber;
		cout << "| " << setw(30) << left << C.clientName;
		cout << "| " << setw(15) << left << C.balance;
		cout << endl;

		TotalBalances += C.balance;
	}

	cout << "\n-------------------------------------------------------------\n\n";

	cout << "\n\tTotal Balance = " << TotalBalances;
}

void choseTransaction(enTransactions choice)
{
	vector<stClientData> vClientsData;

	string AccountNumber;

	stClientData ClientData;

	double Ammount = 0;

	switch (choice)
	{
	case enTransactions::eDeposite:
	{
		cout << "------------------------------\n";
		cout << "\tDeposite Screen";
		cout << "\n------------------------------\n";
		Ammount = Deposite(vClientsData, AccountNumber, ClientData, "Enter Deposite Ammount : ");

		updateAmmountInVector(vClientsData, AccountNumber, Ammount);

		saveVectorStClientDatatoFile(ClientsFileName, vClientsData);

		goToTransactionMenue();

		break;
	}
	case enTransactions::eWithdraw:
	{
		cout << "------------------------------\n";
		cout << "\tWithdraw Screen";
		cout << "\n------------------------------\n";
		Ammount = withdraw(vClientsData, AccountNumber, ClientData, "Enter Withdrawal Ammount : ");

		updateAmmountInVector(vClientsData, AccountNumber, Ammount);

		saveVectorStClientDatatoFile(ClientsFileName, vClientsData);

		goToTransactionMenue();

		break;
	}
	case enTransactions::eTotalBalances:
	{
		printTotalBalances(vClientsData);

		goToTransactionMenue();

		break;
	}
	case enTransactions::eMainMenue:
	{
		showMainMenue();

		break;
	}

	}
}

void choseUserFunction(enUsersMenue choice)
{
	switch (choice)
	{
	case enUsersMenue::eUsersList:
	{
		showUserList();
		break;
	}
	case enUsersMenue::eAddUsers:
	{
		AddUsersData();
		break;
	}
	case enUsersMenue::eDeleteUser:
	{
		DeleteUser();
		break;
	}
	case enUsersMenue::eUpdateUser:
	{
		updateUser();
		break;
	}
	case enUsersMenue::eFindUser:
	{
		findUser(UsersFileName);
		break;
	}
	case enUsersMenue::eMainMenueFromUsers:
	{
		showMainMenue();
		break;
	}

	}
}

void startUsers()
{
	if (!checkPermissions(enPermessions::pUsers))
	{
		AccessDeniedMessage();
		goToMainMenue();
		return;
	}

	enUsersMenue choice;

	showUsersMenue();

	do
	{
		choice = readChoiceFromUsersMenue();

		system("cls");

		choseUserFunction(choice);

	} while (choice != enUsersMenue::eMainMenueFromUsers);

}

void startTransactions()
{
	if (!checkPermissions(enPermessions::pTransactions))
	{
		AccessDeniedMessage();
		goToMainMenue();
		return;
	}

	showTransactionsMenue();

	enTransactions Choice;

	do
	{
		Choice = readTransaction();

		system("cls");

		choseTransaction(Choice);

	} while (Choice != enTransactions::eMainMenue);
}

void choseFunction(enMainMenue choice)
{
	switch (choice)
	{
	case enMainMenue::eShowCLientsList:
	{
		showClientList();
		break;
	}
	case enMainMenue::eAddNewClient:
	{
		AddClientsData(ClientsFileName);
		break;
	}
	case enMainMenue::eDeleteClient:
	{
		DeleteClient();
		break;
	}
	case enMainMenue::eUpdateClientInfo:
	{
		updateClientData();
		break;
	}
	case enMainMenue::eFindClint:
	{
		findClientUsingAccountNumber(ClientsFileName);
		break;
	}
	case enMainMenue::eTransactoins:
	{
		startTransactions();
		break;
	}
	case enMainMenue::eUsers:
	{
		startUsers();
		break;
	}
	case enMainMenue::eExit: {
		Login();
		break;
	}

	}
}

bool searchForUserByUserNameAndPassword(string userName, string password, stUserData& userData)
{
	vector<stUserData> vUsersData = loadUsersDataFromFile(UsersFileName);

	for (stUserData U : vUsersData)
	{
		if (userName == U.userName && password == U.password)
		{
			userData = U;
			
			return true;
		}
	}

	return false;
}

void start()
{
	showMainMenue();

	enMainMenue choice;

	do
	{
		choice = readChoiceFromMainMenue();

		system("cls");

		choseFunction(choice);

	} while (true);
}

void Login()
{
	bool loginFail = false;

	do
	{
		string userName, password;

		system("cls");

		cout << "--------------------------------------\n";
		cout << "\tLogin Screen";
		cout << "\n--------------------------------------\n\n";

		if (loginFail)
		{
			cout << "\nInvalide User Name or Passwerd\n\n";
		}

		cout << "Enter User Name : ";
		cin >> userName;
		cout << "Enter Password : ";
		cin >> password;

		if (searchForUserByUserNameAndPassword(userName, password, currentUser))
		{
			loginFail = false;

			start();
		}
		else
		{
			loginFail = true;
		}

	} while (loginFail);
}

int main()
{
	
	Login();

	return 0;
}
