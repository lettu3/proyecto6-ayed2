#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "string.h"

int main(){

    string str1 = string_create("arbol");
    string str2 = string_create("bosque");
    string str3 = string_create("arbol");


    printf("\narbol es menor que bosque?: %i\n", string_less(str1, str2));
    printf("\narbol igual a bosque?: %i\n", string_eq(str1, str2));
    printf("\narbol igual a bosque?: %i\n", string_eq(str1, str3));
    
    str1 = string_destroy(str1);
    str2 = string_destroy(str2);
    str3 = string_destroy(str3);
    return(EXIT_SUCCESS);
}