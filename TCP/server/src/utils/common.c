#include "./common.h"

char *remove_leading_spaces(char *str)
{
    while (isspace(*str))
    {
        str++;
    }
    return str;
};

char *tail(char *str, char *delim)
{
    char *p = strstr(str, delim);

    if (p == NULL)
        return NULL;

    *p = '\0';
    return p + strlen(delim);
};

char *append_to_string(char *string_src, char *new_string) {
    if (string_src == NULL) {
        return new_string;
    }
    char *new_string_src = malloc(sizeof(char) * (strlen(string_src) + strlen(new_string) + 1));
    sprintf(new_string_src, "%s%s", string_src, new_string);
    return new_string_src;
};

char *get_value(char *line, char *key)
{
    if (line == NULL) return NULL;

    char *key_with_colon = malloc(strlen(key) + 2);
    sprintf(key_with_colon, "%s:", key);
    char *value = malloc(sizeof(char) * MAX_CHARS);
    char *line_copy = malloc(sizeof(char) * MAX_CHARS);
    strcpy(line_copy, line);
    line_copy = strtok(line_copy, "\n");
    while (line_copy != NULL)
    {
        if (strstr(line_copy, key_with_colon) != NULL)
        {
            value = tail(line_copy, key_with_colon);
            return remove_leading_spaces(value);
        }
        line_copy = strtok(NULL, "\n");
    }
    return NULL;
};

char *get_query(char *line, char *key)
{
    if (line == NULL) return NULL;

    char *key_with_equal = malloc(strlen(key) + 2);
    sprintf(key_with_equal, "%s=", key);
    char *value = malloc(sizeof(char) * MAX_CHARS);
    char *line_copy = malloc(sizeof(char) * MAX_CHARS);
    strcpy(line_copy, line);
    line_copy = strtok(line_copy, "&");
    while (line_copy != NULL)
    {
        if (strstr(line_copy, key_with_equal) != NULL)
        {
            value = tail(line_copy, key_with_equal);
            return remove_leading_spaces(value);
        }
        line_copy = strtok(NULL, "&");
    }
    return NULL;
};
