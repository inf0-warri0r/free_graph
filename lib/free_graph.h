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

#ifndef free_graph_h__
#define free_graph_h__

/*get the scale of the fg_graph*/
extern double fg_get_scale(int a, double max, double min);

/*create a line parelel to Y axes*/
extern int fg_create_y(fg_graph *g, 
				fg_range *range_y,  // y value range in the fg_graph
				double y, 			// y value of the line
				fg_color color); 	// the colour of the graph

/*create a line parelel to Y axes smaller than leanth ofthe greaf*/
extern int fg_create_y_2(fg_graph *g, 
				fg_area  *out, 		//area/boundries of the fg_graph
				fg_range *range_x,	// x value range of the line
				double y, 			// y value of the line
				fg_color color);	// the colour of the graph

/*create a line parelel to X axes*/
extern int fg_create_x(fg_graph *g, 
				fg_range *range_x, // x value range of the fg_graph
				double x, 		   // x value of the line
				fg_color color);   // the colour of the graph

/*create a line parelel to X axes smaller than leanth ofthe graph*/
extern int fg_create_x_2(fg_graph *g, 
				fg_area  *out, 		//area/boundries of the fg_graph
				fg_range *range_y,	// y value range of the line
				double x, 			// x value of the line
				fg_color color);	// the colour of the graph

/*write the fg_graph to the bitmap*/
extern int fg_write_bitmap(fg_graph *g, 
					char *name); 	//name of the bitmap

/*draw set of horizontel lines in the fg_graph*/ 
extern int fg_draw_grid_y(fg_graph *g, 
			fg_range *range_y,  // y value range in the fg_graph
			double iter, 		// gap between two lines 
			fg_color color);	// the colour of the graph

/*draw set of vertical lines in the fg_graph*/ 
extern int fg_draw_grid_x(fg_graph *g, 
			fg_range *range_x,  // x value range in the fg_graph
			double iter,		// gap between two lines 
			fg_color color);	// the colour of the graph

/*clear the fg_graph*/
extern void fg_clear_graph(fg_graph *g,
			fg_color color);	// the colour of the background

/*draw the fg_graph of an equation*/
extern int fg_draw_graph(fg_graph *g,
			double (*f)(double),//function containing the equation
			fg_area *out,	    //area/boundries of the fg_graph
			fg_color color);	// the colour of the graph

/*draw the fg_graph of an equation between given x and y values*/
extern int fg_draw_graph_2(struct fg_graph *g,
			double (*f)(double),//function containing the equation
			fg_area *out,		//area/boundries of the fg_graph
			fg_area *in,		//given boundies inside whole fg_graph 
			fg_color color);	// the colour of the graph
			
/*draw a line between two points*/
extern int fg_draw_line(fg_graph *g,
			 fg_area *out,		//area/boundries of the fg_graph
			 fg_point *p1,		//point 1
			 fg_point *p2,		//point 2
			 fg_color color);	// the colour of the graph

/*mark a point in fg_graph*/
extern int fg_draw_point(fg_graph *g,
			 fg_area *out,		//area/boundries of the fg_graph
			 fg_point *p,		//point to mark
			 fg_color color);	// the colour of the graph
	
/*draw a fg_graph with given list of points*/		 
extern int fg_draw_graph_3(fg_graph *g,
			 fg_area *out,		//area/boundries of the fg_graph
			 double *x_axe,		//x point list
			 double *y_axe,		//y point list
			 int x_len,			//lenth of x point list
			 int y_len,			//length of y point list
			 fg_color color);	// the colour of the graph
			 
/*initialice data*/
extern fg_graph *fg_init(int x, int y); /*width and height of the bitmap in pixels */
extern void fg_free(fg_graph *g);
#endif 
