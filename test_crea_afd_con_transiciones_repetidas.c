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

  addSymbolToAlphabet(&s, create_str_from_chain("a"));
  addSymbolToAlphabet(&s, create_str_from_chain("b"));

  addStateToQ(&q, create_str_from_chain("q0"));
  addStateToQ(&q, create_str_from_chain("q1"));
  addStateToQ(&q, create_str_from_chain("qf"));

  addStateToF(&f, q, create_str_from_chain("qf"));

  addTransition(q,s, deterministic, &delta, create_str_from_chain("a"), create_str_from_chain("q0"), create_str_from_chain("q1"));
  addTransition(q,s, deterministic, &delta, create_str_from_chain("b"), create_str_from_chain("q0"), create_str_from_chain("q0"));
  addTransition(q,s, deterministic, &delta, create_str_from_chain("a"), create_str_from_chain("q1"), create_str_from_chain("qf"));
  addTransition(q,s, deterministic, &delta, create_str_from_chain("b"), create_str_from_chain("q1"), create_str_from_chain("q1"));
  addTransition(q,s, deterministic, &delta, create_str_from_chain("a"), create_str_from_chain("qf"), create_str_from_chain("qf"));
  addTransition(q,s, deterministic, &delta, create_str_from_chain("b"), create_str_from_chain("qf"), create_str_from_chain("qf"));
  addTransition(q,s, deterministic, &delta, create_str_from_chain("b"), create_str_from_chain("qf"), create_str_from_chain("qf"));

  initialState = create_str_from_chain("q0");

  a = creaAutomata(deterministic, q, s, delta, initialState, f);

  return 0;
}
