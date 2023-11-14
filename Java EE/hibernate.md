# note spring-hibernate

Hibernate è un ORM (Object Relational Mapping) che si occupa di mappare i tipi di dato Java con i tipi di dato SQL.
Con persistence in ava di intendono tutte quelle collezioni di dati delle classi e dei metodi Java che memorizzano in modo persistente (resistente a riavvii) all'interno del database in modo continuo.

Hibernate è l'implementazione dell'interfaccia JPA (Java Persistence Api) utilizzata come standard per definire il mapping tra oggetti-relazioni tramite l'utilizzo di annotazioni.

## Architettura JPA
Persistente (javax.persistence)
    |
    |
EntityManagerFactory ---> Persistence Unit
    |
    |            ---> EntityTransaction
EntityManager ---|
    |            ---> Query
    |
Entity

## JDBC
JDBC (java Database Connectivity) fornisce una serie di API Java per l'interazione con i database.

## Vantaggi di Hibernate
- Supporta la mappatura tra oggetti e tabelle relazionali e viceversa con la possibilità di eseguire operazioni CRUD.
- Elimina tutto il codice stndard di JDBC occupandosi anche della gestione delle risorse tale che il programmatore dovrà occparsi soltanto della logica di business (Service).
- Supporta la gestione delle transazioni ed assicura che non ci siano dati incoerenti.

## Annotazioni
- @Entity, viene utilizzata per contrassegnare una classe come Entità bean che può essere resa persistente all'interno del database da Hibernate.
- @Table, viene utilizzata per definire la mappatura tra una entità e la tabella nel database.
- @Id, utilizzata su una variabile d'istanza e serve a indicare che tale attributo è una chiave primaria per la relativa tabella nel DB.
- @GeneratedValue, indica che il calore del campo viene generato automaticamente.
- @Column, serve per mappare la variabile d'istanza in una colonna della tabella nel DB.

## Hibernate Session
E' l'interfaccia che si frappone tra l'applicazione Java e il framework Hibernate, che permette di definire i seguenti metodi:
- save(...)
Questo metodo è utilizzato per salvare le entità nel database, ma può essere usato anche al di fuori di una transazione. Ciò significa che se sono presenti delle relazioni a cascata tra entità o se vengono effettuate delle modifiche quando non è presente la transazione, la save() permette di salvare solo l'entità primaria a meno che non scarichiamo la sessione e non salva le modifiche.

### Transazione
Una transazione è una sequenza di operazioni che funzionano in maniera atomica, essa infatti può essere considerata completata soltanto quando tutte le operazioni che la compongono sono state completate correttamente. Soddisfa le proprietà ACID.

- persist(...)
E' simile al metodo save() ma permette di salvare anche eventuali modifiche se esse sono apportate prima del commit o prima del flush() (svuotamento) della sessione.
Di conseguenza questo obbliga a usare il metodo persist() all'interno dei limiti di una transazione e tale metodo alla fine della propria esecuzione non restituisce nulla (a differenza di save() che ritorna invece l'oggetti salvato).

- update(...)
E' utilizzato quando vogliamo solamente modificare le informazioni di una entità.

- merge(...)
Permette di aggiornare i valori esistenti e ritorna lo stesso oggetto che gli viene passato in input. Permette di monitorare l'oggetto per eventali aggiornamenti futuri.

## Differenza tra save() e persist()
- persist() ritorna null, save() ritora l'oggetto serializzabile.
- persist non garantisce che venga assegnato l'identificativo all'istanza in modo immediato, ma l'assegnazione potrebbe avvenire dopo.
- save effettua l'insert nel database anche fuori da una transazione mentre persist no, lo effettua solamente all'interno.

### Serializzazione
Serializzare un oggetto significa trasformarlo in array di bit per la sua trasmissione o archiviazione.

## Contesto di persistenza
Hibernate utilizza il contesto di persistenza pe gestire il ciclo di vita dell'entità. E' come una cache in cui tutte le entità vengono depositate e prelevate dal database passano. Tiene traccia di tutte le modifiche che vengono effettuate alle entità e se qualcosa dovesse cambiare durante una transazione essa viene etichettata come sporca.
Al termine della transazione le modifiche vengono salvate nella memoria permanente.

Esistono due tipi di Contesti di Persistenza:
- Nell'ambito della transazione. (Default)
- Nell'ambito esteso.

