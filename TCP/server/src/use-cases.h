#ifndef USE_CASES_H
#define USE_CASES_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "./utils/request.h"
#include "./utils/response.h"
#include "./repositories/movie_txt_repository.h"

Response *find_movies(Request *request);
Response *find_movie_by_id(Request *request);
Response *register_movie(Request *request);
Response *append_genre_to_movie(Request *request);
Response *delete_movie(Request *request);

#endif
