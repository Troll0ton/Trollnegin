#include "lines_handle.h"

//-----------------------------------------------------------------------------

int comp_strs_by_begin (void *first_p, void *second_p)
{
    struct Line *first_line  = (struct Line*) first_p;
    struct Line *second_line = (struct Line*) second_p;

    char *begin_line_1 = first_line->begin_line;
    char *begin_line_2 = second_line->begin_line;

    while(!((*begin_line_1 >= 'A' && *begin_line_1 <= 'Z') || (*begin_line_1 >= 'a' && *begin_line_1 <= 'z')))
    {
        begin_line_1++;
    }

    while(!((*begin_line_2 >= 'A' && *begin_line_2 <= 'Z') || (*begin_line_2 >= 'a' && *begin_line_2 <= 'z')))
    {
        begin_line_2++;
    }

    return strcmp (begin_line_1, begin_line_2);
}

//-----------------------------------------------------------------------------

int comp_strs_by_end (void *first_p, void *second_p)
{
    struct Line *first_line  = (struct Line*) first_p;
    struct Line *second_line = (struct Line*) second_p;

    char *end_line_1 = first_line->begin_line  + first_line->line_lenght  - 1;
    char *end_line_2 = second_line->begin_line + second_line->line_lenght - 1;

    while(!((*end_line_1 >= 'A' && *end_line_1 <= 'Z') || (*end_line_1 >= 'a' && *end_line_1 <= 'z')))
    {
        end_line_1--;
    }

    while(!((*end_line_2 >= 'A' && *end_line_2 <= 'Z') || (*end_line_2 >= 'a' && *end_line_2 <= 'z')))
    {
        end_line_2--;
    }

    int min_len = find_min_len (first_line->line_lenght + 1, second_line->line_lenght + 1);

    for(int counter = 0; counter < min_len; counter++)
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

int find_min_len (int first_i, int second_i)
{
    if(first_i > second_i)
    {
        return first_i;
    }

    return second_i;
}

//-----------------------------------------------------------------------------

struct Line *lines_separator (struct File *Oper_file)
{
    struct Line *Arr_struct = (struct Line*) calloc (Oper_file->num_of_lines, sizeof (struct Line));

    int num_line = 0;
    int cur_len  = 0;

    int file_len = Oper_file->text_size;

    for(int i = 0; i < file_len; i++)
    {
        if(Oper_file->file_buffer[i] == '\n')
        {
            Oper_file->file_buffer[i] = '\0';

            Arr_struct[num_line].begin_line  = Oper_file->file_buffer + i - cur_len;
            Arr_struct[num_line].line_lenght = cur_len;

            cur_len = 0;
            num_line++;
        }

        else
        {
            cur_len++;
        }
    }

    Arr_struct[num_line].begin_line = Oper_file->file_buffer +
                                      Oper_file->text_size -
                                      cur_len;

    num_line++;

    return Arr_struct;
}

//-----------------------------------------------------------------------------

void bubble_sort (void* string_array,  int num_of_lines,
                  int   comp_strs (void* first_str, void* second_str))
{
    for(int i = 0; i < num_of_lines; i++)
    {
        for(int j = i + 1; j < num_of_lines; j++)
        {
            if(comp_strs ((struct Line*) string_array + i, (struct Line*) string_array + j) > 0)
            {
                swap_lines ((struct Line*) string_array + i, (struct Line*) string_array + j, sizeof (struct Line));
            }
        }
    }
}

//-----------------------------------------------------------------------------

void swap_lines (void* first_pointer, void* second_pointer, size_t size_of_struct)
{
    char tmp = 0;

    for(int i = 0; i < int(size_of_struct); i++)
    {
       tmp = *((char*)first_pointer + i);

       *((char*)first_pointer + i)  = *((char*)second_pointer + i);
       *((char*)second_pointer + i) = tmp;
    }
}

//-----------------------------------------------------------------------------

void purificate_mem (struct Line *Text, struct File *File_input)
{
    free (File_input->file_buffer);

    free (File_input);

    free (Text);
}

//-----------------------------------------------------------------------------

