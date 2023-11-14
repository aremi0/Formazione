## Annotazioni

- @ControllerAdvice
Si utilizza per definire un metodo dentro un controller MVC per gestire le eccezioni
```java
@ControllerAdvice
public class MyController {
    // ...
    @ExceptionHandler(value = { CustomException1.class, CustomEsception2.class })
    public void handleException() {
        // ...
    }
}
```

- @ResponseStatus
```java
@ResponseStatus(value = HttpStatus.NOT_FOUND)
public class MyResourceNotFoundException extends RuntimeException
```
permette di mappare le eccezioni dall'applicativo su determinati httpStatus_code.


- @Autowired
Utilizzata per eseguire l'iniziezione di dipendenze automaticamente. Il framework cerca un bean corrispondente nel suo ApplicationContext e lo inietta automaticamente nel componente annotato.

- @Inject
Simile a @Autowired ed è uno standard Java EE per l'iniezione delle dipendenze.

- @Qualifier
Può essere utilizzata esclusivamente in combinazione con @Autowired, viene usato quando ci sono più implementazioni di una interfaccia o di una classe

---

- Differenze tra @Autowired e @Inject
1) @Autowired esiste soltanto nel framework Spring, @Inject invece è uno standard di Java EE.
2) @Autowired offre maggiore flessibilità e configurabilità rispetto a @Inject perchè può essere usato in combinazione con @Qualifier.
3) @Autowired pporta riferimenti incrociati automatici, i Bean possono quindi riferirsi l'un l'altro senza causare una dipendenze circolari perchè in qualche modo le Spring le gestisce (attraverso lazy ecc...). Con @Inject le dipendenze circolari vanno risolte manualmente.
4) @AUtowired permette di gestire anche le dipendenze opzionali attraverso un parametro booleano *required* (@Autowired(reuired = false)), con @Inject non è possibile.


---

http request
GET
The GET method requests a representation of the specified resource. Requests using GET should only retrieve data.

HEAD
The HEAD method asks for a response identical to a GET request, but without the response body.

POST
The POST method submits an entity to the specified resource, often causing a change in state or side effects on the server.

PUT
The PUT method replaces all current representations of the target resource with the request payload.

DELETE
The DELETE method deletes the specified resource.

CONNECT
The CONNECT method establishes a tunnel to the server identified by the target resource.

OPTIONS
The OPTIONS method describes the communication options for the target resource.

TRACE
The TRACE method performs a message loop-back test along the path to the target resource.

PATCH
The PATCH method applies partial modifications to a resource.



Programmazione dichiarativa
Convention over Configuration:




Spring nasce per lo svilppo di applicazioni enterprise, ovvero per applicazioni aziendali, bancarie o finanziarie.

In una app spring abbiamo un nucleo (core) con le funzioni principali e poi tutta una serie di moduli (sicurezza, data, web, jpa, clod, ...)

L'obiettivo è la massima riusabilità del codice e ridurre al massimo l'accoppiamento tra i vari componenti, seguendo l'idea dell'inversion of control, tilizzando come implementazione la dependency injection.

spring boot ha permesso di semplificare notevolmente la creazione di applicazioni spring. Sprngboot è semlicemente un modulo di sring che semplifica la creazione di applicazioni spring.

Il problema elle dipendenze: immaginiamo una classe veicolo che al suo interno utilizza una istanza della classe motore. Il probblema è che si crea in questo modo un forte accoppiamento tra le due classi, ovvero una dipendenza perchè la classe veicolo dipende dalla classe motore. Mentre infatti la classe motore è "libera" la classe "veicolo" ha una dipendenza con la classe "motore".
L'inversion of control dice che anzichè creare le dipendenze all'interno della classe che ne ha bisogno, la creazione o la gestione completa di queste dipendenze viene delegata a una qualche entità che è al di fuori della classe, in qesto caso a spring. L'inversione del controllo avviene perchè la calsse veicolo ha ancora bisogno della classe motore, ma non si creerà più l'istanza di cui ha bisogno ma sarà spring a gestire la dipendenza.

