#include "lines_handle.h"
#include "input_output.h"

//-----------------------------------------------------------------------------

int compare_strings_begin (void *first_p, void *second_p)
{
    struct Line *first_line  = (struct Line*) first_p;
    struct Line *second_line = (struct Line*) second_p;

    return strcmp ((*first_line).begin_line, (*second_line).begin_line);
}

//-----------------------------------------------------------------------------

int compare_strings_end (void *first_p, void *second_p)
{
    struct Line *first_line  = (struct Line*) first_p;
    struct Line *second_line = (struct Line*) second_p;

    int min_len = 0;

    char *end_line_1 = (*first_line ).begin_line + (*first_line ).line_lenght - 1;
    char *end_line_2 = (*second_line).begin_line + (*second_line).line_lenght - 1;

    // min_len  =  min( ..->line_lenght, ...);

    if((*first_line).line_lenght <= (*second_line).line_lenght)
    {
        min_len = (*first_line).line_lenght + 1;
    }

    else
    {
        min_len = (*second_line).line_lenght + 1;
    }


    for(int i = 0; i < min_len; i++)
    {
        if(*end_line_1 != *end_line_2)
        {
            return (*end_line_1 - *end_line_2);
        }

        end_line_1--;
        end_line_2--;
    }

    return SAME_LINES;
}

//-----------------------------------------------------------------------------

int lines_separator (struct File_buffer *File, struct Line *Arr_struct)
{
    int num_line = 0;
    int cur_len  = 0;

    int file_len = (*File).file_size;

    for(int i = 0; i < file_len; i++)
    {
        if((*File).file_data[i] == '\n')
        {
            (*File).file_data[i] = '\0';

            Arr_struct[num_line].begin_line  = (*File).file_data + i - cur_len;
            Arr_struct[num_line].line_lenght = cur_len;

            cur_len = 0;
            num_line++;
        }

        else
        {
            cur_len++;
        }
    }

    Arr_struct[num_line].begin_line = (*File).file_data +
                                      (*File).file_size -
                                      cur_len;

    num_line++;

    return num_line;
}

//-----------------------------------------------------------------------------

void bubble_sort (void* string_array,  int num_of_lines,
                  int compare_strings (void* first_str, void* second_str))
{
    for(int i = 0; i < num_of_lines; i++)
    {
        for(int j = i + 1; j < num_of_lines; j++)
        {
            if(compare_strings ((struct Line*) string_array + i, (struct Line*) string_array + j) > 0)
            {
                swap_lines ((struct Line*) string_array + i, (struct Line*) string_array + j, sizeof (struct Line));
            }
        }
    }
}

//-----------------------------------------------------------------------------

void swap_lines (void* first_pointer, void* second_pointer, size_t size_of_struct)
{
    // char tmp = 0;
    // (char*)tmp_pointer
    // for ( i < size_of_struct;
    // first_pointer[i] = second_pointer[i];
    //
    // 50000000 - 8
    // void* tmp_pointer = calloc (1, size_of_struct);

    memcpy (tmp_pointer,    first_pointer,  size_of_struct);
    memcpy (first_pointer,  second_pointer, size_of_struct);
    memcpy (second_pointer, tmp_pointer,    size_of_struct);

    // free (tmp_pointer);
}

//-----------------------------------------------------------------------------
