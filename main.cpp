#include <iostream>
#include <vector>
#include <string>

#include "customer.hpp"

int main(){
    //Loop to get all attributes of customer with exception handling.
    Customer customer;
    std::cout << customer;
    std::cout << customer.get_email() << " " << customer.get_id() << std::endl;

    return 0;
}