# Análisis de elección de modelo para AF

## TAD: Automata Finito

```
typedef struct Transicion {
  dataType inputState; //Datatype tipo string perteneciente a Q
  dataType inputSymbol; //Datatype tipo string perteneciente a Sigma
  dataType outputStates; //set de estados de destino, subconjunto de Q

  Transicion * next;
} Transicion;

typedef Transicion * PTransicion;

typedef struct{
    Tdata states, sigma, currentState, acceptStates;

    PTransicion * delta;

    int deterministic;
} Automata;

```
Este modelado diverge ligeramente del diseño original (Caso 2 de las propuestas de la cátedra):

- Transicion cumple rol de Transicion y TransicionNode simultaneamente, para simplificar el acceso a sus elementos
- Se reemplaza los str por dataType (AST) para habilitar el uso de la librería disponible de AST

## Planeamiento

El objetivo general es crear el AF de a elementos, y definir estructuras de control para que siempre se cumpla la definición

- `createSigma` Aprovechará la creación de `dataType` de tipo `STR` para identificar los símbolos del lenguaje
- `createStates` Aprovechará la creación de `dataType` de tipo `SET` para acumular `STR`s que representen cada estado posible
- `createSubsetStates` nos permitirá crear `Automata.acceptStates` tanto como `Transition.outputStates`, al iterar sobre los elementos del set `Automata.states` y seleccionar cuáles formarán parte del subconjunto. Si se trata de un AFD, limitaremos `Transition.outputStates` a un elemento, ni más ni menos.
- `createDelta` se apoyará en `Automata.sigma` y `Automata.states` para asignar un par de inputs, y `createSubsetStates` para definir el output, asegurándose de no repetir combinaciones de inputs, y de utilizar sólamente los estados y símbolos disponibles.
- `createAutomaton` es el módulo mayor, ordenando los llamados de los módulos antes mencionados para inicializar el Autómata
- Luego el autómata inicializado tendrá acceso a dos funciones para evaluar una cadena:
- - `evaluate_chain(Automata, dataType de tipo LIST con STRs de un caracter de largo)` que iterará y actualizará el estado actual del Autómata por cada caracter usando:
- - `evaluate_character(current_state, dataType de tipo STR)`
> evaluate_chain representa la extensión de delta, y evaluate_character representa a delta
