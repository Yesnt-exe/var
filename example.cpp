#include <iostream>
#include "Include/var++.hpp"

int main(){
try{
    var example = 25;

    std::cout << example << '\n'; // prints 25

    example += "a";

    std::cout << example << '\n'; // prints "25a"

    example = 25.555;

    std::cout << example << '\n'; // prints 25.555

    std::cout << example.fstr() << '\n'; //prints 25.555000
    return 0;
}
catch(VarException e){
    std::cout << e.what(); // if an exception occurs, this will tell what happened
    return 1;
}
}