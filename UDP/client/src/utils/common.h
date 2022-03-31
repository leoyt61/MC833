#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_CHARS 1024

char *remove_leading_spaces(char *str);

char *head(char *str, char *delim);

char *tail(char *str, char *delim);

char *append_to_string(char *string_src, char *new_string);

char *copy_string(char *string_src);

char *get_value_from_text(char *line, char *key);

#endif
