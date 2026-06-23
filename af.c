#include "af.h"

void addSymbolToAlphabet (Sigma * alphabet, Tdata symbol){
  if(!isStr(symbol)){
    printf("Símbolo inválido: Debe ser STR\n");
  } else if((*alphabet) == NULL){
    (*alphabet) = (Sigma) create_set();
    insert_set((*alphabet), symbol);
  } else {
    insert_set((*alphabet), symbol);
  }
}

void addStateToQ (Q * Q, Tdata state){
  if(!isStr(state)){
    printf("Estado inválido: Debe ser STR\n");
  } else if((*Q) == NULL){
    (*Q) = (Sigma) create_set();
    insert_set((*Q), state);
  } else {
    insert_set((*Q), state);
  }
}

void addStateToF (F * F, Q Q, Tdata state){
  if(!isStr(state)){
    printf("Estado inválido: Debe ser STR\n");
  } else if(!belongs(state, Q)){
    printf("Estado inválido: Debe pertenecer a Q\n");
  } else if((*F) == NULL){
    (*F) = (Sigma) create_set();
    insert_set((*F), state);
  } else {
    insert_set((*F), state);
  }
}

PTransicion createTransition(Tdata input, Tdata currentState, Tdata outputState, Sigma alphabet, Q Q){
  PTransicion transicion;

  if (!isStr(input) || !isStr(currentState) || !isStr(outputState)){
    printf("Datos inválidos para la transicion.\n");
    return NULL;
  } else if (!belongs(input, alphabet)) {
    printf("Input debe ser un elemento del alfabeto.\n");
    return NULL;
  } else if (!belongs(currentState, Q)) {
    printf("currentState debe ser un elemento del conjunto de estados.\n");
    return NULL;
  } else if (!belongs(outputState, Q)) {
    printf("outputState debe ser un subconjunto del conjunto de estados.\n");
    return NULL;
  } else {
    transicion = (PTransicion) malloc(sizeof(Transicion));

    transicion->inputState = currentState;
    transicion->outputState = outputState;
    transicion->inputSymbol = input;
    transicion->next = NULL;
    return transicion;
  }
}

int deltaAlreadyHasDeterministicTransition(PTransicion delta, Tdata input, Tdata currentState){
  int alreadyFound;
  alreadyFound = 0;

  if(delta != NULL){
    while(delta != NULL && !alreadyFound){
      if(equals(delta->inputSymbol, input) && equals(delta->inputState, currentState)) alreadyFound = 1;
      delta = delta->next;
    }
  }

  return alreadyFound;
}

int deltaAlreadyHasNonDeterministicTransition(PTransicion delta, Tdata input, Tdata currentState, Tdata outputState){
  int alreadyFound;
  alreadyFound = 0;
  if(delta != NULL){
    while(delta != NULL && !alreadyFound){
      if(equals(delta->inputSymbol, input) && equals(delta->inputState, currentState) && equals(delta->outputState, outputState) ) alreadyFound = 1;
      delta = delta->next;
    }
  }
  return alreadyFound;
}

void addTransition(Q Q, Sigma alphabet, int deterministic, PTransicion * delta, Tdata input, Tdata currentState, Tdata outputState){
  PTransicion transicion, aux;

  if((*delta) == NULL){
    (*delta) = createTransition(input, currentState, outputState, alphabet, Q);
  }
  else {
    if (deterministic && deltaAlreadyHasDeterministicTransition((*delta), input, currentState) ||
        !deterministic && deltaAlreadyHasNonDeterministicTransition((*delta), input, currentState, outputState)){
          printf("This tranistion is already defined\n");
        }
    else {
      aux = (*delta);
      while(aux->next != NULL){
        aux = aux->next;
      }
      aux->next = createTransition(input, currentState, outputState, alphabet, Q);
    }
  }

  return;
}

void imprimeDelta(PTransicion delta){
  if(delta == NULL){
    printf("Delta vacío");
  } else {
    while(delta != NULL){
      printf("delta( ");
      imprime_dato(delta->inputState);
      printf(", ");
      imprime_dato(delta->inputSymbol);
      printf(" ) = ");
      imprime_dato(delta->outputState);
      printf("\n");
      delta = delta->next;
    }
  }
}

