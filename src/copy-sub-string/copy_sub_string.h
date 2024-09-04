/* File:         copy_sub_string.h
 *
 * Author:       Raffy Doquenia
 *
 * Date & time:  04/01/2024-10:16:23-PM
 */

#ifndef COPY_SUB_STRING_H
#define COPY_SUB_STRING_H

	/* A function the copy a specific sub-string of a string.
	 *
	 * Parameters:
	 * source 			= the input of text to copy sub-string from.
	 * start_position 	= cursor position in the 'source' text where the copy
	 * 					  starts. Note, position starts at 1.
	 * length 			= size of the sub-string to copy.
	 * output 			= a pointer or char array where the copied sub-string is
	 * 					  copied to.
	 *
	 * Return value:
	 * This function does not return a value.
	 */

	void copy_sub_string(char const *source, int const start_position, int const length, char output[]);

#endif //COPY_SUB_STRING_H_INCLUDED


