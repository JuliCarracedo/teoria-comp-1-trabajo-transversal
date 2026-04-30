#ifndef TAD_DATA
#define TAD_DATA

#include "String.h"

#define STR 1
#define SET 2
#define LIST 3

typedef struct dataType{
    int nodeType;   /* STR, SET, LIST */
    union{
        str string;
        struct{
            struct dataType* data;
            struct dataType* next;
        };
    };
} dataType;

typedef struct dataType* Tdata;
// create operations
Tdata create_str_ast();
Tdata create_list();
Tdata create_set();
Tdata list_from_str(Tdata);
Tdata str_from_list(Tdata list);

// Funciones agnosticas
void imprime_dato(Tdata);
int equals(Tdata A, Tdata B);
Tdata copia_dato(Tdata);

// STR operations
int compareStr(Tdata, Tdata);
void concatStr(Tdata, Tdata);

// LIST operations
void append(Tdata* list, Tdata elem);
int length(Tdata list);
void concat(Tdata l1, Tdata l2);

int search(Tdata list, Tdata elem);

// SET operations
void insert_set(Tdata set, Tdata elem); // Sin duplicados
int belongs(Tdata elem, Tdata set);
void remove_set(Tdata* set, Tdata elem);
void deep_free(Tdata* set);

// SET Algebra
Tdata union_set(Tdata A, Tdata B);
Tdata intersection_set(Tdata A, Tdata B);
Tdata difference_set(Tdata A, Tdata B);

int subset(Tdata A, Tdata B);

#endif
