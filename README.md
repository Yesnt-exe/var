## Var?
  -One type multiple uses, you can declare only one variable and set it to almost anything you want
  -Example: 
  ```c++
  #include <iostream>
  #include "var++.hpp"
  
  int main(){
  var Example = 25;
  Example += "str";
  std::cout << Example; ("25.000000str"); // that 25.xxxstr will be fixed in next update
  }
  
  ```
## Planned updates:
  For now var supports only std::string, and builtin data types but i will add support for:
    - std::vector
    - std::map
    and more...
