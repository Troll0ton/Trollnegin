#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys\stat.h>

//-----------------------------------------------------------------------------

int compare_strings (const void *first_i, const void *second_i);

int num_of_strings (char *buf, int buf_size);

int size_of_file (FILE *file);

int file_reader (char *buf, int buf_size, FILE *file);

int line_detector (char *buf, int buf_size, int *string_num);

//-----------------------------------------------------------------------------

char *buf;

//-----------------------------------------------------------------------------

int main ()
{
    FILE   *file  = fopen ("hamlet.txt", "rb");
    assert (file != NULL);

    int   buf_size = size_of_file (file) + 1;

    buf = (char*) calloc (buf_size, sizeof (char));

    file_reader (buf, buf_size, file);

    int *string_num = (int*) calloc (num_of_strings (buf, buf_size), sizeof (int));

    int num = line_detector (buf, buf_size, string_num);

    qsort (string_num, num, sizeof (int), &compare_strings);

    for(int i = 0; i < num; i++)
    {
        printf ("\n%s", (buf + *(string_num + i)));
    }

    printf ("\n");

}

//-----------------------------------------------------------------------------

int compare_strings (const void *first_i, const void *second_i)
{
    int i1 = *(const int*) first_i;
    int i2 = *(const int*) second_i;

    char *first_str  = buf + i1;
    char *second_str = buf + i2;

    return strcmp (first_str, second_str);
}

//-----------------------------------------------------------------------------

int num_of_strings (char *buf, int buf_size)
{
    int string_counter = 0;

    for(int i = 0; i < buf_size; i++)
    {
        if(buf[i] == '\n')
        {
            string_counter++;
        }
    }

    return string_counter + 1;
}

//-----------------------------------------------------------------------------

int size_of_file (FILE *file)
{
    struct stat buffer;
    fstat (fileno (file), &buffer);

    return buffer.st_size;

    fclose (file);
}

//-----------------------------------------------------------------------------

int file_reader (char *buf, int buf_size, FILE *file)
{
    fread (buf, sizeof (char), buf_size, file);
    *(buf + buf_size) = '\0';
    printf ("%s\n", buf);

    int text_size = num_of_strings (buf, buf_size);

    return text_size;
}

//-----------------------------------------------------------------------------

int line_detector (char *buf, int buf_size, int *string_num)
{
    int kol = 0;
    int posit = 0;

    for(int i = 0; i <= buf_size; i++)
    {
        if(*(buf + i) == '\n' || *(buf + i) == '\r')
        {
            if(*(buf + i - 1) != '\n' && *(buf + i - 1) != '\r' && *(buf + i - 1) != '\0')
            {
                *(string_num + kol) = posit;
                posit = i + 1;
                kol++;
            }

            else
            {
                posit++;
            }

            *(buf + i) = '\0';
        }

        else
        {
            if(i == buf_size)
            {
                if(*(buf + i - 1) != '\n' && *(buf + i - 1) != '\r' && *(buf + i - 1) != '\0')
                {
                    *(string_num + kol) = posit;
                }
            }
        }
    }

    return (kol + 1);
}

//-----------------------------------------------------------------------------

