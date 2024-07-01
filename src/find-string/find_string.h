/* File:         find_string.h
 *
 * Author:       Raffy Doquenia
 *
 * Date & time:  04/01/2024-10:12:57-PM
 */

#ifndef FIND_STRING_H
#define FIND_STRING_H

	/* A function that finds the position of a sub-string from a text.
	 *
	 * Parameters:
	 *	string 	= the input text where to find the sub-string.
	 *	find 	= the sub-string to look for.
	 *
	 * Return value:
	 *	The function returns the position of the sub-string starting from 1. Else it returns 0 if the sub-string is not found.
	 *
	 * For function errors, the following negative values are returned:
	 *	-1 = if function parameter string is empty.
	 *	-2 = if function parameter find is empty.
	 *	-3 = if both function parameters are empty.
	 */


	int find_string(char const *string, char const *find);

#endif //FIND_STRING_H_INCLUDED


