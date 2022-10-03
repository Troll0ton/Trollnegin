//! @file input_output.h

#ifndef   INPUT_OUTPUT_H
#define   INPUT_OUTPUT_H

//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys\stat.h>

//-----------------------------------------------------------------------------

#define DATA_TEXT_FILE "hamlet.txt"
#define OUT_FILE "hamlet1.txt"

//-----------------------------------------------------------------------------

struct Option
{
    char *opt_name;

    int (*func)(void *first_p, void *second_p);   // func = buble_sort(...)
                                                  // func = function(...)
};

//-----------------------------------------------------------------------------

struct File
{
    char *file_buffer; //

    int   text_size;

    int   num_of_lines;
};

//-----------------------------------------------------------------------------

void handle_args         (int argc, char* argv[], const struct Option cmd[], int options_range,
                          void* string_array,     int num_of_lines);

int  get_num_of_strs     (struct File *File_input);

struct File *file_reader (struct File *File_input, FILE *file);

int  get_file_size       (FILE *file);

int  file_printer        (struct Line *Text, int num_of_lines);

//-----------------------------------------------------------------------------

#endif //INPUT_OUTPUT_H
