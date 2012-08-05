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

char *fg_error(int errnum){
	if(errnum < 0) errnum = -1 * errnum;
	//if (errnum < SND_ERROR_BEGIN) return (char *) strerror(errnum);
	//errnum -= SND_ERROR_BEGIN;
	if (errnum >= sizeof(fg_error_codes) / sizeof(char *)) return "Unknown error";
	return fg_error_codes[errnum];
}

void fg_perror(const char *message, int errnum){

		char *error = fg_error(errnum);
		fprintf(stderr, "%s : %s", message, error);
}
