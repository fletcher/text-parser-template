/**

	Parser-Template -- Boilerplate parser example using re2c lexer and lemon parser.

	@file parser.y

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


//
// Language grammar here
//

%token_type {int}


%left PLUS MINUS.
%left DIVIDE TIMES.

main	::= ins.

ins		::= ins in.
ins		::= in.

in		::= program NEWLINE.
in		::= program.

program ::= expr(A).					{ fprintf(stdout, "Result = %d\n", A); }

expr(A)	::= PAREN_L expr(B) PAREN_R.	{ A = B; }

expr(A) ::= expr(B) DIVIDE expr(C).		{ A = B / C; }
expr(A) ::= expr(B) TIMES expr(C).		{ A = B * C; }
expr(A) ::= expr(B) PLUS expr(C).		{ A = B + C; }
expr(A) ::= expr(B) MINUS expr(C).		{ A = B - C; }

expr(A) ::= INTEGER(B). { A = B; }


//
// Additional Configuration
//

%include {
	#include <assert.h>
	#include <stdio.h>
	#include <stdlib.h>

	#include "parser.h"
}


// Improved error messages for debugging:
//	http://stackoverflow.com/questions/11705737/expected-token-using-lemon-parser-generator

// %syntax_error { 
// 	int n = sizeof(yyTokenName) / sizeof(yyTokenName[0]);
// 	for (int i = 0; i < n; ++i) {
// 		int a = yy_find_shift_action(yypParser, (YYCODETYPE)i);
// 		if (a < YYNSTATE + YYNRULE) {
// 			printf("expected token: %s\n", yyTokenName[i]);
// 		}
// 	}
// }

