#include <iostream>
#include "Include/var++.hpp"

int main(){
    var Example = 25;
    Example = Example + "Str"; // that will remove .xxx
    std::cout << Example;
}