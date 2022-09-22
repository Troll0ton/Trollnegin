//! @file lines_handle.h

#ifndef   LINES_HANDLE_H
#define   LINES_HANDLE_H

//-----------------------------------------------------------------------------

extern char *buf;

//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys\stat.h>

//-----------------------------------------------------------------------------

int compare_strings (const void *first_i, const void *second_i);

int line_detector (char *buf, int buf_size, int *string_num);

//-----------------------------------------------------------------------------

#endif //LINES_HANDLE_H