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
    Customer(std::string id,std::string firstname,std::string middlename,std::string lastname,std::string email);
    std::string get_firstname() const;
    std::string get_middlename() const;
    std::string get_lastname() const;
    std::string get_email() const;
    std::string get_id() const;
    std::vector<std::string>& get_accounts();
    void add_account(std::string);
};