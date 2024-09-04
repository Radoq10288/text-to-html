/* File:         copy_sub_string.c
 *
 * Author:       Raffy Doquenia
 *
 * Date & time:  04/01/2024-10:16:23-PM
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "copy_sub_string.h"


#define EMPTY_STRING	""


void copy_sub_string(char const *source, int const start_position, int const length, char output[]) {
	int char_index = 0,
		dest_index = 0,

		// Reduce by 1 to make the counting of character appear to user as if
		// it start at 1.
		src_index = start_position - 1,

		src_size = strlen(source);

	// Add 1 to length to accommodate the null character that will be
	// appended at the end.
	char *temp = malloc(sizeof(char) * (length + 1));

	strcpy(temp, EMPTY_STRING);
	while (char_index != src_size) {
		if (char_index >= (start_position - 1) && dest_index != length) {
			temp[dest_index++] = source[src_index++];
			if (dest_index == length) { break; }
		}
		char_index++;
	}

	temp[dest_index] = '\0';
	strcpy(output, temp);
	free(temp);
}


