/* File:         make-txt-to-html\src\main.c
 *
 * Author:       Radoq10288
 *
 * Date & time:  07/10/2022-09:12:05-PM
 */

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strrep.h"


#define EMPTY_STRING	"\0"


char html_content_1[] = {
	"<!DOCTYPE html>\n"
	"<html>\n"
	"\t<head>\n"
	"\t\t<title>My Webpage</title>\n"
	"\t</head>\n"
	"\t<body>\n"
	"\t\t<p>"
};

char html_content_2[] = {
	"</p>\n"
	"\t</body>\n"
	"</html>\n\n\n"
};


static void help(void) {
	printf("\nUsage:\n"
			"    make-th [Text file filename] [Option]    For converting text file to html.\n"
			"    make-th [Option]                         For other options to show help, version, etc.\n"
			"\n"
			"Options:\n"
			"    -h                 Show this help.\n"
			"    -t, --title        Set the title of the html file.\n"
			"    -v, --version      Show current version of this software.\n");
}


int main(int argc, char *argv[]) {
	char text_file_name[256] = EMPTY_STRING,
		 html_file_name[256] = EMPTY_STRING,
		 page_title[256] = EMPTY_STRING;
	int getopt_status, option_index = 0;

	if (argc == 1) {
		fprintf(stderr, "make-th\nError: No argument or option specified.\nInfo: Type 'make-th -h/--help' to see usage and available options.");
		goto maketh_error;
	}
	strcpy(text_file_name, argv[1]);

	while(true) {
        static struct option long_options[] = {
            {"help",		no_argument,		0,  	'h'},
            {"title",		required_argument,	0,  	1},
            {"version",		no_argument,		0,		'v'},
            {0,				0,					0,		0}
        };

		opterr = 0;
		getopt_status = getopt_long(argc, argv, ":ht:v", long_options, &option_index);
        if (getopt_status == -1) {
			break;
		}

		switch(getopt_status) {
			case 'h':
				help();
				goto skipotherprocess;
			case 1:
			case 't':
				if (argc == 3) {
					fprintf(stderr, "make-th\nError: No text file is specified for convertion.\n");
					goto maketh_error;
				}
				strcpy(page_title, optarg);
				break;
			case 'v':
				//version();
				printf("Show current version.\n");
				goto skipotherprocess;
			case ':':
				if (optopt == 0) {
					fprintf(stderr, "make-th\nError: The long option --%s requires an argument.\n", long_options[option_index].name);
				}
				else {
					fprintf(stderr, "make-th\nError: The short option -%c requires an argument.\n", optopt);
				}
				goto maketh_error;
			case 0:
			case '?':
				if (optopt != 0) {
					fprintf(stderr, "make-th\nError: Unknown short option '-%c'.\n", optopt);
				}
				else {
					fprintf(stderr, "make-th\nError: Unknown long option '%s'.\n", argv[(optind - 1)]);
				}
				fprintf(stderr, "Info: Type 'make-th -h/--help' to see available options.\n");
				goto maketh_error;
        }
    }


	FILE *input_file, *output_file;
	if (!(input_file = fopen(text_file_name, "r"))) {
		fprintf(stderr, "make-th\nError: Failed to open file '%s' for reading.\n", text_file_name);
		goto maketh_error;
	}

	strcpy(html_file_name, strrep(text_file_name, "txt", "html"));
	if (!(output_file = fopen(html_file_name, "a"))) {
		fprintf(stderr, "make-th\nError: Failed to create file 'the.html' for appending.\n");
		goto maketh_error;
	}

	char text_line[2][1000], *output;
	int str_index = 0, total_str_len = 0;

	// Write to stream the initial part of the html file.
	output = strrep(html_content_1, "My Webpage", page_title);
	fprintf(output_file, "%s", output);
	output = EMPTY_STRING;

	strcpy(text_line[0], EMPTY_STRING);
	strcpy(text_line[1], EMPTY_STRING);
	while (true) {
		if (feof(input_file)) {break;}
		fgets(text_line[str_index], 1000, input_file);
		total_str_len += strlen(text_line[str_index]);
		str_index++;

		if (str_index == 2) {
			char buffer[total_str_len];

			strcpy(buffer, text_line[0]);
			strcat(buffer, text_line[1]);

			// Convert plain text paragraphs to html formatted paragraph
			if ((output = strrep(buffer, "\n\n", "</p>\n\n\t\t<p>"))) {
				strcpy(buffer, output);
				fputs(buffer, output_file);
			}
			else {
				fputs(text_line[0], output_file);
			}

			strcpy(buffer, EMPTY_STRING);
			strcpy(text_line[0], EMPTY_STRING);
			if (strcmp(text_line[1], "\n") != 0) {
				strcpy(text_line[0], text_line[1]);
				str_index = 1;
				total_str_len = strlen(text_line[0]);
			}
			else {
				str_index = 0;
				total_str_len = 0;
			}
			strcpy(text_line[1], EMPTY_STRING);
		}
	}

	// Write to stream the last part of the html file.
	fprintf(output_file, "%s", html_content_2);

	fclose(input_file);
	fclose(output_file);
	skipotherprocess:;

    return 0;

	maketh_error:;
	return 1;
}


