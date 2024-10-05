#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void logIn();

string ClientsFileName = "D:/vs projects/project5(Bank extension2)/project5(Bank extension2)/Clients data file Extension2.text";

struct stClient
{
	string AccountNumber = "";
	string PinCode = "";
	string ClientName = "";
	string PhoneNumber = "";
	double Balance = 0;
};

stClient currentClient;

enum enAtmMainMenue {QuickWithDraw = 1, NormalWithDraw = 2, Deposite = 3, CheckBalance = 4, LogOut = 5};

void printMainMenue()
{
	system("cls");

	cout << "===================================================================\n";
	cout << "\t\t\tATM Main Menue";
	cout << "\n===================================================================\n";
	cout << "\t[1] Quick WithDraw\n";
	cout << "\t[2] Normal WithDraw\n";
	cout << "\t[3] Deposite\n";
	cout << "\t[4] Check Balance\n";
	cout << "\t[5] Log Out\n";
	cout << "===================================================================\n";
}

void gotoMainMenue()
{
	cout << "\n\nPress any key to go to Main Menue...";
	system("pause > 0");
	printMainMenue();
}

enAtmMainMenue readMainMenueAnswer()
{
	short ans = 0;

	do
	{
		cout << "\nEnter Your Choice [1 to 5] : ";
		cin >> ans;

	} while (ans > 5 || ans < 1);

	return enAtmMainMenue(ans);
}

string convertStClientToString(stClient client, string delimeter = "#//#")
{
	string dataInOneLine = "";

	dataInOneLine += client.AccountNumber + delimeter;
	dataInOneLine += client.PinCode + delimeter;
	dataInOneLine += client.ClientName + delimeter;
	dataInOneLine += client.PhoneNumber + delimeter;
	dataInOneLine += to_string(client.Balance);

	return dataInOneLine;
}

vector<string> splitString(string s, string delimeter = "#//#")
{
	vector<string> vSplit;

	short pos = s.find(delimeter);

	string word = "";

	while (pos != string::npos)
	{
		word = s.substr(0, pos);

		if (word != "")
		{
			vSplit.push_back(word);
		}

		s.erase(0, pos + delimeter.length());

		pos = s.find(delimeter);
	}

	if (s != "")
	{
		vSplit.push_back(s);
	}

	return vSplit;
}

stClient convertStringToStClient(string s)
{
	stClient client;

	vector<string> vSplit = splitString(s);

	client.AccountNumber = vSplit[0];
	client.PinCode = vSplit[1];
	client.ClientName = vSplit[2];
	client.PhoneNumber = vSplit[3];
	client.Balance = stod(vSplit[4]);

	return client;
}

void saveVectorToFile(vector<stClient>& vClients, string fileName)
{
	fstream file;

	file.open(fileName, ios::out); // write mode

	if (file.is_open())
	{
		string line = "";

		for (stClient& c : vClients)
		{
			line = convertStClientToString(c);

			file << line << endl;
		}

		file.close();
	}
}

vector<stClient> loadDataFromFile(string fileName)
{
	vector<stClient> vClients;

	fstream file;

	file.open(fileName, ios::in); // read mode

	if (file.is_open())
	{
		string line;
		stClient client;

		while (getline(file, line))
		{
			client = convertStringToStClient(line);

			vClients.push_back(client);
		}

		file.close();
	}

	return vClients;
}

bool searchForClient(string AccountNumber, string PinCode, vector<stClient>& vClients, stClient& client)
{
	vClients = loadDataFromFile(ClientsFileName);

	for (stClient c : vClients)
	{
		if (c.AccountNumber == AccountNumber && c.PinCode == PinCode)
		{
			client = c;
			
			return true;
		}
	}

	return false;
}

void deposite(double Amount)
{
	vector<stClient> vClients = loadDataFromFile(ClientsFileName);

	char yn;
	cout << "\nAre You Sure You Want To Make This Transaction Y/N ? ";
	cin >> yn;

	if (tolower(yn) == 'y');
	{
		for (stClient& c : vClients)
		{
			if(c.AccountNumber == currentClient.AccountNumber)
			{
				c.Balance += Amount; // edit balance in file

				currentClient.Balance += Amount; // to update client in runtime only 
			}
		}

		saveVectorToFile(vClients, ClientsFileName);

		cout << "Transaction Done Successfully...";
	}
}

