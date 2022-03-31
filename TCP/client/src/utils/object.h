#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *** key_value_pairs;
    unsigned int size;
} Object;

Object * new_object();

void set_value(Object * object, char * key, char * value);

char * get_value(Object * object, char * key);

#endif
