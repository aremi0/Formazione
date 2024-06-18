## C++ Standard Libraries:  

- `include <iostream>;` gestione input/output  
    *cout <<*, *cin >>*, ...
  
---
- `include <array>;` metodi oggetti array a dimensioni fisse `array<T,N>`  
    *std::size(my_array)* o *values.size()*, *values.at(i)*, ...  
    `std::array<double, 100> values {};` crea un array di 100 double  
    E' possibile comparare due oggetti *array<>* con gli operatori di confronto (==, >=, ...)
  
---
- `include <vector>;` metodi oggetti array a dimensioni variabili `array<T>`  
```
//std::vector<double> values(20, 99);     // Vector contains 20 double values - all 99
std::vector<double> values(20);           // Vector contains 20 double values - all zero
values.push_back(3.1415);                 // Add an element to the end of the vector
values.clear(), std::erase(values, 7), values.pop_back(), ...
```  
E' importante notare come venga usata la functional initialization piuttosto che la braces, in quanto quest'ultima apporterebbe un significato diverso:  
`std::vector<long> numbers{20, 99L};   // Vector contains 2 long values: 20 and 99`
  
---
- `include <cctype>;` funzioni stringhe  
    *std::isalpha()*, *std::tolower()*, ...
  
---
- `include <numbers>;` funzioni matematiche  
    *std::numbers::pi*, *sqrt()*, ...
  
---
- `include <iomanip>;` manipolatori io stream  
    *std::fixed* << *std::setprecision(20)*
  
---
- `include <memory>;` [smart-pointer](./smart-raw-pointers.md)
  
---
  