void quickWithdrawScreen()
{
	system("cls");

	cout << "----------------------------------------------------\n";
	cout << "\t\tQuick Withraw Screen";
	cout << "\n----------------------------------------------------\n\n";
	cout << "[1] 50 \t [2] 100\n";
	cout << "[3] 200\t [4] 400\n";
	cout << "[5] 800\t [6] 1000\n";

	short Amount = 0;
	do
	{
		cout << "\nEnter Your Choice [1 to 6] : ";
		cin >> Amount;

	} while (Amount < 1 || Amount > 6);

	switch (Amount)
	{
	case 1 :
	{
		if (currentClient.Balance > 50)
		{
			deposite(50 * -1);

			gotoMainMenue();
		}
		else
		{
			cout << "\nAmount Exceeds the limit, you can withdraw up to \"" << currentClient.Balance << "\"";

			gotoMainMenue();
		}
		break;
	}
	case 2 :
	{
		if (currentClient.Balance > 100)
		{
			deposite(100 * -1);

			gotoMainMenue();
		}
		else
		{
			cout << "\nAmount Exceeds the limit, you can withdraw up to \"" << currentClient.Balance << "\"";

			gotoMainMenue();
		}
		break;
	}
	case 3:
	{
		if (currentClient.Balance > 200)
		{
			deposite(200 * -1);

			gotoMainMenue();
		}
		else
		{
			cout << "\nAmount Exceeds the limit, you can withdraw up to \"" << currentClient.Balance << "\"";

			gotoMainMenue();
		}
		break;
	}
	case 4:
	{
		if (currentClient.Balance > 400)
		{
			deposite(400 * -1);

			gotoMainMenue();
		}
		else
		{
			cout << "\nAmount Exceeds the limit, you can withdraw up to \"" << currentClient.Balance << "\"";

			gotoMainMenue();
		}
		break;
	}
	case 5:
	{
		if (currentClient.Balance > 800)
		{
			deposite(800 * -1);

			gotoMainMenue();
		}
		else
		{
			cout << "\nAmount Exceeds the limit, you can withdraw up to \"" << currentClient.Balance << "\"";

			gotoMainMenue();
		}
		break;
	}

	case 6:
	{
		if (currentClient.Balance > 1000)
		{
			deposite(1000 * -1);

			gotoMainMenue();
		}
		else
		{
			cout << "\nAmount Exceeds the limit, you can withdraw up to \"" << currentClient.Balance << "\"";

			gotoMainMenue();
		}
		break;
	}
	}
}

void depositeScreen()
{
	system("cls");

	cout << "------------------------------------------------\n";
	cout << "\t\tDeposite Screen";
	cout << "\n------------------------------------------------\n";

	double Amount = 0;

	cout << "\nEnter Amount to Deposite : ";
	cin >> Amount;

	deposite(Amount);

	gotoMainMenue();
}

void withDrawScreen()
{
	system("cls");

	cout << "------------------------------------------------\n";
	cout << "\t\tWithdraw Screen";
	cout << "\n------------------------------------------------\n";

	double Amount = 0;

	cout << "\nEentr Amount to Withdraw : ";
	cin >> Amount;

	if (currentClient.Balance > Amount)
	{
		deposite(Amount * -1);

		gotoMainMenue();
	}
	else
	{
		cout << "\nAmount Exceeds the limit, you can withdraw up to \"" << currentClient.Balance << "\"";
		
		gotoMainMenue();
	}
}

void  checkBalance()
{
	system("cls");

	cout << "----------------------------------------------------\n";
	cout << "\t\tCheck Balance Screen";
	cout << "\n----------------------------------------------------\n\n";

	cout << "Your Balance is : " << currentClient.Balance;

	gotoMainMenue();
}

void choseOperationFromMainMenue(enAtmMainMenue choice)
{
	switch (choice)
	{
	case QuickWithDraw:
	{
		quickWithdrawScreen();

		break;
	}
	case NormalWithDraw:
	{
		withDrawScreen();

		break;
	}
	case Deposite:
	{
		depositeScreen();

		break;
	}
	case enAtmMainMenue::CheckBalance:
	{
		checkBalance();

		break;
	}
	case LogOut:
	{
		logIn();
		
		break;
	}
	default:
		break;
	}
}

void Start()
{
	enAtmMainMenue choice;

	printMainMenue();
	
	do
	{
		choice = readMainMenueAnswer();

		choseOperationFromMainMenue(choice);

	} while (choice != enAtmMainMenue::LogOut);
}

void logIn()
{
	bool loginFail = false;

	vector<stClient> vClints;

	do
	{
		system("Cls");

		cout << "---------------------------------------------\n";
		cout << "\t\tLogin screen";
		cout << "\n---------------------------------------------\n\n";

		if (loginFail == true)
		{
			cout << "Invalid Account Number / Password\n\n";
		}

		cout << "Enter Account Number : ";
		cin >> currentClient.AccountNumber;
		cout << "Enter Pin Code : ";
		cin >> currentClient.PinCode;

		if(searchForClient(currentClient.AccountNumber, currentClient.PinCode, vClints, currentClient))
		{
			loginFail = false;
		}
		else
		{
			loginFail = true;
		}

	} while (loginFail);

	Start();
}

int main()
{

	logIn();

	return 0;
}
