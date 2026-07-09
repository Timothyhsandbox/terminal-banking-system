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
    void run();
    std::string get_current_time();
    void read_customers();//Not implimented yet
    void read_accounts();//Not implimented yet
    void make_account();
    void make_customer();
    void transfer(Account&,Account&,double);
    void deposit(Account&,double);
    void withdraw(Account&,double);
    void show();
    void log_customers();//Haven't implimented yet.
    void log_accounts();//Done.
    void view_customer();
    void regestered_id(std::string id);
    void view_all_customers();
    void remove_customer();
    void view_account();
    std::unordered_map<std::string,Account>::iterator regestered_account(std::string);
    void view_all_accounts();
};