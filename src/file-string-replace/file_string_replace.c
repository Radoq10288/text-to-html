/* File:         file-string-replace\file_string_replace.c
 *
 * Author:       Raffy Doquenia
 *
 * Date & time:  04/02/2024-10:33:52-AM
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_string_replace.h"
#include "string_replace.h"


#define EMPTY_STRING	""


int fstring_replace(const char *input_file_name, const char *output_file_name, const char *old_string, const char *new_string) {
	FILE *input_file;
	if ((input_file = fopen(input_file_name, "r")) == NULL) {
		return -1;	// Failed to open input file
	}
	
	FILE *output_file;
	if ((output_file = fopen(output_file_name, "a")) == NULL) {
		return -2;	// Failed to create output file or file already exist
	}

	bool is_old_string_found = false;
	int ch, ch_counter = 0,
		ts_size = strlen(old_string),
		ms_size = strlen(new_string);
	char temp_string[ts_size], modified_string[ms_size];

	strcpy(temp_string, EMPTY_STRING);
	while ((ch = fgetc(input_file)) != EOF) {
		temp_string[ch_counter] = ch;
		ch_counter++;

		if (ch_counter == ts_size) {
			int mod_str_size;
			mod_str_size = string_replace(temp_string, old_string, new_string, modified_string);

			if (mod_str_size == 0) {
				fputc(temp_string[0], output_file);
				memmove(temp_string, temp_string + 1, ts_size);
			}
			else {
				modified_string[ms_size] = '\0';
				fputs(modified_string, output_file);
				strcpy(modified_string, EMPTY_STRING);
				strcpy(temp_string, EMPTY_STRING);
				is_old_string_found = true;
				/* Another decrement to ch_counter before the decrement outside this else
				 * statement to avoid the single space character after the '<p>' tag.
				 */
				ch_counter--;
			}
			ch_counter--;
		}
	}

	fclose(input_file);
	fclose(output_file);
	if (ch == EOF && is_old_string_found == true) {
		return 0;
	}
	else {
		return 1;	// old_string is not found
	}
}


