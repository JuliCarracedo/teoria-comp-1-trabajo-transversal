#include "String.h"

void creaCadena(str cadena){
  char c;
  int i;

  c = getchar();
  i = 0;

  while(c!='\n' && c!= EOF && i <= MAX_CADENA){
    cadena[i] = c;
    i++;
    c=getchar();
  }

  cadena[i] = '\0';
}

void concatCadena(str cad1, str cad2){
  int i, j;
  i = 0;

  while(cad1[i] != '\0' && i < MAX_CADENA){
    i++;
  }

  j =0;

  while(cad2[j] != '\0' && j < MAX_CADENA){
    cad1[i] = cad2[j];
    i++;
    j++;
  }

  cad1[i] = '\0';
}

int comparaCadena(str cad1, str cad2){
  int i, iguales;

  i = 0;
  iguales = 1;

  while(iguales && cad1[i] != '\0' && cad2[i] != '\0'){
    if(cad1[i] != cad2[i]) iguales = 0;
    i++;
  }

  return iguales;
}

// Cadena 2 -> cadena 1
void copiaCadena(str cad1, str cad2){
  int i;

  i = 0;

  do{
    cad1[i] = cad2[i];
    i++;
  }while(cad2[i] != '\0' && i <= MAX_CADENA );
}

char accessPos(str cadena, int i){
  if(i < MAX_CADENA) return cadena[i];
  else return '\0';
}
