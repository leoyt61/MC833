#include "use-cases.h"

Response *find_movies(Request *request) {
    int count;
    Movie **fetched_movies;
    char *genre = get_query(request->query, "genre");
    
    if (genre != NULL) {
        count = get_movies_count_by_genre(genre);
        fetched_movies = get_movies_by_genre(genre);
    } else {
        count = get_movies_count();
        fetched_movies = get_movies();
    }

    if (count == 0 || fetched_movies == NULL) {
        return create_response(NOT_FOUND, "text/plain", "No movies found");
    }

    char *response_body = NULL;

    for (int i = 0; i < count; i++) {
        char *movie_text = parse_movie_to_text(fetched_movies[i]);
        char * head_text = malloc(sizeof(char) * 100);
        response_body = append_to_string(response_body, head_text);
        response_body = append_to_string(response_body, movie_text);
        response_body = append_to_string(response_body, "\n");
        free(movie_text);
        free(head_text);
    }

    return create_response(OK, "text/plain", response_body);
};

Response *find_movie_by_id(Request *request) {
    char *req_id = get_value(request->path_variables, "id");

    if (req_id == NULL) return create_response(BAD_REQUEST, "text/plain", "Invalid parameter: id");

    int id = atoi(req_id);

    Movie *fetched_movie = get_movie_by_id(id);

    if (fetched_movie == NULL) return create_response(NOT_FOUND, "text/plain", "Movie not found");

    char *response_body = parse_movie_to_text(fetched_movie);
    return create_response(OK, "text/plain", response_body);
};

Response *register_movie(Request *request) {    
    char *req_id = get_value(request->body, "id");
    char *req_title = get_value(request->body, "title");
    char *req_director = get_value(request->body, "director");
    char *req_year = get_value(request->body, "year");
    char *req_genres = get_value(request->body, "genres");

    if (req_id == NULL) return create_response(BAD_REQUEST, "text/plain", "Missing parameter: id");
    if (req_title == NULL) return create_response(BAD_REQUEST, "text/plain", "Missing parameter: title");
    if (req_director == NULL) return create_response(BAD_REQUEST, "text/plain", "Missing parameter: director");
    if (req_year == NULL) return create_response(BAD_REQUEST, "text/plain", "Missing parameter: year");
    if (req_genres == NULL) return create_response(BAD_REQUEST, "text/plain", "Missing parameter: genres");

    int id = atoi(req_id);
    int year = atoi(req_year);

    Movie **fetched_movies = get_movies();
    int count = get_movies_count();

    for (int i = 0; i < count; i++) {
        if (fetched_movies[i]->id == id) {
            return create_response(BAD_REQUEST, "text/plain", "Movie already exists with id");
        }
    }

    Movie *movie = init_movie(id, req_title, req_director, year, req_genres);

    save_movie(movie);

    return create_response(CREATED, "text/plain", "Movie saved");
};

Response *append_genre_to_movie(Request *request) {
    char *req_id = get_value(request->path_variables, "id");

    if (req_id == NULL) return create_response(BAD_REQUEST, "text/plain", "Invalid parameter: id");

    int id = atoi(req_id);

    char *new_genre = get_value(request->body, "genre");

    if (new_genre == NULL) return create_response(BAD_REQUEST, "text/plain", "Missing parameter: genre");

    Movie *fetched_movie = get_movie_by_id(id);

    if (fetched_movie == NULL) return create_response(NOT_FOUND, "text/plain", "Movie not found");

    if (movie_has_genre(fetched_movie, new_genre)) {
        return create_response(BAD_REQUEST, "text/plain", "Movie already has this genre");
    }
    
    add_genre_to_movie(id, new_genre);

    return create_response(OK, "text/plain", "Genre added to movie");
};

Response *delete_movie(Request *request) {
    char *req_id = get_value(request->path_variables, "id");

    if (req_id == NULL) return create_response(BAD_REQUEST, "text/plain", "Invalid parameter: id");

    int id = atoi(req_id);

    if(remove_movie(id)) {
        return create_response(BAD_REQUEST, "text/plain", "Movie not found");
    }

    return create_response(OK, "text/plain", "Movie deleted");
};
