# Análisis de elección de modelo para AF

## TAD: Automata Finito

```
typedef struct Transicion {
  dataType inputState; //Datatype tipo string perteneciente a Q
  dataType inputSymbol; //Datatype tipo string perteneciente a Sigma
  dataType outputState; //Estado de destino, perteneciente a Q

  Transicion * next;
} Transicion;

typedef Transicion * PTransicion;

typedef struct{
    Sigma alfabeto;
    Q states;
    F acceptStates;
    Tdata initialState;

    PTransicion * delta;

    int deterministic;
} Automata;

```
Este modelado diverge ligeramente del diseño original (Caso 2 de las propuestas de la cátedra):

- Transicion cumple rol de Transicion y TransicionNode simultaneamente, para simplificar el acceso a sus elementos
- Se reemplaza los str por dataType (AST) para habilitar el uso de la librería disponible de AST

## Planeamiento

El objetivo general es crear el AF de a elementos, y definir estructuras de control para que siempre se cumpla la definición;

- `addSymbolToSigma` Aprovechará la creación de `dataType` de tipo `STR` para identificar los símbolos del lenguaje
- `addStateToQ` Aprovechará la creación de `dataType` de tipo `SET` para acumular `STR`s que representen cada estado posible
- `addStateToF` nos permitirá crear `F acceptStates`, al iterar sobre los elementos del set `Q states` y seleccionar cuáles formarán parte del subconjunto. Si se trata de un AFD.
- `createDelta` se apoyará en `Sigma` y `Q` para asignar un par de inputs, asegurándose de no repetir combinaciones de inputs, y de utilizar sólamente los estados y símbolos disponibles.
- `creaAutomata` es el módulo mayor, ordenando los llamados de los módulos antes mencionados para inicializar el Autómata
- Luego el autómata inicializado tendrá acceso a una función para evaluar una cadena:
- - `procesaPalabra(Tdata palabra, Automata a)` que iterará y actualizará el estado actual por cada caracter consumido, partiendo del estado inicial del AF. Las transiciones individuales se hacen con `consumeCaracter`. Si se trata de un AFND, se deriva el procesamiento a otra función `procesaConAFND`
- - `consumeCaracter(Tdata input, Tdata currentState, PTransicion delta)` Toma una letra (input), un estado previo y busca en Delta qué salida tiene asignado ese par de entradas
- - `procesaConAFND(Tdata listaCaracteres, PTransicion delta, Tdata currentState)` Toma una letra (input), un estado previo y busca en Delta qué salidas puede tener asignado ese par de entradas, pero juntándolas en un conjunto para modelar el no determinismo de la transición.

Luego es suficiente con preguntar al final de procesaPalabra, el estado resultante pertenece a F? o en AFND, el conjunto de estados resultantes tiene intersección con F?

> evaluate_chain representa la extensión de delta, y evaluate_character representa a delta
