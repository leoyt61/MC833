#ifndef MOVIE_SERVICE_H
#define MOVIE_SERVICE_H

#include "../utils/pseudo_http.h"

char *movie_service_base_url;

void init_movie_service();

char *get_movies(Object *filter, int show_more_infos);

char **get_list_of_movies_with_id_and_title(char *response_body, int *list_size);

void sort_list_of_movies_by_id(char **list_of_movies_and_ids, int list_size);

char * join_list_of_movies(char **list_of_movies_and_ids, int list_size);

char *get_movie_by_id(int id);

char *add_genre_to_movie(int movie_id, char *genre);

char *create_movie(Object *movie);

char *remove_movie(int movie_id);

#endif
