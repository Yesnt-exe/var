## Var?
  -One type multiple uses, you can declare only one variable and set it to almost anything you want
  -Example: 
  ```c++
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

  ```
## Planned updates:
  Support for more dynamic allocation (now var uses minimum 80bytes per one variable on g++ 64). Easier IO with console and special library for easy file IO using var.
## Warning:
  if str() function is used with floating number it will return a version of that number with max 4 digits after . if you want better precision use fstr() or directly get value by longfloat() or customtype()
  all operators are using str() formatting when a floating number is combined with a string
