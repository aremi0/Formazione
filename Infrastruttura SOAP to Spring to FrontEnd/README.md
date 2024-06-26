# Infrastruttura Backend-for-Frontend

## Infrastructure
1. **First layer**: a Spring webserver created with the aim of simulating a front-end that sends rest requests.
It is controlled via rest sends to specific endpoints.
2. **Second layer**: a Spring microservice that translates front-end rest requests to soap to be sended
at the layer below and which implements the business logic.
3. **Third layer**: a spring web services server that uses just soap request and interact with the database.

## How to launch
1. Clone those three repos:
    - [frontend-simulator](https://github.com/aremi0/frontend-webserver-infrastructure-2)
    - [backend-for-frontend](https://github.com/aremi0/spring-webserver-infrastructure-3)
    - [backend-simulator](https://github.com/aremi0/soap-webserver-infrastructure-1)
2. Perform a **maven** `clean install` of all three microservices within their respective "target" subdirectories.  
The final result should be:
    - "/your_workspace/frontend/target/frontend-0.0.1-SNAPSHOT.jar"
    - "/your_workspace/microservizio/target/microservizio-0.0.1-SNAPSHOT.jar"
    - "/your_workspace/sas/target/sas-0.0.1-SNAPSHOT.jar"
3. Open a terminal and move to the *sas* directory, which contain database and docker files.
4. Run `$ docker build -t simulatore-sas .`
5. Then run `docker-compose up`  
At this point probably the sas-jdk container will crash because Hibernate was unable
to reach the database, but the context of the architecture will be created and
the two container for database and database managment will be running.
6. Open the browser and connect to `http://localhost:8080` and insert `root` both
for username and password.
7. Use the file `prenotazioni.sql` inside the cloned directory to import all data.
8. Now 
9. Run the JDK container through Docker-Desktop or re-launch `docker-compose up`.

## Requests
- **GET** to `http://localhost:8081/ws/sas.wsdl` for the *wsdl contract*.

**SOAP Protocol 1.1**   
**SAAJ MessaFactory 1.3**  
**Application used:** Insomnia <small>[link](https://insomnia.rest/)</small>  
**URL:** http://localhost:8081/ws  
**Method:** POST  
**Header:** Content-Type: text/xml  

- **GetDipendenteById:**
```http
GET http://localhost:8082/api/dipendente/{id_dipendente}
```

- **GetDipendentiByIdSede:**
```http
GET http://localhost:8082/api/dipendentiBySede/{id_sede}
```