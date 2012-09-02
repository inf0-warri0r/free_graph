/*
* Author :Tharindra Galahena
* Project:free_graph - fg_graph drawing library for c/c++ (linux)
* Date   :28/06/2012
*
*
* 
* 
*     Copyright 2012 Tharindra Galahena
*
* This file is part of free_graph.
*
* free_graph is free software: you can redistribute it and/or modify it under the terms of 
* the GNU General Public License as published by the Free Software Foundation, either 
* version 3 of the License, or any later version. free_graph is distributed in the hope 
* that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General 
* Public License for more details.
*
* You should have received a copy of the GNU General Public License along with free_graph. 
* If not, see http://www.gnu.org/licenses/.
* 
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
