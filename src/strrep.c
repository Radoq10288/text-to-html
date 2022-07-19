#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


#define EMPTY_STRING	"\0"


static int char_type(int character) {
	int (*func_prt[])(int) = {
		&isalpha, &iscntrl, &isdigit,
		&ispunct, &isspace
	};

	if (iscntrl(character) && isspace(character)) {return 5;}

	int func_prt_index = 0, char_type;

	while (func_prt_index != 5) {
		if ((*func_prt[func_prt_index])(character) != 0) {
			char_type = func_prt_index;
			break;
		}
		func_prt_index++;
	}

	return char_type;
}


static int str_type(char *string) {
	bool alphabet = false, control = false,
		 digit = false, punctuation = false,
		 space = false, mixed = false;
	bool str_type_list[] = {
		 alphabet, control, digit,
		 punctuation, space, mixed
	};

	int (*func_prt[])(int) = {
		&isalpha, &iscntrl, &isdigit,
		&ispunct, &isspace
	};

	int char_index = 0, string_size = strlen(string),
		str_type_index;

	while (char_index != string_size) {
		str_type_index = 0;
		while (str_type_index != 5) {
			if ((*func_prt[str_type_index])(string[char_index]) != 0) {
				str_type_list[str_type_index] = true;
			}
			str_type_index++;
		}
		char_index++;
	}

	int str_type_list_index, true_counter = 0;
	str_type_index = 0;

	while (str_type_index != 6) {
		if (str_type_list[str_type_index] == true) {
			true_counter += 1;
			str_type_list_index = str_type_index;
		}
		str_type_index++;
	}

	if (true_counter > 1) {
		return 5;
	}
	else {
		return str_type_list_index;
	}
}


static char *result_string;

static void free_result_string(void) {
	free(result_string);
	result_string = NULL;
}

char* strrep(char *input_string, char *old_string, char *new_string) {
	bool is_old_string_found = false;
	int buffer_size = strlen(old_string),
		result_string_length = strlen(input_string) + 1;
	char buffer[buffer_size];

	/* Set the size of result_string based on the length of input_string
	 * and new_string. If new_string has the same length as old_string, use
	 * the length of input_string as default size.
	 */

	if (strlen(new_string) > strlen(old_string) || strlen(new_string) < strlen(old_string)) {
		result_string_length = (strlen(input_string) - strlen(old_string) + strlen(new_string) + 2);
	}
	result_string = malloc(sizeof(char) * result_string_length);

	strcpy(buffer, EMPTY_STRING);
	strcpy(result_string, EMPTY_STRING);
	int buffer_count = 1, char_index = 0;

	while (char_index != strlen(input_string)) {
		if (str_type(old_string) == char_type(input_string[char_index]) || str_type(old_string) == 5) {
			strncat(buffer, &input_string[char_index], 1);

			if (buffer_count == buffer_size && strcmp(old_string, buffer) == 0) {
				strncat(result_string, new_string, strlen(new_string));
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
				//Do nothing for now...
			}
			buffer_count++;
		}
		else {
			if (strcmp(buffer, EMPTY_STRING) != 0) {
				strcat(result_string, buffer);
				strcpy(buffer, EMPTY_STRING);
				buffer_count = 1;
			}
			strncat(result_string, &input_string[char_index], 1);
		}

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


