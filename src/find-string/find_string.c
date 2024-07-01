/* File:         find_string.c
 *
 * Author:       Raffy Doquenia
 *
 * Date & time:  04/01/2024-10:12:57-PM
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "find_string.h"


#define EMPTY_STRING	""


int find_string(char const *string, char const *find) {

	// If one or both of the function parameter has an empty value.
	if ((strcmp(string, EMPTY_STRING) != 0) && (strcmp(find, EMPTY_STRING) == 0)) { return -1; }
	if ((strcmp(string, EMPTY_STRING) == 0) && (strcmp(find, EMPTY_STRING) != 0)) { return -2; }
	if ((strcmp(string, EMPTY_STRING) == 0) && (strcmp(find, EMPTY_STRING) == 0)) { return -3; }

	int find_size = strlen(find);
	char temp[find_size];

	int string_size = strlen(string);
	int string_index = 0;
	int string_pos = 0;
	int il_counter = 0;	// 'il' stands for inner loop.
	int cs_counter = 0;	// 'cs' stands for chracter scanning.
	
	while (string_index != string_size) {
		il_counter = 0;
		cs_counter = string_index;
		strcpy(temp, "\0");
		
		while (il_counter != find_size) {
			temp[il_counter++] = string[cs_counter++];
		}
		
		// Puts a null character at the end of the string to avoid random
		// unwanted characters which are appended at the end or sometimes
		// remnants of a previously long text copied to it.
		temp[il_counter] = '\0';
		
		// Note:
		// The return value will be zero if the value of 'find' is not
		// found from the value of 'string'.
		if (strcmp(temp, find) == 0) {
			// Add 1 due to string_index counting starting from 0 as the initial
			// index value of array.
			string_pos = string_index + 1;
			break;
		}
		
		string_index++;
	}

	return string_pos;
}


