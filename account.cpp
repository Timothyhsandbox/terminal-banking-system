#include "account.hpp"  

#include <iostream>
#include <string>
#include <chrono> // Track time
#include <random>
#include <stdexcept>
#include <cctype>

void deposit();
void withdraw();
void transfer();
void display_account();
std::string get_current_time();
void valid_pin(std::string);
std::string get_pin();
float initial_account_balance();
void valid_balance(float);

std::ostream& operator<<(std::ostream &os,const Account &a) {

}

//Random account maker.
std::string make_account_number() {
//Check if is unique with bank first.
}

std::string Account::get_current_time() {
//No corilation is a helper function.

}

Account::Account() {
    //Still have to add functions
    : account_number{},owner_id{},status{},datetime_created{},pin{},balance{} {}
}

std::string get_owner_id() {
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
            std::cout << e.what();
            std::cout << "Enter PIN again.\n";
        }
        
    }
    return pin;
}

void valid_pin(std::string pin) {
    //Check length to be 4.
    if(pin.length() != 4)
        throw std::invalid_argument("Pin must be 4 charactors long.");

    for(const char c:pin){
        if(!std::isdigit(c))
            throw std::invalid_argument("Pin must contain only digits.");
    }
}

float initial_account_balance() {
    float balance;

    while(true){
        try{
            std::cout << "How much would you like to save with your account: ";
            std::cin >> balance;

            valid_balance(balance);
            break;
        }
        catch(const std::exception &e){
            std::cout << e.what() << " Please enter valid account balance.";
        }
    }
}

void valid_balance(float balance) {
    //balace more than 0
    if(balance < 0)
        std::invalid_argument("Balance cannot be less than zero.");
}