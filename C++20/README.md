# learning-cpp20
Apprendimento **personale** C++20;  
Best-practices, bad-practices, new functionalities and modern programming style.  
> N.b. Chiaramente saranno presentati unicamente quei concetti che non conosco o con cui non ho particolare dimestichezza.  
  
---
## Pre-requisiti
Un compilatore che supporti C++20:  
- ~~G++-11 o superiore~~
- MSVC 19.24 o superiore[^1]  
  
---
## Fonti
### *C++20*  
- [Beginning C++20](https://github.com/Apress/beginning-cpp20)
- [C++20 compiler support](https://en.cppreference.com/w/cpp/compiler_support#cpp20)
- [GCC support for C++20](https://gcc.gnu.org/projects/cxx-status.html#cxx20)
  
---
## Capitoli
- [Ripasso new-delete](./chapters/ripasso-new-delete.md)
- [Best-Practices](./chapters/best-practices.md)
- [C++ Standard Libraries](./chapters/cpp-standard-libraries.md)
- [Alcuni concetti base](./chapters/concetti-base.md)
- [Regola d'oro della allocazione dinamica](./chapters/concetti-base.md#7-regola-doro-della-allocazione-dinamica)
- ['auto' keyword](./chapters/auto-keyboard.md)
- [SmartPointer vs RawPointer](./chapters/smart-raw-pointers.md)
  
---
## Sorgenti
- [inizio.cpp](./source/1inizio.cpp)
  
---
## Idea progetto
- ???
- Contribuire al progetto [Barony](https://github.com/TurningWheel/Barony)
  
---
## TO-DO
- [x] Formattare per bene README
- [x] Sistemare .gitignore
- [x] Impostare ambiente di sviluppo per C++20
- [ ] Finire libro "Beginning C++20" ![Progress](https://progress-bar.dev/29/)
- [ ] Ideare un progetto sensato
- [ ] Migliorare suddivione in capitoli
- [ ] Iniziare sviluppo di un progetto
  
---
---
[^1]: #### Using the Visual Studio 2022 non preview version:  
    1. Create an empty C++ project
    2. Open project properties: Project → Properties
    3. Go to Configuration Properties → C/C++ → Language → and set the C++ Language Standard option to Preview - Features from the Latest C++
    4. In the same section, set Enable Experimental C++ Standard Library Modules to Yes (/experimental:module)
    5. Go to Configuration Properties → C/C++ → Advanced → and set the Compile As option to Compile as C++ Module Internal Partition (/internalPartition)
    6. Add header file to your project, which contains an import declaration for every standard library header you want to import. For example:
    ```
    #pragma once
    import <iostream>;
    import <array>;
    import <vector>;
    ```
    7. Recompile your project
    8. Done, now everything should work fine
  
---