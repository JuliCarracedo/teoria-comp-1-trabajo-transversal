#include "datatype.h"

Tdata create_str_ast(){
    Tdata data;
    data = (Tdata) malloc(sizeof (dataType));
    data->nodeType = STR;
    printf("Ingreasa la cadena deseada:");
    creaCadena(data->string);

    return data;
}

Tdata create_str_from_char(char c){
    Tdata data;
    data = (Tdata) malloc(sizeof (dataType));
    data->nodeType = STR;
    data->string[0]= c;
    data->string[1]= '\0';

    return data;
}

Tdata create_empty_str_ast(){
    Tdata data;
    data = (Tdata) malloc(sizeof (dataType));
    data->nodeType = STR;
    copiaCadena(data->string, "");

    return data;
}

Tdata create_list(){
    Tdata data;
    data = (Tdata) malloc(sizeof (dataType));
    data->nodeType = LIST;
    data->data = NULL;
    data->next = NULL;

    return data;
}

Tdata create_set(){
    Tdata data;
    data = (Tdata) malloc(sizeof (dataType));
    data->nodeType = SET;
    data->data = NULL;
    data->next = NULL;

    return data;
}

Tdata list_from_str(Tdata string){
    Tdata list;
    char aux;
    int i;

    if(string == NULL) return NULL;
    else if(string->nodeType != STR) return NULL;
    else{
        list = create_list();
        i = 0;
        aux = accessPos(string->string, i);
        while(aux != '\0'){
            append(&list, create_str_from_char(aux));
            aux = accessPos(string->string, ++i);
        }

        return list;
    }
}

Tdata str_from_list(Tdata list){
    Tdata ast_str;

    ast_str = create_empty_str_ast();
    if(list == NULL) return NULL;
    else if(list->nodeType != LIST) return NULL;
    else{
        while(list != NULL){
            if(list->data->nodeType == STR){
                concatStr(ast_str, list->data);
            }
            list = list->next;
        }
    }

    return ast_str;
}

void imprime_lista(Tdata);
void imprime_set(Tdata);

void imprime_dato(Tdata data){
    if(data == NULL) return;

    switch (data->nodeType){
        case STR:
            printf("\"%s\"", data->string);
            break;
        case LIST:
            printf("[ ");
            while(data != NULL){
                imprime_dato(data->data);
                printf("; ");
                data = data->next;
            }
            printf(" ]");
            break;
        case SET:
            printf("{ ");
            while(data != NULL){
                imprime_dato(data->data);
                printf("; ");
                data = data->next;
            }
            printf(" }");
            break;

        default:
            break;
    }
}

int compareStr(Tdata dat_1, Tdata dat_2){
    int comp;
    if(dat_1->nodeType != STR || dat_2->nodeType != STR) comp = 1;
    else comp = comparaCadena(dat_1->string, dat_2->string);
    return comp;
}

void concatStr(Tdata dat_1, Tdata dat_2){
    if(dat_1->nodeType != STR || dat_2->nodeType != STR) return;
    concatCadena(dat_1->string, dat_2->string);
}

Tdata copia_dato(Tdata data){
    Tdata nuevo;
    if (data == NULL) {
        return NULL;
    }
    else {
        nuevo = (Tdata) malloc(sizeof(dataType));
        nuevo->nodeType = data->nodeType;

        switch (data->nodeType){
            case STR:
                copiaCadena(nuevo->string, data->string);
                break;
            default:
                nuevo->data = copia_dato(data->data);
                nuevo->next = copia_dato(data->next);
                break;
        }

        return nuevo;
    }
}

// d2 -> d1
void append(Tdata * lista, Tdata elem){
    Tdata actual;
    actual = *lista;
    if(actual == NULL) return;
    if(actual->nodeType != LIST) return;

    if(actual->data == NULL){
        actual->data = copia_dato(elem);
    } else {
        while(actual->next != NULL){
            actual = actual->next;
        }
        actual->next = create_list();
        (actual->next)->data = copia_dato(elem);
        (actual->next)->next = NULL;
    }
}

int length(Tdata lista){
    int i;

    if(lista == NULL) return -1;
    if(lista->nodeType != LIST) return -1;

    i=0;
    while(lista != NULL){
        if(lista->data != NULL) i++;
        lista = lista->next;
    }

    return i;
}

//c1 = [c1, c2];
void concat(Tdata c1, Tdata c2){
    if(c1->nodeType != LIST || c2->nodeType != LIST){ return; }
    while(c2 != NULL){
        append(&c1, c2->data);
        c2 = c2->next;
    }
}


