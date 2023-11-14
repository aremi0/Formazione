## Introduzione

JAX-RS (ovvero Java API for RESTful Web Services) è un set di API Java, tra cui annotazioni, per la creazione di API REST.

JBoss è una implementazione portable delle specifiche JAX-RS.
JBoss WildFly 10 è una delle tante versioni di JBoss.

JBoss WildFly 10 viene con RESTEasy che facilita, grazie al resteasy-servlet-initializer, l'integrazione di una Servlet standard grazie all'interfaccia ServletContainerInitializer.

**pom.xml con reasteasy**

```xml
<properties>
    <resteasy.version>3.0.14.Final</resteasy.version>
</properties>
<dependencies>
    <dependency>
        <groupId>org.jboss.resteasy</groupId>
        <artifactId>resteasy-servlet-initializer</artifactId>
        <version>${resteasy.version}</version>
    </dependency>
    <dependency>
        <groupId>org.jboss.resteasy</groupId>
        <artifactId>resteasy-client</artifactId>
        <version>${resteasy.version}</version>
    </dependency>
</dependencies>
```

## jboss-deployment-structure.xml
In JBoss tutto ciò che è deployato come WAR, JAR o EAR è un modulo, chiamati moduli dinamici.  
Esistono anche i moduli statici, ce sono contenuti nella directory $JBOSS_HOMR/modules.  
Per applicazioni standalone il *jboss-deployment-structure.xml* è d'obbligo per escludere alcuni moduli.  
Nel seguente modo tutte le classi e file JAR contenuti nel WAR saranno caricati:

```xml
<jboss-deployment-structure>
    <deployment>
        <exclude-subsystems>
            <subsystem name="resteasy" />
        </exclude-subsystems>
        <exclusions>
            <module name="javaee.api" />
            <module name="javax.ws.rs.api"/>
            <module name="org.jboss.resteasy.resteasy-jaxrs" />
        </exclusions>
        <local-last value="true" />
    </deployment>
</jboss-deployment-structure>
```

## JBoss per REST Application: pom.xml
If you are going to run RESTEasy with JBoss version 6 or higher you can choose to adopt the libraries already bundled in the application server, thus simplifying the pom:

```xml
<dependencies>
    <dependency>
        <groupId>org.jboss.resteasy</groupId>
        <artifactId>resteasy-jaxrs</artifactId>
        <version>${resteasy.version}</version>
    </dependency>
<dependencies>
```

Notice that jboss-deployment-structure.xml is no longer needed.

## Application Class
The javax.ws.rs.core.Application class is a standard JAX-RS class that you may implement to provide information on your deployment:

```java
@ApplicationPath("/rest")
public class RestEasyServices extends Application {

    private Set<Object> singletons = new HashSet<Object>();

    public RestEasyServices() {
        singletons.add(new MovieCrudService());
    }

    @Override
    public Set<Object> getSingletons() {
        return singletons;
    }
}
```

Praticamente quei singleton sono equiparabili ai Bean Scope di Spring, che appunto di default sono dei singleton. Ogni oggetto della lista singleton andrà a contenere un "Component".  
Si, si deve fare a mano pure questo.  
  
Mentre i classes servono per annotare "come bean" un controller o qualunque class deve essere avviata come "bean".  
Sostanzialmente, spring in automatico ha il component scan, J2EE no e si deve specificare a mano.