#include "./interface.h"

void start_interface()
{
    init_movie_service();

    int option;
    do
    {
        fflush(stdout);
        system("clear");
        printf("MC833 Client\n\n");
        printf("##################################\n");
        printf("1 - List movies\n");
        printf("2 - Register movie\n");
        printf("0 - Exit\n");
        printf("\n");
        printf("Option: ");
        scanf("%d", &option);
        printf("\n");
        fflush(stdin);
        switch (option)
        {
        case 1:
            show_movies_interface();
            break;
        case 2:
            create_movie_interface();
            break;
        case 0:
            break;
        default:
            printf("Invalid option!\n");
            break;
        }
    } while (option != 0);
};

void show_movies_interface()
{
    int option;
    int show_all = 1;
    int show_more_infos = 0;
    char *genre;
    do
    {
        fflush(stdout);
        system("clear");
        Object *query_params = NULL;

        if (show_all == 0)
        {
            query_params = new_object();
            set_value(query_params, "genre", genre);
            system("clear");
            printf("Movies with genre: %s\n\n", genre);
        } else {
            printf("All movies\n\n");
        }

        char *response = get_movies(query_params, show_more_infos);
        printf("%s", response);

        printf("\n");
        printf("##################################\n");
        printf("1 - Clean genre filter\n");
        printf("2 - Filter by genre\n");
        printf("3 - Select movie\n");
        if (show_more_infos == 0) printf("4 - Show more infos\n");
        else if (show_more_infos == 1) printf("4 - Show less infos\n");
        printf("0 - Go back\n");
        printf("\n");
        printf("Option: ");
        scanf("%d", &option);
        printf("\n");
        fflush(stdin);
        switch(option)
        {
        case 1:
            system("clear");
            show_all = 1;
            break;
        case 2:
            fflush(stdout);
            system("clear");
            printf("Enter genre: ");
            genre = malloc(sizeof(char) * INPUT_MAX_CHARS);
            scanf("%s", genre);
            printf("\n");
            fflush(stdin);
            show_all = 0;
            break;
        case 3:
            show_movie_by_id_interface();
            break;
        case 4:
            if (show_more_infos == 0) show_more_infos = 1;
            else if (show_more_infos == 1) show_more_infos = 0;
        case 0:
            break;
        default:
            printf("Invalid option!\n");
            break;
        }
    } while (option != 0);
};

void show_movie_by_id_interface()
{
    fflush(stdout);
    system("clear");
    printf("Enter the movie ID: ");
    int id;
    scanf("%d", &id);
    printf("\n");
    fflush(stdin);

    int option;
    do
    {
        fflush(stdout);
        system("clear");
        printf("Movie with ID: %d\n\n", id);
        char *response = get_movie_by_id(id);
        printf("%s", response);
        printf("\n");
        printf("##################################\n");
        printf("1 - Add genre\n");
        printf("2 - Remove movie\n");
        printf("0 - Go back\n");
        printf("\n");
        printf("Option: ");
        scanf("%d", &option);
        printf("\n");
        fflush(stdin);

        switch(option)
        {
        case 1:
            add_genre_to_movie_interface(id);
            break;
        case 2:
            remove_movie_by_id_interface(id);
            return;
        case 0:
            break;
        default:
            printf("Invalid option!\n");
            break;
        }
    } while (option != 0);
};

void add_genre_to_movie_interface(int id)
{
    fflush(stdout);
    system("clear");
    printf("Enter genre: ");
    char *genre = malloc(sizeof(char) * INPUT_MAX_CHARS);
    scanf("%s", genre);
    printf("\n");
    fflush(stdin);
    char *response = add_genre_to_movie(id, genre);
    printf("Response:\n%s\n", response);
    sleep(3);
};

void create_movie_interface()
{
    fflush(stdout);
    system("clear");
    printf("Enter movie ID: ");
    char *id = malloc(sizeof(char) * INPUT_MAX_CHARS);
    scanf("%s", id);
    printf("\n");
    fflush(stdin);

    printf("Enter movie title: ");
    char *title = malloc(sizeof(char) * INPUT_MAX_CHARS);
    scanf("%[^\n]*c", title);
    printf("\n");
    fflush(stdin);

    printf("Enter movie year: ");
    char *year = malloc(sizeof(char) * INPUT_MAX_CHARS);
    scanf("%s", year);
    printf("\n");
    fflush(stdin);

    printf("Enter movie director: ");
    char *director = malloc(sizeof(char) * INPUT_MAX_CHARS);
    scanf("%[^\n]*c", director);
    printf("\n");
    fflush(stdin);

    printf("Enter movie genre: ");
    char *genre = malloc(sizeof(char) * INPUT_MAX_CHARS);
    scanf("%[^\n]*c", genre);
    printf("\n");
    fflush(stdin);

    Object *movie = new_object();
    set_value(movie, "id", id);
    set_value(movie, "title", title);
    set_value(movie, "year", year);
    set_value(movie, "director", director);
    set_value(movie, "genres", genre);

    char *response = create_movie(movie);
    printf("Response:\n%s\n", response);
    sleep(3);
};

void remove_movie_by_id_interface(int id)
{
    fflush(stdout);
    system("clear");
    char *response = remove_movie(id);
    printf("Response:\n%s\n", response);
    sleep(3);
};