int belongs(Tdata elem, Tdata set);
int equals(Tdata elem1, Tdata elem2){
    int is_equal;
    Tdata aux;
    is_equal = 0;
    if(elem1 == NULL || elem2 == NULL){ is_equal = elem1 == NULL && elem2 == NULL; }
    else if(elem1->nodeType != elem2->nodeType){ is_equal = 0;}
    else if(elem1->nodeType == STR){
        is_equal = compareStr(elem1, elem2);
    } else if(elem1->nodeType == LIST){
        if(length(elem1) != length(elem2)) is_equal = 0;
        else{
            is_equal = 1;
            while(elem1 != NULL && is_equal == 1){
                is_equal = equals(elem1->data, elem2->data);
                elem1 = elem1->next;
                elem2 = elem2->next;
            }
            return is_equal;
        }
    } else if(elem1->nodeType == SET){
        is_equal = 1;
        aux = elem1;
        while(aux != NULL && is_equal == 1){
            is_equal = belongs(aux->data, elem2);
            aux = aux->next;
        }
        aux = elem2;
        while(aux != NULL && is_equal == 1){
            is_equal = belongs(aux->data, elem1);
            aux = aux->next;
        }
    }

    return is_equal;
}

int belongs(Tdata elem, Tdata set){
    int res;
    res = 0;
    if(set->nodeType != SET) res = -1;
    while(set != NULL && res == 0){
        res = equals(set->data, elem);
        set = set->next;
    }
    return res;
}

int search(Tdata list, Tdata elem){
    int is_present;
    is_present = 0;
    if(list->nodeType != LIST) is_present = -1;
    else{
        while(list!=NULL && is_present == 0){
            if(equals(elem, list->data)) is_present = 1;
            list = list->next;
        }
    }

   return is_present;
}

void deep_free(Tdata *data){
    Tdata actual;
    actual = *data;
    if ((*data) == NULL) return;
    else{
        switch (actual->nodeType)
        {
        case STR:
            free(actual);
            break;
        default:
            deep_free(&(actual->data));
            deep_free(&(actual->next));
            free(actual);
        }
    }
    (*data) = NULL;
}

void remove_set(Tdata* set, Tdata elem){
    Tdata actual, siguiente;
    int encontrado;
    actual = *set;

    if(actual == NULL){ return; }
    else if(actual->nodeType!= SET){ return; }
    else if(equals(actual->data, elem)){
        if(actual->next == NULL){
            *set = NULL;
        } else{
            *set = actual->next;
        }
        deep_free(&(actual->data));
        free(actual);
    } else{
        siguiente = actual->next;
        if(siguiente == NULL) return;
        encontrado = equals(siguiente->data, elem);
        while(siguiente->next != NULL && !encontrado){
            actual = siguiente;
            siguiente = siguiente->next;
            encontrado = equals(siguiente->data, elem);
        }
        if(encontrado){
            actual->next = siguiente->next;
            deep_free(&siguiente->data);
            free(siguiente);
        }
    }
}

void insert_set(Tdata set, Tdata elem){
    Tdata new;
    if(set == NULL) return;
    else if(set->nodeType != SET) return;
    else{
        if(set->data == NULL){
            set->data = copia_dato(elem);
        }
        else if(!belongs(elem, set)){
            while(set->next != NULL) {
                set = set->next;
            }
            new = (Tdata) malloc(sizeof(dataType));
            new->nodeType = SET;
            new->next = NULL;
            new->data = copia_dato(elem);
            set->next = new;
        }
    }
}

Tdata union_set(Tdata set1, Tdata set2){
    Tdata new;
    if(set1->nodeType != SET || set2->nodeType != SET){
        return NULL;
    } else {
        new = (Tdata) malloc(sizeof(dataType));
        new->nodeType = SET;
        new->data = NULL;
        new->next = NULL;

        while(set1 != NULL){
            insert_set(new, set1->data);
            set1 = set1->next;
        }
         while(set2 != NULL){
            insert_set(new, set2->data);
            set2 = set2->next;
        }
    }
    return new;
}

Tdata difference_set(Tdata set1, Tdata set2){
    Tdata new;
    if(set1->nodeType != SET || set2->nodeType != SET){
        return NULL;
    } else {
        new = (Tdata) malloc(sizeof(dataType));
        new->nodeType = SET;
        new->data = NULL;
        new->next = NULL;

        while(set1 != NULL){
            if(!belongs(set1->data, set2)) insert_set(new, set1->data);
            set1 = set1->next;
        }
    }
    return new;
}

Tdata intersection_set(Tdata set1, Tdata set2){
    Tdata new, aux;
    if(set1->nodeType != SET || set2->nodeType != SET){
        return NULL;
    } else {
        new = (Tdata) malloc(sizeof(dataType));
        new->nodeType = SET;
        new->data = NULL;
        new->next = NULL;
        aux = set1;
        while(aux != NULL){
            if(belongs(aux->data, set2)) insert_set(new, aux->data);
            aux = aux->next;
        }

        aux = set2;
        while(aux != NULL){
            if(belongs(aux->data, set1)) insert_set(new, aux->data);
            aux = aux->next;
        }
    }
    return new;
}

