# PL/SQL: Guida by aremi

## Tipi di comandi in SQL:

- **DML** è l'insieme di comandi utilizzati per **aggiungere, modificare o eliminare** i dati da un database. In SQL, i comandi DML includono `INSERT`, `UPDATE`, e `DELETE`.
  
- **DDL** comprende i comandi responsabili della **creazione, modifica e eliminazione** delle strutture di dati, come le tabelle. I comandi DDL principali sono `CREATE TABLE`, `ALTER TABLE`, e `DROP TABLE`.

- **DQL** (Data Query Language): Utilizzato per **leggere e interrogare** i dati, principalmente attraverso il comando `SELECT`.
  
- **DCL** (Data Control Language): Gestisce le **autorizzazioni e il controllo di accesso** ai dati, con comandi come `GRANT` e `REVOKE`.
  
- **TCL** (Transaction Control Language): Gestisce le **transazioni** nel database, con comandi come `COMMIT` e `ROLLBACK`.

In PL/SQL, che è l'estensione procedurale di SQL fornita da Oracle, troverai anche acronimi come:

- **NO COPY**: Un parametro che può **migliorare le prestazioni** passando grandi quantità di dati nei parametri `OUT`.

Questi acronimi aiutano a categorizzare le diverse operazioni che si possono eseguire su un database SQL e PL/SQL, rendendo più semplice la comprensione e l'applicazione dei vari comandi.

## Schema:
In PL/SQL, il termine "SCHEMA" si riferisce a un **contenitore logico** che raggruppa strutture di dati, chiamate **oggetti di schema**. Ogni account utente di Oracle Database possiede uno schema che ha lo stesso nome dell'utente. Gli oggetti di schema possono includere tabelle, viste, sequenze, sinonimi, indici, procedure, funzioni, package, trigger e altri elementi che costituiscono la struttura e l'organizzazione dei dati all'interno del database.

Lo schema è quindi una sorta di **spazio di lavoro** o **ambiente** che contiene tutti gli oggetti creati dall'utente e che definiscono il database. È importante per organizzare e gestire i dati in modo efficiente e per implementare la sicurezza, garantendo che solo gli utenti autorizzati possano accedere o modificare gli oggetti di schema.

## Blocchi:
I blocchi in PL/SQL sono unità fondamentali di codice che raggruppano dichiarazioni e istruzioni correlate. Un blocco PL/SQL ha una struttura predefinita con tre parti principali:

1. **Sezione Dichiarazioni**: Questa sezione è opzionale e viene utilizzata per dichiarare variabili, cursori, eccezioni e altri oggetti necessari nel blocco. Inizia con la parola chiave `DECLARE`¹.

2. **Sezione Esecuzione**: È la parte obbligatoria del blocco che contiene il codice PL/SQL e SQL eseguibile, come la logica di business. Questa sezione inizia con la parola chiave `BEGIN` e deve contenere almeno una riga di codice eseguibile¹.

3. **Sezione Gestione delle Eccezioni**: Anche questa sezione è opzionale e serve a gestire le eccezioni che possono verificarsi durante l'esecuzione del blocco. Inizia con la parola chiave `EXCEPTION`¹.

Il blocco si conclude sempre con la parola chiave `END`. I blocchi possono essere anonimi, cioè senza un nome, oppure possono essere nominati quando formano il corpo di una procedura, funzione o trigger².

Ecco un esempio di blocco PL/SQL anonimo:

```plsql
DECLARE
  -- Sezione dichiarazioni (opzionale)
  v_numero NUMBER;
BEGIN
  -- Sezione esecuzione (obbligatoria)
  v_numero := 10;
  DBMS_OUTPUT.PUT_LINE('Il numero è: ' || v_numero);
EXCEPTION
  -- Sezione gestione delle eccezioni (opzionale)
  WHEN OTHERS THEN
    DBMS_OUTPUT.PUT_LINE('Si è verificato un errore.');
END;
```

In questo esempio, viene dichiarata una variabile, assegnato un valore e stampato il risultato. Se si verifica un'eccezione, verrà gestita nella sezione `EXCEPTION`.

### Tipi di Blocchi:
In PL/SQL, esistono principalmente due tipi di blocchi:

1. **Blocchi Anonimi**: Sono blocchi di codice che non hanno un nome e vengono eseguiti immediatamente. Non vengono salvati nel database e sono utili per eseguire rapidamente comandi o test¹.

