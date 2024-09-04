/* File:         txt2html\src\main.c
 *
 * Author:       Radoq10288
 *
 * Date & time:  07/10/2022-09:12:05-PM
 */

#include <assert.h>

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_string_replace.h"
#include "string_replace.h"


#define EMPTY_STRING	"\0"

/* Error messages
 */

#define INVALID_INPUT_FILE_ERROR	"Can not convert the file"
#define FILE_CREATE_ERROR	"Failed to create the file"
#define FILE_OPEN_ERROR	"Failed to open the file for reading"
#define FILE_EXIST_ERROR	"The file already exist"

/* Warning messages
 */
#define NO_ARG_WARN	"No argument or option is specified"
#define NO_INPUT_FILE_WARN	"No text file is specified for convertion"
#define UNKNOWN_OPTION_WARN	"The option specified is unknown"

/* Information messages
 */
#define GIVE_HELP_INFO	"Please use help option to get more info on using txt2html"
#define GIVE_INPUT_FILE_INFO	"Only files with '.txt' extension is accepted"
#define GIVE_OPTION_INFO	"This option requires an argument"
#define GIVE_VERSION_INFO	"0.1.3-alpha.2"


typedef struct {
	char name[255];
	char extension[6];
	char page_title[255];
	int content_index;
} File;


static void help(void) {
	printf("\nUsage:\n"
			"    txt2html [Text file filename] [Option]    For converting text file to html.\n"
			"    txt2html [Option]                         For other options to show this help and version.\n"
			"\n"
			"Options:\n"
			"    calibre-epub-xhtml	Creates an xhtml file used in creating epub in calibre.\n"
			"    help         		Show this help.\n"
			"    title        		Set the title of the html file.\n"
			"    version      		Show current version of this software.\n");
}


static void version(void) {
	printf("\ntxt2html version %s, Copyright (C) 2022 Radoq10288\n"
			"txt2html comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\n"
			"This is free software, and you are welcome to redistribute it\n"
			"under certain conditions; type `show c' for details.\n", GIVE_VERSION_INFO);
}


static char html_content[][150] = {
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


int main(int argc, char *argv[]) {
	File text, html;
	html.content_index = 0;
	
	int getopt_status, option_index = 0;

	if (argc == 1) {
		fprintf(stderr, "txt2html\nWarning: %s.\nInfo: %s.\n", NO_ARG_WARN, GIVE_HELP_INFO);
		goto txt2html_error;
	}

	/* Initial values for the text and html data structure.
	 */
	strcpy(text.name, argv[1]);
	strcpy(html.page_title, text.name);
	strcpy(html.extension, "html");
	
	while(true) {
        static struct option long_options[] = {
        	{"calibre-epub-xhtml",		no_argument,		0,		0},
            {"help",					no_argument,		0,  	1},
            {"title",					required_argument,	0,  	2},
            {"version",					no_argument,		0,		3},
            {0,				0,					0,		0}
        };

		opterr = 0;
		getopt_status = getopt_long(argc, argv, ":", long_options, &option_index);
        if (getopt_status == -1) {
			break;
		}

		switch(getopt_status) {
			case 0:
				strcpy(html.extension, "xhtml");
				html.content_index++;
				break;
			case 1:
				help();
				goto skipotherprocess;
			case 2:
				if (argc == 3) {
					fprintf(stderr, "txt2html\nWarning: %s.\n", NO_INPUT_FILE_WARN);
					goto txt2html_error;
				}
				strcpy(html.page_title, optarg);
				break;
			case 3:
				version();
				goto skipotherprocess;
			case ':':
				fprintf(stderr, "txt2html\nOption: %s\nWarning: %s.\n", argv[optind - 1], NO_ARG_WARN);
				fprintf(stderr, "Info: %s.\n", GIVE_OPTION_INFO);
				goto txt2html_error;
			case '?':
				fprintf(stderr, "txt2html\nOption: %s\nWarning: %s.\n", argv[optind - 1], UNKNOWN_OPTION_WARN);
				fprintf(stderr, "Info: %s.\n", GIVE_HELP_INFO);
				goto txt2html_error;
        }
    }

	char result[256];
	FILE *output_file;

	strcpy(result, EMPTY_STRING);
	string_replace(text.name, "txt", html.extension, result);
	if (strcmp(result, "\0") == 0) {
		fprintf(stderr, "txt2html\nError: %s '%s'!\n",INVALID_INPUT_FILE_ERROR ,text.name);
		fprintf(stderr, "Info: %s.\n", GIVE_INPUT_FILE_INFO);
		goto txt2html_error;
	}
	strcpy(html.name, result);

	if (!fopen(html.name, "r")) {
		if (!(output_file = fopen(html.name, "a"))) {
			fprintf(stderr, "txt2html\nError: %s '%s'.\n", FILE_CREATE_ERROR, html.name);
			goto txt2html_error;
		}
	}
	else {
		fprintf(stderr, "txt2html\nFile: %s\nError: %s!\n", html.name, FILE_EXIST_ERROR);
		goto txt2html_error;
	}

	// Write to stream the initial part of the html file.
	char output[150];
	string_replace(html_content[html.content_index], "My Webpage", html.page_title, output);
	fputs(output, output_file);
	strcpy(output, EMPTY_STRING);
	fclose(output_file);

	// Convert text file to html file
	int status = 0;
	status = fstring_replace(text.name, html.name, "\n\n", "</p>\n\n\t\t<p>");
	switch (status) {
		case -2:
			fprintf(stderr, "txt2html\nFile: %s\nError: %s\n", html.name, FILE_CREATE_ERROR);
			goto txt2html_error;
		case -1:
			fprintf(stderr, "txt2html\nFile: %s\nError: %s.\n", text.name, FILE_OPEN_ERROR);
			goto txt2html_error;
		case 1:
			fprintf(stderr, "txt2html\nError: Can't find the text '\n\n'.\n");
			goto txt2html_error;
	}

	// Write to stream the last part of the html file.
	output_file = fopen(html.name, "a");
	fputs(html_content[2], output_file);
	fclose(output_file);

	skipotherprocess:;

    return 0;

	txt2html_error:;
	return 1;
}


