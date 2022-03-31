#ifndef MOVIE_TXT_REPOSITORY_H
#define MOVIE_TXT_REPOSITORY_H

#include <sys/mman.h>
#include "../models/movie.h"
#include "../utils/file_handler.h"

#define MAX_MOVIES 100

char *movies_dir;

void init_movies_repository(char *dir);

void save_movie(Movie *movie);

int add_genre_to_movie(unsigned int id, char *genre);

int movie_has_genre(Movie *movie, char *genre);

Movie **get_movies_by_genre(char *genre);

Movie *get_movie_by_id(unsigned int id);

Movie **get_movies();

int get_movies_count();

int get_movies_count_by_genre(char *genre);

int remove_movie(int id);

#endif
