/*

	main.c -- Template main()

	Copyright © 2015-2016 Fletcher T. Penney.


	This program is free software you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation either version 2 of the License, or
	(at your option) any later version.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with this program if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
	
*/

#include <stdio.h>
#include <stdlib.h>

#include "d_string.h"

#define kBUFFERSIZE 4096	// How many bytes to read at a time

// Base parser function declarations
#include "parser.h"

void *ParseAlloc();
void Parse();
void ParseFree();


DString * stdin_buffer() {
	/* Read from stdin and return a GString *
		`buffer` will need to be freed elsewhere */

	char chunk[kBUFFERSIZE];
	size_t bytes;

	DString * buffer = d_string_new("");

    while ((bytes = fread(chunk, 1, kBUFFERSIZE, stdin)) > 0) {
    	d_string_append_c_array(buffer, chunk, bytes);
    }

	fclose(stdin);

	return buffer;
}


DString * scan_file(char * fname) {
	/* Read from stdin and return a GString *
		`buffer` will need to be freed elsewhere */

	char chunk[kBUFFERSIZE];
	size_t bytes;

	FILE * file;

	if ((file = fopen(fname, "r")) == NULL ) {
		return NULL;
	}

	DString * buffer = d_string_new("");

    while ((bytes = fread(chunk, 1, kBUFFERSIZE, file)) > 0) {
    	d_string_append_c_array(buffer, chunk, bytes);
    }

	fclose(file);

	return buffer;
}


int main(int argc, char** argv) {
	DString * buffer = NULL;

	if (argc > 1) {
		buffer = scan_file(argv[1]);
	} else {
		buffer = stdin_buffer();
	}

	if (buffer == NULL) {
		fprintf(stderr, "Error reading input.\n");
		exit(0);
	}

	void* pParser = ParseAlloc (malloc);

	Parse (pParser, INTEGER, 15);
	Parse (pParser, DIVIDE, 0);
	Parse (pParser, INTEGER, 5);
	Parse (pParser, 0, 0);

	ParseFree(pParser, free);
	d_string_free(buffer, true);
}
