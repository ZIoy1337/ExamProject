#include <iostream>
#include <string>
#include <fstream>

class Wallet {
private:
    std::string name;
    double balance;
    bool isCredit;

public:
    Wallet(std::string name, bool isCredit) : name(name), isCredit(isCredit), balance(0) {}
    
    void deposit(double amout)
    {
        balance += amout;
        std::cout << name << "Balans popolnen na: $" << amout << ". Vash balans: $" << balance << "\n";
    }

    bool expenditure(double amout)
    {
        if (!isCredit && balance < amout)
        {
            std::cout << "Nehvataet sredstv\n";
            return false;
        }
        
        balance -= amout;
        std::cout << "Spisano $" << amout << " s " << name << ". Balans: " << balance << "\n";
        return true;
    }

    double getBalance() const { return balance; }
    std::string getName() const { return name; }
};

class Transaction {
public:
    std::string category;
    double amout;
    std::string date;

    Transaction(std::string category, double amount, std::string date)
        : category(category), amout(amout), date(date) {
    }
};

class FinanceManager {
private:
    Wallet* wallets[10];
    int walletCount;
    Transaction* transactions[100];
    int transactionCount;

public:
    FinanceManager() : walletCount(0), transactionCount(0) {}
    void addWallet(std::string name, bool isCredit)
    {
        if (walletCount < 10)
        {
            wallets[walletCount++] = new Wallet(name, isCredit);
            std::cout << "Dobavlen :" << name << "\n";
        }
        else {
            std::cout << "Max kolichestvo portmane dostignuto\n";
        }
    }
    Wallet* getWallet(std::string name) {
        for (int i = 0; i < walletCount; i++) {
            if (wallets[i]->getName() == name) return wallets[i];
        }
        std::cout <<"Portmane ne nayden\n";
    }
    void addTransaction(std::string walletName, std::string category, double amount, std::string date) {
        Wallet* wallet = getWallet(walletName);
        if (!wallet) {
            std::cout << "Portmane ne nayden\n";
            return;
        }
        if (!wallet->expenditure(amount)) return;
        transactions[transactionCount++] = new Transaction(category, amount, date);
    }
    void saveReport() {
        std::ofstream file("finance_report.txt");
        file << "Tranzakcii:\n";
        for (int i = 0; i < transactionCount; i++) {
            file << transactions[i]->date << " - " << transactions[i]->category << ": " << transactions[i]->amout << "\n";
        }
        file.close();
        std::cout << "Otchet sohranen\n";
    }
    ~FinanceManager() {
        for (int i = 0; i < walletCount; i++) delete wallets[i];
        for (int i = 0; i < transactionCount; i++) delete transactions[i];
    }
};