int hasAllNecesaryTransitions(Q states, Sigma alphabet, PTransicion delta){
  int hasAll;
  Tdata states_copy, alphabet_copy, popped_state, popped_sym;
  states_copy = copia_dato(states);
  alphabet_copy = copia_dato(alphabet);
  hasAll = 1;

  popped_state = pop(&states_copy);
  while (popped_state != NULL && hasAll){

    popped_sym = pop(&alphabet_copy);
    while(popped_sym != NULL && hasAll){
      hasAll = hasAll && deltaAlreadyHasDeterministicTransition(delta, popped_sym, popped_state);

      deep_free(&popped_sym);
      popped_sym = pop(&alphabet_copy);
    }
    deep_free(&alphabet_copy);
    deep_free(&popped_state);
    popped_state = pop(&states_copy);
    alphabet_copy = copia_dato(alphabet);
  }

  deep_free(&alphabet_copy);
  deep_free(&states_copy);
  return hasAll;
}

Automata creaAutomata(int determinista, Q states, Sigma alphabet, PTransicion delta, Tdata initialState, F acceptState){
  Automata afd;

  if (determinista && !hasAllNecesaryTransitions(states, alphabet, delta)){
    printf("Función delta debe estar completamente definida para un AFD\n");
  } else {
    if(belongs(initialState, states)){
      afd.alphabet = alphabet;
      afd.states = states;
      afd.acceptStates = acceptState;
      afd.delta = delta;
      afd.deterministic = determinista;
      afd.initialState = initialState;
    } else {
      printf("Estado inicial inválido\n");
    }
  }

  return afd;
}

Tdata consumeCaracter(Tdata input, Tdata currentState, PTransicion delta){
  int found;
  found = 0;
  Tdata output;
  while(!found && delta!= NULL){
    if (equals(input, delta->inputSymbol) && equals(currentState, delta->inputState)){
      found = 1;
      output = copia_dato(delta->outputState);
    }
    delta = delta->next;
  }

  return output;
}

Tdata consumeCaracterAFND(Tdata input, Tdata currentState, PTransicion delta){
  Tdata output;
  output = create_set();
  while(delta!= NULL){
    if (equals(input, delta->inputSymbol) && equals(currentState, delta->inputState)){
      insert_set( output, copia_dato(delta->outputState));
    }
    delta = delta->next;
  }

  return output;
}

Tdata procesaConAFND(Tdata listaCaracteres, PTransicion delta, Tdata currentState){
  Tdata resultStates, resultStatesElement, finalStates, aux, copiaListaCaracteres;
  copiaListaCaracteres = copia_dato(listaCaracteres);

  if(length(listaCaracteres) > 0){
    resultStates = consumeCaracterAFND(pop(&copiaListaCaracteres), currentState, delta);
    finalStates = create_set();
    while(size(resultStates) > 0){
      resultStatesElement = pop(&resultStates);
      aux = copia_dato(finalStates);
      deep_free(&finalStates);
      finalStates = union_set(aux, procesaConAFND(copiaListaCaracteres, delta, resultStatesElement));
      deep_free(&resultStatesElement);
      deep_free(&aux);
    }

    deep_free(&resultStates);
    deep_free(&copiaListaCaracteres);
    return finalStates;
  }
  else {
    finalStates = create_set();
    insert_set(finalStates, currentState);
    return finalStates;
  }
}

int procesaPalabra(Tdata cadena, Automata automata){
  Tdata listaCaracteres, currentState, afndResultStates, intersection;
  int isAccept;
  listaCaracteres = list_from_str(cadena);
  currentState = copia_dato(automata.initialState);

  if(automata.deterministic){
    while(length(listaCaracteres) > 0){
      currentState = consumeCaracter(pop(&listaCaracteres), currentState, automata.delta);
    }
    isAccept = belongs(currentState, automata.acceptStates);

    deep_free(&listaCaracteres);
    deep_free(&currentState);
    return isAccept;
  } else {
    afndResultStates = procesaConAFND(listaCaracteres, automata.delta, automata.initialState);
    intersection = intersection_set(afndResultStates, automata.acceptStates);
    isAccept = size(intersection) > 0;
    deep_free(&afndResultStates);
    deep_free(&intersection);
    deep_free(&listaCaracteres);
    deep_free(&currentState);
    return isAccept;
  }
}

