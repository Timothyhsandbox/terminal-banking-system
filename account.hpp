#pragma once
#include <iostream>
#include <string>
#include <chrono>

class Account{
friend std::ostream& operator<<(std::ostream &os,const Account &a);
private:
    std::string account_number;
    std::string owner_id;
    float balance;
    std::string status;
    std::string datetime_created;
    std::string pin;
public:
    Account();
    void deposit();
    void withdraw();
    void transfer();
    void display_account();
    std::string get_current_time();
};