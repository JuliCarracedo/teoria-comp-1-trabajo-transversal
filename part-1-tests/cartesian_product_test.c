#include "datatype.h"

Tdata buildTuple(Tdata elem1, Tdata elem2);
Tdata cartesianProduct(Tdata set1, Tdata set2);

int main(){
  Tdata set1, set2, product;
  printf("Producto cartesiano de dos conjuntos:\n");
  printf("Escribe el conjunto A (3 elementos):\n");

  set1 = create_set();
  insert_set(set1, create_str_ast());
  insert_set(set1, create_str_ast());
  insert_set(set1, create_str_ast());

  printf("Escribe el conjunto B (2 elementos):\n");
  set2 = create_set();
  insert_set(set2, create_str_ast());
  insert_set(set2, create_str_ast());

  printf("1) AxB:\n");
  product = cartesianProduct(set1, set2);
  imprime_dato(product);
  free(product);
  printf("\n");
  printf("2) BxA:\n");
  product = cartesianProduct(set2, set1);
  imprime_dato(product);
  free(product);
  printf("\n");
}

Tdata buildTuple(Tdata elem1, Tdata elem2){
  Tdata tuple;

  tuple = create_list();

  append(&tuple, elem1);
  append(&tuple, elem2);

  return tuple;
}

Tdata cartesianProduct(Tdata set1, Tdata set2){
  Tdata aux1, aux2, product;

  product = create_set();

  aux1 = set1;
  while(aux1 != NULL){
    aux2 = set2;
    while(aux2!= NULL){
      insert_set(product, buildTuple(aux1->data, aux2->data));
      aux2 = aux2->next;
    }
    aux1 = aux1->next;
  }

  return product;
}
