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
std::string get_current_time();

std::string get_current_time() {
    auto now = std::chrono::system_clock::now(); //Gets time from system
    std::time_t now_c = std::chrono::system_clock::to_time_t(now); //Changes to time_t type
    std::tm local_time = *std::localtime(&now_c);
    std::ostringstream oss;
    oss << std::put_time(&local_time,"%Y-%m-%d %H:%M:%S");
    return oss.str(); //Return as a std::string
}

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

void Bank::log_accounts() {
    std::ofstream file{"account.txt",std::ios::app};
    if(!file)
        throw std::runtime_error("Could not open account.txt");
    else   
        for(const auto& [acc_id,acc_obj]:accounts)
            file << acc_obj << std::endl;
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

void Bank::log_customers() {
    std::ofstream file{"customer.txt",std::ios::app};
    if(!file)
        throw std::runtime_error("Could not open customer.txt");
    else   
        for(const auto& [cus_id,cus_obj]:customers)
            file << cus_obj << std::endl;
}

void Bank::transfer(Account &from,Account &to,double balance) {
    from.withdraw(balance);
    to.deposit(balance);
    log_transaction(from,to,balance);
}

void log_transaction(Account &from,Account &to,double amount) {
    std::ofstream file{"transaction.txt",std::ios::app};
    if(!file)
        throw std::runtime_error("Could not open transaction.txt");
    else   
        file << get_current_time() << "|" << "TRASFER" << "|" << from.get_account_number() << "|" << to.get_account_number() << "|" << amount << std::endl;
}

//Testing functions=================================================
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