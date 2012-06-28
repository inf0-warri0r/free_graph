/*
*Author :Tharindra Galahena
*Project:free_graph - graph drawing library for c/c++ (linux)
*Date   :28/06/2012
*/

#ifndef free_graph_h__
#define free_graph_h__

/*store bitmap data*/
struct graph{
	struct bmp_header *h;
	int pixel_width;
	int pixel_height;
	char **pix;
};
/*get the scale of the graph*/
extern double fg_get_scale(int a, double max, double min);

/*create a line parelel to Y axes*/
extern int fg_create_y(struct graph *g, 
				double range_y_min, //minimum y value in the graph
				double range_y_max, //maximum y value in the graph
				double y, 		// y value of the line
				char color); 		// char which has value between 0x00 to 0xFF

/*create a line parelel to Y axes smaller than leanth ofthe greaf*/
extern int fg_create_y_2(struct graph *g, 
				double range_x_min, //minimum x value in the graph
				double range_x_max, //maximum x value in the graph
				double range_y_min, //minimum y value in the graph
				double range_y_max, //maximum y value in the graph
				double x_min, 		//minimum x value of the line (start)
				double x_max, 		//minimum x value of the line (end)
				double y, 		// y value of the line
				char color);		// char which has value between 0x00 to 0xFF

/*create a line parelel to X axes*/
extern int fg_create_x(struct graph *g, 
				double range_x_min, //minimum x value in the graph
				double range_x_max, //maximum x value in the graph
				double x, 		// y value of the line
				char color);		// char which has value between 0x00 to 0xFF

/*create a line parelel to X axes smaller than leanth ofthe greaf*/
extern int fg_create_x_2(struct graph *g, 
				double range_x_min, //minimum x value in the graph
				double range_x_max, //maximum x value in the graph
				double range_y_min, //minimum y value in the graph
				double range_y_max, //maximum y value in the graph
				double y_min, 		//minimum y value of the line (start)
				double y_max, 		//minimum y value of the line (end)
				double x, 		// y value of the line
				char color);		// char which has value between 0x00 to 0xFF

/*write the graph to the bitmap*/
extern void fg_write_bitmap(struct graph *g, 
					char *name); 	//name of the bitmap

/*draw set of horizontel lines in the graph*/ 
extern void fg_draw_grid_y(struct graph *g, 
			double range_y_min, //minimum y value in the graph
			double range_y_max, //maximum y value in the graph
			double iter, 		//gap between two lines 
			char color);		// char which has value between 0x00 to 0xFF

/*draw set of vertical lines in the graph*/ 
extern void fg_draw_grid_x(struct graph *g, 
			double range_x_min, //minimum x value in the graph
			double range_x_max, //maximum x value in the graph
			double iter,		//gap between two lines 
			char color);		// char which has value between 0x00 to 0xFF

/*clear the graph*/
extern void fg_clear_graph(struct graph *g,
			char color);		//char which has value between 0x00 to 0xFF(background)

/*draw the graph of an equation*/
extern void fg_draw_graph(struct graph *g,
			double (*f)(double),//function containing the equation
			double range_x_min, //minimum x value in the graph
			double range_x_max, //maximum x value in the graph
			double range_y_min, //minimum y value in the graph
			double range_y_max, //maximum y value in the graph
			char color);		// char which has value between 0x00 to 0xFF

/*draw the graph of an equation between given x and y values*/
extern void fg_draw_graph_2(struct graph *g,
			double (*f)(double),//function containing the equation
			double range_x_min, //minimum x value in the graph
			double range_x_max, //maximum x value in the graph
			double range_y_min, //minimum y value in the graph
			double range_y_max, //maximum y value in the graph
			double range_X_min, //minimum x value in the whole graph
			double range_X_max, //maximum x value in the whole graph
			double range_Y_min, //minimum y value in the whole graph
			double range_Y_max, //maximum y value in the whole graph
			char color);		// char which has value between 0x00 to 0xFF

/*initialice data*/
extern struct graph *fg_init(int x, int y); /*width and height of the bitmap in pixels */

#endif 
