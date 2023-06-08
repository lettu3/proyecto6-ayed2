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
    if (d != NULL){
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
    if (dict!=NULL){
        if(dict->key == NULL){
            dict->key = word;
            dict->value = def;
        }
        else if (key_eq(dict->key, word)){
            free(dict->value);
            dict->value = def;
        }
        else if (key_less(word, dict->key)){
            dict->left = dict_add(dict->left, word, def);
        }
        else{
            dict->right = dict_add(dict->right, word, def);
        }
    }
    else{
        dict = dict_empty();
        dict->key = word;
        dict->left = def;
    }
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    key_t def=NULL;
    /* need implementation */
    return NULL;
}

bool dict_exists(dict_t dict, key_t word) {
    bool exists = false;
    if (dict != NULL && dict->key != NULL){
        if (key_less(dict->key, word)){
            exists = dict_exists(dict->left, word);
        }
        else if (key_eq(dict->key, word)){
            exists = true;
        }
        else{
            exists = dict_exists(dict->right, word);
        }
    }
    return exists;
}

unsigned int dict_length(dict_t dict) {
    unsigned int length = 0u;
    while (dict != NULL && dict->key != NULL)
    {
        length = length + 1 + dict_length(dict->left) + dict_length(dict->right);
    }
    
    return length;
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
    dict = dict_remove_all(dict);
    free(dict);
    return dict;
}

