/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "abb.h" /* TAD abb */

#define exit_option 7

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

abb abb_from_file(const char *filepath) {
    FILE *file = NULL;
    abb read_tree;

    read_tree = abb_empty();
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0u;
    unsigned int size = 0u;
    int res = 0;
    res = fscanf(file, " %u ", &size);
    if (res != 1) {
        fprintf(stderr, "Invalid format.\n");
        exit(EXIT_FAILURE);
    }
    while (i < size) {
        abb_elem elem;
        res = fscanf(file," %d ", &(elem));
        if (res != 1) {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        read_tree = abb_add(read_tree, elem);

       ++i;
    }
    fclose(file);
    return read_tree;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* parse the file to obtain an abb with the elements */
    abb tree = abb_from_file(filepath);

    /*dumping the tree*/
//implementacion aqui
    int user_input = 0;
    abb_elem user_modify = 0;

    while(user_input != exit_option){
        printf("\n Elija una opcion entre las siguientes:\n"
               "\n"
               "\t---------------------------------------------------------------\n"
               "\t* 1: Mostrar árbol por pantalla                               |\n"
               "\t* 2: Agregar un elemento                                      |\n"
               "\t* 3: Eliminar un elemento                                     |\n"
               "\t* 4: Chequear existencia de elemento                          |\n"
               "\t* 5: Mostrar longitud del árbol                               |\n"
               "\t* 6: Mostrar raiz, máximo y mínimo del árbol                  |\n"
               "\t* 7: Salir                                                    |\n"
               "\t---------------------------------------------------------------\n"
               "\n Escriba aqui su eleccion: ");
        
        scanf("%i", &user_input);
        if(user_input>7 || user_input < 1){
            printf("\n Porfavor introduzca una opcion valida!!!\n\n\n\n\n\n\n\n\n");
        }

        if (user_input == 1){
            abb_dump(tree);
            if (abb_is_empty(tree)){
                printf("\nArbol vacio\n\n\n\n\n\n\n\n\n");
            }
        }
        else if(user_input == 2){
            printf("\n Introduzca el valor que quiere añadir al arbol: ");
            scanf("%i", &user_modify);
            tree = abb_add(tree, user_modify);

        }
        else if (user_input == 3){
            printf("\n Introduzca el valor que quiere añadir al arbol: ");
                scanf("%i", &user_modify);
            if(!abb_exists(tree, user_modify)){
                printf("\nEl elemento no existe en el arbol\n\n\n\n\n\n\n\n\n");
            }
            else{
                abb_remove(tree, user_modify);
            }
        }
        else if (user_input == 4){
            printf("\n Introduzca el valor que quiere verificar si existe: ");
                scanf("%i", &user_modify);
            if(abb_exists(tree, user_modify)){
                printf("\n El elemento existe en el arbol\n\n\n\n\n\n\n\n\n\n");
            }
            else{
                printf("\nEl elemento no existe en el arbol\n\n\n\n\n\n\n\n\n");
            }
        }
        else if (user_input == 5){
            printf("\nLa longitud del arbol es %u\n\n\n\n\n\n\n\n\n", abb_length(tree));
        }
        else if (user_input == 6){
            if (!abb_is_empty(tree)) {
                printf("\n");
                printf("raiz: %d\n minimo: %d\n maximo: %d\n\n\n\n\n\n\n\n\n", abb_root(tree),
                                                       abb_min(tree),
                                                       abb_max(tree));
            } 
            else {
                printf("\nÁrbol vacío\n");
            }
        }
        
    }

//libero memoria
    tree = abb_destroy(tree);
    /*
     * Modificar e implementar con un ciclo una interfaz que permita al usuario
     * realizar una de las siguientes operaciones en cada iteración:
     *
     * 1 ........ Mostrar árbol por pantalla
     * 2 ........ Agregar un elemento
     * 3 ........ Eliminar un elemento
     * 4 ........ Chequear existencia de elemento
     * 5 ........ Mostrar longitud del árbol
     * 6 ........ Mostrar raiz, máximo y mínimo del árbol
     * 7 ........ Salir
     *
     * Se debe solicitar un número de entrada para realizar una de las acciones.
     *
     * Para las opciones 2, 3 y 4 se le deberá pedir al usuario que ingrese el
     * elemento a agregar, eliminar o chequear respectivamente.
     *
     * Al salir debe liberarse toda la memoria utilizada.
     *
     */
    return (EXIT_SUCCESS);
}
