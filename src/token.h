/**

	Parser-Template -- Boilerplate parser example using re2c lexer and lemon parser.

	@file token.h

	@brief 


	@author	Fletcher T. Penney
	@bug	

**/

/*

	Copyright © 2016 Fletcher T. Penney.


	The `c-template` project is released under the MIT License.
	
	GLibFacade.c and GLibFacade.h are from the MultiMarkdown v4 project:
	
		https://github.com/fletcher/MultiMarkdown-4/
	
	MMD 4 is released under both the MIT License and GPL.
	
	
	CuTest is released under the zlib/libpng license. See CuTest.c for the text
	of the license.
	
	
	## The MIT License ##
	
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:
	
	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.

*/


#ifndef TOKEN_PARSER_TEMPLATE_H
#define TOKEN_PARSER_TEMPLATE_H

struct token {
	unsigned short		type;
	size_t				start;
	size_t				len;

	struct token *		next;
	struct token *		prev;
	struct token *		child;
};

typedef struct token token;


/// Get pointer to a new token
token * token_new(unsigned short type, size_t start, size_t len, token * prev);

/// Create a parent for a chain of tokens
token * token_new_parent(token * child, unsigned short type, token * prev);

/// Free token
void token_free(token * t);

/// Free token tree
void token_tree_free(token * t);

/// Describe the contents of the token tree
void token_tree_describe(token * t, char * string);

#endif

