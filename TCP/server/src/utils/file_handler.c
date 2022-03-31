#include "./file_handler.h"

char *read_file(char *filename)
{
    printf("Reading file %s\n", filename);
    char *buffer = 0;
    long length;
    FILE *f = fopen(filename, "rb");

    if (f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer)
        {
            fread(buffer, 1, length, f);
        }
        fclose(f);
    }

    if (buffer)
    {
        return buffer;
    }

    printf("Could not read file %s\n", filename);

    return NULL;
};

void write_file(char *filename, char *buffer)
{
    printf("Writing file: %s\n", filename);
    FILE *f = fopen(filename, "wb");

    if (f)
    {
        fwrite(buffer, 1, strlen(buffer), f);
        fclose(f);
        return;
    }

    printf("Could not write file %s\n", filename);
};

void remove_file(char *filename) {
    remove(filename);
};

unsigned int count_files_in_dir(char *dir) {
    unsigned int count = 0;
    DIR *d;
    struct dirent *dir_entry;

    d = opendir(dir);
    if (d) {
        while ((dir_entry = readdir(d)) != NULL) {
            if (strcmp(dir_entry->d_name, ".") != 0 && strcmp(dir_entry->d_name, "..") != 0) {
                count++;
            }
        }
        closedir(d);
    }

    return count;
};

void order_filenames(char **filenames, unsigned int count) {
    char *temp;
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count - 1; j++) {
            if (strcmp(filenames[j], filenames[j + 1]) > 0) {
                temp = filenames[j];
                filenames[j] = filenames[j + 1];
                filenames[j + 1] = temp;
            }
        }
    }
};

char **get_filenames_in_dir(char *dir) {
    int count = count_files_in_dir(dir);
    char **filenames = malloc(sizeof(char *) * count);
    DIR *d;
    struct dirent *dir_entry;
    unsigned int i = 0;

    d = opendir(dir);
    if (d) {
        while ((dir_entry = readdir(d)) != NULL) {
            if (strcmp(dir_entry->d_name, ".") != 0 && strcmp(dir_entry->d_name, "..") != 0) {
                filenames[i] = malloc(sizeof(char) * (strlen(dir_entry->d_name) +strlen(dir) + 1));
                strcpy(filenames[i], dir);
                strcat(filenames[i], "/");
                strcat(filenames[i], dir_entry->d_name);
                i++;
            }
        }
        closedir(d);
    }

    order_filenames(filenames, count);
    return filenames;
};
