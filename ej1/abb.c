#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>
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
    if(tree == NULL){
        inv = true;
    }
    else{
        if (tree->left != NULL){
            inv = inv && elem_less(tree->left->elem, tree->elem);
        }
        else if (tree->right != NULL){
            inv = inv && elem_less(tree->elem, tree->right->elem);
        }
        inv = inv && invrep(tree->right) && invrep(tree->left);
    }
    return inv;
}

abb abb_empty(void) {
    abb tree = NULL;
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));
    if (abb_is_empty(tree)){
        abb new = malloc(sizeof(struct _s_abb));
        new->elem = e;
        new->left = NULL;
        new->right = NULL;
        tree = new;
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
    while (!exists && !abb_is_empty(tree)){
        if(elem_eq(e, tree->elem)){
            exists = true;
        }
        else if (elem_less(e, tree->elem)) {
            exists = abb_exists(tree->left, e);
        }
        else if (elem_less(tree->elem, e)){
            exists = abb_exists(tree->right, e);
        }
    }
    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0;
    assert(invrep(tree));
    if(!abb_is_empty(tree)){
        length =  1 + abb_length(tree->left) + abb_length(tree->right);
    }
    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));
    /*
     * Needs implementation
     */
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}


abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree->elem;                              //devuelvo el primer elemento al que apunta el arbol
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e = INT_MIN;
    abb auxtree = tree;
    assert(invrep(tree) && !abb_is_empty(tree));
    while(!abb_is_empty(tree->right)){
        auxtree = auxtree ->right;
    }
    max_e = auxtree -> elem;
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e = INT_MAX;
    abb auxtree = tree;
    assert(invrep(tree) && !abb_is_empty(tree));
    while (!abb_is_empty(tree->left)){
        auxtree = auxtree->left;
    }
    min_e = auxtree->elem;
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree) {
    assert(invrep(tree));
    if (tree != NULL) {
        abb_dump(tree->left);
        printf("%d ", tree->elem);
        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));
    if(!abb_is_empty(tree)){
        tree->left= abb_destroy(tree->left);
        tree->right = abb_destroy(tree->right);
    }
    free(tree);
    tree = NULL;
    assert(tree == NULL);
    return tree;
}

