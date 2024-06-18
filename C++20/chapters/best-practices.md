## Best-Practices  

- Dopo aver [deallocato](./ripasso-new-delete.md) (*delete*) è good-practice settare puntatore a *nullptr*.
  
---
- [Regola d'oro della allocazione dinamica.](./concetti-base.md#7-regola-doro-della-allocazione-dinamica)
  
---
- Dichiarare ogni variabile/puntatore in new-line proprie piuttosto che tutte in una sola linea.  
In particolare è buona prassi associare il puntatore al tipo, piuttosto che alla variabile.  
```
long number {1256l};
long* pNumber {&number};
long *p1 {}, *p2 {};
```
  
---
- Evitare l'uso dei *magic numbers* ma usare piuttosto delle costanti:  
```
char materieDate[7]        // 7 è un magic numbers!!! [X]

const unsigned tot {7};     // codice più generico     [V]
char materieDate[tot];
```  
- Usare *using* al posto di *typedef*  
Entrambe le parole chiave hanno lo scopo di definire un alias ad un tipo fondamentale.  
La keyword *using* è semplicemente più facilmente leggibile rispetto la *typedef*.  
Per quanto possa sembrare superfluo, questa prassi ha invece molto senso nel caso si debba dichiarare una variabile di un tipo molto complesso alla lettura, ad esempio:  
`std::map< std::shared_ptr<Contact>, std::string >`  
Allora ecco che questo potrebbe diventare:  
```
using PhoneBook = std::map< std::shared_ptr<Contact>, std::string >;
PhoneBook rubrica;
```
  
---
- Usare meno *namespace*/*enumeration*/*using* possibile (o quanto più brevi possibile), in quanto in un team di sviluppo ognuno potrebbe usare stessi nomi su funzioni proprie, creando conflitti.  
    - Per quanto riguarda gli enum: è meglio usare gli *scoped enums* ovvero `enum class`  
    In questo modo ci si riferirà all'enum con uno scope diretto ' *::* '  
    ```
    enum class Day{
        Lunedi
        Martedi
        Mercoledi
        Giovedi
        Venerdi
        Sabato
        Domenica
    };

    Day oggi {Day::Mercoledi};
    ```
  
---