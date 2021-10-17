## Var?
  -One type multiple uses, you can declare only one variable and set it to almost anything you want
  -Example: 
  ```c++
  #include <iostream>
  #include "var++.hpp"
  
  int main(){
  var Example = 25;
  Example = Example + "str";
  std::cout << Example; // Output: "25str" 
  }
  
  ```
## Planned updates:
  For now var supports only std::string, and builtin data types but i will add support for:
    - std::vector
    - std::map
    and more...
## Warning!
  If you use += instead of a = a + b then ".xxx" will appear in a number converted to string. 
  It will be fixed in next update
