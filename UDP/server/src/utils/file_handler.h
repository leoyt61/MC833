#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

char *read_file(char *filename);

void write_file(char *filename, char *buffer);

void remove_file(char *filename);

unsigned int count_files_in_dir(char *dir);

void order_filenames(char **filenames, unsigned int count);

char **get_filenames_in_dir(char *dir);

#endif
