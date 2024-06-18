## *'auto'* keyboard  

La parola chiave *auto* indica che sarà il compilatore a dedurre il tipo di una variabile. Ad esempio:  
```
auto m {10};                    //m sarà int
auto n {200ul};                 //m sarà unsigned long
auto p {std::numbers::pi};      //p sarà double

auto* pdata {new std::vector<int>{}};       //pdata sarà un puntatore di tipo vector<int>
(*pdata).push_back(66);                     //add an element containing 66
pdata->push_back(67);                       //add an element containing 67
```
Ad ogni modo non è esattamente questo l'uso per cui è stata pensata la keyword *auto*, nel definire delle variabili di tipo fondamentale è infatti consigliato specificare esplicitamente il tipo. Questa keyword verrà invece usata appropriatamente più avanti.  
L'inizializzazione *braces* è inoltre sconsigliata nel caso di variabili *auto* in quanto, in base alla versione del compilatore, *auto* ritorna tipi differenti:
- C++11 and C++14:
`auto i {10};       // i has type std::initializer_list<int> !!!`
- C++17 e successivi:
`auto i {10};       // i has type int`
  