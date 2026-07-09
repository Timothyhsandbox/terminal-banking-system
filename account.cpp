#include "account.hpp"  

#include <iostream>
#include <string>
#include <chrono> // Track time
#include <iomanip> //To make stream object
#include <random>
#include <stdexcept>
#include <cctype>
#include <sstream>

void deposit(double);
void withdraw(double);
void transfer(double,Account&);
void display_account();
std::string get_current_time();
void valid_pin(std::string);
std::string get_owner_id();
void valid_id(std::string);
std::string get_pin();
double initial_account_balance();
void valid_balance(std::string&);

std::ostream& operator<<(std::ostream &os,const Account &a) {
    os << a.account_number << "|" << a.owner_id << "|" << a.balance << std::endl;
    return os;
}

Account::Account(std::string acc_num,std::string id)
    //Still have to add functions(Will let Bank make account number because need to access all the accounts)
    : account_number(acc_num),owner_id(id),status("Active"),datetime_created(get_current_time()),pin(get_pin()),balance(initial_account_balance()) {};

std::string get_current_time() {
    auto now = std::chrono::system_clock::now(); //Gets time from system
    std::time_t now_c = std::chrono::system_clock::to_time_t(now); //Changes to time_t type
    std::tm local_time = *std::localtime(&now_c);
    std::ostringstream oss;
    oss << std::put_time(&local_time,"%Y-%m-%d %H:%M:%S");
    return oss.str(); //Return as a std::string
}

std::string get_owner_id() {
    std::string id;

    while(true){
        try{
            std::cout << std::setw(12) << "National ID: ";
            std::getline(std::cin,id);

            valid_id(id);
            break;
        }
        catch(const std::exception &e) {
            std::cout << "[ERROR]" << e.what() << "please enter valid id.\n";
        }
    }
    return id;
}

void Account::valid_id(std::string id) {
    //Check for length
    if(id.length() != 13)
        throw std::invalid_argument("ID must be 13 charactors long ");
    
    //Check digits
    for(const char c:id){
        if(!std::isdigit(c))
            throw std::invalid_argument("ID must contain only digits ");
    }
}

std::string get_pin() {
    std::string pin;

    while(true){
        try{
            std::cout << "Enter a pin(4 digits): ";
            std::getline(std::cin,pin);

            valid_pin(pin);
            break;
        }
        catch(const std::exception &e){
            std::cout << "[ERROR]" << e.what() << "enter PIN again.\n";
        }
        
    }
    return pin;
}

void valid_pin(std::string pin) {
    //Check length to be 4.
    if(pin.length() != 4)
        throw std::invalid_argument("Pin must be 4 charactors long ");

    for(const char c:pin){
        if(!std::isdigit(c))
            throw std::invalid_argument("Pin must contain only digits ");
    }
}

double initial_account_balance() {
    std::string balance;

    while(true){
        try{
            std::cout << "Initial balance: ";
            std::getline(std::cin,balance);

            valid_balance(balance);
            break;
        }
        catch(const std::exception &e){
            std::cout << e.what() << " please enter valid account balance." << std::endl;
        }
    }
    return std::stod(balance);
}

void valid_balance(std::string  &balance) {
    try{
        float value = std::stof(balance);//validates input for you.

        if (value < 0) {
            throw std::invalid_argument("Balance cannot be less than zero ");
        }
    }
    catch(const std::exception&) {
        throw std::invalid_argument("Invalid balance ");
    }
}

void Account::deposit(double amount) {
    if(amount <= 0)
        throw std::invalid_argument("Amount must be positive ");
    this->balance += amount;
}

void Account::withdraw(double amount) {
    if(amount <= 0)
        throw std::invalid_argument("Amount must be positive ");

    if(amount > this->balance)
        throw std::invalid_argument("Low balance: " + std::to_string(amount));
    this->balance -= amount;
}

std::string Account::get_account_number() {
    return this->account_number;
}

std::string Account::get_account_balance() {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << balance;
    return oss.str();
}

std::string Account::get_account_id() {
    return owner_id;
}