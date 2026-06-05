#include "datatype.h"

int main(){
  Tdata dato1, dato2, dato3;

  dato1 = create_str_ast();
  printf("Cadena:\n");
  imprime_dato(dato1);
  printf("\nLista:\n");
  dato2 = list_from_str(dato1);
  imprime_dato(dato2);
  printf("\nCadena:\n");
  dato3 = str_from_list(dato2);
  imprime_dato(dato3);

}
