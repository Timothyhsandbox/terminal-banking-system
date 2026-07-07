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
#include <chrono>
#include <limits>

void log_transfer(Account &from,Account &to,double amount);
void log_deposit(Account&,double);
void log_withdraw(Account&,double);
std::string make_account_id();
std::string input_id();
void valid_id(std::string id);
std::string get_current_time();
void view_customer();


//====================================================================================================//
void Bank::run() {
    while(true){
        std::cout << std::string(52,'=') << std::endl << std::endl;
        std::cout << "          HINES BANK MANAGEMENT SYSTEM" <<std::endl << std::endl;
        std::cout << std::string(52,'=') << std::endl;
        std::cout << std::setw(26) << std::left << "[ Customer Management ]" << "|"<< std::setw(26) << "[ Account Management ]" << std::endl;
        std::cout << std::setw(26) << std::left << "1. Create Customer" << "|"<< std::setw(26) << "5. Create Account" << std::endl;
        std::cout << std::setw(26) << std::left << "2. View Customer" << "|"<< std::setw(26) << "6. View Account" << std::endl;
        std::cout << std::setw(26) << std::left << "3. View All Customers" << "|"<< std::setw(26) << "7. View All Accounts" << std::endl;
        std::cout << std::setw(26) << std::left << "4. Remove Customer" << "|"<< std::setw(26) << "8. Close Account" << std::endl ;
        std::cout << std::string(52,'-') << std::endl;
        std::cout << std::setw(26) << std::left << "[ Transactions ]" << "|"<< std::setw(26) << "[ Reports ]" << std::endl;
        std::cout << std::setw(26) << std::left << "9.  Deposit" << "|"<< std::setw(26) << "12. View Customer Transactions" << std::endl;
        std::cout << std::setw(26) << std::left << "10. Withdraw" << "|"<< std::setw(26) << "13. View All Transactions" << std::endl;
        std::cout << std::setw(26) << std::left << "11. Transfer" << "|"<< std::setw(26) << std::endl;
        std::cout << std::string(52,'-') << std::endl;
        std::cout << "0. Exit\n";
        std::cout << std::string(52,'=') << std::endl;
        
        int fn;
        std::cout << "Function: ";
        std::cin >> fn;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        bool terminate{false};
        switch (fn){
            case 0:
            {
                //Log data to files:
                this->log_accounts();
                this->log_customers();
                terminate = true;
                std::cout << "Hines Bank closing..." << std::endl;
                break;
            }
            case 1:   
                //input personal information into bank data base.
                this->make_customer();
                break;
            case 2:
                //Enter ID to see personal data.
                this->view_customer();
                break;
            case 5:
                this->make_account();
                //Need to catch exception for not a verified person.
                break;
            default:
                std::cout << "[ERROR] Invalid call enter again." << std::endl;
                break;
        } 

        if(terminate)
            break;

    }
}

