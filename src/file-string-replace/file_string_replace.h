/* File:         file-string-replace\file_string_replace.h
 *
 * Author:       
 *
 * Date & time:  04/02/2024-10:33:52-AM
 */

#ifndef FILE_STRING_REPLACE_H
#define FILE_STRING_REPLACE_H

	/* A function that replace a specific sub-string with a new specified
	 * sub-string in a text file.
	 *
	 * Parameters:
	 * 	input_file_name 	= the source text file.
	 *	output_file_name	= the resulting modified text file.
	 * 	old_string 			= the sub-string to be replaced.
	 * 	new_string 			= the new string to replace the old_string.
	 * 	output_string 		= a pointer or char array where the modified string
	 * 					  	  will be copied to.
	 *
	 * Return value:
	 * 	1 	= doesn't found old_string
	 *	0 	= old_string is found and replaced with new_string
	 *	-1 	= failed to open input_file_name
	 *	-2	= failed to open output_file_name
	 */


	int fstring_replace(const char *input_file_name, const char *output_file_name, const char *old_string, const char *new_string);

#endif //FILE_STRING_REPLACE_H_INCLUDED


