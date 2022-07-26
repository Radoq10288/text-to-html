#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "strrep.h"


#define EMPTY_STRING	"\0"


static char *result_string;

static void free_result_string(void) {
	free(result_string);
	result_string = NULL;
}

char* strrep(const char *input_string, const char *old_string, const char *new_string) {
	bool is_old_string_found = false;
	size_t buffer_size = strlen(old_string),
		   input_str_size = strlen(input_string),
		   new_str_size = strlen(new_string),
		   result_str_size = input_str_size + 1;
	char buffer[buffer_size];

	/* Set the size of result_string based on the length of input_string
	 * and new_string. If new_string has the same length as old_string, use
	 * the length of input_string as default size.
	 */

	if (new_str_size > strlen(old_string) || new_str_size < strlen(old_string)) {
		result_str_size = (input_str_size - strlen(old_string) + new_str_size + 1);
	}
	result_string = malloc(sizeof(char) * result_str_size);

	strcpy(buffer, EMPTY_STRING);
	strcpy(result_string, EMPTY_STRING);
	int buffer_count = 1, char_index = 0;

	while (char_index != input_str_size) {
		strncat(buffer, &input_string[char_index], 1);

		if (strcmp(old_string, buffer) == 0) {
			strncat(result_string, new_string, new_str_size);
			strcpy(buffer, EMPTY_STRING);
			is_old_string_found = true;
			buffer_count -= 1;
		}
		else if (buffer_count == buffer_size) {
			strncat(result_string, &buffer[0], 1);
			if (buffer_count > 1) {
				memmove(buffer, buffer+1, (buffer_size - 1));
			}
			buffer[(buffer_size - 1)] = '\0';
			buffer_count -= 1;
		}
		else {
			// Do nothing here...
		}
		buffer_count++;
		char_index++;
	}

	atexit(free_result_string);
	if (is_old_string_found == false) {
		return NULL;	// old_string is not found, return NULL
	}
	else {
		return result_string;
	}
}


