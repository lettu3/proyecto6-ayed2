#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

static bool invrep(abb tree) {
    bool inv = true;

    if (tree == NULL || (tree->left == NULL && tree->right == NULL)){
        inv = true;
    }

    else if (tree->right == NULL){
        inv = inv && elem_less(tree->left->elem, tree->elem) && invrep(tree->left);
    }

    else if (tree->left == NULL){
        inv = inv && !elem_less(tree->right->elem, tree->elem) && invrep(tree->right);
    }

    else {
        inv = inv && 
              elem_less(tree->left->elem, tree->elem)  &&
              !elem_less(tree->right->elem, tree->elem) &&
              invrep(tree->left) &&
              invrep(tree->left);
    }

    return inv;
}

abb abb_empty(void) {
    abb tree = NULL;
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}


static bool is_leaf(abb tree){
    bool res = tree->left == NULL  && tree->right == NULL;
    return res;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));

    if (abb_is_empty(tree)){
        abb new = NULL;
        new = malloc(sizeof(struct _s_abb));
        new->elem = e;
        new->left = NULL;
        new->right = NULL;
        tree = new;
    }
    else if (elem_less(e, tree->elem)){
        tree->left = abb_add(tree->left, e);
    }
    else if (!elem_less(e, tree->elem)){
        tree->right = abb_add(tree->right, e);
    }

    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree) {
    bool is_empty=false;
    assert(invrep(tree));
    is_empty = (tree == NULL);
    return is_empty;
}

bool abb_exists(abb tree, abb_elem e) {
    bool exists=false;
    assert(invrep(tree));

    if (abb_is_empty(tree)){
        exists = false;
    }

    else if (elem_eq(e, tree->elem)){
        exists = true;
    }

    else if (elem_less(e, tree->elem)){
        exists = abb_exists(tree->left, e);
    }

    else {
        exists = abb_exists(tree->right, e);
    }

    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0;
    assert(invrep(tree));

    if(!abb_is_empty(tree)){
        length = 1 + abb_length(tree->left) + abb_length(tree->right);
    }

    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));
    //implementacion
    if (abb_exists(tree, e)){
        if (elem_eq(e, tree->elem)){
            //
            if (tree->left == NULL && tree->right == NULL){
                free(tree);
                tree = NULL;
            }
            else if (tree->left == NULL){
                abb auxtree = tree;
                tree = tree->right;
                free(auxtree);
                auxtree = NULL;
            }
            else if (tree->right == NULL){
                abb auxtree = tree;
                tree = tree->left;
                free(auxtree);
                auxtree = NULL;
            }
            else{
                abb auxtree_search = tree->left;  //voy a buscar al elemento mas grande del subarbol izquierdo
                while (!is_leaf(auxtree_search)){
                    auxtree_search = auxtree_search->right;
                }
                tree->elem = auxtree_search->elem;  //ahora este elemento es la raiz de mi arbol/subarbol
                tree->left = abb_remove(tree->left, tree->elem);               //elimino esa hoja             
            }
            //
        }
        else if (elem_less(e, tree->elem)){
            tree->left = abb_remove(tree->left, e);
        }
        else{
            tree->right = abb_remove(tree->right, e);
        }        
    }
    //implementacion
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}


abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    
    root = tree->elem;

    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    abb aux = tree;
    assert(invrep(tree) && !abb_is_empty(tree));
    while (!abb_is_empty(aux)){
        max_e = aux->elem;
        aux = aux->right;
    }
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    abb aux = tree;
    assert(invrep(tree) && !abb_is_empty(tree));
    while (!abb_is_empty(aux)){
        min_e = aux->elem;
        aux = aux->left;
    }
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree) {
    assert(invrep(tree));
    if (tree != NULL) {
        printf("%d ", tree->elem);
        abb_dump(tree->left);

        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));

    if (!abb_is_empty(tree)){
        tree->left = abb_destroy(tree->left);
        tree->right = abb_destroy(tree->right);
        free(tree);
        tree = NULL;
    }

    assert(tree == NULL);
    return tree;
}

