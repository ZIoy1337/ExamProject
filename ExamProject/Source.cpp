#include <iostream>
#include <string>
#include <fstream>

struct Transaction 
{
    std::string walletName;
    std::string category;
    double amount;
    int date;
};

struct Wallet 
{
    std::string name;
    std::string type;
    double balance;
};

const int MAX_WALLETS = 10;
const int MAX_TRANSACTIONS = 100;

Wallet wallets[MAX_WALLETS];
Transaction transactions[MAX_TRANSACTIONS];

int walletCount = 0;
int transactionCount = 0;

void addWallet()
{
    bool canAddWallet = 0;
    if (walletCount < MAX_WALLETS)
    {
        canAddWallet = 1;
    }
    else
    {
        std::cout << "Wallet limit reached!\n";
    }

    if (canAddWallet)
    {
        std::cout << "Enter wallet name: ";
        std::cin >> wallets[walletCount].name;
        std::cout << "Enter type (debit/credit): ";
        std::cin >> wallets[walletCount].type;
        wallets[walletCount].balance = 0;
        walletCount++;
    }
}

void deposit()
{
    std::string name;
    double amount;
    std::cout << "Enter wallet name";
    std::cin >> name;
    std::cout << "Enter amount";
    std::cin >> amount;
    bool found = false;
    for (int i = 0; i < walletCount; i++)
    {
        if (wallets[i].name == name)
        {
            wallets[i].balance += amount;
            found = true;
            break;
        }
    }
    if (!found)
    {
        std::cout << "Wallet not found!\n";
    }
}

void addExpense()
{
    if (transactionCount >= MAX_TRANSACTIONS)
    {
        std::cout << "Transaction limit reached!\n";
        return;
    }

    std::string name, category;
    double amount;
    int date;
    std::cout << "Enter wallet name: ";
    std::cin >> name;
    std::cout << "Enter category: ";
    std::cin >> category;
    std::cout << "Enter amount: ";
    std::cin >> amount;
    std::cout << "Enter date (YYYYMMDD): ";
    std::cin >> date;

    bool found = false;
    for (int i = 0; i < walletCount; i++)
    {
        if (wallets[i].name == name)
        {
            if (wallets[i].balance >= amount)
            {
                wallets[i].balance -= amount;
                transactions[transactionCount++] =
                { name, category, amount, date };
                found = true;
                break;
            }
            else
            {
                std::cout << "Insufficient funds!\n";
                return;
            }
        }
    }
    if (!found)
    {
        std::cout << "Wallet not found!\n";
    }
}

void generateReport(int fromDate)
{
    double total = 0;
    for (int i = 0; i < transactionCount; i++)
    {
        if (transactions[i].date >= fromDate)
        {
            total += transactions[i].amount;
            std::cout << transactions[i].walletName << " - " << transactions[i].category << " - $" << transactions[i].amount << "\n";
        }
    }
    std::cout << "Total: $" << total << "\n";
}

void saveReportToFile(int fromDate, std::string filename) {
    std::ofstream file(filename);
    double total = 0;
    for (int i = 0; i < transactionCount; i++) {
        if (transactions[i].date >= fromDate) {
            file << transactions[i].walletName << " - " << transactions[i].category << " - $" << transactions[i].amount << "\n";
            total += transactions[i].amount;
        }
    }
    file << "Total: $" << total << "\n";
    file.close();
}

void topExpenses(int fromDate) {
    Transaction top[3] = { {"", "", 0, 0}, {"", "", 0, 0}, {"", "", 0, 0} };

    for (int i = 0; i < transactionCount; i++) {
        if (transactions[i].date >= fromDate) {
            for (int j = 0; j < 3; j++) {
                if (transactions[i].amount > top[j].amount) {
                    for (int k = 2; k > j; k--) {
                        top[k] = top[k - 1];
                    }
                    top[j] = transactions[i];
                    break;
                }
            }
        }
    }

    std::cout << "Top 3 expenses:\n";
    for (int i = 0; i < 3; i++) {
        if (top[i].amount > 0) {
            std::cout << top[i].category << " - $" << top[i].amount << "\n";
        }
    }
}
