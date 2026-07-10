#include "bank.hpp"
#include "account.hpp"
#include "customer.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <random>
#include <stdexcept>
#include <chrono>
#include <limits>
#include <cctype>
#include <sstream>
#include <algorithm>

std::string get_current_time();
void log_transfer(Account &from,Account &to,double amount);
void log_deposit(Account&,double);
void log_withdraw(Account&,double);
std::string make_account_id();
std::string input_id();
void valid_id(std::string id);
void view_customer();
void view_all_customers();
std::string input_acc_id();
void valid_acc_id(std::string);
double input_amount();
void valid_amount(double);
std::vector<std::string> split(const std::string&,char);
//====================================================================================================//
void Bank::run() {
    //Load data from files.
    load_customers();
    load_accounts();

    bool terminate{false};
    while(true){
        std::cout << std::string(52,'=') << std::endl << std::endl;
        std::cout << "           HINES BANK MANAGEMENT SYSTEM" <<std::endl << std::endl;
        std::cout << std::string(52,'=') << std::endl;
        std::cout << std::setw(26) << std::left << "[ Customer Management ]" << "|"<< std::setw(26) << "[ Account Management ]" << std::endl;
        std::cout << std::setw(26) << std::left << "1. Create Customer" << "|"<< std::setw(26) << "5. Create Account" << std::endl;
        std::cout << std::setw(26) << std::left << "2. View Customer" << "|"<< std::setw(26) << "6. View Account" << std::endl;
        std::cout << std::setw(26) << std::left << "3. View All Customers" << "|"<< std::setw(26) << "7. View All Accounts" << std::endl;
        std::cout << std::setw(26) << std::left << "4. Remove Customer" << "|"<< std::setw(26) << "8. Close Account" << std::endl ;
        std::cout << std::string(52,'-') << std::endl;
        std::cout << std::setw(26) << std::left << "[ Transactions ]" << "|"<< std::setw(26) << "[ Reports ]" << std::endl;
        std::cout << std::setw(26) << std::left << "9.  Deposit" << "|"<< std::setw(26) << "12. View Customer Transactions" << std::endl;
        std::cout << std::setw(26) << std::left << "10. Withdraw" << "|"<< std::setw(26) << "13. View All Transactions" << std::endl;
        std::cout << std::setw(26) << std::left << "11. Transfer" << "|"<< std::setw(26) << std::endl;
        std::cout << std::string(52,'-') << std::endl;
        std::cout << "0. Exit\n";
        std::cout << std::string(52,'=') << std::endl;
        
        int fn;
        std::cout << "Function: ";
        if (!(std::cin >> fn)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "[ERROR] Invalid input.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch(fn){
            case 0:
            {
                //Log accounts and customers to file.txt
                log_accounts();
                log_customers();
                terminate = true;
                std::cout << "Saving data..." << std::endl;
                std::cout << "Hines Bank closing..." << std::endl;
                break;
            }
            case 1: 
            {
                try{
                //input personal information into bank data base.
                    this->make_customer();
                }
                catch(const std::exception& e){
                    std::cout << e.what() << std::endl;
                }
               break;
            }
            case 2:
                //Enter ID to see personal data.
                this->view_customer();
                break;
            case 3:
                this->view_all_customers();
                break;
            case 4: 
                this->remove_customer();
                break;
            case 5:
            {
                try{
                    this->make_account();
                }catch(const std::exception& e){
                    //Need to catch exception for not a verified person.
                    std::cout << e.what() << std::endl;
                }
                break;
            }
            case 6:
            {
                this->view_account();
                break;
            }
            case 7:
            {
                this->view_all_accounts();
                break;
            }
            case 8:
            {
                this->close_account();
                break;
            }
            case 9:
            {
                this->deposit();
                break;
            }
            case 10:
            {
                this->withdraw();
                break;
            }
            case 11:
            {
                this->transfer();
                break;
            }
            case 12:
            {
                this->view_customer_transactions();
                break;
            }
            case 13:
            {
                this->view_all_transactions();
                break;
            }
            default:
                std::cout << "[ERROR] Invalid call enter again." << std::endl;
                break;
        } 

        if(terminate)
            break;

    }
}