void imprimeAutomata(Automata automata){
  printf("Automata Finito ");
  if(!automata.deterministic)  printf("No ");
  printf("Determinista: G=(Sigma, Q, Delta, q_0, F) tal que\n");
  printf("Sigma = ");
  imprime_dato(automata.alphabet);
  printf("\n");
  printf("Q = ");
  imprime_dato(automata.states);
  printf("\n");
  printf("q_0 = ");
  imprime_dato(automata.initialState);
  printf("\n");
  printf("F = ");
  imprime_dato(automata.acceptStates);
  printf("\n");
  printf("Delta = \n");
  imprimeDelta(automata.delta);
  printf("\n");
}

void process_AFND_delta_for_transformation(PTransicion * nuevoDelta, Sigma nuevoSigma, F viejoF, F nuevoF, Q nuevosEstados, Tdata setEntradas, PTransicion viejoDelta) {
  // Combinar todas las transiciones para un caracter

  Tdata nuevoSigmaCopia, poppedSigma, setEntradasCopia, poppedState, accumulatorStates, accumulatorStatesAux, intersection, nuevosEstadosCopia;

  nuevoSigmaCopia = copia_dato(nuevoSigma);
  nuevosEstadosCopia = copia_dato(nuevosEstados);

  while(size(nuevoSigmaCopia) > 0){
    poppedSigma = pop(&nuevoSigmaCopia);

    accumulatorStates = create_set();
    setEntradasCopia = copia_dato(setEntradas);

    while(size(setEntradasCopia) > 0){
      poppedState = pop(&setEntradasCopia);

      accumulatorStatesAux = union_set(copia_dato(accumulatorStates), consumeCaracterAFND(poppedSigma, poppedState, viejoDelta));

      deep_free(&accumulatorStates);
      accumulatorStates = copia_dato(accumulatorStatesAux);
      deep_free(&accumulatorStatesAux);


      deep_free(&poppedState);
    }

    addStateToQ(&nuevosEstados, copia_dato(str_from_list(accumulatorStates)));

    intersection = intersection_set(viejoF, accumulatorStates);
    if(size(intersection) > 0) insert_set(nuevoF, str_from_list(accumulatorStates));
    deep_free(&intersection);

    addTransition(nuevosEstados, nuevoSigma, 1, nuevoDelta, copia_dato(poppedSigma), str_from_list(setEntradas), str_from_list(accumulatorStates));

    if(!equals(nuevosEstadosCopia, nuevosEstados)){
      process_AFND_delta_for_transformation(nuevoDelta, nuevoSigma, viejoF, nuevoF, nuevosEstados, copia_dato(accumulatorStates), viejoDelta);
    }

    deep_free(&poppedSigma);
    deep_free(&setEntradasCopia);
  }

  deep_free(&accumulatorStates);
  deep_free(&nuevosEstadosCopia);
  deep_free(&nuevoSigmaCopia);
  deep_free(&setEntradasCopia);
}

Automata afnd_to_afd(Automata automata){
  Sigma nuevoSigma;
  Tdata nuevoInicial, initialStateSet;
  F nuevoF, viejoF;
  PTransicion nuevoDelta, viejoDelta;
  Q nuevosEstados;
  int deterministic;

  viejoDelta = automata.delta;

  viejoF = automata.acceptStates;

  deterministic = 1;

  nuevoSigma = copia_dato(automata.alphabet);

  nuevoInicial = copia_dato(automata.initialState);
  initialStateSet = create_set();
  insert_set(initialStateSet, copia_dato(nuevoInicial));

  nuevosEstados = create_set();
  insert_set(nuevosEstados, nuevoInicial);

  nuevoF = create_set();
  if(belongs(nuevoInicial, viejoF)) insert_set(nuevoF, nuevoInicial);

  nuevoDelta = NULL;

  process_AFND_delta_for_transformation(&nuevoDelta, nuevoSigma, viejoF, nuevoF, nuevosEstados, copia_dato(initialStateSet), viejoDelta);

  return creaAutomata(1, nuevosEstados, nuevoSigma, nuevoDelta, nuevoInicial, nuevoF);
}
