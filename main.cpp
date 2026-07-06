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

    Bank bank;
    /*
    Account acc1("1111111111111");
    Account acc2("2222222222222");

    std::cout << acc1 << '\n' << acc2 << std::endl;
    Mikorn.transfer(acc1,acc2,500);
    std::cout << acc1 << '\n' << acc2 << std::endl;

    */
    bank.make_customer();
    bank.make_account();

    bank.make_customer();
    bank.make_account();

    bank.show();

    bank.log_accounts();

    return 0;
}