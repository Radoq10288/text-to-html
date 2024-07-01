/* File:         string_replace.h
 *
 * Author:       Raffy Doquenia
 *
 * Date & time:  04/01/2024-10:08:54-PM
 */

#ifndef STRING_REPLACE_H
#define STRING_REPLACE_H

	/* A function that replace a specific sub-string with a new specified
	 * sub-string.
	 *
	 * Parameters:
	 * 	input_string 	= the string to be modified,
	 * 	old_string 		= the sub-string to be replaced.
	 * 	new_string 		= the new string to replace the old_string.
	 * 	output_string 	= a pointer or char array where the modified string
	 * 					  will be copied to.
	 *
	 * Return value:
	 * 	The function returns the size of the newly modified string.
	 */


	int string_replace(const char *input_string, const char *old_string, const char *new_string, char output_string[]);

#endif //STRING_REPLACE_H_INCLUDED


