#include "af.h"

int main(){
  int deterministic;
  Sigma s;
  Q q;
  F f;
  PTransicion delta;
  Automata a,b;
  Tdata initialState;

  s = NULL;
  q = NULL;
  f = NULL;
  delta = NULL;
  deterministic = 0;

  addSymbolToAlphabet(&s, create_str_from_chain("0"));
  addSymbolToAlphabet(&s, create_str_from_chain("1"));

  addStateToQ(&q, create_str_from_chain("q0"));
  addStateToQ(&q, create_str_from_chain("q1"));
  addStateToQ(&q, create_str_from_chain("q2"));
  addStateToQ(&q, create_str_from_chain("q3"));
  addStateToQ(&q, create_str_from_chain("q4"));
  addStateToQ(&q, create_str_from_chain("q5"));

  addStateToF(&f, q, create_str_from_chain("q5"));

  addTransition(q,s, deterministic, &delta, create_str_from_chain("0"), create_str_from_chain("q0"), create_str_from_chain("q0"));

  addTransition(q,s, deterministic, &delta, create_str_from_chain("1"), create_str_from_chain("q0"), create_str_from_chain("q0"));
  addTransition(q,s, deterministic, &delta, create_str_from_chain("1"), create_str_from_chain("q0"), create_str_from_chain("q1"));
  addTransition(q,s, deterministic, &delta, create_str_from_chain("1"), create_str_from_chain("q0"), create_str_from_chain("q2"));

  addTransition(q,s, deterministic, &delta, create_str_from_chain("0"), create_str_from_chain("q1"), create_str_from_chain("q2"));
  addTransition(q,s, deterministic, &delta, create_str_from_chain("0"), create_str_from_chain("q1"), create_str_from_chain("q3"));

  addTransition(q,s, deterministic, &delta, create_str_from_chain("1"), create_str_from_chain("q2"), create_str_from_chain("q4"));

  addTransition(q,s, deterministic, &delta, create_str_from_chain("0"), create_str_from_chain("q3"), create_str_from_chain("q5"));

  addTransition(q,s, deterministic, &delta, create_str_from_chain("1"), create_str_from_chain("q4"), create_str_from_chain("q5"));

  addTransition(q,s, deterministic, &delta, create_str_from_chain("0"), create_str_from_chain("q5"), create_str_from_chain("q5"));
  addTransition(q,s, deterministic, &delta, create_str_from_chain("1"), create_str_from_chain("q5"), create_str_from_chain("q5"));


  initialState = create_str_from_chain("q0");

  a = creaAutomata(deterministic, q, s, delta, initialState, f);

  printf("---- AFND convertido a AFD de ejemplo TP 2.1 Ejercicio 5 ----\n");

  b = afnd_to_afd(a);
  // imprimeAutomata(b);
  printf("\n");
  // printf("1) Palabra: 001\n");
  // if (procesaPalabra(create_str_from_chain("001"), b)) printf("Es aceptada\n");
  // else printf("No es aceptada\n");

  // printf("2) Palabra: 010111\n");
  // if (procesaPalabra(create_str_from_chain("010111"), b)) printf("Es aceptada\n");
  // else printf("No es aceptada\n");

  // printf("3) Palabra: 011\n");
  // if (procesaPalabra(create_str_from_chain("011"), b)) printf("Es aceptada\n");
  // else printf("No es aceptada\n");

  // printf("4) Palabra: 100\n");
  // if (procesaPalabra(create_str_from_chain("100"), b)) printf("Es aceptada\n");
  // else printf("No es aceptada\n");

  // printf("4) Palabra: 01001\n");
  // if (procesaPalabra(create_str_from_chain("01001"), b)) printf("Es aceptada\n");
  // else printf("No es aceptada\n");

  // printf("4) Palabra: 01110\n");
  // if (procesaPalabra(create_str_from_chain("01110"), b)) printf("Es aceptada\n");
  // else printf("No es aceptada\n");
  return 0;
}
