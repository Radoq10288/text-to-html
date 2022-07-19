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


	skipotherprocess:;

    return 0;

	maketh_error:;
	return 1;
}


