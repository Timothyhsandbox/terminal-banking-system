#include "customer.hpp"

#include <string>
#include <iostream>
#include <stdexcept>
#include <cctype>

std::string inputfirstname();
std::string inputmiddlename();
std::string inputlastname();
std::string inputemail();
std::string inputid();
void valid_id(std::string id);
void valid_name(std::string str); 
void add_account(std::string account); 

std::ostream& operator<<(std::ostream &os,const Customer &cus) {
    if(cus.middle_name != "")
        os << cus.first_name << " " << cus.middle_name << " " << cus.last_name << std::endl;
    else
        os << cus.first_name << " " << cus.last_name << std::endl;

    return os;
}

Customer::Customer()
    : first_name(inputfirstname()),
      middle_name(inputmiddlename()),
      last_name(inputlastname()),
      customer_id(inputid()),
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

std::string inputid() {
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

void Customer::add_account(std::string account) {
    account_ids.push_back(account);
}
