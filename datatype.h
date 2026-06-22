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
Tdata str_from_list(Tdata);
Tdata create_str_from_chain(str);

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

Tdata pop(Tdata * list); //LIST AND SET

// SET Algebra
Tdata union_set(Tdata A, Tdata B);
Tdata intersection_set(Tdata A, Tdata B);
Tdata difference_set(Tdata A, Tdata B);

int size(Tdata A);

int a_subset_of_b(Tdata A, Tdata B);

int isSet(Tdata elem);
int isStr(Tdata elem);
int isList(Tdata elem);

#endif
