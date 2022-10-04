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

#include "lines_handle.h"

//-----------------------------------------------------------------------------

//"hamlet.txt"
//"hamlet1.txt"

//-----------------------------------------------------------------------------

#define SKIP_ARG 1

//-----------------------------------------------------------------------------

#define CMD_FUNC_ARGS int  *arg_num,\
                      char *argv[],\
                      FILE **file_in,\
                      FILE **file_out,\
                      int   (*comp_par)(void *first_p, void *second_p)

//-----------------------------------------------------------------------------

const int num_of_support_args = 4;

//-----------------------------------------------------------------------------

struct Option
{
    char *opt_name;

    int (*func)(CMD_FUNC_ARGS);
};

//-----------------------------------------------------------------------------

struct File
{
    char *file_buffer;

    int   text_size;

    int   num_of_lines;
};

//-----------------------------------------------------------------------------

void         handle_args (int   argc,     char *argv[],    const struct Option cmd[],                            int options_range,
                  FILE **file_in,  FILE **file_out,  int         (*comp_par)(void *first_p, void *second_p)                    );

int          set_input_file  (CMD_FUNC_ARGS);

int          set_output_file (CMD_FUNC_ARGS);

int          comp_par_begin  (CMD_FUNC_ARGS);

int          comp_par_end    (CMD_FUNC_ARGS);

int          get_num_of_strs (struct File *File_input);

struct File *file_reader     (FILE *file);

int          get_file_size   (FILE *file);

int          file_printer    (struct Line *Text, int num_of_lines, FILE *file_out);

//-----------------------------------------------------------------------------

const Option cmd_args[] =
{
    {"--begin",  comp_par_begin },
    {"--end",    comp_par_end   },

    {"-if",      set_input_file },
    {"-of",      set_output_file},
};

//-----------------------------------------------------------------------------

#endif //INPUT_OUTPUT_H
