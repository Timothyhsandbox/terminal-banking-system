#pragma once
#include <iostream>
#include <string>
#include <vector>

class Customer{
friend std::ostream& operator<<(std::ostream &os,const Customer &cus);
private:
    std::string first_name;
    std::string middle_name; //If do not have middle name input must be "-" string.
    std::string last_name;
    std::string customer_id;
    std::string email;
    std::vector<std::string> account_ids;
public:
    Customer(std::string id);
    std::string get_email() const;
    std::string get_id() const;
    void add_account(std::string);
};