#include "movie.h"


Movie *init_movie(unsigned int id, char *title, char *director, int year, char *genres) {
    Movie *movie = (Movie *) malloc(sizeof(Movie));
    movie->id = id;
    movie->title = title;
    movie->director = director;
    movie->year = year;
    movie->genres = genres;
    return movie;
};

void add_genre(Movie *movie, char *genre)
{
    if (movie->genres == NULL)
    {
        movie->genres = genre;
    }
    else
    {
        sprintf(movie->genres, "%s, %s", movie->genres, genre);
    }
};

char *parse_movie_to_text(Movie *movie)
{
    char *movie_text = malloc(sizeof(char) * MAX_CHARS);
    sprintf(movie_text, "id: %d\ntitle: %s\ndirector: %s\nyear: %d\ngenres: %s\n", movie->id, movie->title, movie->director, movie->year, movie->genres);
    return movie_text;
};

Movie *parse_text_to_movie(char *text) {
    char *id_str = get_value(text, "id");
    char *title = get_value(text, "title");
    char *year_str = get_value(text, "year");
    char *director = get_value(text, "director");
    char *genres = get_value(text, "genres");

    int id = atoi(id_str);
    int year = atoi(year_str);

    Movie *movie = init_movie(id, title, director, year, genres);
    return movie;
};
