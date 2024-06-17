# Apprendimento Machine Learning con Python
## Tensori
In PyTorch, un **tensore** è un'entità fondamentale che rappresenta una matrice multidimensionale di numeri. È simile agli array in Numpy e viene utilizzato per eseguire operazioni matematiche su GPU, il che accelera notevolmente i calcoli.

Ecco un esempio di come si può creare un tensore in PyTorch:

```python
import torch

# Crea un tensore 2x3 inizializzato con zeri
tensore_zero = torch.zeros(2, 3)

# Crea un tensore 2x3 inizializzato con uni
tensore_uno = torch.ones(2, 3)

# Crea un tensore 2x3 con valori casuali
tensore_casuale = torch.rand(2, 3)

# Crea un tensore dalle dimensioni specificate con valori non inizializzati
tensore_vuoto = torch.empty(2, 3)

# Crea un tensore 4D con valori casuali
tensore_4d_casuale = torch.rand(2, 3, 4, 5)

print(tensore_zero)
print(tensore_uno)
print(tensore_casuale)
print(tensore_vuoto)
```

I tensori sono la base per costruire reti neurali e per eseguire calcoli nel deep learning. Sono dotati di un sistema di autograd integrato che permette di calcolare automaticamente i gradienti necessari per l'ottimizzazione dei modelli.

## Grafo Computazionale e Backpropagation
### Grafo Computazionale
Nel Machine Learning, un **grafo computazionale** è una struttura che rappresenta tutte le operazioni (come nodi) e le connessioni tra queste operazioni (come archi) che sono state eseguite su tensori. È un grafo diretto aciclico (DAG) che tiene traccia di ogni passo nel calcolo di una funzione, permettendo così di calcolare automaticamente i gradienti durante la fase di *backpropagation*.

Nel contesto di PyTorch e del machine learning, un **grafo computazionale** è utilizzato per rappresentare e calcolare le operazioni eseguite durante il passaggio in avanti (*forward pass*) e durante la *backpropagation* di una rete neurale. Ecco un esempio di come potrebbero essere rappresentati nodi e archi in questo scenario:

**Nodi:**
- **Operazioni matematiche**: come addizione, moltiplicazione, o funzioni di attivazione (es. ReLU, Sigmoid).
- **Tensori**: che rappresentano i dati di input, i pesi, i bias, o i risultati intermedi.
- **Funzione di perdita**: il nodo finale che calcola la differenza tra l'output previsto e il valore target.

**Archi:**
- **Flusso dei dati**: indicano la direzione del flusso dei dati attraverso la rete, da un'operazione all'altra.
- **Dipendenze**: mostrano come l'output di un'operazione diventa l'input per un'altra.
- **Gradienti**: durante la backpropagation, rappresentano il flusso dei gradienti calcolati rispetto a ciascun nodo.

### Backpropagation
La **backpropagation**, o retropropagazione, è un algoritmo chiave nell'apprendimento delle reti neurali. Consiste nel calcolare il gradiente della funzione di perdita rispetto a tutti i pesi della rete. Questo processo inizia dall'ultimo strato della rete e procede a ritroso verso l'input, da qui il termine "backpropagation". In PyTorch, questo è gestito automaticamente dal modulo `torch.autograd`, che calcola i gradienti necessari per aggiornare i pesi durante l'addestramento di una rete neurale⁴.

Ecco un esempio di come funziona la backpropagation in PyTorch:

```python
import torch

# Definizione di un semplice modello lineare
x = torch.tensor([1.0, 2.0, 3.0], requires_grad=True)
y = torch.tensor([2.0, 4.0, 6.0])
w = torch.tensor([1.0], requires_grad=True)

# Calcolo della funzione di perdita
loss = torch.mean((w * x - y) ** 2)

# Calcolo dei gradienti
loss.backward()

# I gradienti dei pesi
print(w.grad)
```

Nell'esempio, `loss.backward()` calcola i gradienti della funzione di perdita rispetto a `w`, che possono poi essere utilizzati per aggiornare i pesi del modello. Questo processo è fondamentale per l'addestramento delle reti neurali, permettendo loro di "imparare" dai dati.

---

Ecco un semplice esempio di codice che mostra come PyTorch crea un grafo computazionale durante il forward e il backward pass:

```python
import torch
import torch.nn as nn
import torch.nn.functional as F

# Definizione di un semplice modello di rete neurale
class SimpleNet(nn.Module):
    def __init__(self):
        super(SimpleNet, self).__init__()
        self.fc1 = nn.Linear(10, 5)
        self.fc2 = nn.Linear(5, 1)

    def forward(self, x):
        x = F.relu(self.fc1(x))
        x = self.fc2(x)
        return x

# Creazione di un'istanza del modello
modello = SimpleNet()

# Dati di input
input = torch.randn(1, 10)

# Forward pass
output = modello(input)

# Calcolo della funzione di perdita
target = torch.tensor([1.0])
perdita = F.mse_loss(output, target)

# Backward pass
perdita.backward()
```

