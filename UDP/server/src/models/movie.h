#ifndef MOVIE_H
#define MOVIE_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../utils/common.h"

typedef struct
{
    unsigned int id;
    char *title;
    char *director;
    int year;
    char *genres;
} Movie;

Movie *init_movie(unsigned int id, char *title, char *director, int year, char *genres);

void add_genre(Movie *movie, char *genre);

char *parse_movie_to_text(Movie *movie);

Movie *parse_text_to_movie(char *text);

#endif
