#include "bank.hpp"
#include "account.hpp"
#include "customer.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <unordered_map>

void Bank::transfer(Account &from,Account &to,double balance) {
    from.withdraw(balance);
    to.deposit(balance);
}

void log_transaction(Account &from,Account &to,double amount) {
    std::ofstream file{"transaction.txt",std::ios::app};
    if(!file)
        throw std::runtime_error("Could not open transaction");
    else   
        file << from.get_account_number() << "," << to.get_account_number() << "," << amount << std::endl;
}