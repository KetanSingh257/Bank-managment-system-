#include <iostream>
#include <string>
using namespace std;

#define MIN_BALANCE 500
#define MAX 100

namespace bank
{

    class Account
    {
    protected:
        int accNo;
        string name;
        float balance;

    public:
        Account()
        {
            accNo = 0;
            name = "";
            balance = 0;
        }

        Account(int accNo, string name, float balance)
        {
            this->accNo = accNo;
            this->name = name;
            this->balance = balance;
        }

        void deposit(int amount)
        {
            if (amount <= 0)
            {
                cout << "Invalid amount\n";
                return;
            }
            balance += amount;
            cout << "Deposit successful\n";
        }

        void deposit(float amount)
        {
            if (amount <= 0)
            {
                cout << "Invalid amount\n";
                return;
            }
            balance += amount;
            cout << "Deposit successful\n";
        }

        void withdraw(float amount)
        {
            if (amount <= 0)
            {
                cout << "Invalid amount\n";
            }
            else if (balance - amount < MIN_BALANCE)
            {
                cout << "Minimum balance required\n";
            }
            else
            {
                balance -= amount;
                cout << "Withdrawal successful\n";
            }
        }

        virtual void interest()
        {
            cout << "No interest\n";
        }

        void transfer(Account &acc, float amount)
        {
            if (amount <= 0 || balance < amount)
            {
                cout << "Transfer failed\n";
                return;
            }

            balance -= amount;
            acc.balance += amount;

            cout << "Transfer successful\n";
        }

        void display() const
        {
            cout << "\n----------------------\n";
            cout << "Account No: " << accNo << "\n";
            cout << "Name: " << name << "\n";
            cout << "Balance: " << balance << "\n";
            cout << "----------------------\n";
        }

        int getAccNo()
        {
            return accNo;
        }

        ~Account()
        {
            cout << "\nAccount " << accNo << " removed\n";
        }
    };

    class Savings : public Account
    {
    public:
        Savings(int accNo, string name, float balance)
            : Account(accNo, name, balance) {}

        void interest()
        {
            balance += balance * 0.05;
            cout << "5% Interest Added\n";
        }
    };

    class Current : public Account
    {
    public:
        Current(int accNo, string name, float balance)
            : Account(accNo, name, balance) {}
    };

}

using namespace bank;

Account *findAccount(Account *accounts[], int total, int accNo)
{
    for (int i = 0; i < total; i++)
    {
        if (accounts[i]->getAccNo() == accNo)
            return accounts[i];
    }
    return NULL;
}

int main()
{
    Account *accounts[MAX];
    int total = 0;
    int choice;

    cout << "===== BANK MANAGEMENT SYSTEM =====\n";

    while (true)
    {
        cout << "\n1 Create Savings Account\n";
        cout << "2 Create Current Account\n";
        cout << "3 Deposit\n";
        cout << "4 Withdraw\n";
        cout << "5 Display All\n";
        cout << "6 Add Interest\n";
        cout << "7 Transfer\n";
        cout << "8 Delete Account\n";
        cout << "9 Exit\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input (enter number)\n";
            continue;
        }

        if (choice == 1 || choice == 2)
        {
            int accNo;
            string name;
            float balance;

            cout << "Enter Account Number: ";
            cin >> accNo;

            if (findAccount(accounts, total, accNo) != NULL)
            {
                cout << "Account already exists\n";
                continue;
            }

            cout << "Enter Name: ";
            cin >> name;

            cout << "Enter Balance: ";
            cin >> balance;

            if (choice == 1)
                accounts[total] = new Savings(accNo, name, balance);
            else
                accounts[total] = new Current(accNo, name, balance);

            total++;
            cout << "Account created successfully\n";
        }

        else if (choice == 3)
        {
            int acc, amount;
            cout << "Enter Account Number: ";
            cin >> acc;

            Account *a = findAccount(accounts, total, acc);

            if (a == NULL)
            {
                cout << "Account not found\n";
                continue;
            }

            cout << "Enter Amount: ";
            cin >> amount;

            a->deposit(amount);
        }

        else if (choice == 4)
        {
            int acc;
            float amount;

            cout << "Enter Account Number: ";
            cin >> acc;

            Account *a = findAccount(accounts, total, acc);

            if (a == NULL)
            {
                cout << "Account not found\n";
                continue;
            }

            cout << "Enter Amount: ";
            cin >> amount;

            a->withdraw(amount);
        }

        else if (choice == 5)
        {
            cout << "\nTotal Accounts: " << total << "\n";

            for (int i = 0; i < total; i++)
                accounts[i]->display();
        }

        else if (choice == 6)
        {
            int acc;
            cout << "Enter Account Number: ";
            cin >> acc;

            Account *a = findAccount(accounts, total, acc);

            if (a == NULL)
            {
                cout << "Account not found\n";
                continue;
            }

            a->interest();
        }

        else if (choice == 7)
        {
            int from, to;
            float amount;

            cout << "From Account: ";
            cin >> from;
            cout << "To Account: ";
            cin >> to;

            Account *A = findAccount(accounts, total, from);
            Account *B = findAccount(accounts, total, to);

            if (A == NULL || B == NULL)
            {
                cout << "Account not found\n";
                continue;
            }

            cout << "Enter Amount: ";
            cin >> amount;

            A->transfer(*B, amount);
        }

        else if (choice == 8)
        {
            int acc;
            cout << "Enter Account Number: ";
            cin >> acc;

            for (int i = 0; i < total; i++)
            {
                if (accounts[i]->getAccNo() == acc)
                {
                    delete accounts[i];
                    accounts[i] = accounts[total - 1];
                    total--;
                    cout << "Account deleted successfully\n";
                    break;
                }
            }
        }
        else if (choice == 9)
        {
            cout << "Thank you\n";
            break;
        }

        else
        {
            cout << "Invalid choice\n";
        }
    }

    return 0;
}