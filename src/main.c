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


char html_content[][150] = {
	"<!DOCTYPE html>\n"
	"<html>\n"
	"\t<head>\n"
	"\t\t<title>My Webpage</title>\n"
	"\t</head>\n"
	"\t<body>\n"
	"\t\t<p>",

	"<?xml version='1.0' encoding='utf-8'?>\n"
	"<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
	"\t<head>\n"
	"\t\t<title>My Webpage</title>\n"
	"\t</head>\n"
	"\t<body>\n"
	"\t\t<p>",

	"</p>\n"
	"\t</body>\n"
	"</html>\n\n\n"
};


static void help(void) {
	printf("\nUsage:\n"
			"    make-t2h [Text file filename] [Option]    For converting text file to html.\n"
			"    make-t2h [Option]                         For other options to show help, version, etc.\n"
			"\n"
			"Options:\n"
			"    -h, --help         Show this help.\n"
			"    -t, --title        Set the title of the html file.\n"
			"    -v, --version      Show current version of this software.\n");
}


static void version(void) {
	printf("\nmake-t2h version 0.1.0-alpha.1, Copyright (C) 2022 Radoq10288\n"
			"make-t2h comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\n"
			"This is free software, and you are welcome to redistribute it\n"
			"under certain conditions; type `show c' for details.\n");
}


int main(int argc, char *argv[]) {
	char file_extension[6] = "html",
		 html_file_name[256] = EMPTY_STRING,
		 page_title[256] = EMPTY_STRING,
		 text_file_name[256] = EMPTY_STRING;
	int getopt_status, html_content_index = 0, option_index = 0;

	if (argc == 1) {
		fprintf(stderr, "make-t2h\nError: No argument or option specified.\nInfo: Type 'make-t2h -h/--help' to see usage and available options.");
		goto maket2h_error;
	}
	strcpy(text_file_name, argv[1]);

	while(true) {
        static struct option long_options[] = {
            {"help",		no_argument,		0,  	'h'},
            {"title",		required_argument,	0,  	1},
            {"version",		no_argument,		0,		'v'},
            {"xhtml",		no_argument,		0,		2},
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
					fprintf(stderr, "make-t2h\nError: No text file is specified for convertion.\n");
					goto maket2h_error;
				}
				strcpy(page_title, optarg);
				break;
			case 2:
				strcpy(file_extension, "xhtml");
				html_content_index++;
				break;
			case 'v':
				version();
				goto skipotherprocess;
			case ':':
				if (optopt == 0) {
					fprintf(stderr, "make-t2h\nError: The long option --%s requires an argument.\n", long_options[option_index].name);
				}
				else {
					fprintf(stderr, "make-t2h\nError: The short option -%c requires an argument.\n", optopt);
				}
				goto maket2h_error;
			case 0:
			case '?':
				if (optopt != 0) {
					fprintf(stderr, "make-t2h\nError: Unknown short option '-%c'.\n", optopt);
				}
				else {
					fprintf(stderr, "make-t2h\nError: Unknown long option '%s'.\n", argv[(optind - 1)]);
				}
				fprintf(stderr, "Info: Type 'make-t2h -h/--help' to see available options.\n");
				goto maket2h_error;
        }
    }

	FILE *output_file;

	strcpy(html_file_name, strrep(text_file_name, "txt", file_extension));
	if (!fopen(html_file_name, "r")) {
		if (!(output_file = fopen(html_file_name, "a"))) {
			fprintf(stderr, "make-t2h\nError: Failed to create file '%s'.\n", html_file_name);
			goto maket2h_error;
		}
	}
	else {
		fprintf(stderr, "make-t2h\nError: File '%s' already exist!\n", html_file_name);
		goto maket2h_error;
	}	

	// Write to stream the initial part of the html file.
	char  *output;
	output = strrep(html_content[html_content_index], "My Webpage", page_title);
	fputs(output, output_file);
	output = EMPTY_STRING;

	// Convert text file to html file
	if (file_strrep(text_file_name, output_file, "\n\n", "</p>\n\n\t\t<p>") != 0) {
		fprintf(stderr, "make-t2h\nError: Failed to open file '%s' for reading.\n", text_file_name);
		goto maket2h_error;
	}

	// Write to stream the last part of the html file.
	fputs(html_content[2], output_file);

	fclose(output_file);
	skipotherprocess:;

    return 0;

	maket2h_error:;
	return 1;
}


