#include "datatype.h"

int main(){
  Tdata dato1, dato2, dato3;

//   printf("Ejemplo de conjunto vacío:\n");
//   dato1 = create_set();
//   imprime_dato(dato1);
//   printf("\n");
//   free(dato1);
// //////////////////////////////////////////////////////////////////

//   printf("Ejemplo de listas anidadas:\n");
//   dato1 = create_list();
//   printf("Lista 1:\n");
//   append(&dato1, create_str_ast());
//   append(&dato1, create_str_ast());

//   printf("Lista 2:\n");
//   dato2 = create_list();
//   append(&dato2, create_str_ast());
//   append(&dato2, create_str_ast());

//   dato3 = create_list();
//   append(&dato3, create_str_ast());
//   append(&dato3, create_str_ast());

//   printf("Lista 3:\n");
//   append(&dato2, dato3);
//   append(&dato1, dato2);
//   imprime_dato(dato1);
//   printf("\n");

//   free(dato1);
//   free(dato2);
//   free(dato3);
// //////////////////////////////////////////////////////////////////
//   printf("Ejemplo de incorporación de elementos duplicados a un conjunto:\n");

//   dato1 = create_set();
//   dato2 = create_str_ast();

//   insert_set(dato1, dato2);
//   insert_set(dato1, dato2);
//   insert_set(dato1, dato2);
//   insert_set(dato1, dato2);
//   insert_set(dato1, dato2);
//   insert_set(dato1, dato2);

//   imprime_dato(dato1);
//   printf("\n");
//   free(dato1);
//   free(dato2);
//////////////////////////////////////////////////////////////////
  printf("Ejemplo de Elementos clonados:\n");
  dato1 = create_set();
  dato2 = create_list();

  printf("Insertamos elementos en un set:\n");
  insert_set(dato1, create_str_ast());
  insert_set(dato1, create_str_ast());
  insert_set(dato1, create_str_ast());

  printf("Insertamos elementos en una lista y la incorporamos al set:\n");
  append(&dato2, create_str_ast());
  append(&dato2, create_str_ast());
  append(&dato2, create_str_ast());

  insert_set(dato1, dato2);
  imprime_dato(dato1);
  printf("\n");

  printf("Clonamos el set y le agregamos dos datos mas a la copia:\n");
  dato3 = copia_dato(dato1);
  insert_set(dato3, create_str_ast());
  insert_set(dato3, create_str_ast());

  printf("El original:\n");
  imprime_dato(dato1);
  printf("\n");

  printf("La copia:\n");
  imprime_dato(dato3);
  printf("\n");

  printf("Destruye la copia:\n");

  deep_free(&dato3);

  printf("El original:\n");
  imprime_dato(dato1);
  printf("\n");

  printf("La copia:\n");
  imprime_dato(dato3);
  printf("\n");
}
