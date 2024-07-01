/* File:         string_replace.c
 *
 * Author:       Raffy Doquenia
 *
 * Date & time:  04/01/2024-10:08:54-PM
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "copy_sub_string.h"
#include "find_string.h"
#include "string_replace.h"


int string_replace(const char *input_string, const char *old_string, const char *new_string, char output_string[]) {
	bool is_old_string_found = false;
	int input_str_size = strlen(input_string),
		new_str_size = strlen(new_string),
		old_str_size = strlen(old_string);
	size_t result_str_size = input_str_size;
	char *result_string;
	
	/* Set the size of result_string based on the length of input_string
	 * and new_string. If new_string has the same length as old_string, use
	 * the length of input_string as default size.
	 */

	if (new_str_size > old_str_size || new_str_size < old_str_size) {
		result_str_size = (input_str_size - old_str_size) + new_str_size;
	}
	result_string = malloc(sizeof(char) * result_str_size + 1);

	int string_pos = find_string(input_string, old_string);
	if (string_pos > 0) {
		copy_sub_string(input_string, 1, (string_pos - 1), result_string);
		strncat(result_string, new_string, new_str_size);
		
		char copied_string[250];
		copy_sub_string(input_string, (string_pos + old_str_size), input_str_size - ((string_pos - 1) + old_str_size), copied_string);
		strncat(result_string, copied_string, strlen(copied_string));
		is_old_string_found = true;
	}

	if (is_old_string_found == false) {
		strcpy(output_string, "\0");	// old_string is not found, return NULL
		result_str_size = 0;
	}
	else {
		strncpy(output_string, result_string, result_str_size);
		output_string[result_str_size] = '\0';
	}

	free(result_string);
	result_string = NULL;
	return result_str_size;
}


