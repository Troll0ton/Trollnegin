#include "lines_handle.h"
#include "input_output.h"

//-----------------------------------------------------------------------------

int get_num_of_strs (struct File *File_input)
{
    int string_counter = 0;

    for(int pos = 0; pos < File_input->text_size; pos++)
    {
        if(File_input->file_buffer[pos] == '\n')
        {
            string_counter++;
        }
    }

    string_counter++;

    return string_counter;
}

//-----------------------------------------------------------------------------

void handle_args (int argc,          char* argv[],       const struct Option cmd[],
                  int options_range, void* string_array, int          num_of_lines)
{
    assert (argc != 0);
    assert (argv != NULL);
    assert (cmd  != NULL);

    for(int arg_num = 1; arg_num < argc; arg_num++)
    {
        for(int i = 0; i < options_range; i++)
        {
            if(strcmp (argv[arg_num], cmd[i].opt_name) == 0)
            {
                cmd[i].func (string_array, num_of_lines, cmd[i].func, arg_num, argv);
            }
        }
    }
}

//-----------------------------------------------------------------------------

int get_file_size (FILE *file)
{
    struct stat file_stat = {0};

    fstat (fileno (file), &file_stat);

    return file_stat.st_size;
}

//-----------------------------------------------------------------------------

struct File *file_reader (FILE *file)
{
    struct File readed_File = {0};

    readed_File->text_size   = get_file_size (file) + 1;
    readed_File->file_buffer = (char*) calloc (readed_File->text_size, sizeof (char));

    fread (readed_File->file_buffer, sizeof (char), readed_File->text_size, file);

    readed_File->file_buffer[readed_File->text_size - 1] = '\0';
    readed_File->num_of_lines = num_of_strings (readed_File);

    return (&readed_File);
}

//-----------------------------------------------------------------------------

int file_printer (struct Line *Text, int num_of_lines) //OPEN and CLOSE exit file!
{
    FILE   *file_out  = fopen (OUT_FILE, "w+");
    assert (file_out != NULL);

    for(int pos = 0; pos < num_of_lines; pos++)
    {
        fprintf (file_out, "\n%s", Text[pos].begin_line);
    }

    fclose (file_out);

    return 0;
}

//-----------------------------------------------------------------------------
