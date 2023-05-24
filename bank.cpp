//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************

#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

class account
{
    int acno;
    char name[50];
    int deposit;
    char type;
    int PIN;

public:
    void create_account();     //function to get data from user
    void show_account() const; //function to show data on screen
    void modify();             //function to add new data
    void dep(int);             //function to accept amount and add to balance amount
    void draw(int);            //function to accept amount and subtract from balance amount
    void report() const;       //function to show data in tabular format
    int retacno() const;       //function to return account number
    int retPIN() const;       //function to return account PIN
    int retdeposit() const;    //function to return balance amount
    char rettype() const;      //function to return type of account
};                             //class ends here

void account::create_account()
{
    cout << "\nEnter The account No. :";
    cin >> acno;
    cout << "\nEnter The Name of The account Holder : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nEnter Type of The account (C/S) : ";
    cin >> type;
    type = toupper(type);
    cout << "\nEnter 4 digit PIN : ";
    cin >> PIN;
    cout << "\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
    cin >> deposit;
    cout << "\nAccount Created..";
}

void account::show_account() const
{
    cout << "\nAccount No. : " << acno;
    cout << "\nAccount Holder Name : ";
    cout << name;
    cout << "\nType of Account : " << type;
    cout << "\nBalance amount : " << deposit;
}

void account::modify()
{
    cout << "\nAccount No. : " << acno;
    cout << "\nModify Account Holder Name : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nModify Type of Account : ";
    cin >> type;
    type = toupper(type);
    cout << "\nModify Balance amount : ";
    cin >> deposit;
}

void account::dep(int x)
{
    deposit += x;
}

void account::draw(int x)
{
    deposit -= x;
}

void account::report() const
{
    cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}

int account::retacno() const
{
    return acno;
}
int account::retPIN() const
{
    return PIN;
}

int account::retdeposit() const
{
    return deposit;
}

char account::rettype() const
{
    return type;
}

//***************************************************************
//    	function declaration
//****************************************************************
void write_account();            //function to write record in binary file
void display_sp(int);            //function to display account details given by user
void modify_account(int, int);        //function to modify record of file
void delete_account(int);        //function to delete record of file
void display_all();              //function to display all account details
void deposit_withdraw(int, int, int); // function to desposit/withdraw amount for given account

//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************

int main()
{
    char ch;
    int num;
    int PIN;
    do
    {
        system("cls");
        cout << "\n\tMAIN MENU";
        cout << "\n\t01. NEW ACCOUNT";
        cout << "\n\t02. DEPOSIT AMOUNT";
        cout << "\n\t03. WITHDRAW AMOUNT";
        cout << "\n\t04. BALANCE ENQUIRY";
        cout << "\n\t05. ALL ACCOUNT HOLDER LIST";
        cout << "\n\t06. CLOSE AN ACCOUNT";
        cout << "\n\t07. MODIFY AN ACCOUNT";
        cout << "\n\t08. EXIT";
        cout << "\n\tSelect Your Option (1-8) ";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case '1':
            write_account();
            break;
        case '2':
            cout << "\n\tEnter The account No. : ";
            cin >> num;
            cout << "\n\tEnter the PIN : ";
            cin >> PIN;
            deposit_withdraw(num, PIN, 1);
            break;
        case '3':
            cout << "\n\tEnter The account No. : ";
            cin >> num;
            cout << "\n\tEnter the PIN : ";
            cin >> PIN;
            deposit_withdraw(num, PIN, 2);
            break;
        case '4':
            cout << "\n\tEnter The account No. : ";
            cin >> num;
            display_sp(num);
            break;
        case '5':
            display_all();
            break;
        case '6':
            cout << "\n\tEnter The account No. : ";
            cin >> num;
            delete_account(num);
            break;
        case '7':
            cout << "\n\tEnter The account No. : ";
            cin >> num;
            cout << "\n\tEnter the PIN : ";
            cin >> PIN;
            modify_account(num, PIN);
            break;
        case '8':
            cout << "\n\tThanks for using bank managemnt system";
            break;
        default:
            cout << "\a";
        }
        cin.ignore();
        cin.get();
    } while (ch != '8');
    return 0;
}

//***************************************************************
//    	function to write in file
//****************************************************************

void write_account()
{
    account ac;
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char *>(&ac), sizeof(account));
    outFile.close();
}

//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_sp(int n)
{
    account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\nBALANCE DETAILS\n";

    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        if (ac.retacno() == n)
        {
            ac.show_account();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false)
        cout << "\nAccount number does not exist";
}

//***************************************************************
//    	function to modify record of file
//****************************************************************

void modify_account(int n, int PIN)
{
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char *>(&ac), sizeof(account));
        if (ac.retacno() == n && ac.retPIN() == PIN)
        {
            ac.show_account();
            cout << "\nEnter The New Details of account" << endl;
            ac.modify();
            int pos = (-1) * static_cast<int>(sizeof(account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(account));
            cout << "\n\t Record Updated";
            found = true;
        }
        else{
            cout<<"Invalid Credentials" <<endl;
        }
    }
    File.close();
    if (found == false)
        cout << "\n Record Not Found ";
}

//***************************************************************
//    	function to delete record of file
//****************************************************************

void delete_account(int n)
{
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        if (ac.retacno() != n)
        {
            outFile.write(reinterpret_cast<char *>(&ac), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat", "account.dat");
    cout << "\n\tRecord Deleted ..";
}

//***************************************************************
//    	function to display all accounts deposit list
//****************************************************************

void display_all()
{
    account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\n\t\tACCOUNT HOLDER LIST\n";
    cout << "====================================================\n";
    cout << "A/c no.      NAME           Type  Balance\n";
    cout << "====================================================\n";
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        ac.report();
    }
    inFile.close();
}

//***************************************************************
//    	function to deposit and withdraw amounts
//****************************************************************

void deposit_withdraw(int n, int PIN, int option)
{
    int amt;
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char *>(&ac), sizeof(account));
        if (ac.retacno() == n && ac.retPIN() == PIN)
        {
            ac.show_account();
            if (option == 1)
            {
                cout << "\n\tTO DEPOSITE AMOUNT ";
                cout << "\nEnter The amount to be deposited : ";
                cin >> amt;
                ac.dep(amt);
            }
            if (option == 2 )
            {
                cout << "\n\tTO WITHDRAW AMOUNT ";
                cout << "\nEnter The amount to be withdraw : ";
                cin >> amt;
                int bal = ac.retdeposit() - amt;
                if ((bal < 500 && ac.rettype() == 'S') || (bal < 1000 && ac.rettype() == 'C'))
                    cout << "\n Insufficience balance";
                else
                    ac.draw(amt);
            }
            int pos = (-1) * static_cast<int>(sizeof(ac));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(account));
            cout << "\n\t Record Updated";
            found = true;
        }
        else{
            cout<<"Invalid Creadentials"<<endl;
        }
    }
    File.close();
    if (found == false)
        cout << "\n Record Not Found ";
}


//***************************************************************
//    			END OF PROJECT
//***************************************************************