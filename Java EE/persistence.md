# note spring-persistence

## Annotazioni

- @PutMapping(path = "/api/{studentId}")
- @PathVariable("studentId)
- @RequestBody
Serve per leggere e deserializzare il request body in un Object attraverso HttpMessageConverter
- @RequestParam(required = false)
- @RequestParam
Si usa per legare dei parametri query a un argomento di un metodo in un controller
- @ResponseBody
Si usa su un metodo per avere il tipo di ritorno serializzato al body della risposta attraverso un HttpMessageConverter

- @Transactional
Viene usato nel service di una entity per effettare delle UPDATE senza interpellare il repository (quindi senza repo.save(asd)) ma usando invece i metodi getter e setter disponibili al Service. Non viene usata nessuna query perchè questa annotazione permette all'entità di entrare in uno stato di modifica che viene gestita da spring.
Questa annotazione marca un metodo o una classe come transazione.
La transazione, se opportunamente configurata, garantisce le proprietà ACID (Atomicità, Consistenza, Isolamento, Durevolezza).

- @Controller e @RestController
L'annotazione @Controller è una specializzazione dell'annotazione @Component che ci consente di gestire gli endpoint dell'applicativo. Viene usata tipicamente insieme all'annotazione @RequestMapping:
```java
@Controller
@RequestMapping("books")
public class SimpleBookController {
    @GetMapping("/{id}", produces = "application/json")
    ...
}
```

L'annotazione @RestController è una specializzazione dell'annotazione @Controller che include le annotazioni @Controller e @ResponseBody

- @Transient
Ogni attributo di una entity con questa annotazione non avrà una colonna nella tabella della entty nel DB.

- @Query("SELECT s FROM Student s WHERE s.email = ?1")
Può essere usato nei reporitory al sopra il metodo;
Optional<Student> findStudentByEmail(String email)
per specificare nel dettaglio cosa il metodo deve fare.

## Gestione delle eccezioni

Dalla versone 3.2 di Spring è stato implementato il supporto per un @ExceptionHandler globale grazie all'annotazione @ControllerAdvice
```java
@ControllerAdvice
public class RestResponsiveEntityExceptionHandler extends ResponseEntityExceptionHandler {
    
    @ExceptionHandler(value = {IllegalArgumentException.class, IllegalStateException.class})
    protected ResponseEntity<Object> handleConflict(RuntimeException ex, WebRequest request) {
        String bodyOfResponse = "asdrubale";
        return handleExceptionInternal(ex, bodyfResponse, new HttpHeaders(),
                                        HttpStatus.CONFLICT, request)
    }

       @ExceptionHandler(value = {IoException.class})
    protected ResponseEntity<Object> handleConflict(IoException ex, WebRequest request) {
        String bodyOfResponse = "asdrubale";
        return handleExceptionInternal(ex, bodyfResponse, new HttpHeaders(),
                                        HttpStatus.CONFLICT, request)
    }
}
```

L'annotazione @ControllerAdvice ci consente di consilidare l' @ExceptionHandler in un unico componente globale per la gestione degli errori.
Vantaggi:
- Mappare diversi tipi di eccezioni in un unico metodo generico, permettendoci di gestirle tutte assieme.
- Fornisce il pieno controllo sul body della risposta e sullo status code.
- Fa buon uso della risposta RESTful ReponseEntity.