Il primo è legato alla transazione, per cui appena essa termina le entità presenti nel contesto verrano scaricate nella memoria principale.
Il secondo tipo invece può estendersi a più transazioni.
```java
@PersistenceContext         (default)
private EntityManager em;

@PersistenceContext(type = PersistenceContextType.EXTENDED)
private EntityManager em;
```

# Hibernate Criteria
Hibernate Criteria è una API semplificata per il filtraggio delle query SQL:
```java
CriteriaBuilder cb = em.getCriteriaBuilder()
CriteriaQuery<Person> criteria = cb.createQuery(Person.class);
Root<Person> root = criteria.from(Person.class);

// posso aggiungere dinamicamente where, senza scrivere oscenità come 'where 1=1'

criteria.where(cb.equal(root.get("name"), "CHANGE"));
List<Person> personList = em.createQuery(criteria).getResultList();
```

Nella Criteria API sono presenti due oggetti principali che possono essere utilizzati per creare le query SQL, ovvero l'oggetto CriteriaBuilder e un oggetto CriteriaQuery.
Il primo passaggio consiste nel gestire un oggetto CriteriaBuilder che funge da factory principale delle criteria query e dei suoi elementi, e quindi creare un oggetto CriteriaQuery.

## CriteriaQuery
Ci consente di scrivere query senza utilizzare raw SQL e ci dà un controllo orientato agli oggetti sulle query (una delle caratteristiche principali di Hibernate).

## CriteriaBuilder
E' una interfaccia utilizzata per costruire criteria query, selezioni composte, espressioni, predicati e ordinamenti.
Presenta diversi metodi di espressione (equal, notEqual, like, ...) e metodi predicati (and, or, not).

## Predicate
Serve per costruire clausole where
```java
Predicate predicateForBlueColor = cb.equal(root.get("eyeColor"), "blue");
```

## TypedQuery
Offre una opzione per assegnare il tipo di entità quando si crea una query e quindi qualsiasi operazione successiva non necessita di un cast esplicito al tipo previsto. JpaRepository usa internamente TypedQuery che è una sottoclasse di Query.

## Query (nativo)
Si riferisce alle query sql effettive. Queste query sono le istruzioni qsl che possono essere direttamente eseguite sul DB.
```java
@Query(value = "SELECT * FROM Users u WHERE u.status = :status", nativeQuery = true)
User findUserByStatus(@Param("status") Integer status);
```

# Metodi di EntityManager

## unwrap
Abbiamo definito che all'apertura di un EntityManager viene aperto, se non esiste già, anche un contesto di persistenza: stiamo lavorando le entità con uno strato che ogni volta che nota una modifica all'entità si sincronizza al db automaticamente senza effettuare save() o update().

Questo perchè all'interno di un Contesto di Persistenza esiste una Session "che non vediamo" associata all'EntityManager in uso ed una volta fatta la modifica si attiva e persiste le modifiche per noi. Va da sè che chiudendo l'EntityManager, chiudiamo anche la sessione ad esso associata.

Possiamo avere accesso alle API di Hibernate tramite JPA ed ottenere la Session corrente di un EntityManager o la sua SessionFactory attraverso il metodo unwrap.

```java
Session session = entityManager.unwrap(Session.class);
SessionFactory sf = entityManager.getEntityManagerFatory().nwrap(SessionFactory.class);
```

## persist
Operazione attraverso il quale si effetta un inserimento di dati nel database all'interno di una transazione. Equivalente al session.save() di Hibernate.

## getDelegate
Restituisce l'oggetto provider sottostante per EntityManager. Ad esempio, possiamo ottenere un oggetto Session usando un EntityManager.

## Differenze tra unwrap e getDelegate
- getDelegate() resituisce un tipo dipendente dalla classe di implementazione, mentre unwrap() un tipo specifico per consentire l'accesso all'API specifica del provider.
- unwrap() genera una java.lang.IllegalStateException se la sessione è chisa, getDelegate() no.

# merge
Operazione attraverso il quale si inseriscono/modificano i dati sul database all'interno di una transazione. Equivalente di session.saveOrUpdate() di Hibernate.

# contains
Permette di contrikkare se una untità si trova nello stato di managed.

# flush e commit
Con la flush() lo stati di persistenza di Hibernate di sincronizza con il database, comunicandogli le operazioni di insert, update, e delete edìffettuate e non ancora persistite.
Quest sono ora in sospeso. E' soltanto con la commit che i dati dentro una transazione vengono scritti sul database.
Una flush() è sempre chiamata come parte di una commit()