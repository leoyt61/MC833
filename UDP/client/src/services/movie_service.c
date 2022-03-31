#include "./movie_service.h"

void init_movie_service()
{
    char *ENV_HOST = getenv("MC833_P2_ENV_HOST");
    char *ENV_PORT = getenv("MC833_P2_ENV_PORT");

    if (ENV_HOST == NULL)
    {
        printf("Error: ENV_HOST not set!\n");
        exit(1);
    }

    if (ENV_PORT == NULL)
    {
        printf("Error: ENV_PORT not set!\n");
        exit(1);
    }

    char *base_url = malloc(sizeof(char) * (strlen(ENV_HOST) + strlen(ENV_PORT) + 9));
    sprintf(base_url, "http://%s:%s/%s", ENV_HOST, ENV_PORT, "movies");
    movie_service_base_url = copy_string(base_url);
};

char *get_movies(Object *filter, int show_more_infos)
{
    Response *response = pseudo_http("GET", movie_service_base_url, NULL, filter, NULL);
    if (response->status == OK && show_more_infos == 0)
    {
        int *list_size = malloc(sizeof(int));
        char **list_of_movies_and_ids = get_list_of_movies_with_id_and_title(response->body, list_size);
        sort_list_of_movies_by_id(list_of_movies_and_ids, *list_size);
        return join_list_of_movies(list_of_movies_and_ids, *list_size);
    }
    if (response->status == SERVER_ERROR && strcmp(response->body, "TRY_AGAIN") == 0)
    {
        return response->message;
    }
    return response->body;
};

char **get_list_of_movies_with_id_and_title(char *response_body, int *list_size)
{
    char **list_of_movies_and_ids = malloc(sizeof(char *) * MAX_CHARS);
    char *body = copy_string(response_body);
    int i = 0;
    while (body != NULL && strcmp(body, "") != 0)
    {
        char *movie = head(body, "\n\n");
        char *movie_id = get_value_from_text(movie, "id");
        char *movie_title = get_value_from_text(movie, "title");
        char *movie_with_id_and_title = malloc(sizeof(char) * (strlen(movie_id) + strlen(movie_title) + 2));
        if (atoi(movie_id) >= 10)
        {
            sprintf(movie_with_id_and_title, "%s -  %s\n", movie_id, movie_title);
        }
        else
        {
            sprintf(movie_with_id_and_title, "%s  -  %s\n", movie_id, movie_title);
        }
        list_of_movies_and_ids[i] = copy_string(movie_with_id_and_title);
        i++;
        body = tail(body, "\n\n");
    }
    *list_size = i;
    return list_of_movies_and_ids;
};

void sort_list_of_movies_by_id(char **list_of_movies_and_ids, int list_size)
{
    int i, j;
    for (i = 0; i < list_size; i++)
    {
        for (j = i + 1; j < list_size; j++)
        {
            if (atoi(list_of_movies_and_ids[i]) > atoi(list_of_movies_and_ids[j]))
            {
                char *aux = list_of_movies_and_ids[i];
                list_of_movies_and_ids[i] = list_of_movies_and_ids[j];
                list_of_movies_and_ids[j] = aux;
            }
        }
    }
};

char * join_list_of_movies(char **list_of_movies_and_ids, int list_size)
{
    char *movies_with_id_and_title = malloc(sizeof(char) * MAX_CHARS);
    int i;
    for (i = 0; i < list_size; i++)
    {
        sprintf(movies_with_id_and_title, "%s%s", movies_with_id_and_title, list_of_movies_and_ids[i]);
    }
    return movies_with_id_and_title;
};

char *get_movie_by_id(int id)
{
    char *url = malloc(sizeof(char) * (strlen(movie_service_base_url) + 2));
    sprintf(url, "%s/%d", movie_service_base_url, id);
    Response *response = pseudo_http("GET", url, NULL, NULL, NULL);
    if (response->status == SERVER_ERROR && strcmp(response->body, "TRY_AGAIN") == 0)
    {
        return response->message;
    }
    return response->body;
};

char *add_genre_to_movie(int movie_id, char *genre)
{
    Object *body = new_object();
    set_value(body, "genre", genre);

    char *url = malloc(sizeof(char) * (strlen(movie_service_base_url) + 2));
    sprintf(url, "%s/%d/add-genre", movie_service_base_url, movie_id);

    Response *response = pseudo_http("PATCH", url, NULL, NULL, body);
    if (response->status == SERVER_ERROR && strcmp(response->body, "TRY_AGAIN") == 0)
    {
        return response->message;
    }
    return response->body;
};

char *create_movie(Object *movie)
{
    Response *response = pseudo_http("POST", movie_service_base_url, NULL, NULL, movie);
    if (response->status == SERVER_ERROR && strcmp(response->body, "TRY_AGAIN") == 0)
    {
        return response->message;
    }
    return response->body;
};

char *remove_movie(int movie_id)
{
    char *url = malloc(sizeof(char) * (strlen(movie_service_base_url) + 2));
    sprintf(url, "%s/%d", movie_service_base_url, movie_id);
    Response *response = pseudo_http("DELETE", url, NULL, NULL, NULL);
    if (response->status == SERVER_ERROR && strcmp(response->body, "TRY_AGAIN") == 0)
    {
        return response->message;
    }
    return response->body;
};
