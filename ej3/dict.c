#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "dict.h"
#include "key_value.h"

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};


struct _node_t * create_node(key_t word, value_t def){
    struct _node_t * new = NULL;
    new = malloc(sizeof(struct _node_t));
    new->key = word;
    new->value = def;
    new->right = NULL;
    new->left = NULL;

    return new;
}

static bool invrep(dict_t d){
    bool inv = true;

    if (d == NULL || (d->left == NULL && d->right == NULL)){
        inv = true;
    }

    else if (d->right == NULL){
        inv = inv && key_less(d->left->key, d->key) && invrep(d->left);
    }

    else if (d->left == NULL){
        inv = inv && !key_less(d->right->key, d->key) && invrep(d->right);
    }

    else {
        inv = inv && 
              key_less(d->left->key, d->key)  &&
              !key_less(d->right->key, d->key) &&
              invrep(d->left) &&
              invrep(d->left);
    }

    return inv;
}

dict_t dict_empty(void) {
    dict_t dict = NULL;
    assert(invrep(dict) && dict_length(dict) == 0u);
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(invrep(dict));
    dict_t p = NULL;
    if(dict == NULL){
        p = create_node(word, def);
        dict = p;
    }
    else{
        if(key_eq(dict->key, word)){
            dict->key = key_destroy(dict->key);
            dict->value = value_destroy(dict->value);
            dict->key = word;
            dict->value = def;
        }
        else if(key_less(dict->key, word)){
            dict->right = dict_add(dict->right, word, def);
        }
        else if(key_less(word, dict->key)){
            dict->left = dict_add(dict->left, word, def);
        }
    }
    assert(invrep(dict) && value_eq(def, dict_search(dict, word)));
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    assert(invrep(dict));
    value_t def = NULL;
    if(dict_length(dict) != 0u){
        if(key_eq(dict->key, word)){
            def = dict->value;
        }
        else if(key_less(dict->key, word)){
            def = dict_search(dict->right, word);
        }
        else{
            def = dict_search(dict->left, word);
        }
    }
    assert((def != NULL) == dict_exists(dict, word));
    return def;
}

bool dict_exists(dict_t dict, key_t word) {
    assert(invrep(dict));
    bool exists = false;
    if(dict != NULL){
        if(key_eq(dict->key, word)){
            exists = true;
        }
        else if(key_less(dict->key, word)){
            exists = dict_exists(dict->right, word);
        }
        else if(key_less(word, dict->key)){
            exists = dict_exists(dict->left, word);
        }
    }
    assert(invrep(dict));
    return exists;
}

unsigned int dict_length(dict_t dict) {
    assert(invrep(dict));
    unsigned int n = 0u;
    if(dict != NULL){
        n = (dict_length(dict->right) + dict_length(dict->left) + 1u);
    }
    assert(invrep(dict) && (dict != NULL || n == 0u));
    return n;
}

static dict_t min_dict_key(dict_t dict){
    dict_t p = dict;
    while(p->left != NULL){
        p = p->left;
    }
    return p;
}

dict_t dict_remove(dict_t dict, key_t word) {
    assert(invrep(dict));
    dict_t p = NULL;
    if(dict != NULL){
        if(key_eq(dict->key, word)){
            if(dict->right == NULL){
                p = dict;
                dict = dict->left;
                p->value = value_destroy(p->value);
                p->key = key_destroy(p->key);
                free(p);
                p = NULL;
            }
            else if(dict->left == NULL){
                p = dict;
                dict = dict->right;
                p->key = key_destroy(p->key);
                p->value = value_destroy(p->value);
                free(p);
                p = NULL;
            }
            else{
                p = min_dict_key(dict->right);
                dict->value = value_destroy(dict->value);
                dict->key = key_destroy(dict->key);
                dict->key = key_clone(p->key);
                dict->value = value_clone(p->value);
                dict->right = dict_remove(dict->right, dict->key);
            }
        }
        else if(key_less(dict->key, word)){
            dict->right = dict_remove(dict->right, word);
        }
        else{
            dict->left = dict_remove(dict->left, word);
        }
    }
    assert(invrep(dict) && !dict_exists(dict, word));
    return dict;
}

dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));
    if(dict != NULL){
        dict->left = dict_remove_all(dict->left);
        dict->right = dict_remove_all(dict->right);
        dict = dict_remove(dict, dict->key);
    }
    assert(invrep(dict) && dict_length(dict) == 0u);
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict) && file != NULL);
    if (dict != NULL){
        key_dump(dict->key, file);
        fprintf(file, ": ");
        value_dump(dict->value, file);
        fprintf(file, "\n");
        dict_dump(dict->left, file);
        dict_dump(dict->right, file);
    }
}

dict_t dict_destroy(dict_t dict) {
    assert(invrep(dict));
    if(dict != NULL){
        dict->left = dict_destroy(dict->left);
        dict->right = dict_destroy(dict->right);
        dict->key = key_destroy(dict->key);
        dict->value = value_destroy(dict->value);
        free(dict);
    }
    dict = NULL;
    assert(dict == NULL);
    return dict;
}