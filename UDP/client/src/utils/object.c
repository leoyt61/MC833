#include "./object.h"

Object *new_object()
{
    Object *object = (Object *) malloc(sizeof(Object));
    object->size = 0;
    object->key_value_pairs = (char ***) malloc(sizeof(char **));
    object->key_value_pairs[0] = (char **) malloc(sizeof(char *) * 2);
    return object;
};

void set_value(Object *object, char *key, char *value)
{
    if (get_value(object, key) != NULL) {
        for (int i = 0; i < object->size; i++) {
            if (strcmp(object->key_value_pairs[i][0], key) == 0) {
                object->key_value_pairs[i][1] = value;
            }
        }
        return;
    }

    object->key_value_pairs[object->size][0] = key;
    object->key_value_pairs[object->size][1] = value;
    object->size++;
    object->key_value_pairs = (char ***) realloc(object->key_value_pairs, sizeof(char **) * (object->size + 1));
    object->key_value_pairs[object->size] = (char **) malloc(sizeof(char *) * 2);
};

char *get_value(Object *object, char *key)
{
    for (int i = 0; i < object->size; i++) {
        if (strcmp(object->key_value_pairs[i][0], key) == 0) {
            return object->key_value_pairs[i][1];
        }
    }
    return NULL;
};
