#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_CHARS 1024

char *remove_leading_spaces(char *str);

char *tail(char *str, char *delim);

char *append_to_string(char *string_src, char *new_string);

char *get_value(char *line, char *key);

char *get_query(char *line, char *key);

#endif
