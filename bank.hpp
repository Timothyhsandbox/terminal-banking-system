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
    void run();//Used to run program in main
    void make_account();
    void make_customer();
    void transfer(Account&,Account&,double);
    void deposit(Account&,double);
    void withdraw(Account&,double);
    void show();
    void log_customers();//Haven't implimented yet.
    void log_accounts();//Done.
    std::string get_current_time();
};