//=====================================Interface Helper Functions======================================//
void Bank::view_customer() {
    std::cout << std::string(52,'=') << std::endl << std::endl;
    std::cout << "             VIEW CUSTOMER INFORMATION" <<std::endl << std::endl;
    std::cout << std::string(52,'=') << std::endl;

    char action{};
    std::string id{};
    while(true){
        try{
            id = input_id();
            regestered_id(id);
            break;
        }
        catch(const std::exception &e){
            std::cout << "[ERROR] " << e.what() << " (enter e to exit or n to re-enter): ";
            std::cin >> action;

            if(action == 'e')
                break;
            else if(action == 'n')
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    if(action != 'e'){
        //Find customer in unordered map.
        auto it = customers.find(id);
        Customer &c = it->second;

        std::cout << "First name: " << c.get_firstname() << std::endl;
        std::cout << "Middle name: " << c.get_middlename() << std::endl;
        std::cout << "Last name: " << c.get_lastname() << std::endl;
        std::cout << "Email: " << c.get_email() << '\n' << std::endl;

        std::cout << "Accounts" << std::endl;
        std::cout << std::string(52,'-') << std::endl;
        for(const std::string &elem: c.get_accounts())
            std::cout << elem << std::endl;
        std::cout << std::string(52,'=') << std::endl;
    }else{
        std::cout << "Returning to main menu..." << std::endl;
    }

}

void Bank::regestered_id(std::string id) {
    if(customers.find(id) == customers.end())
        throw std::invalid_argument("Customer hasn't regestered");
}
//====================================================================================================//

std::string Bank::get_current_time() {
    auto now = std::chrono::system_clock::now(); //Gets time from system
    std::time_t now_c = std::chrono::system_clock::to_time_t(now); //Changes to time_t type
    std::tm local_time = *std::localtime(&now_c);
    std::ostringstream oss;
    oss << std::put_time(&local_time,"%Y-%m-%d %H:%M:%S");
    return oss.str(); //Return as a std::string
}

void Bank::make_account() {
    //Make sure that you or a customer first.
    std::cout << "========== ACCOUNT INFORMATION ==========" << std::endl;
    std::cout << "|Verify customer id|" << std::endl;
    std::string id = input_id();
    if(customers.find(id) == customers.end())
        throw std::invalid_argument("Person hasn't varified identity.");

    //Make an valid account id.
    std::string acc_id = make_account_id();
    while(accounts.find(acc_id) != accounts.end())
        acc_id = make_account_id();
    
    //Construct and make Account objects into unordered map
    accounts.emplace(acc_id,Account(acc_id,id));

    //Add to customers accounts vector
    customers.at(id).add_account(acc_id);
}

std::string make_account_id() {
    //Random account 8 digit id maker.
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(10000000,99999999);

    return std::to_string(dist(gen));
}

void Bank::log_accounts() {
    std::ofstream file{"account.txt",std::ios::trunc};
    if(!file)
        throw std::runtime_error("Could not open account.txt");
    else   
        for(const auto& [acc_id,acc_obj]:accounts)
            file << acc_obj;
}

void Bank::make_customer() {
    std::cout << std::string(52,'=') << std::endl << std::endl;
    std::cout << "          HINES BANK MANAGEMENT SYSTEM" <<std::endl << std::endl;
    std::cout << std::string(52,'=') << std::endl;

    std::string id = input_id();

    //Check if customer already in customers
    if (customers.find(id) != customers.end())
        throw std::invalid_argument("Customer already exists.");

    customers.emplace(id,Customer(id));
}

std::string Bank::input_id() {
    std::string id;

    while(true){
        try{
            std::cout << std::setw(12) << "National ID: ";
            std::getline(std::cin,id);

            valid_id(id);
            break;
        }
        catch(const std::exception &e) {
            std::cout << e.what() << " please enter again.\n";
        }
    }
    return id;
}

void valid_id(std::string id) {
    //Check for length
    if(id.length() != 13)
        throw std::invalid_argument("ID must be 13 charactors long ");
    
    //Check digits
    for(const char c:id){
        if(!std::isdigit(c))
            throw std::invalid_argument("ID must contain only digits ");
    }
}

void Bank::log_customers() {
    std::ofstream file{"customer.txt",std::ios::trunc};
    if(!file)
        throw std::runtime_error("Could not open customer.txt");
    else   
        for(const auto& [cus_id,cus_obj]:customers)
            file << cus_obj << std::endl;
}

void Bank::transfer(Account &from,Account &to,double balance) {
    from.withdraw(balance);
    to.deposit(balance);
    log_transfer(from,to,balance);
}

void log_transfer(Account &from,Account &to,double amount) {
    std::ofstream file{"transaction.txt",std::ios::app};
    if(!file)
        throw std::runtime_error("Could not open transaction.txt");
    else   
        file << get_current_time() << "|" << "TRASFER" << "|" << from.get_account_number() << "|" << to.get_account_number() << "|" << amount << std::endl;
}

void deposit(Account& acc,double amount) {
    bool condition{false};
    char action{};
    while(true){
        try{
            acc.deposit(amount);

            if(condition)
                if(action == 'e')
                    break;
                else if(action == 'n'){
                    std::cout << "Enter new deposit amount: ";
                    std::cin >> amount;
                    condition = false;
                }else
                    throw std::invalid_argument("invalid input");
            else
                break;
        }
        catch(const std::exception& e){
            std::cout << e.what() << "(e to exit,n new withdraw amount.): ";
            std::cin >> action;
            condition = true;
        }
    }
}

void log_deposit(Account& acc,double amount) {
    std::ofstream file{"transaction.txt",std::ios::app};
    if(!file)
        throw std::runtime_error("Could not open transaction.txt");
    else   
        file << get_current_time() << "|" << "DEPOSIT" << "|-|" << acc.get_account_number() << "|" << amount << std::endl;
}

void withdraw(Account& acc,double amount) {
    bool condition{false};
    char action{};
    while(true){
        try{
            acc.withdraw(amount);

            if(condition)
                if(action == 'e')
                    break;
                else if(action == 'n'){
                    std::cout << "New withdraw amount: ";
                    std::cin >> amount;
                    condition = false;
                }else
                    throw std::invalid_argument("invalid input");
            else
                break;
        }
        catch(const std::exception& e){
            std::cout << e.what() << "(e to exit,n new withdraw amount.): ";
            std::cin >> action;
            condition = true;
        }
    }

}

void log_withdraw(Account& acc,double amount) {
    std::ofstream file{"transaction.txt",std::ios::app};
    if(!file)
        throw std::runtime_error("Could not open transaction.txt");
    else   
        file << get_current_time() << "|" << "WITHDRAW" << "|" << acc.get_account_number() << "|-|" << amount << std::endl;
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