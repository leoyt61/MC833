#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include "./services/movie_service.h"

#define INPUT_MAX_CHARS 128

void start_interface();

void show_movies_interface();

void show_movie_by_id_interface();

void add_genre_to_movie_interface(int id);

void create_movie_interface();

void remove_movie_by_id_interface(int id);

#endif
