/// Re2c scanner data
struct Scanner {
	char * start;	//!< Start of current token
	char * cur;		//!< Character currently being examined
	char * ptr;		//!< Used for backtracking by re2c
};

typedef struct Scanner Scanner;
