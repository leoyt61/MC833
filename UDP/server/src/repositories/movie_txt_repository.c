#include "movie_txt_repository.h"

void init_movies_repository(char *dir) {
    movies_dir = (char *) mmap(NULL, sizeof(char) * MAX_CHARS, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, 0, 0);
    strcpy(movies_dir, dir);
};

void save_movie(Movie *movie) {
    char * filename = malloc(sizeof(char) * 100);
    sprintf(filename, "%s/%d.txt", movies_dir, movie->id);

    char *file_content = parse_movie_to_text(movie);

    printf("Movie saved:\n");
    printf("id: %d\n", movie->id);
    printf("title: %s\n", movie->title);
    printf("director: %s\n", movie->director);
    printf("year: %d\n", movie->year);
    printf("genres: %s\n", movie->genres);
    printf("\n");

    write_file(filename, file_content);
};

int add_genre_to_movie(unsigned int id, char *genre) {
    Movie *movie = get_movie_by_id(id);

    if (movie == NULL) return 1;

    add_genre(movie, genre);
    save_movie(movie);
    return 0;
};

int movie_has_genre(Movie *movie, char *genre) {
    char *substring = strstr(movie->genres, genre);
    if (substring == NULL) return 0;
    return 1;
};

Movie **get_movies_by_genre(char *genre) {
    Movie **all_movies = get_movies();
    int count = get_movies_count_by_genre(genre);

    if (count == 0) return NULL;

    int all_movies_count = get_movies_count();

    Movie **movies_by_genre = malloc(sizeof(Movie*) * count);
    int j = 0;
    for (int i = 0; i < all_movies_count; i++) {
        if (strstr(all_movies[i]->genres, genre) != NULL) {
            movies_by_genre[j] = all_movies[i];
            j++;
        }
    }
    return movies_by_genre;
};

Movie *get_movie_by_id(unsigned int id) {
    char *filename = malloc(sizeof(char) * 100);
    sprintf(filename, "%s/%d.txt", movies_dir, id);

    char *file_content = read_file(filename);

    if (file_content == NULL) return NULL;

    Movie *movie = parse_text_to_movie(file_content);
    return movie;
};

Movie **get_movies() {
    int count = get_movies_count();
    char **filenames = get_filenames_in_dir(movies_dir);
    Movie **movies = malloc(sizeof(Movie*) * count);
    for (int i = 0; i < count; i++) {
        char *filename = filenames[i];
        char *file_content = read_file(filename);
        Movie *movie = parse_text_to_movie(file_content);
        movies[i] = movie;
    }
    return movies;
};

int get_movies_count() {
    return count_files_in_dir(movies_dir);
};

int get_movies_count_by_genre(char *genre) {
    Movie **all_movies = get_movies();
    int all_count = get_movies_count();
    int count = 0;
    for (int i = 0; i < all_count; i++) {
        if (strstr(all_movies[i]->genres, genre) != NULL) {
            count++;
        }
    }

    if (count == 0) return 0;
    return count;
};

int remove_movie(int id) {

    Movie *movie = get_movie_by_id(id);

    if (movie == NULL) return 1;

    char *filename = malloc(sizeof(char) * 100);
    sprintf(filename, "%s/%d.txt", movies_dir, id);
    
    remove_file(filename);

    return 0;
};
