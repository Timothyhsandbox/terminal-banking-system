#include "customer.hpp"

#include <string>
#include <iostream>

std::string inputfirstname();
std::string inputmiddlename();
std::string inputlastname();
std::string inputemail();
std::string inputid();

std::ostream& operator<<(std::ostream &os,const Customer &cus) {
    os << cus.first_name << " " << cus.middle_name << " " << cus.last_name << std::endl;
    return os;
}

Customer::Customer()
    : first_name(inputfirstname()),
     middle_name(inputmiddlename()),
     last_name(inputlastname()),
     customer_id(inputid()),
     email(inputemail()) {
        std::cout << "constructor called." << std::endl;
    };

std::string Customer::get_email() const {
    return email;
}

std::string Customer::get_id() const {
    return customer_id;
}

std::string inputfirstname(){
    std::string firstname;

    std::cout << "Enter firstname: ";
    std::getline(std::cin,firstname);       
    return firstname;
}

std::string inputmiddlename(){
    std::string middlename;

    std::cout << "Enter middlename(If you do not have middlename input -): ";
    std::getline(std::cin,middlename);
    
    if(middlename == "-")
        return "";
    else
        return middlename;
}

std::string inputlastname(){
    std::string lastname;

    std::cout << "Enter Lastname: ";
    std::getline(std::cin,lastname);

    return lastname;
}

std::string inputemail(){
    std::string email;

    std::cout << "Enter email: ";
    std::getline(std::cin,email);
    return email;
}

std::string inputid(){
    std::string id;

    std::cout << "Enter your id: ";
    std::getline(std::cin,id);
    return id;
}

