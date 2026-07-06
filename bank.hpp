#pragma once
#include "account.hpp"
#include "customer.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

class Bank{
friend std::ostream& operator<<(std::ostream &os,const Bank &b);
private:
    //Stores first = customer-id,second = customer object
    std::unordered_map<std::string,Customer> customers;
    //Stores first = account_number,second = Account object
    std::unordered_map<std::string,Account> accounts;
    std::string input_id();
public:
    void make_account();
    void make_customer();
    void transfer(Account&,Account&,double);
    void show();
};