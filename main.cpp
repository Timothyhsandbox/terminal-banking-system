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

    Bank Mikorn;
    Account acc1;
    Account acc2;
    
    std::cout << acc1 << '\n' << acc2 << std::endl;
    Mikorn.transfer(acc1,acc2,500);
    std::cout << acc1 << '\n' << acc2 << std::endl;

    return 0;
}