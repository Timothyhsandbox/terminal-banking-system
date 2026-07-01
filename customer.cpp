#include "customer.hpp"

#include <string>

std::ostream& operator<<(std::ostream &os,const Customer &cus) {
    os << cus.first_name << " " << cus.middle_name << " " << cus.last_name << std::endl;
    return os;
}

Customer::Customer(std::string customer_id,std::string first_name,std::string middle_name,std::string last_name,std::string pin,std::string email)
    : customer_id{customer_id},first_name{first_name},middle_name{middle_name},last_name{last_name},pin{pin},email{email} {};

std::string Customer::get_name() const {
    if(middle_name == "-")
        return first_name + " " + last_name;
    else
        return first_name + " " + middle_name + " " + last_name;
};

std::string Customer::get_pin() const {
    return pin;
}

std::string Customer::get_id() const {
    return customer_id;
}