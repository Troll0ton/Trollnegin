//! @file main.h

#ifndef   MAIN_H
#define   MAIN_H

//-----------------------------------------------------------------------------

#include "lines_handle.h"
#include "input_output.h"

//-----------------------------------------------------------------------------

const int num_of_support_args = 2;

//-----------------------------------------------------------------------------

const Option cmd_args[] =
{
    {"-b",  comp_strs_by_begin},
    {"-e",  comp_strs_by_end},

    {"-of", set_input_file},
    {"-if", set_output_file},
};

//-----------------------------------------------------------------------------

#endif //MAIN_H
