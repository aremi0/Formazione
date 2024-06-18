## Concetti Base  

### 1. Uso dei moduli:
`import <library>;`  
Ancora non supportato da *G++11*.
  
---
### 2. Modalità di inizializzazione:
- *braces*: `int appleCount {15.26}`      **(safer)**  
Non permette la perdità di dati (compile error), ad esempio: `int appleCount {15.26}` darebbe errore in quanto *15.26* non è *int*
- *functional*: `int orangeCount(4.32)`   **(warning cast)**  
- *assignment*: `int bananaCount = 6.12`  **(warning cast)**  
  
---
### 3. Assegnazioni letterali:
`unsigned long age {99ul}`  
Nonostante sia totalmente indifferente specificare al compilatore il suffisso letterale corretto, vi sono alcuni casi in cui esso è necessario; ad esempio quando si vuole inizializzare una variabile di tipo *auto*.
  
---
### 4. Cast Esplicito vs C-Style cast:
`static_cast<type_to_convert_to>(expression)` **vs** `(type_to_convert_to)expression`  
La keyword *static_cast* si riferisce al fatto che il cast è verificato compile-time. Più avanti, quando si parlerà di classi, verrà introdotto il *dynamic_cast* in cui la conversione viene verificata run-time.  
In generale il casting dovrebbe essere una necessità rara. Nel caso in cui fosse necessario allora sarebbe bene usare la sintassi del cast esplicito (static o dinamic), piuttosto che il C-Style o il cast implicito.  
`y = static_cast<int>(z);`  
`y = (int)z`
  
---
### 5. Range-Base for loop:
```
int values [] {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
int total {};
for (auto x : values)
    total += x;
```
Un range può essere definito da un array ma anche da una stringa. *x* assumerà man mano ogni valore in *values*.
  
---
### 6. Puntatori e costanti:  
```
const char* pstars[] {
    "Fatty Arbuckle", "Clara Bow", "Lassie",
    "Slim Pickens", "Boris Karloff", "Mae West",
    "Oliver Hardy", "Greta Garbo"
    };

*pstars[0] = 'X';        // Will not compile...
pstars[5] = pstars[6];   // OK... cioè posso far puntare p[5] a p[6], non contravvenendo alla specifica const
```  
```
const char* const pstars[] {
    "Fatty Arbuckle", "Clara Bow", "Lassie",
    "Slim Pickens", "Boris Karloff", "Mae West",
    "Oliver Hardy", "Greta Garbo"
    };

//in questo caso invece l'extra const successivo al tipo andrà a definire che; sia gli indirizzi che i valori saranno costanti e immutabili
```  
To summarize, you can distinguish three situations that arise using const when applied to pointers and the things to which they point:  
- A pointer to a constant: You can’t modify what’s pointed to, but you can set the pointer to point to something else.  
- A constant pointer: The address stored in the pointer can’t be changed. A constant pointer can only ever point to the address that it’s initialized with. However, the contents of that address aren’t constant and can be changed. Suppose you define an integer variable data and a constant pointer pdata.  
- A constant pointer: The address stored in the pointer can’t be changed. A constant pointer can only ever point to the address that it’s initialized with. However, the contents of that address aren’t constant and can be changed. Suppose you define an integer variable data and a constant pointer pdata.
  
---
### 7. Regola d'oro della allocazione dinamica:
*Never use the operators new, new[], delete, and delete[] directly in day-to-day coding. These operators have no place in modern C++ code. Always use either the **std::vector<>** container (to replace dynamic arrays) or a **smart pointer** (to dynamically allocate individual objects and manage their lifetimes). These high-level alternatives are much, much safer than the low-level memory management primitives and will help you tremendously by eradicating dangling pointers, multiple deallocations, allocation/deallocation mismatches, and memory leaks from your programs.*
  
---
