#include <iostream>
#include "Include/var++.hpp"

int main(){
try{
    var example = 25;

    std::cout << example << '\n'; // should print 25

    example += "a";

    std::cout << example << '\n'; // should print "25a"

    example = 25.555;

    std::cout << example << '\n'; // should print 25.555

    std::cout << example.fstr() << '\n'; // should print 25.555000

    std::cout << Type(example) << std::endl; // should print Float

    example *= var(5);
    
    std::cout << example << '\n'; // should print 127.775
    
    example /= 5;
    
    std::cout << example << '\n'; // should print 25.555

    example %= 5;

    std::cout << example << '\n'; // should print 0.555

    example = "aaa";

    std::cout << example << '\n'; // should print aaa

    example += 'g';

    std::cout << example << '\n'; // should print aaag

    example += 42;

    std::cout << example << '\n'; // should print aaag*  * because 42 is ascii for *

    example = "t";

    example += VarFromNumeric(42);

    std::cout << example << '\n'; // should print t42 because i used VarFromNumeric

    //example %= 11; // should throw exception

    example = var(50, 60, 555, "gg"); // array initialization (allows multiple types always)

    example = std::vector<int>({5, 10, 15, 20, 25}); // array initialization (allows only specified type at initialization, can append multiple types)

    example = std::array<int, 2>{5,10}; //array initialization (allows only specified type and specified length at initialization, can append multiple types)

    std::cout << example << '\n';


}
catch(VarException e){
    std::cout << e.what(); // if an exception occurs, this will tell what happened
    return 0;
}
}