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
        else if(d->right == NULL){
            inv = inv && invrep(d->left) && key_less(d->left->key, d->key);
        }
        else if(d->left == NULL){
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

    assert(invrep(dict) && (dict_length(dict) == 0u));
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
        dict->value = def;
    }
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    key_t def=NULL;
    if (dict != NULL){
        if (key_eq(dict->key, word)){
            def = dict->value;
        }
        else if (key_less(word, dict->key)){
            def = dict_search(dict->left, word);
        }
        else{
            def = dict_search(dict->right, word);
        }
    }
    return def;
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
    assert(invrep(dict));
    unsigned int length = 0u;
    if (dict->key != NULL){
        if(dict->left == NULL &&  dict->right == NULL){
            length = 0u;
        }
        else if (dict->left == NULL ){
            length = 1 + dict_length(dict->right);
        }
        else if (dict->right == NULL){
            length = 1 + dict_length(dict->left);
        }
    }
    return length;
}

dict_t dict_remove(dict_t dict, key_t word) {
    if (dict_exists(dict, word)){
       if (word == dict->key){
           dict->right->left = dict->left;
           
           free(dict->key);
           dict->key = NULL;
           
           free(dict->value);
           dict->value = NULL;
           
           free(dict);
       }
       else if (key_less(word, dict->key)){
           dict->left = dict_remove(dict->left, word);
       }
       else {
           dict->right = dict_remove(dict->right, word);
       }
    }
    return dict;
}

dict_t dict_remove_all(dict_t dict) {
    dict_remove(dict, dict->key);
    dict_remove(dict->left, dict->left->key);
    dict_remove(dict->right, dict->right->key);
    return dict;
}

/*void dict_dump(dict_t dict, FILE *file) {
    //implementar

}
*/
dict_t dict_destroy(dict_t dict) {
    dict = dict_remove_all(dict);
    free(dict);
    return dict;
}

