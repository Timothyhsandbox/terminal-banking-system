#include "bank.hpp"
#include "account.hpp"
#include "customer.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <random>
#include <stdexcept>

void log_transaction(Account &from,Account &to,double amount);
std::string make_account_id();
std::string input_id();
void valid_id(std::string id);

void Bank::make_account() {
    //Make sure that you or a customer first.
    std::cout << std::string(10,'=') << "Verify customer id" << std::string(11,'=') << std::endl;
    std::string id = input_id();
    if(customers.find(id) == customers.end())
        throw std::invalid_argument("Person hasn't varified identity.");

    //Make an valid account id.
    std::string acc_id = make_account_id();
    while(accounts.find(acc_id) != accounts.end())
        acc_id = make_account_id();
    
    //Construct and make Account objects into unordered map
    std::cout << std::string(12,'=') << "Create account" << std::string(13,'=') << std::endl;
    accounts.emplace(acc_id,Account(acc_id));
}

std::string make_account_id() {
    //Random account 8 digit id maker.
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(10000000,99999999);

    return std::to_string(dist(gen));
}

void log_account() {

}

void Bank::make_customer() {
    std::string id = input_id();
    customers.emplace(id,Customer(id));
}

std::string Bank::input_id() {
    std::string id;

    while(true){
        try{
            std::cout << "Enter id: ";
            std::getline(std::cin,id);

            valid_id(id);
            break;
        }
        catch(const std::exception &e) {
            std::cout << e.what();
            std::cout << ".Please enter again.\n";
        }
    }
    return id;
}

void valid_id(std::string id) {
    //Check for length
    if(id.length() != 13)
        throw std::invalid_argument("ID must be 13 charactors long.");
    
    //Check digits
    for(const char c:id){
        if(!std::isdigit(c))
            throw std::invalid_argument("ID must contain only digits.");
    }
}

void log_customer() {

}

void Bank::transfer(Account &from,Account &to,double balance) {
    from.withdraw(balance);
    to.deposit(balance);
    log_transaction(from,to,balance);
}

void log_transaction(Account &from,Account &to,double amount) {
    std::ofstream file{"transaction.txt",std::ios::app};
    if(!file)
        throw std::runtime_error("Could not open transaction");
    else   
        file << from.get_account_number() << "," << to.get_account_number() << "," << amount << std::endl;
}

//Testing functions
void Bank::show() {
    std::cout << std::string(39,'=') << std::endl;

    for(const auto &acc: accounts){
        std::cout << acc.first << '\n' << acc.second << std::endl;
    }

    std::cout << std::string(39,'=') << std::endl;

    for(const auto &cus: customers){
        std::cout << cus.first << '\n' << cus.second << std::endl;
    }
}