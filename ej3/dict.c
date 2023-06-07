#include <assert.h>
#include <stdlib.h>
#include "dict.h"
#include "key_value.h"

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

static bool invrep(dict_t d) {
    bool inv = false;
    if (inv != NULL){
        if(d->key == NULL || (d->left == NULL && d->right == NULL)){
            inv = true;
        }
        else if(d->right = NULL){
            inv = inv && invrep(d->left) && key_less(d->left->key, d->key);
        }
        else if(d->left = NULL){
            inv = inv && invrep(d->right) && !key_less(d->right->key, d->key);
        }
        else{
            inv = inv && invrep(d->left) && invrep(d->right) && key_less(d->left->key, d->key) && !key_less(d->right->key, d->key);
        }
    }
    return inv;
}

dict_t dict_empty(void) {
    dict_t dict = NULL;
    dict = malloc(sizeof(struct _node_t));
    dict->left = NULL;
    dict->right = NULL;
    dict->key = NULL;
    dict->value = NULL;

    assert(dict != NULL && (dict_length(dict) == 0u));
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    
    if(dict_exists(dict, word)){
        if (key_eq(dict->key, word)){
            free(dict->value);
            dict->value = NULL;
            dict->value = def;
        }
        else if (key_less(dict->key, word)){
            dict->left = dict_add(dict->left, word, def);
        }
        else{
            dict->right = dict_add(dict->right, word, def);
        }
    }
    else{
        if (dict->key == NULL){
            dict->key = word;
            dict->value = def;
        }
    }
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    key_t def=NULL;
    
    return NULL;
}

bool dict_exists(dict_t dict, key_t word) {
    /* needs implementation */
    return false;
}

unsigned int dict_length(dict_t dict) {
    /* needs implementation */
    return 0u;
}

dict_t dict_remove(dict_t dict, key_t word) {
    /* needs implementation */
    return dict;
}

dict_t dict_remove_all(dict_t dict) {
    /* needs implementation */
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    /* needs implementation */
}

dict_t dict_destroy(dict_t dict) {
    /* needs implementation */
    return dict;
}