La dependency Injection è una implementazione del pattern dell'inverion of control, cioè è una delle tante modalità per applicare la inversion of control.
L'inserimento dela dipendenza avviene in maniera automatica, gestita da spring. Esistono più modi per applicare l'iniezione. In questo modo possiamo disaccoppiare le due classi. 

Un Bean è ostanzialmente un oggetto il cui ciclo di vita è gestito direttament dal framework Spring. Qesto vuol dire che un bean è una istanza di una classe che viene creta, gestita e distrutta dal framework. queste istanze non saranno create direttamente dal programmatore ma lasceremo a Spring di fare tutte queste peraizoni, il nostro compito sarà quello di dichiarare la necessità di utilizzare determinati oggetti (bean) e lascaire a spring tutto il resto.

Come fa spring a sapere quali sono i Bean che deve gestire. Le modalità sono due:
1. definire una classe e definirla con la annotazione stereotipo @Component (@Controller, @RESTController, @Service, @Repository, ...), in quest modo andremo a dire a spring che quella classe è un componente, quindi spring andrà a gestire quella classe attraverso l'Application Context.
2. definire dei Bean usando la notazione @Bean. Si crea una classe e la si annota con @Configuration, dopodichè ciascun metodo che andrà ad istanziare la classe di cui abbiamo bisogno dovrà essere annotato @Bean.

Questi Bean una volta creati da spring  a vivere all'interno di un'area chiamata IoC-Container (inversion of control container) ed esistono delle interfacce con cui possiamo interagire, la più potente è appunto l'Application Context. Con SpringBoot buona parte delle operazioni che vedremo saranno poi trasparenti.

Scope dei Bean; Normalmente Spring crea una sola istanza per ciascun Bean, ovvero la modalità di default di spring per la creazione dei Bean è la modalità Singleton. Oni qual volta andremo a referenziare quel Bean di fatto andremo a lavorare sempre sulla stessa istanza.
Quindi dei Bean generati da una classe in realtà esisterà una sola istanza che verrà condivisa tra tutte le classi che usano quel Bean. Ciò è modificabile andando a lavorare sullo Bean Scope, permettendoci, ad esempio con la modalità PROTOTYPE, di ottenere più istanze diverse per Bean.

Perchè usare la notazione @Configuration e @Bean se ci sono già le annotazione stereotipo?
Le notazioni stereotipo possono essere utilizzate per le classi che scrive il programmatore, ma una libreria (quindi una dipendenza esterna) perciò un jar in cui non possiamo scrivere il codice allora possiamo usare la notazione @Configuration e @Bean.

Gli springboot-starter sono dipendenze che vanno a racchiudere tutte le dipendenze di un modulo.
Quindi per esempio il springboot-web-starter è una dipendenza che inseriamo nel pom ma che poi in mainera trasparente chiamerà tutte le dipendenze del modulo web.

Di default all'avvio dell'applicazione di spring vengono caricati (istanziati) tutti i bean che sono configurati all'iterno dell'app (@Component, @cofiguration e @Bean, @Repository, ...), che poi saranno disponibili all'interno dell' IoC-Container.
Ma caricare tutti i bean non è sempre quello che si vole perchè si ritarda l'avvio dell'applicazione, si parla di approccio lazy quando si ritarda l'istaniazione del Bean non all'avvio del programma ma soltanto qando il Bean è utilizzato.

Annotazione @Lazy e @Lazy(value = false)

