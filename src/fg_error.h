/*
*Author :Tharindra Galahena
*Project:free_fg_graph - fg_graph drawing library for c/c++ (linux)
*Date   :28/06/2012
*/

#ifndef fg_error_h__
#define fg_error_h__

/*return the error message of the code */
extern char *fg_error(int errnum);
/*print a error massage for error code*/
extern void fg_perror(const char *message, int errnum);

#endif 
