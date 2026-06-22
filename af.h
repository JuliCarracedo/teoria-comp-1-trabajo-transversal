#include "datatype.h"

#ifndef AF
#define AF

typedef struct Transicion {
  Tdata inputState; //Datatype tipo string perteneciente a Q
  Tdata inputSymbol; //Datatype tipo string perteneciente a Sigma
  Tdata outputState; //Estado de destino, subconjunto de Q

  struct Transicion * next;
} Transicion;

typedef Transicion * PTransicion;

typedef Tdata Sigma;
typedef Tdata Q;
typedef Tdata F;

typedef struct{
    Tdata initialState;

    Sigma alphabet;
    Q states;
    F acceptStates;

    PTransicion delta;

    int deterministic;
} Automata;


void addSymbolToAlphabet (Sigma *, Tdata);
void addStateToQ (Q *, Tdata);
void addStateToF (F *, Q, Tdata);
void addTransition(Q, Sigma, int, PTransicion *, Tdata input, Tdata currentSate, Tdata outputState);

void imprimeDelta(PTransicion);

Automata creaAutomata(int, Q, Sigma, PTransicion, Tdata, F);
Automata afnd_to_afd(Automata);

int procesaPalabra(Tdata, Automata);
void imprimeAutomata(Automata);

#endif //AF