Modalità di dependency injection, viene gestita attraverso l'annotazione @Autowired che è una annotazione specifica di spring che può essere collocata in 3 punti specifici del codice chiamati punti di injection; Field Injection, Constructor Injection, Setter Injection.
- Field injection: avviene aggiungendo l'annotazione autowired nella dichiarazione del membro della classe.
E' deprecata e riservata a scopi didattici, perchè questa injection funziona in questo modo:
Spring per effettuare l'injection delle dipendenze con questo metodo va di fatto, quaessendo tipicamente i membri privati, ad utilizzare la reflection per consentire di esaminare e modificare la struttura di una classe a runtime, perciò anzichè limitare si crea un accoppiamento con il framework spring stesso per l'uso della reflection. Un altro motivo sta nel fatto che non possiam rendere questi membri come final, che è un problema dal punto di vista della sicurezza. Un altro problema è legato al testing, perchè si ricorre tipicamente ai mock ma diventa impossibile fare dei test senza ricorrere a spring per la reflection. Un altro problema è che poter aggiungere più dipendenze senza un controllo può portare a inserire più dipendenze del necessario.
Inoltre, se usato con lo scope Singleton, avere tante injection senza alcun controllo comporta di avere una superficie più ampia attabile perchè se una injection va a modificare il Bean a runtime allora essendo singleton la modifica si andrà a ripercuotere a tutte le injection che usano quel bean.
- Constrctior Injection: le dipendenze vengono iniettate nel costruttore, che verrà annotato con autowired.
Prima di tutto le dipendenze sono tute specificate nel costruttore, quindi è evdente ch ese andiamo a inserire o rmuovere una dipendenze vuol dire che siamo consci di quello che stiamo facendo (c'è un maggiore controllo di non proliferazione).
Si possono rendere le dipendenze final, poichè l'inizializzazione deve essere fatat contestualmente all'inizilizzazione dell'oggetto attraverso la chiamata al costruttore. Inoltre essendo l'inizializazione al costruttore si evitano anche nullpointerexception.
Se comincio a vedere un costruttore con 5, 10, 20 argomenti probabilmente sto violando il principio SOLID della singola responsabilità, perchè avere troppe dipendenze non è un bon segno.
A partire dalla versione 4.3 di spring si può omettere la notazione @autowired solo nel caso in cui la classe abbia UN SOLO costruttore. Se ne ha due invece bisogna specificare l'@autowired per uno dei costruttori. Si risolve anche il problema del testing.
Il problema è che con il costruttore tutte le dipendenze sono obbligatorie, mentre può essere che si voglia ch alcune dipendenze siano opzionali ovvero che siano iniettate  seconda di vri casi.
- Setter Injection: la notazione @autowired viene posizionata in corrispondenza di un metodo Setter impostando @Autowired(required = false), con cui appunto si andrà a iniettare la dipendenza solo in un momento specifico o in un caso specifico, rendendo la dipendenzan opzionale.

Classe pojo:
In Java, POJO sta per “Plain Old Java Object”. Si tratta di un oggetto ordinario che non è vincolato da alcuna restrizione speciale. Un POJO è un tipo semplice senza riferimenti a particolari framework. Non ha alcuna convenzione di denominazione per le nostre proprietà e metodi. Ad esempio, possiamo creare un POJO di base per un dipendente con tre proprietà: nome, cognome e data di inizio.
Un POJO può essere utilizzato da qualsiasi programma Java poiché non è legato a nessun framework

Un attributo *final* può essere inizializzato o in-line oppure nel costruttore.

Dipendenze circolari:
Spring determina un ordine con cui creare i Bean, se avessimo 3 dipendenze con i 3 Bean di esempio A->B->C in cui il bean A dipende dal bean B che dipende a sua volta dal bean C allora in questo caso Spring andrà a creare prima C poi B e infine A.
Si crea una dipendenze circolare nel caso in cui C dovesse avere una dipendenza da A, in questo caso Spring non riesce a determinare da quale bean iniziare a creare i bean.
La presenza di dipendenze circolari implica una mal progettazione del design dell'applicazione, probabilemente si sta violando il principio della singola responsabilità.
- Un metodo per aggirare questo problema è quello di utilizzare l'annotation @Lazy, che farà in modo che durante la creazione del bean A questo venga creato inizializzando il bean C con un proxy che poi successivamente inizializzato alla creazione del bean C.
- Un altro metodo è quello di utilizzare, anzichè l'injectino con il costruttore, quella con il setter. La dipendenza alla creazione di A non verrà quindi creata, ma verrà impostata successivamente con il setter.

