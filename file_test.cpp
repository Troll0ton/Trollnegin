#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys\stat.h>

//-----------------------------------------------------------------------------

void call_funct (FILE** file_in);

//-----------------------------------------------------------------------------

int main ()
{
    FILE* file_input = NULL;

    printf ("OK");

    call_funct (&file_input);

    char test1[100] = "\0";

    fread (test1, sizeof (char), 10, file_input);

    printf ("%s", test1);

    fclose (file_input);

    return 0;
}

//-----------------------------------------------------------------------------

void call_funct (FILE** file_in)
{
    *file_in = fopen ("hamlet.txt", "rb");
}

//-----------------------------------------------------------------------------
