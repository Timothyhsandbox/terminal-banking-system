#include "customer.hpp"

#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cctype>
#include <algorithm>

std::string inputfirstname();
std::string inputmiddlename();
std::string inputlastname();
std::string inputemail();
void valid_name(std::string str); 
void add_account(std::string account); 

std::ostream& operator<<(std::ostream &os,const Customer &cus) {
    os << cus.customer_id << "|" 
       << cus.first_name << "|" 
        << cus.middle_name << "|" 
        << cus.last_name << "|"
        << cus.email;

    bool first{true};
    for(const auto &elem:cus.account_ids)
        if(first){
            os << elem;
            first = false;
        }else
            os << "," << elem;            

    return os;
}

Customer::Customer(std::string id)
    : first_name(inputfirstname()),
      middle_name(inputmiddlename()),
      last_name(inputlastname()),
      customer_id(id),
      email(inputemail()),
      account_ids(std::vector<std::string>{}) {};

std::string Customer::get_firstname() const {
    return first_name;
}

std::string Customer::get_middlename() const {
    return middle_name;
}

std::string Customer::get_lastname() const {
    return last_name;
}

std::string Customer::get_email() const {
    return email;
}

std::string Customer::get_id() const {
    return customer_id;
}

std::vector<std::string> Customer::get_accounts() const {
    return account_ids;
}

std::string inputfirstname() {
    std::string firstname;

    while(true){
        try{
            std::cout << std::setw(12) << "First name :";
            std::getline(std::cin,firstname);
            valid_name(firstname);
            break;
        }
        catch(const std::exception &e){
            std::cout << "[ERROR]" << e.what() << " enter first name again." << std::endl;
        }
    }
    return firstname;
}

std::string inputmiddlename() {
    std::string middlename;

    while(true){
        try{
            std::cout << std::setw(12) << "Middle Name(or -): ";
            std::getline(std::cin,middlename);

            if(middlename == "-")
                break;

            valid_name(middlename);
            break;
        }
        catch(const std::exception &e) {
            std::cout << "[ERROR]" << e.what() << " enter middle name again." << std::endl;
        }
    }
    return middlename;
}

std::string inputlastname() {
    std::string lastname;

    while(true){
        try{
            std::cout << "Last Name: ";
            std::getline(std::cin,lastname);
            valid_name(lastname);
            break;
        }
        catch(const std::exception &e) {
            std::cout << "[ERROR]" << e.what() << " enter lastname again." << std::endl;
        }
    }
    return lastname;
}

void valid_name(std::string str) {
    if(str == "")
        throw std::invalid_argument("Haven't entered information");
    for(const char c:str){
        if(!std::isalpha(c))
            throw std::invalid_argument("Name must contain only characters");
    }
}

void valid_email(std::string email) {
    if(email == "")
        throw std::invalid_argument("Haven't entered information");
}

std::string inputemail() {
    std::string email;

    while(true){
        try{
            std::cout << "Email: ";
            std::getline(std::cin,email);

            valid_email(email);
            break;
        }
        catch(const std::exception& e){
            std::cout << e.what() << " please enter email again." << std::endl;
        }
    }
    return email;
}

void Customer::add_account(std::string account) {
    account_ids.push_back(account);
}

