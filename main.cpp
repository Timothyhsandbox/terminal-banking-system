#include <iostream>
#include <vector>
#include <string>

#include "bank.hpp"
#include "account.hpp"
#include "customer.hpp"

int main(){
    //Loop to get all attributes of customer with exception handling.
    /*
    Customer customer;
    std::cout << customer;
    std::cout << customer.get_email() << " " << customer.get_id() << std::endl;
    */

    Account acc;
    std::cout << acc << std::endl;
    acc.deposit(1000.058);

    std::cout << acc << std::endl;
    acc.withdraw(500);
    std::cout << acc << std::endl;

    return 0;
}