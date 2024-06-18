## Smart Pointers vs Raw Pointer  

Tutti i tipi di puntatori discussi fin'ora fanno parte di quei puntatori 'old C' chiamati *raw pointers* in quanto essi non contengono altro che un indirizzo di memoria.  
Gli *smart pointers* forniscono invece più servizi, tra cui il non dover preoccuparsi di deallocare manualmente e molto altro che vedremo più avanti.  
GLi *smart pointers* sono definiti nella libreria `<memory>` e se ne distignuono tre tipi:  
- `unique_ptr<T>` l'oggetto si comporta come un puntatore di tipo T ed è 'unico' nel senso che non possono esserci più di un oggetto *unique_ptr* che punta ad uno stesso indirizzo di memoria allo stesso tempo.  
Ciò è possibile perchè il compilatore non permette la copia di un *unique_ptr*.  
- `shared_ptr<T>` 