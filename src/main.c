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
#include <string.h>

#include "d_string.h"
#include "lexer.h"

#define kBUFFERSIZE 4096	// How many bytes to read at a time

// Base parser function declarations
#include "parser.h"

void *ParseAlloc();
void Parse();
void ParseFree();

int scan(Scanner * s, char * stop);


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
		// Read file
		buffer = scan_file(argv[1]);
	} else {
		// Default string if no file to parse
		buffer = d_string_new("(5 + 3) * (27 / 3)\n((5 + 3) * (27 / 3) * (5 + 3) * (27 / 3))\n");

		// Read from stdin
		// buffer = stdin_buffer();
	}

	if (buffer == NULL) {
		fprintf(stderr, "Error reading input.\n");
		exit(0);
	}

	// Create a parser (for lemon)
	void* pParser = ParseAlloc (malloc);

	// Create a scanner (for re2c)
	Scanner s;
	s.start = buffer->str;
	s.cur = s.start;

	// Where do we stop parsing?
	char * stop = buffer->str + buffer->currentStringLength;

	int val;			// Value of INTEGER
	char * substring;	// Substring of buffer to convert to INTEGER value
	size_t len;			// len of INTEGER token
	int token;			// TOKEN type

	do {
		token = scan(&s, stop);

		fprintf(stderr, "token %d (%d/%d)\n", token, (int)(s.start - buffer->str), (int)(s.cur - buffer->str));
		
		if (token == INTEGER) {
			len = s.cur - s.start + 1;
			
			substring = malloc(len);
			strncpy(substring, s.start, len);
			substring[len] = '\0';

			val = atoi(substring);
			free(substring);
			Parse(pParser, token, val);
		} else {
			Parse(pParser, token, 0);
		}
	} while (token != 0);

	// End the parse and clean up
	Parse(pParser, 0, 0);

	ParseFree(pParser, free);
	d_string_free(buffer, true);
}
