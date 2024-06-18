## Ripasso *new* e *delete*  

```
double* pvalue {new double {3.14}};       //new ritorna un puntatore alla locazione creata
delete pvalue;
pvalue = nullptr;                         //dopo aver deallocato è good-practice settare puntatore a nullptr

double* data {new double[100] {}};          //alloca un array di 100 double inizializzati a 0
float* fdata{ new float[20] { .1f, .2f }};  //alloca un array di 20 float inizializzati a 0 tranne i primi 2

delete[] data;                  //...
delete[] fdata;                 //dealloca array dinamico, che sia unidimensionale, bi, tri, ecc...

data = nullptr;         //...
fdata = nullptr;        //reset the pointer
```  
Nonostante sia possibile definire anche array multidimensionali con qualche riga di codice:  
```
double** carrots{ new double*[rows] {} };
for (size_t i = 0; i < rows; ++i)
    carrots[i] = new double[columns] {};
...
for (size_t i = 0; i < rows; ++i)
    delete[] carrots[i];
delete[] carrots;
```
Questo genere di allocazione è sconsigliato in quanto allocherebbe memoria non-contiguamente. L'uso di metodi nativi come `<vector>` permette di evitare ciò. I processi tendono ad essere molto, molto più veloci quando lavorano su memoria contigua.