2. **Blocchi con Nome**: Questi includono procedure, funzioni, trigger e pacchetti che sono memorizzati nel database. I blocchi con nome possono essere richiamati e riutilizzati, e sono fondamentali per la creazione di applicazioni modulari e riutilizzabili².

   - **Procedure**: Sono sottoprogrammi che eseguono azioni specifiche e possono accettare parametri in ingresso e restituire valori.
   - **Funzioni**: Simili alle procedure, ma sono progettate per restituire un singolo valore.
   - **Trigger**: Sono blocchi che vengono automaticamente eseguiti in risposta a determinati eventi nel database, come inserimenti, aggiornamenti o cancellazioni.
   - **Pacchetti**: Sono collezioni di procedure, funzioni e variabili globali che consentono di raggruppare logicamente elementi correlati.

Ecco un esempio di blocco anonimo in PL/SQL:

```plsql
BEGIN
  -- Codice eseguibile
  DBMS_OUTPUT.PUT_LINE('Questo è un blocco anonimo.');
END;
```

E un esempio di procedura (blocco con nome):

```plsql
CREATE PROCEDURE SalutaUtente
AS
BEGIN
  DBMS_OUTPUT.PUT_LINE('Ciao, utente!');
END SalutaUtente;
```

I blocchi con nome come le procedure devono essere prima creati nel database e poi possono essere eseguiti con una chiamata separata.

---

## Variabili
### Naming Conventions per PL/SQL:
Le convenzioni di denominazione in PL/SQL sono importanti per mantenere il codice organizzato e facilmente comprensibile. Ecco alcune linee guida generali¹²⁴⁵:

- **Lunghezza**: I nomi devono essere brevi ma descrittivi, il limite massimo è di 30 caratteri.
- **Caratteri iniziali**: I nomi devono iniziare con una lettera ASCII, maiuscola o minuscola.
- **Case Unsensitive**: I nomi sono case unsensitive.
- **Caratteri consentiti**: Dopo il primo carattere, possono essere utilizzati numeri, il carattere di sottolineatura (_) e il segno del dollaro ($).
- **Parole chiave**: Evitare l'uso di parole chiave riservate di PL/SQL come nomi di variabili o oggetti.
- **Casi**: Anche se PL/SQL non è case-sensitive, è comune usare maiuscole per le parole chiave (es. `BEGIN`, `EXCEPTION`, `END`) e minuscole per i nomi di variabili e procedure.
- **Prefissi e suffissi**: Utilizzare prefissi o suffissi coerenti per identificare il tipo di oggetto, come `_tbl` per le tabelle o `_pk` per le chiavi primarie.
- **Nomi qualificati**: Utilizzare nomi qualificati per evitare ambiguità, specialmente quando si lavora con più schemi o database.

Ecco un esempio di come potrebbero essere utilizzate queste convenzioni:

```sql
-- Variabili
v_employee_id NUMBER;
v_full_name VARCHAR2(100);

-- Variabili di Bind
b_employee_id NUMBER;

-- Costanti
c_max_salary CONSTANT NUMBER := 10000;

-- Cursori
CURSOR cur_employee IS SELECT * FROM employees;

-- Exception
e_value_error EXCEPTION;

-- Funzioni
FUNCTION calculate_bonus_fun(p_employee_id NUMBER) RETURN NUMBER IS
BEGIN
    -- Corpo della funzione
END calculate_bonus_fun;

-- Procedure
PROCEDURE p_calculate_bonus IS
BEGIN
    -- Corpo della procedura
END p_calculate_bonus;

-- Packages
PACKAGE pkg_employee_management IS
    -- Specifica del package
END pkg_employee_management;
```

### Variabili e Bind-Variable; differenza:
Le variabili normali sono utilizzate all'interno del codice PL/SQL per memorizzare dati temporanei. Sono dichiarate nella sezione di dichiarazione di un blocco PL/SQL e il loro scopo è di contenere valori che possono essere modificati durante l'esecuzione del blocco.

Le variabili di bind, invece, sono utilizzate per passare valori da e verso il database in istruzioni SQL dinamiche o in blocchi PL/SQL. Queste variabili agiscono come segnaposto all'interno di un'istruzione SQL o PL/SQL e sono legate a valori effettivi al momento dell'esecuzione. L'uso delle variabili di bind può migliorare le prestazioni perché permette al database di riutilizzare i piani di esecuzione SQL.

In PL/SQL, quando si utilizzano variabili normali in un'istruzione SQL statica all'interno di un blocco PL/SQL, queste vengono trattate come variabili di bind dal compilatore PL/SQL. Questo significa che non è necessario distinguere esplicitamente tra le due quando si scrive codice PL/SQL. Tuttavia, la distinzione diventa importante quando si utilizza SQL dinamico o si interagisce con il database da un'applicazione esterna, come Java o C#.

