#include <iostream>
#include <vector>
#include <string>

#include "customer.hpp"

int main(){
    //Loop to get all attributes of customer with exception handling.
    Customer c1{"6767","Timothy","Dan","Hines","2981","timothydanhines@gmail.com"};

    std::cout << c1 << std::endl;
    std::cout << c1.get_name() << c1.get_pin() << c1.get_id() << std::endl;
    

    return 0;
}