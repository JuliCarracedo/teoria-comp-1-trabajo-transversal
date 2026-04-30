#ifndef TAD_CADENA
#define TAD_CADENA
#define MAX_CADENA 100
#include <stdio.h>
#include <stdlib.h>

typedef char str[MAX_CADENA];

void creaCadena(str);
void concatCadena(str, str);
void copiaCadena(str, str);
char accessPos(str, int);
void writePos(str, int, char);
int comparaCadena(str, str);

#endif