In questo esempio, ogni chiamata a una funzione come `F.relu` o `F.mse_loss` aggiunge un nodo al grafo, mentre ogni risultato intermedio crea un arco che collega i nodi. Durante il backward pass, PyTorch calcola automaticamente i gradienti per ogni tensore che ha `requires_grad=True`, seguendo il grafo computazionale creato durante il forward pass.

## Gradiente
I **gradienti** in PyTorch e nel contesto dell'apprendimento automatico sono essenzialmente le derivate parziali di una funzione di perdita rispetto a ciascun parametro del modello. In altre parole, indicano quanto una piccola variazione in un parametro influisce sulla funzione di perdita.

Nell'addestramento delle reti neurali, i gradienti sono fondamentali perché guidano il processo di ottimizzazione. Durante la backpropagation, i gradienti di ogni parametro sono calcolati e utilizzati per aggiornare i pesi del modello in modo da minimizzare la funzione di perdita. Questo processo è noto come discesa del gradiente.

Ecco un esempio di come si calcolano i gradienti in PyTorch:

```python
import torch

# Definiamo un tensore che richiede il calcolo del gradiente
x = torch.tensor([1.0, 2.0, 3.0], requires_grad=True)

# Definiamo una semplice funzione di perdita
y = x * 2
loss = y.sum()

# Calcoliamo i gradienti
loss.backward()

# Ora x.grad contiene i gradienti di loss rispetto a x
print(x.grad)
```

Nell'esempio, dopo aver chiamato `loss.backward()`, `x.grad` conterrà i gradienti di `loss` rispetto a `x`. Questi gradienti sono poi utilizzati per aggiornare i parametri del modello durante l'addestramento.

## Funzione di Perdita
La **funzione di perdita** in PyTorch, e più in generale nell'apprendimento automatico, è una misura che quantifica la differenza tra il valore previsto dal modello e il valore reale o target. Serve per valutare quanto bene o male un modello sta facendo previsioni sui dati.

Ci sono diverse funzioni di perdita disponibili in PyTorch, ognuna adatta a diversi tipi di problemi di apprendimento. Ad esempio:
- **Errore Quadratico Medio (MSE)**: utilizzato per problemi di regressione.
- **Entropia Incrociata**: utilizzata per problemi di classificazione.
- **Errore Assoluto Medio (MAE)**: un'altra funzione di perdita per la regressione, meno sensibile agli outlier rispetto al MSE.

La scelta della funzione di perdita dipende dall'obiettivo specifico e dalla natura del problema. Durante il processo di addestramento, si cerca di minimizzare questa funzione di perdita aggiustando i parametri del modello, come i pesi delle connessioni in una rete neurale, attraverso un processo chiamato **ottimizzazione**.

Ecco un esempio di come si definisce e si utilizza una funzione di perdita in PyTorch:

```python
import torch
import torch.nn as nn

# Definizione di un modello semplice
modello = nn.Linear(in_features=10, out_features=1)

# Definizione della funzione di perdita MSE
funzione_perdita = nn.MSELoss()

# Dati di esempio
input = torch.randn(3, 10)
target = torch.randn(3, 1)

# Forward pass: calcola la previsione del modello
output = modello(input)

# Calcola la perdita
perdita = funzione_perdita(output, target)

print(perdita)
```

In questo esempio, `nn.MSELoss()` crea un criterio di perdita MSE che calcola la media dei quadrati delle differenze tra le previsioni e i target reali. Questo valore di perdita è poi utilizzato per guidare l'aggiornamento dei pesi del modello durante l'addestramento.

## I pesi delle connessioni nelle reti neurali
Nelle reti neurali, i **pesi delle connessioni** sono parametri che determinano l'importanza relativa degli input per un neurone. Sono stabiliti durante il processo di apprendimento della rete e si aggiornano continuamente attraverso l'algoritmo di backpropagation.

In una rete neurale, ogni connessione tra due neuroni ha un peso associato. Questi pesi influenzano la forza del segnale che viene trasmesso da un neurone all'altro. Durante il processo di addestramento, la rete neurale impara quali pesi producono le migliori previsioni rispetto ai dati di addestramento.

Ecco come funzionano i pesi in una rete neurale:
- **Inizializzazione**: I pesi vengono inizialmente impostati a valori casuali o secondo una certa distribuzione.
- **Forward Pass**: Durante il passaggio in avanti, gli input vengono moltiplicati per i loro pesi e sommati insieme prima di essere passati attraverso una funzione di attivazione.
- **Calcolo della Perdita**: Viene calcolata una funzione di perdita che misura l'errore tra le previsioni della rete e i valori reali.
- **Backpropagation**: Durante la backpropagation, i gradienti della funzione di perdita vengono calcolati e propagati indietro attraverso la rete.
- **Aggiornamento dei Pesi**: I pesi vengono aggiornati in modo da ridurre l'errore, tipicamente utilizzando un algoritmo di ottimizzazione come la discesa del gradiente.

Il processo di aggiornamento dei pesi è cruciale perché permette alla rete neurale di "imparare" dai dati e migliorare le sue previsioni nel tempo.