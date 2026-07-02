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

};