Ecco un esempio che mostra la differenza nell'uso:

```sql
-- Variabile normale in PL/SQL
DECLARE
  v_empno NUMBER := 7369;
  v_ename VARCHAR2(10);
BEGIN
  SELECT ename INTO v_ename FROM emp WHERE empno = v_empno;
  DBMS_OUTPUT.PUT_LINE(v_ename);
END;
```

```sql
-- Variabile di bind in SQL dinamico
DECLARE
  v_sql VARCHAR2(100);
  v_empno NUMBER := 7369;
  v_ename VARCHAR2(10);
BEGIN
  v_sql := 'SELECT ename FROM emp WHERE empno = :1';
  EXECUTE IMMEDIATE v_sql INTO v_ename USING v_empno;
  DBMS_OUTPUT.PUT_LINE(v_ename);
END;
```

Nel primo esempio, `v_empno` è una variabile normale che viene automaticamente trattata come una variabile di bind dal compilatore PL/SQL. Nel secondo esempio, `v_empno` è esplicitamente utilizzata come una variabile di bind in un'istruzione SQL dinamica.

### Variabili, altre cose da sapere
- La concatenazione tra due stringhe avviene per mezzo dell'operatore `||`. Per esempio `v_text := ' PL\SQL' || ' COURSE';`
- NUMBER(*precision*, *scale*) è un tipo primitivo in cui *precision* indica il minimo del numero totale di cifre che può contenere la variabile, mentre *scale* il minimo della precisione decimale. Per esempio `v_number NUMBER(2, 2) := 50.12` darà errore perchè il numero totale di cifre è almeno 4 (si considera anche la parte decimale), la dichiarazione corretta sarebbe `v_number NUMBER(4, 2) := 50.12`, mentre `v_number NUMBER(4, 1) := 50.12` tronca alla prima cifra decimale `50.1`.
- PLS_INTEGER, BINARY_FLOAT e BINARY_DOUBLE: questi formati sono più veloci di NUMBER(p, s), all'assegnazione di un BINARY_FLOAT o BINARY_DOUBLE bisogna inserire 'f' o 'd' dopo la cifra `v_number BINARY_FLOAT := 50.12f`.
- `SYSDATE` e `SYSTIMESTAMP` ritornano da data di adesso con diversa precisione.
- DATE: contiene la data gg-MM-yy, `v_date DATE NOT NULL := SYSDATE`. 
- TIMESTAMP: contiene la data gg-MM-yy hh:mm:ss.sss, `v_date TIMESTAMP NOT NULL := SYSTIMESTAMP`. 
- INTERVAL è un tipo primitivo che serve per misurare quanti giorni in secondi o mesi in anni sono passati. Per esempio

### Attributo `%TYPE`
In PL/SQL, `%TYPE` è un attributo che consente di dichiarare una variabile per essere dello stesso tipo di dati di una colonna di una tabella del database o di un'altra variabile già dichiarata. Questo è particolarmente utile per mantenere la consistenza dei tipi di dati e per adattarsi automaticamente ai cambiamenti di schema delle tabelle del database.  
<big><u>Attenzione</u></big>, se la colonna è dichiarata come `NOT NULL` la variabile dichiarata con `%TYPE` può comunque contenere `NULL`.

Ecco alcuni punti chiave su `%TYPE`:
- **Consistenza dei tipi di dati**: Utilizzando `%TYPE`, puoi assicurarti che la variabile sia sempre dello stesso tipo della colonna a cui si riferisce¹.
- **Manutenibilità**: Se il tipo di dati di una colonna cambia, non devi modificare manualmente il tipo di dati delle variabili PL/SQL correlate¹.
- **Leggibilità del codice**: Rende il codice più leggibile e chiaro, poiché è evidente a quale colonna di tabella si riferisce la variabile¹.

La sintassi per usare `%TYPE` è la seguente:
```plsql
DECLARE
  v_variable table.column_name%TYPE;
BEGIN
  -- Il tuo codice PL/SQL qui
END;
```

Per esempio, se hai una tabella `dipendenti` con una colonna `stipendio` di tipo `NUMBER`, puoi dichiarare una variabile `v_stipendio` che abbia lo stesso tipo di dati della colonna `stipendio` così:
```plsql
DECLARE
  v_stipendio dipendenti.stipendio%TYPE;
BEGIN
  -- Il tuo codice PL/SQL qui
END;
```

In questo modo, `v_stipendio` sarà di tipo `NUMBER`, e se in futuro il tipo di dati della colonna `stipendio` cambiasse, `v_stipendio` si adatterebbe automaticamente al nuovo tipo.

