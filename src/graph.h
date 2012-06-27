#include "structs.h"
#include "graph.c"

double get_scale(int a, double max, double min);
struct bmp_header * fill_header(int pixel_width, int pixel_height);
int create_y(graph *g, double range_y_min, double range_y_max, double y, char color);
int create_x(graph *g, double range_x_min, double range_x_max, double x, char color);
void write_bitmap(graph *g, char *name);
void draw_graphid_y(graph *g, 
			double range_y_min, 
			double range_y_max, 
			double iter, 
			char color);

void draw_graphid_x(graph *g, 
			double range_x_min, 
			double range_x_max, 
			double iter, 
			char color);

void clear_grapheft(graph *g);

void draw_grapheft(graph *g,
			 double (*f)(double),
			 double range_x_min,
			 double range_x_max,
			 double range_y_min,
			 double range_y_max);

void draw_grapheft_2(graph *g,
			 double (*f)(double),
			 double range_x_min,
			 double range_x_max,
			 double range_y_min,
			 double range_y_max,
			 double range_X_min,
			 double range_X_max,
			 double range_Y_min,
			 double range_Y_max);

void draw_grapheft_in_x(graph *g,
			 double (*f)(double),
			 double range_x_min,
			 double range_x_max,
			 double range_y_min,
			 double range_y_max,
			 double range_X_min,
			 double range_X_max,
			 double range_Y_min,
			 double range_Y_max);

graph *init(int x, int y);
