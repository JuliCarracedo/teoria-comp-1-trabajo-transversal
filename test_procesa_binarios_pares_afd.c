#include "af.h"

int main(){
  int deterministic;
  Sigma s;
  Q q;
  F f;
  PTransicion delta;
  Automata a;
  Tdata initialState;

  s = NULL;
  q = NULL;
  f = NULL;
  delta = NULL;
  deterministic = 1;

  addSymbolToAlphabet(&s, create_str_from_chain("0"));
  addSymbolToAlphabet(&s, create_str_from_chain("1"));

  addStateToQ(&q, create_str_from_chain("par"));
  addStateToQ(&q, create_str_from_chain("impar"));

  addStateToF(&f, q, create_str_from_chain("par"));

  addTransition(q,s, deterministic, &delta, create_str_from_chain("0"), create_str_from_chain("par"), create_str_from_chain("par"));
  addTransition(q,s, deterministic, &delta, create_str_from_chain("0"), create_str_from_chain("impar"), create_str_from_chain("par"));
  addTransition(q,s, deterministic, &delta, create_str_from_chain("1"), create_str_from_chain("par"), create_str_from_chain("impar"));
  addTransition(q,s, deterministic, &delta, create_str_from_chain("1"), create_str_from_chain("impar"), create_str_from_chain("impar"));

  initialState = create_str_from_chain("par");

  a = creaAutomata(deterministic, q, s, delta, initialState, f);

  printf("---- AFD Para aceptar numeros pares en binario ----\n");
  printf("1) Palabra: 0\n");
  if (procesaPalabra(create_str_from_chain("0"), a)) printf("Es aceptada\n");
  else printf("No es aceptada\n");

  printf("2) Palabra: 10\n");
  if (procesaPalabra(create_str_from_chain("10"), a)) printf("Es aceptada\n");
  else printf("No es aceptada\n");

  printf("3) Palabra: 110101000110\n");
  if (procesaPalabra(create_str_from_chain("110101000110"), a)) printf("Es aceptada\n");
  else printf("No es aceptada\n");

  printf("4) Palabra: 1\n");
  if (procesaPalabra(create_str_from_chain("1"), a)) printf("Es aceptada\n");
  else printf("No es aceptada\n");

  printf("5) Palabra: 100001\n");
  if (procesaPalabra(create_str_from_chain("100001"), a)) printf("Es aceptada\n");
  else printf("No es aceptada\n");

  printf("6) Palabra: 0000\n");
  if (procesaPalabra(create_str_from_chain("0000"), a)) printf("Es aceptada\n");
  else printf("No es aceptada\n");

  return 0;
}
