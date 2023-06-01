/* File:         txt2html\src\main.c
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


typedef struct {
	char name[255];
	char extension[6];
	char page_title[255];
	int content_index;
} File;


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


static void help(void) {
	printf("\nUsage:\n"
			"    txt2html [Text file filename] [Option]    For converting text file to html.\n"
			"    txt2html [Option]                         For other options to show help, version, etc.\n"
			"\n"
			"Options:\n"
			"    -h, --help         		Show this help.\n"
			"    -t, --title        		Set the title of the html file.\n"
			"        --calibre-epub-xhtml	Creates an xhtml file used in creating epub in calibre.\n"
			"    -v, --version      		Show current version of this software.\n");
}


static void version(void) {
	printf("\ntxt2html version 0.1.3-alpha.2, Copyright (C) 2022 Radoq10288\n"
			"txt2html comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\n"
			"This is free software, and you are welcome to redistribute it\n"
			"under certain conditions; type `show c' for details.\n");
}


int main(int argc, char *argv[]) {
	File text, html;
	html.content_index = 0;
	
	int getopt_status, option_index = 0;

	if (argc == 1) {
		fprintf(stderr, "txt2html\nError: No argument or option specified.\nInfo: Type 'txt2html -h/--help' to see usage and available options.\n");
		goto txt2html_error;
	}
	strcpy(text.name, argv[1]);
	strcpy(html.extension, "html");

	while(true) {
        static struct option long_options[] = {
        	{"calibre-epub-xhtml",		no_argument,		0,		2},
            {"help",					no_argument,		0,  	'h'},
            {"title",					required_argument,	0,  	1},
            {"version",					no_argument,		0,		'v'},
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
					fprintf(stderr, "txt2html\nError: No text file is specified for convertion.\n");
					goto txt2html_error;
				}
				strcpy(html.page_title, optarg);
				break;
			case 2:
				strcpy(html.extension, "xhtml");
				html.content_index++;
				break;
			case 'v':
				version();
				goto skipotherprocess;
			case ':':
				if (optopt == 0) {
					fprintf(stderr, "txt2html\nError: The long option --%s requires an argument.\n", long_options[option_index].name);
				}
				else {
					fprintf(stderr, "txt2html\nError: The short option -%c requires an argument.\n", optopt);
				}
				goto txt2html_error;
			case 0:
			case '?':
				if (optopt != 0) {
					fprintf(stderr, "txt2html\nError: Unknown short option '-%c'.\n", optopt);
				}
				else {
					fprintf(stderr, "txt2html\nError: Unknown long option '%s'.\n", argv[(optind - 1)]);
				}
				fprintf(stderr, "Info: Type 'txt2html -h/--help' to see available options.\n");
				goto txt2html_error;
        }
    }

	char result[256];
	FILE *output_file;

	strcpy(result, EMPTY_STRING);
	strrep(text.name, "txt", html.extension, result);
	if (result == NULL) {
		fprintf(stderr, "txt2html\nError: Can not convert the file '%s'!\n"
						"info: Only files with '.txt' extension is accepted.\n", text.name);
		goto txt2html_error;
	}
	strcpy(html.name, result);

	if (!fopen(html.name, "r")) {
		if (!(output_file = fopen(html.name, "a"))) {
			fprintf(stderr, "txt2html\nError: Failed to create file '%s'.\n", html.name);
			goto txt2html_error;
		}
	}
	else {
		fprintf(stderr, "txt2html\nError: File '%s' already exist!\n", html.name);
		goto txt2html_error;
	}	

	// Write to stream the initial part of the html file.
	char output[150];
	strrep(html_content[html.content_index], "My Webpage", html.page_title, output);
	fputs(output, output_file);
	strcpy(output, EMPTY_STRING);

	// Convert text file to html file
	if (file_strrep(text.name, output_file, "\n\n", "</p>\n\n\t\t<p>") != 0) {
		fprintf(stderr, "txt2html\nError: Failed to open file '%s' for reading.\n", text.name);
		goto txt2html_error;
	}

	// Write to stream the last part of the html file.
	fputs(html_content[2], output_file);

	fclose(output_file);
	skipotherprocess:;

    return 0;

	txt2html_error:;
	return 1;
}


