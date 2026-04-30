#include "datatype.h"

int main(){
  Tdata set1, set2, set3, set4, set5, list1, list2;
  printf("Pruebas: Creación de uniones\n");
  printf("1) Union de un set vacío con un set con cadenas\n");

  set1 = create_set();
  set2 = create_set();
  printf("Ingrese 2 cadenas al set:\n");
  insert_set(set2, create_str_ast());
  insert_set(set2, create_str_ast());

  set3 = union_set(set1, set2);

  printf("S1 U S2:\n");
  imprime_dato(set3);
  printf("\n");

  free(set1);
  free(set2);
  free(set3);
//////////////////////////////////////////////////////////////////
  printf("2) Union de dos sets con cadenas\n");

  set1 = create_set();

  printf("Ingrese 2 cadenas al set 1:\n");
  insert_set(set1, create_str_ast());
  insert_set(set1, create_str_ast());


  printf("Ingrese 2 cadenas al set 2:\n");
  set2 = create_set();
  insert_set(set2, create_str_ast());
  insert_set(set2, create_str_ast());

  set3 = union_set(set1, set2);

  printf("S1 U S2:\n");
  imprime_dato(set3);
  printf("\n");

  free(set1);
  free(set2);
  free(set3);
//////////////////////////////////////////////////////////////////
  printf("3) Union de un set con cadenas y otro con una lista\n");
  set1 = create_set();

  printf("Ingrese 2 cadenas al set 1:\n");
  insert_set(set1, create_str_ast());
  insert_set(set1, create_str_ast());

  printf("Ingrese 2 cadenas a la lista dentro de set 2:\n");
  list1 = create_list();
  append(&list1, create_str_ast());
  append(&list1, create_str_ast());

  set2 = create_set();
  insert_set(set2, list1);
  set3 = union_set(set1, set2);

  printf("S1 U S2:\n");
  imprime_dato(set3);
  printf("\n");


  free(set1);
  free(set2);
  free(set3);
  free(list1);
//////////////////////////////////////////////////////////////////
  printf("4) Union de un set con un set dentro y otro con una lista dentro\n");
  set1 = create_set();
  set4 = create_set();

  printf("Ingrese 2 cadenas al set dentro de set 1:\n");
  insert_set(set4, create_str_ast());
  insert_set(set4, create_str_ast());
  insert_set(set1, set4);

  printf("Ingrese 2 cadenas a la lista dentro de set 2:\n");
  list1 = create_list();
  append(&list1, create_str_ast());
  append(&list1, create_str_ast());

  set2 = create_set();
  insert_set(set2, list1);
  set3 = union_set(set1, set2);

  printf("S1 U S2:\n");
  imprime_dato(set3);
  printf("\n");

  free(set1);
  free(set2);
  free(set3);
  free(list1);
//////////////////////////////////////////////////////////////////
  printf("5) Union de dos sets que contienen listas\n");

  set1 = create_set();
  list2 = create_list();

  printf("Ingrese 2 cadenas a la lista dentro de set 1:\n");
  list2 = create_list();
  append(&list2, create_str_ast());
  append(&list2, create_str_ast());

  insert_set(set1, list2);

  printf("Ingrese 2 cadenas a la lista dentro de set 2:\n");

  list1 = create_list();
  append(&list1, create_str_ast());
  append(&list1, create_str_ast());

  set2 = create_set();
  insert_set(set2, list1);

  set3 = union_set(set1, set2);

  printf("S1 U S2:\n");
  imprime_dato(set3);
  printf("\n");


  free(set1);
  free(set2);
  free(set3);
  free(list1);
  free(list2);
//////////////////////////////////////////////////////////////////
  printf("6) Union de dos sets que contienen sets\n");

  set1 = create_set();
  set4 = create_set();

  printf("Ingrese 2 cadenas al set dentro de set 1:\n");
  set4 = create_set();
  insert_set(set4, create_str_ast());
  insert_set(set4, create_str_ast());

  insert_set(set1, set4);

  printf("Ingrese 2 cadenas al set dentro de set 2:\n");

  set5 = create_set();
  insert_set(set5, create_str_ast());
  insert_set(set5, create_str_ast());

  set2 = create_set();
  insert_set(set2, set5);

  set3 = union_set(set1, set2);

  printf("S1 U S2:\n");
  imprime_dato(set3);
  printf("\n");

  free(set1);
  free(set2);
  free(set3);
  free(set4);
  free(set5);
}
