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


#define EMPTY_STRING	"\0"


static const char html_content_1[] = {
	"<!DOCTYPE html>\n"
	"<html>\n"
	"\t<head>\n"
	"\t\t<title>My Webpage</title>\n"
	"\t</head>\n"
	"\t<body>\n"
	"\t\t<p>"
};

static const char html_content_2[] = {
	"\t\t</p>\n"
	"\t</body>\n"
	"</html>\n\n\n"
};


int main(int argc, char *argv[]) {
	char *page_title = EMPTY_STRING;
	int getopt_status, option_index = 0;

	while(true) {
        static struct option long_options[] = {
            {"help",		no_argument,		0,  	'h'},
            {"title",		required_argument,	0,  	't'},
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
				//help();
				printf("Show some help.\n");
				goto skipotherprocess;
			case 't':
				strcpy(page_title, optarg);
				break;
			case 'v':
				//version();
				printf("Show current version.\n");
				goto skipotherprocess;
        }
    }


	FILE *input_file, *output_file;
	if (!(input_file = fopen(argv[1], "r"))) {
		fprintf(stderr, "make-th\nError: Failed to open file '%s' for reading.\n", argv[1]);
		goto maketh_error;
	}
	if (!(output_file = fopen("the.html", "a"))) {
		fprintf(stderr, "make-th\nError: Failed to create file 'the.html' for appending.\n");
		goto maketh_error;
	}

	char text_line[2][1000];
	int str_index = 0, total_str_len = 0;

	// Write to stream the initial part of the html file.
	fprintf(output_file, "%s", html_content_1);

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

			// convert text file to html
			fprintf(output_file, "%s", buffer);


			strcpy(buffer, EMPTY_STRING);
			strcpy(text_line[0], EMPTY_STRING);
			strcpy(text_line[1], EMPTY_STRING);

			total_str_len = 0;
			str_index = 0;
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


