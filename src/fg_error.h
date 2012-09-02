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

#ifndef fg_error_h__
#define fg_error_h__

/*return the error message of the code */
extern char *fg_error(int errnum);
/*print a error massage for error code*/
extern void fg_perror(const char *message, int errnum);

#endif 
