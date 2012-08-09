/*
*Author :Tharindra Galahena
*Project:free_fg_graph - fg_graph drawing library for c/c++ (linux)
*Date   :28/06/2012
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char *fg_error_codes[] = {
	"x is not in range",
	"y is not in range",
	"outer x range is less or equal to zero",
	"outer y range is less or equal to zero",
	"inner x range is less or equal to zero",
	"inner y range is less or equal to zero",
	"inner x range incorrect",
	"inner y range incorrect",
	"file write error",
	"point is out of range",
	"array index out of range"
};

/*return the error message of the code */
char *fg_error(int errnum){
	if(errnum <= 0) errnum = -1 * errnum;
	else return NULL;
	if (errnum >= sizeof(fg_error_codes) / sizeof(char *)) return "Unknown error";
	return fg_error_codes[errnum];
}
/*print a error massage for error code*/
void fg_perror(const char *message, int errnum){
		char *error = fg_error(errnum);
		if(error != NULL) fprintf(stderr, "%s : %s", message, error);
}
