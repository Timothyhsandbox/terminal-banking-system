#pragma once
#include <iostream>
#include <string>
#include <chrono>

class Account{
friend std::ostream& operator<<(std::ostream &os,const Account &a);
private:
    std::string account_number; //Still don't have a randomizer.
    std::string owner_id; //Done
    std::string status; //Set default to Active can change to frozen and closed.
    std::string datetime_created; //done 
    std::string pin; //Done
    double balance; //Done
public:
    Account(std::string);
    void deposit(double);
    void withdraw(double);
    void valid_id(std::string);
    std::string get_account_number();
};