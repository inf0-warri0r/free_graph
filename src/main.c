#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "graph.h"

double func1(double x){
	return 2*x*x;
}
double func2(double x){
	return 1/cos(x*3.14/180.0);
}
double func4(double x){
	return sin(x*3.14/180.0);
}
double func3(double x){
	return tan(x*3.14/180.0);
}

int main(){
	
	graph *g = init(2000, 1000);

	double range_x_min = -100.0;
	double range_x_max =  100.0;
	double range_y_min = -100.0;
	double range_y_max =  100.0;
	double x_scale = get_scale(g -> pixel_width, range_x_max, range_x_min);
	double y_scale = get_scale(g -> pixel_height, range_y_max, range_y_min);

	clear_grapheft(g);
	
	draw_graphid_y(g, range_y_min, range_y_max,  10.0, (char)0xAA);
	draw_graphid_x(g, range_x_min, range_x_max,  10.0, (char)0xAA);
	create_y(g, range_y_min, range_y_max, 0, (char)0x00);

	create_x(g, range_x_min, range_x_max, 0, (char)0x00);
	draw_grapheft(g, func1, 
			 range_x_min, range_x_max, range_y_min, range_y_max);
	write_bitmap(g, "a.bmp");
}
