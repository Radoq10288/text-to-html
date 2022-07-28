#ifndef STRREP_H
#define STRREP_H

#include <stdio.h>


int file_strrep(const char *input_file_name, FILE *output_file, const char *old_string, const char *new_string);

char* strrep(const char *input_string, const char *old_string, const char *new_string);

#endif //STRREP_H_INCLUDED


