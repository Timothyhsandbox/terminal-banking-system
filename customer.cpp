#include "customer.hpp"

#include <string>
#include <iostream>
#include <stdexcept>
#include <cctype>

std::string inputfirstname();
std::string inputmiddlename();
std::string inputlastname();
std::string inputemail();
void valid_name(std::string str); 
void add_account(std::string account); 

std::ostream& operator<<(std::ostream &os,const Customer &cus) {
    if(cus.middle_name != "")
        os << cus.first_name << " " << cus.middle_name << " " << cus.last_name << std::endl;
    else
        os << cus.first_name << " " << cus.last_name << std::endl;

    return os;
}

Customer::Customer(std::string id)
    : first_name(inputfirstname()),
      middle_name(inputmiddlename()),
      last_name(inputlastname()),
      customer_id(id),
      email(inputemail()),
      account_ids(std::vector<std::string>{}) {
        std::cout << "constructor called." << std::endl;
    };

std::string Customer::get_email() const {
    return email;
}

std::string Customer::get_id() const {
    return customer_id;
}

std::string inputfirstname() {
    std::string firstname;

    while(true){
        try{
            std::cout << "Enter Firstname: ";
            std::getline(std::cin,firstname);
            valid_name(firstname);
            break;
        }
        catch(const std::exception &e){
            std::cout << e.what() << "Enter Firstname again." << std::endl;
        }
    }
    return firstname;
}

std::string inputmiddlename() {
    std::string middlename;

    while(true){
        try{
            std::cout << "Enter middlename(If you do not have middlename input -): ";
            std::getline(std::cin,middlename);

            if(middlename == "-")
                return "";
            
            valid_name(middlename);
            break;
        }
        catch(const std::exception &e) {
            std::cout << e.what() << "Enter middle name again." << std::endl;
        }
    }
    return middlename;
}

std::string inputlastname() {
    std::string lastname;

    while(true){
        try{
            std::cout << "Enter Lastname: ";
            std::getline(std::cin,lastname);
            valid_name(lastname);
            break;
        }
        catch(const std::exception &e) {
            std::cout << e.what() << "Enter lastname again." << std::endl;
        }
    }
    return lastname;
}

void valid_name(std::string str) {
    for(const char c:str){
        if(!std::isalpha(c))
            throw std::invalid_argument("Name must contain only characters.");
    }
}

std::string inputemail() {
    std::string email;

    std::cout << "Enter email: ";
    std::getline(std::cin,email);
    return email;
}

void Customer::add_account(std::string account) {
    account_ids.push_back(account);
}
