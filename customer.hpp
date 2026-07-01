#pragma once
#include <iostream>
#include <string>

class Customer{
friend std::ostream& operator<<(std::ostream &os,const Customer &c);
private:
    std::string customer_id;
    std::string first_name;
    std::string middle_name; //If do not have middle name input must be "-" string.
    std::string last_name;
    std::string pin;
    std::string email;
public:
    Customer(std::string customer_id,std::string first_name,std::string middle_name,std::string last_name,std::string pin,std::string email);
    std::string get_name() const;
    std::string get_pin() const;
    std::string get_id() const;
};
