#include <iostream>
#include <vector>

using namespace std;

// Класс, представляющий банковский аккаунт
class BankAccount {
private:
    string accountNumber;
    double balance;

public:
    BankAccount(string number, double initialBalance) 
    {
        accountNumber = number;
        balance = initialBalance;
    }

    string getAccountNumber() 
    {
        return accountNumber;
    }

    double getBalance() 
    {
        return balance;
    }

    void setBalance(double newBalance) 
    {
        balance = newBalance;
    }
};

// Класс, представляющий платеж
class Payment {
private:
    string fromAccount;
    string toAccount;
    double amount;

public:
    Payment(string from, string to, double paymentAmount) 
    {
        fromAccount = from;
        toAccount = to;
        amount = paymentAmount;
    }

    string getFromAccount() 
    {
        return fromAccount;
    }

    string getToAccount() 
    {
        return toAccount;
    }

    double getAmount() 
    {
        return amount;
    }
};

// Функция для обработки платежей
void processPayments(vector<Payment> payments, vector<BankAccount>& accounts) 
{
    for (int i = 0; i < payments.size(); ++i) 
    {
        // Находим аккаунты отправителя и получателя платежа
        BankAccount* sender = nullptr;
        BankAccount* receiver = nullptr;

        for (int j = 0; j < accounts.size(); ++j)
        {
            if (accounts[j].getAccountNumber() == payments[i].getFromAccount())
            {
                sender = &accounts[j];
            }
            if (accounts[j].getAccountNumber() == payments[i].getToAccount())
            {
                receiver = &accounts[j];
            }

            if (sender != nullptr && receiver != nullptr) 
            {
                break;
            }
        }

        // Если аккаунты найдены, производим перевод денег
        if (sender != nullptr && receiver != nullptr) 
        {
            double amount = payments[i].getAmount();
            if (sender->getBalance() >= amount) 
            {
                sender->setBalance(sender->getBalance() - amount);
                receiver->setBalance(receiver->getBalance() + amount);
                cout << "Платеж выполнен успешно." << endl;
            }
            else {
                cout << "Нехватает средств на счете " << sender->getAccountNumber()
                    << " для проведения платежа в размере " << amount << "." << endl;
            }
        }
        else {
            cout << "Ошибка: не удалось найти аккаунт отправителя или получателя для платежа." << endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    // Создаем банковские аккаунты
    vector<BankAccount> accounts;
    accounts.push_back(BankAccount("111111", 500.0));
    accounts.push_back(BankAccount("222222", 1000.0));
    accounts.push_back(BankAccount("333333", 2000.0));

    // Создаем платежи
    vector<Payment> payments;
    payments.push_back(Payment("111111", "222222", 200.0));
    payments.push_back(Payment("222222", "333333", 500.0));
    payments.push_back(Payment("333333", "444444", 100.0));

    // Обрабатываем платежи
    processPayments(payments, accounts);
}