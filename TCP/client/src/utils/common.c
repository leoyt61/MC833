#include "./common.h"

char *remove_leading_spaces(char *str)
{
    while (isspace(*str))
    {
        str++;
    }
    return str;
};

char *head(char *str, char *delim)
{
    char *allocated_str = (char *)malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(allocated_str, str);
    char *aux = strstr(allocated_str, delim);
    if (aux == NULL)
        return allocated_str;
    *aux = '\0';
    return allocated_str;
};

char *tail(char *str, char *delim)
{
    char *allocated_str = (char *)malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(allocated_str, str);
    char *aux = strstr(allocated_str, delim);

    if (aux == NULL)
        return NULL;

    *aux = '\0';
    return aux + strlen(delim);
};

char *append_to_string(char *string_src, char *new_string)
{
    if (string_src == NULL)
    {
        return new_string;
    }
    char *new_string_src = malloc(sizeof(char) * (strlen(string_src) + strlen(new_string) + 1));
    sprintf(new_string_src, "%s%s", string_src, new_string);
    return new_string_src;
};

char *copy_string(char *string_src)
{
    char *string_dest = malloc(sizeof(char) * (strlen(string_src) + 1));
    int i = 0;
    while (string_src[i] != '\0')
    {
        string_dest[i] = string_src[i];
        i++;
    }
    return string_dest;
};

char *get_value_from_text(char *line, char *key)
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
