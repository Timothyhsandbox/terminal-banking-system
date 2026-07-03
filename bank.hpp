#pragma once
#include "account.hpp"
#include "customer.hpp"

#include <iostream>
#include <string>
#include <unordered_map>

class Bank{
friend std::ostream& operator<<(std::ostream &os,const Bank &b);
private:
    std::unordered_map<std::string,Customer> customers;
    std::unordered_map<std::string,Account> accounts;
public:
    Account make_account();
    std::string make_account_id();
    Customer make_customer();
};