//=====================================Interface Helper Functions======================================//
void Bank::view_customer() {
    std::cout << std::string(52,'=') << std::endl << std::endl;
    std::cout << "             VIEW CUSTOMER INFORMATION" <<std::endl << std::endl;
    std::cout << std::string(52,'=') << std::endl;

    char action{};
    std::string id{};
    while(true){
        try{
            id = input_id();
            regestered_id(id);
            break;
        }
        catch(const std::exception &e){
            std::cout << "[ERROR] " << e.what() << " (enter e to exit or n to re-enter): ";
            std::cin >> action;

            if(action == 'e')
                break;
            else if(action == 'n')
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    if(action != 'e'){
        //Find customer in unordered map.
        auto it = customers.find(id);
        Customer &c = it->second;

        std::cout << "First name: " << c.get_firstname() << std::endl;
        std::cout << "Middle name: " << c.get_middlename() << std::endl;
        std::cout << "Last name: " << c.get_lastname() << std::endl;
        std::cout << "Email: " << c.get_email() << '\n' << std::endl;

        std::cout << "Accounts" << std::endl;
        std::cout << std::string(52,'-') << std::endl;
        for(const std::string &elem: c.get_accounts())
            std::cout << elem << std::endl;
        std::cout << std::string(52,'=') << std::endl;
    }else{
        std::cout << "Returning to main menu..." << std::endl;
    }

}

void Bank::regestered_id(std::string id) {
    if(customers.find(id) == customers.end())
        throw std::invalid_argument("Customer hasn't regestered");
}

void Bank::view_all_customers() {
    std::cout << std::string(52,'=') << std::endl << std::endl;
    std::cout << "                   CUSTOMER LIST" <<std::endl << std::endl;
    std::cout << std::string(52,'=') << std::endl << std::endl;

    std::cout << std::left << std::setw(16) << "National ID" << std::setw(22) << "Name" << "Accounts" << std::endl;
    std::cout << std::string(52,'-') << std::endl << std::endl;

    for(auto& [id,customer]:customers){
        std::string name;
        if(customer.get_middlename() == "-"){
            name = customer.get_firstname() + " " + customer.get_lastname();
            std::cout << std::left << std::setw(16) << id << std::setw(22) << name << customer.get_accounts().size() << std::endl;
        }else{
            name = customer.get_firstname() + " " + customer.get_middlename() + " " + customer.get_lastname();
            std::cout << std::left << std::setw(16) << id << std::setw(22) << name << customer.get_accounts().size() << std::endl;
        }
    }

    std::cout << '\n' << "Total customers: " << customers.size() << std::endl;
    std::cout << std::string(52,'=') << std::endl << std::endl;
}

void Bank::remove_customer() {
    std::cout << std::string(52,'=') << std::endl << std::endl;
    std::cout << "                  CUSTOMER REMOVAL" <<std::endl << std::endl;
    std::cout << std::string(52,'=') << std::endl << std::endl;

    char action{};
    std::string id{};
    while(true){
        try{
            id = input_id();
            regestered_id(id);
            break;
        }
        catch(const std::exception &e){
            std::cout << "[ERROR] " << e.what() << " (enter e to exit or n to re-enter): ";
            std::cin >> action;

            if(action == 'e')
                break;
            else if(action == 'n')
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    if(action != 'e'){
        auto it = customers.find(id);
        auto accs = it->second.get_accounts();
        //remove from customers
        customers.erase(it);
        //remove customer accounts

        for(const auto& acc:accs){
            std::unordered_map<std::string,Account>::iterator it = accounts.begin();
            it = accounts.find(acc);
            std::cout << "Deleted account " << it->first << std::endl;
            accounts.erase(it);
        }

        std::cout << "Customer removed..." <<std::endl;
    }
    std::cout << std::string(52,'=') << std::endl << std::endl;
}

void Bank::view_account() {
    std::cout << std::string(52,'=') << std::endl << std::endl;
    std::cout << "               ACCOUNT INFORMATION" <<std::endl << std::endl;
    std::cout << std::string(52,'=') << std::endl << std::endl;

    char action{};
    std::string acc_id{};
    std::unordered_map<std::string,Account>::iterator it;
    while(true){
        try{
            acc_id = input_acc_id();
            it = regestered_account(acc_id);
            break;
        }
        catch(const std::exception &e){
            std::cout << "[ERROR] " << e.what() << " (enter e to exit or n to re-enter): ";
            std::cin >> action;

            if(action == 'e')
                break;
            else if(action == 'n')
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    if(action != 'e'){
        std::cout << "Owner ID: " << it->second.get_account_id() << std::endl;
        std::cout << "PIN: " << it->second.get_account_pin() << std::endl;
        std::cout << "Amount(THB): " << it->second.get_account_balance() << std::endl << std::endl;
        std::cout << std::string(52,'=') << std::endl;
    }
}

std::unordered_map<std::string,Account>::iterator Bank::regestered_account(std::string acc_id) {
    std::unordered_map<std::string,Account>::iterator it = accounts.find(acc_id);
    if(it == accounts.end())
        throw std::invalid_argument("Account ID doesn't exist.");

    return it;
}

std::string Bank::input_acc_id() {
    std::string acc_id;
    while(true){
        try{
            std::cout << "Enter account id: ";
            std::getline(std::cin,acc_id);
            valid_acc_id(acc_id);
            break;
        }catch(const std::exception& e){
            std::cout << e.what() << std::endl;
        }
    }
    return acc_id;
}

void valid_acc_id(std::string acc_id) {
    if(acc_id.length() != 8)
        throw std::invalid_argument("Invalid Account id.");
    
    for(const char& elem:acc_id){
        if(!std::isdigit(elem))
            throw std::invalid_argument("Invaalid Account id.");
    }
}

void Bank::view_all_accounts() {
    std::cout << std::string(73,'=') << std::endl << std::endl;
    std::cout << std::string(30,' ') << "BANK ACCOUNTS" <<std::endl << std::endl;
    std::cout << std::string(73,'=') << std::endl << std::endl;

    std::cout << std::left << std::setw(15) << "Account No."<< std::setw(18) << "Owner ID"<< std::setw(25) << "Owner Name"<< std::setw(15) <<  "Balance (THB)" << std::endl;
    std::cout << std::string(73,'-') << std::endl; 

    double total_balance{0};
    for(auto& [acc_id,acc_obj]:accounts){
        total_balance += acc_obj.get_account_balance_as_double();

        std::ostringstream owner_name;
        if(customers.at(acc_obj.get_account_id()).get_middlename() != "-"){
            owner_name << customers.at(acc_obj.get_account_id()).get_firstname() << " " <<  customers.at(acc_obj.get_account_id()).get_middlename() << " " << customers.at(acc_obj.get_account_id()).get_lastname();
            std::cout << std::left << std::setw (15) << acc_id << std::setw(18) << acc_obj.get_account_id() << std::setw(25) << owner_name.str() << std::setw(15) << acc_obj.get_account_balance() << std::endl;
        }else{
            owner_name << customers.at(acc_obj.get_account_id()).get_firstname() << " " << customers.at(acc_obj.get_account_id()).get_lastname();
            std::cout << std::left << std::setw (15) << acc_id << std::setw(18) << acc_obj.get_account_id() << std::setw(25) << owner_name.str() << std::setw(15) << acc_obj.get_account_balance() << std::endl;
        }
    }

    std::cout << "\nTotal Accounts: " << accounts.size() << std::endl;
    std::cout << "Total amount: " << std::fixed << std::setprecision(2) << total_balance << std::endl;
    std::cout << std::string(73,'=') << std::endl;

}

void Bank::close_account() {
    //Remove from customer first then remove from unordered map.
    std::cout << std::string(52,'=') << std::endl << std::endl;
    std::cout << "                  ACCOUNT REMOVAL" <<std::endl << std::endl;
    std::cout << std::string(52,'=') << std::endl << std::endl;

    char action{};
    std::string acc_id{};
    std::unordered_map<std::string,Account>::iterator it;
    while(true){
        try{
            acc_id = input_acc_id();
            it = regestered_account(acc_id);
            break;
        }
        catch(const std::exception &e){
            std::cout << "[ERROR] " << e.what() << " (enter e to exit or n to re-enter): ";
            std::cin >> action;

            if(action == 'e')
                break;
            else if(action == 'n')
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    if(action != 'e'){
        //accounts vector passed be reference.
        auto& cus_acc = customers.at(it->second.get_account_id()).get_accounts();

        //Find value in vector
        auto vec_it = std::find(cus_acc.begin(),cus_acc.end(),acc_id);
        std::cout << "Removing account from customer..." << std::endl;
        cus_acc.erase(vec_it);

        //Find value in unordered map
        auto it = accounts.find(acc_id);
        std::cout << "Removeing account from data base..." << std::endl;
        accounts.erase(it);
    }
}

void Bank::view_customer_transactions() {
    std::cout << std::string(64,'=') << std::endl << std::endl;
    std::cout << std::string(20,' ') << "ACCOUNT TRANSACTION HISTORY" << std::endl << std::endl;
    std::cout << std::string(64,'=') << std::endl;

    std::fstream file{"transaction.txt",std::ios::in};
    //Check for impty file.
    if (file.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "No transactions found.\n";
        return;
    }   

    char action{};
    std::string acc_id{};
    std::unordered_map<std::string,Account>::iterator it;
    while(true){
        try{
            acc_id = input_acc_id();
            it = regestered_account(acc_id);
            break;
        }
        catch(const std::exception &e){
            std::cout << "[ERROR] " << e.what() << " (enter e to exit or n to re-enter): ";
            std::cin >> action;

            if(action == 'e')
                break;
            else if(action == 'n')
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::cout << std::left << std::setw(22) << "Date & Time" << std::setw(12) << "Type" << std::setw(10) << "From" << std::setw(10) << "To" << std::setw(10) << "Amount" << '\n';
    std::cout << std::string(64,'-') << std::endl;

    std::string line;
    std::vector<std::string> data;


    if(file){
        while(!file.eof()){
            std::getline(file,line);
            data = split(line,'|');
            //date_time,Type,From,to,amount
            if(data.size() == 5)
                if(data[2] == acc_id || data[3] == acc_id)
                    std::cout << std::left << std::setw(22) << data[0] << std::setw(12) << data[1] << std::setw(10) << data[2] << std::setw(10) << data[3] << std::setw(10) << data[4] << '\n';
        }
    }
    file.close();
    std::cout << std::string(64,'=') << std::endl;
}

void Bank::view_all_transactions() {
    std::cout << std::string(64,'=') << std::endl << std::endl;
    std::cout << std::string(24,' ') << "TRANSACTION HISTORY" << std::endl << std::endl;
    std::cout << std::string(64,'=') << std::endl;
    std::cout << std::left << std::setw(22) << "Date & Time" << std::setw(12) << "Type" << std::setw(10) << "From" << std::setw(10) << "To" << std::setw(10) << "Amount" << '\n';
    std::cout << std::string(64,'-') << std::endl;

    std::fstream file{"transaction.txt",std::ios::in};
    std::string line;
    std::vector<std::string> data;

    //Check for impty file.
    if (file.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "No transactions found.\n";
        return;
    }   

    if(file){
        while(!file.eof()){
            std::getline(file,line);
            data = split(line,'|');
            if(data.size() == 5)
                std::cout << std::left << std::setw(22) << data[0] << std::setw(12) << data[1] << std::setw(10) << data[2] << std::setw(10) << data[3] << std::setw(10) << data[4] << '\n';
            else
                break;  
        }
    }

    std::cout << std::string(64,'=') << std::endl;
}

//====================================================================================================//

std::string Bank::get_current_time() {
    auto now = std::chrono::system_clock::now(); //Gets time from system
    std::time_t now_c = std::chrono::system_clock::to_time_t(now); //Changes to time_t type
    std::tm local_time = *std::localtime(&now_c);
    std::ostringstream oss;
    oss << std::put_time(&local_time,"%Y-%m-%d %H:%M:%S");
    return oss.str(); //Return as a std::string
}

void Bank::make_account() {
    //Make sure that you or a customer first.
    std::cout << std::string(52,'=') << std::endl << std::endl;
    std::cout << "                ACCOUNT INFORMATION" << std::endl << std::endl;
    std::cout << std::string(52,'=') << std::endl;

    std::cout << "Verify customer id" << std::endl;
    std::string id = input_id();
    if(customers.find(id) == customers.end())
        throw std::invalid_argument("Person hasn't varified identity.");
    std::cout << std::string(26,'-') << std::endl;

    //Make an valid account id.
    std::string acc_id = make_account_id();
    while(accounts.find(acc_id) != accounts.end())
        acc_id = make_account_id();
    
    //Construct and make Account objects into unordered map
    accounts.emplace(acc_id,Account(acc_id,id));

    //Add to customers accounts vector
    customers.at(id).add_account(acc_id);
}

std::string make_account_id() {
    //Random account 8 digit id maker.
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(10000000,99999999);

    return std::to_string(dist(gen));
}

void Bank::log_accounts() {
    std::ofstream file{"account.txt"};
    if(!file)
        throw std::runtime_error("Could not open account.txt");
    else   
        for(const auto& [id,acc]:accounts)
            file << acc;
    
}

void Bank::load_accounts() {
    //Read whole file
    std::ifstream file{"account.txt"};

    if(!file){
        std::cerr << "Failed to open file." << std::endl;
        return;
    }

    std::string line;
    while(std::getline(file,line)){

        if(line.empty())
            continue;

        std::vector<std::string> ans = split(line,'|');

        //Create account objects.file format (account_id,National_id,balance)
        accounts.emplace(ans[0],Account(ans[0],ans[1],ans[2],ans[3],std::stod(ans[4])));
    }
    file.close();
}

void Bank::make_customer() {
    std::cout << std::string(52,'=') << std::endl << std::endl;
    std::cout << "             CUSTOMER INFORMATION" <<std::endl << std::endl;
    std::cout << std::string(52,'=') << std::endl;

    std::string id = input_id();

    //Check if customer already in customers
    if (customers.find(id) != customers.end())
        throw std::invalid_argument("Customer already exists.");

    //Constructc customer
    customers.emplace(id,Customer(id));

}

std::string Bank::input_id() {
    std::string id;

    while(true){
        try{
            std::cout << std::setw(12) << "National ID: ";
            std::getline(std::cin,id);

            valid_id(id);
            break;
        }
        catch(const std::exception &e) {
            std::cout << e.what() << " please enter again.\n";
        }
    }
    return id;
}

void valid_id(std::string id) {
    //Check for length
    if(id.length() != 13)
        throw std::invalid_argument("ID must be 13 charactors long ");
    
    //Check digits
    for(const char c:id){
        if(!std::isdigit(c))
            throw std::invalid_argument("ID must contain only digits ");
    }
}
void Bank::load_customers() {
    //Read whole file
    std::ifstream file{"customer.txt"};

    if(!file){
        std::cerr << "Failed to open file." << std::endl;
        return;
    }

    std::string line;
    while(std::getline(file,line)){

        if(line.empty())
            continue;

        std::vector<std::string> ans = split(line,'|');

        //Create customer objects.file format (National_id,firstname,middlename,lastname,email,accounts)
        customers.emplace(ans.at(0),Customer(ans.at(0),ans.at(1),ans.at(2),ans.at(3),ans.at(4)));

        //Deal with accounts of the customer find ',' for multiple accounts 
        Customer &cus = customers.at(ans.at(0));
        if (ans.size() == 6 && !ans[5].empty()) {
            auto accs = split(ans[5], ',');

            for (const auto& account : accs)
                cus.add_account(account);
        }
    }
    file.close();
}


void Bank::log_customers() {
    std::ofstream file{"customer.txt"};
    if(!file)
        throw std::runtime_error("Could not open customer.txt");
    else 
        for(const auto& [cus_id,cus]:customers)
            file << cus << std::endl;
}

void Bank::transfer() {
    std::cout << std::string(52,'=') << std::endl << std::endl;
    std::cout << "                     TRANSFER" <<std::endl << std::endl;
    std::cout << std::string(52,'=') << std::endl;

    char action{};
    while(true){
        try{
            //Input valid amount.
            double amount = input_amount();

            std::cin.clear();   // clear fail state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            //Input valild id
            std::string acc1_id = input_acc_id();
            validate_account(acc1_id);
            auto& acc1 = accounts.at(acc1_id);

            acc1.withdraw(amount);

            //Input valild id
            std::string acc2_id = input_acc_id();
            validate_account(acc2_id);
            auto& acc2 = accounts.at(acc2_id);

            acc2.deposit(amount);

            log_transfer(acc1,acc2,amount);
            break;
        }
        catch(const std::exception &e){
            std::cout << "[ERROR] " << e.what() << " (enter e to exit or n to re-enter): ";
            std::cin >> action;

            if(action == 'e')
                break;
            else if(action == 'n')
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    if(action != 'e'){
        std::cout << "transaction completed." << std::endl;
    }
    std::cout << std::string(52,'=') << std::endl;

}

void log_transfer(Account &from,Account &to,double amount) {
    std::ofstream file{"transaction.txt",std::ios::app};
    if(!file)
        throw std::runtime_error("Could not open transaction.txt");
    else   
        file << get_current_time() << "|" << "TRANSFER" << "|" << from.get_account_number() << "|" << to.get_account_number() << "|" << amount << std::endl;
}

void Bank::deposit() {
    std::cout << std::string(52,'=') << std::endl << std::endl;
    std::cout << "                        DEPOSIT" <<std::endl << std::endl;
    std::cout << std::string(52,'=') << std::endl;

    char action{};
    while(true){
        try{
            //Input valild id
            std::string acc_id = input_acc_id();
            validate_account(acc_id);
            auto& acc = accounts.at(acc_id);

            //Input valid amount.
            double amount = input_amount();
            acc.deposit(amount);
            log_deposit(acc,amount);
            break;
        }
        catch(const std::exception &e){
            std::cout << "[ERROR] " << e.what() << " (enter e to exit or n to re-enter): ";
            std::cin >> action;

            if(action == 'e')
                break;
            else if(action == 'n')
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    if(action != 'e'){
        std::cout << "transaction completed." << std::endl;
    }
    std::cout << std::string(52,'=') << std::endl;

}

void Bank::validate_account(std::string acc_id) {
    if(accounts.find(acc_id) == accounts.end())
        throw std::invalid_argument("Account not registured.");
}

void log_deposit(Account& acc,double amount) {
    std::ofstream file{"transaction.txt",std::ios::app};
    if(!file)
        throw std::runtime_error("Could not open transaction.txt");
    else   
        file << get_current_time() << "|" << "DEPOSIT" << "|-|" << acc.get_account_number() << "|" << amount << std::endl;
}

void Bank::withdraw() {
    std::cout << std::string(52,'=') << std::endl << std::endl;
    std::cout << "                       WITHDRAW" <<std::endl << std::endl;
    std::cout << std::string(52,'=') << std::endl;
    char action{};
    while(true){
        try{
            //Input valild id
            std::string acc_id = input_acc_id();
            validate_account(acc_id);
            auto& acc = accounts.at(acc_id);

            //Input valid amount.
            double amount = input_amount();
            acc.withdraw(amount);
            log_withdraw(acc,amount);
            break;
        }
        catch(const std::exception &e){
            std::cout << "[ERROR] " << e.what() << " (enter e to exit or n to re-enter): ";
            std::cin >> action;

            if(action == 'e')
                break;
            else if(action == 'n')
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    if(action != 'e'){
        std::cout << "transaction completed." << std::endl;
    }
    std::cout << std::string(52,'=') << std::endl;
}

void log_withdraw(Account& acc,double amount) {
    std::ofstream file{"transaction.txt",std::ios::app};
    if(!file)
        throw std::runtime_error("Could not open transaction.txt");
    else   
        file << get_current_time() << "|" << "WITHDRAW" << "|" << acc.get_account_number() << "|-|" << amount << std::endl;
}

double input_amount() {
    double amount;
    char action;
    while(true){
        try{
            std::cout << "Enter amount: ";
            if (!(std::cin >> amount)) {
                std::cin.clear();   // clear fail state
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("Invalid amount.");
            }
            //valid_amount(amount);
            break;
        }catch(const std::exception& e){
            std::cout << "[ERROR] " << e.what() << " (enter e to exit or n to re-enter): ";
            std::cin >> action;

            if(action == 'e')
                break;
            else if(action == 'n')
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    if(action != 'e'){
        return amount;
    }else{
        return 0;
    }
}

std::vector<std::string> split(const std::string& str,char spliter) {
    std::vector<std::string> ans;
    std::stringstream ss(str);
    std::string splited_elem;

    while(std::getline(ss,splited_elem,spliter)){
        ans.push_back(splited_elem);
    }

    return ans;
}