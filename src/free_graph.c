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
#include "fg_structs.h"

#define MAX_Y(a, b) ((a) > (b) ? (a) : (b))
#define MIN_Y(a, b) ((a) < (b) ? (a) : (b))

/*get the scale of the fg_graph*/
double fg_get_scale(int a, double max, double min){
	return (double)a / (max - min);
}

struct bmp_header * fg_fill_header(int pixel_width, int pixel_height){

    struct bmp_header *header = (struct bmp_header *)malloc(sizeof(struct bmp_header));
    header -> BM = 0x4d42;
    header -> size_of_file = sizeof(struct bmp_header) + 3 * pixel_width * pixel_height * 4;
    header -> reserve = 0000;
    header -> offset_of_pixle_data = 54;
    header -> size_of_header = 40;
    header -> width = pixel_width * 2;
    header -> hight = pixel_height * 2;
    header -> num_of_colour_plane = 1;
    header -> num_of_bit_per_pix = 24;
    header -> compression = 0;
    header -> size_of_pix_data = 3 * pixel_width * pixel_height * 4;
    header -> h_resolution = 2835;
    header -> v_resolution = 2835;
    header -> num_of_colour_in_palette = 0;
    header -> important_colours = 0;
    return header;
}
/*create a line parelel to X axes*/
int fg_create_y(fg_graph *g, 
			fg_range *range_y, 
			double y, 
			fg_color color){ 

	double range_y_max = range_y -> max;
	double range_y_min = range_y -> min;
	
	if(range_y_max - range_y_min <= 0) return -3;
	if(range_y_max < y || range_y_min > y) return -1;
	
	fg_color **pix = g -> pix;
	double scale = fg_get_scale(g -> pixel_height, range_y_max, range_y_min);
	int Y = (int)(y*scale - range_y_min*scale);
	int i;
	for(i = 0; i < g -> pixel_width; i++){
		pix[Y][i]	= color;
	}
	return 1;
}
/*create a line parelel to X axes smaller than leanth ofthe greaf*/
int fg_create_y_2(fg_graph *g, 
			fg_area  *out,
			fg_range *range_x,
			double y, 
			fg_color color){
 
	double range_x_min = out -> x_min;
	double range_x_max = out -> x_max;
	double range_y_min = out -> y_min;
	double range_y_max = out -> y_max;

	double x_min = range_x -> min; 
	double x_max = range_x -> max;
	
	if(range_y_max - range_y_min <= 0) return -3;
	if(range_x_max - range_x_min <= 0) return -2;
	if(x_max - x_min <= 0) return -4;		
	if(range_y_max < y || range_y_min > y) return -1;
	
	fg_color **pix = g -> pix;
	double scale_y = fg_get_scale(g -> pixel_height, range_y_max, range_y_min);
	double scale_x = fg_get_scale(g -> pixel_width, range_x_max, range_x_min);

	int Y = (int)(y*scale_y - range_y_min*scale_y);
	int i;
	for(i = x_min*scale_x; i < x_max*scale_x; i++){
		pix[Y][i -  (int)(range_x_min*scale_x)]	= color;
	}
	return 1;
}
/*create a line parelel to Y axes*/
int fg_create_x(fg_graph *g, 
			fg_range *range_x, 
			double x, 
			fg_color color){ 
				
	double range_x_max = range_x -> max;
	double range_x_min = range_x -> min;
	
	if(range_x_max - range_x_min <= 0) return -2;
	if(range_x_max < x || range_x_min > x) return 0;
	
	fg_color **pix = g -> pix;
	double scale = fg_get_scale(g -> pixel_width, range_x_max, range_x_min);
	int X = (int)(x*scale - range_x_min*scale);
	int i;
	for(i = 0; i < g -> pixel_height; i++){
		pix[i][X]	= color;
	}
	return 1;
}
/*create a line parelel to Y axes smaller than leanth ofthe greaf*/
int fg_create_x_2(fg_graph *g, 
			fg_area *out,
			fg_range *range_y,
			double x, 
			fg_color color){
 
	double range_x_min = out -> x_min;
	double range_x_max = out -> x_max;
	double range_y_min = out -> y_min;
	double range_y_max = out -> y_max;

	double y_min = range_y -> min; 
	double y_max = range_y -> max;
	
	if(range_y_max - range_y_min <= 0) 	   return -3;
	if(range_x_max - range_x_min <= 0) 	   return -2;
	if(y_max - y_min <= 0) 				   return -5;
	if(range_x_max < x || range_x_min > x) return 0;
	
	fg_color **pix = g -> pix;
	double scale_y = fg_get_scale(g -> pixel_height, range_y_max, range_y_min);
	double scale_x = fg_get_scale(g -> pixel_width, range_x_max, range_x_min);

	int X = (int)(x*scale_x - range_x_min*scale_x);
	int i;
	for(i = y_min*scale_y; i < y_max*scale_y; i++){
		pix[i -  (int)(range_y_min*scale_y)][X]	= color;
	}
	return 1;
}
/*write the fg_graph to the bitmap*/
int fg_write_bitmap(fg_graph *g, char *name){
	fg_color **pix = g -> pix;

	FILE *fp = fopen(name, "w");
	if(fp == NULL) return -8;
	
	fwrite ((char*)(g -> h), sizeof(struct bmp_header), 1, fp);
	fwrite (&pix[0][0], 1, 1, fp);
	int i, j, k;
	for(i = 0; i < g -> pixel_height; i++){
		for(j = 0; j < g -> pixel_width; j++){
			for(k = 0; k < 2; k++){
				fwrite (&(pix[i][j].G), 1, 1, fp);	
				fwrite (&(pix[i][j].R), 1, 1, fp);
				fwrite (&(pix[i][j].B), 1, 1, fp);		
			}
		}
		for(j = 0; j < g -> pixel_width; j++){
			for(k = 0; k < 2; k++){
				fwrite (&(pix[i][j].G), 1, 1, fp);	
				fwrite (&(pix[i][j].R), 1, 1, fp);
				fwrite (&(pix[i][j].B), 1, 1, fp);			
			}
			
		}	
	}
	fclose(fp);
	return 1;
}
/*draw set of horizontel lines in the fg_graph*/ 
int fg_draw_grid_y(fg_graph *g,
			 fg_range *range_y,
			 double iter,
			 fg_color color){

	double range_y_max = range_y -> max;
	double range_y_min = range_y -> min;
	
	if(range_y_max - range_y_min <= 0) return -3;
	double i = 0;
	if(range_y_min > i) i = range_y_min;
	while(i < range_y_max){
		fg_create_y(g, range_y, i, color);
		i += iter;
	}
	i = 0;
	if(range_y_min < i)
		while(i > range_y_min){
			fg_create_y(g, range_y, i, color);
			i -= iter;
		}
	return 1;
}
/*draw set of vertical lines in the fg_graph*/ 
int fg_draw_grid_x(fg_graph *g,
			 fg_range *range_x,
			 double iter,
			 fg_color color){
	
	double range_x_max = range_x -> max;
	double range_x_min = range_x -> min;
	
	if(range_x_max - range_x_min <= 0) return -2;
	double i = 0;
	if(range_x_min > i) i = range_x_min;
	while(i < range_x_max){
		fg_create_x(g, range_x, i, color);
		i += iter;
	}
	i = 0;
	if(range_x_min < i)
		while(i > range_x_min){
			fg_create_x(g, range_x, i, color);
			i -= iter;
		}
	return 1;
}
/*clear the fg_graph*/
void fg_clear_graph(fg_graph *g, fg_color color){
	fg_color **pix = g -> pix;
	int i, j;
	for(i = 0; i < g -> pixel_height; i++){
		for(j = 0; j < g -> pixel_width; j++){
			pix[i][j] = color;
		}	
	}
}
/*draw the fg_graph of an equation*/
int fg_draw_graph(fg_graph *g,
			 double (*f)(double),
			 fg_area *out,
			 fg_color color){

	double range_x_min = out -> x_min;
	double range_x_max = out -> x_max;
	double range_y_min = out -> y_min;
	double range_y_max = out -> y_max;

	if(range_y_max - range_y_min <= 0) return -3;
	if(range_x_max - range_x_min <= 0) return -2;

	double x_scale = fg_get_scale(g -> pixel_width, range_x_max, range_x_min);
	double y_scale = fg_get_scale(g -> pixel_height, range_y_max, range_y_min);
	fg_color **pix = g -> pix;
	double y;
	double Y_old;
	int start = 0;
	int i, j;
	for(i = range_x_min*x_scale; i < range_x_max*x_scale; i++){
		double x = (double)i/x_scale;

		y = (*f)(x);		

		int Y = (int) (y*y_scale) - range_y_min*y_scale;
		if(start){
			int h, l;
			h = MAX_Y(Y, Y_old);
			l = MIN_Y(Y, Y_old);
			if(h - l < 3 * (g -> pixel_height) / 4)
				for(j = l; j <= h; j++)
					if(j >= 0 && j < g -> pixel_height) 
						pix[j][i - (int)(range_x_min*x_scale)] = color;
		}else start++;
		Y_old = Y;
	}
	return 1;
}
/*draw the fg_graph of an equation between given x and y values*/
int fg_draw_graph_2(fg_graph *g,
			 double (*f)(double),
			 fg_area *out,
			 fg_area *in,
			 fg_color color){
	

	double range_x_min = out -> x_min;
	double range_x_max = out -> x_max;
	double range_y_min = out -> y_min;
	double range_y_max = out -> y_max;
	double range_X_min =  in -> x_min;
	double range_X_max =  in -> x_max;
	double range_Y_min =  in -> y_min;
	double range_Y_max =  in -> y_max;

	if(range_y_max - range_y_min <= 0) return -3;
	if(range_x_max - range_x_min <= 0) return -2;
	if(range_x_min > range_X_min || range_x_max < range_X_max) return -6;
	if(range_y_min > range_Y_min || range_y_max < range_Y_max) return -7;
	if(range_Y_max - range_Y_min <= 0) return -5;
	if(range_X_max - range_X_min <= 0) return -4;
	
	double X_scale = fg_get_scale(g -> pixel_width, range_x_max, range_x_min);
	double Y_scale = fg_get_scale(g -> pixel_height, range_y_max, range_y_min);
	fg_color **pix = g -> pix;
	double y;
	double Y_old;
	int start = 0;
	int i, j;
	for(i = range_X_min*X_scale; i < range_X_max*X_scale; i++){
		
		double x = (double)i/X_scale;

		y = (*f)(x);		

		int Y = (int) (y*Y_scale) - range_y_min*Y_scale;
		if(i > range_x_min*X_scale && i < range_x_max*X_scale){
			if(start){
				int h, l;
				h = MAX_Y(Y, Y_old);
				l = MIN_Y(Y, Y_old);
				if(h - l < 3 * (g ->  pixel_height) / 4)
					for(j = l; j <= h; j++)
						if(j > range_Y_min*Y_scale - range_y_min*Y_scale 
						&& j < range_Y_max*Y_scale - range_y_min*Y_scale){ 
							pix[j][i - (int)(range_x_min*X_scale)] = color;
							
						}
			}else start++;
		}
		Y_old = Y;
	}
	return 1;
}
int fg_draw_line(fg_graph *g,
			 fg_area *out,
			 fg_point *p1,
			 fg_point *p2,
			 fg_color color){

	double range_x_min = out -> x_min;
	double range_x_max = out -> x_max;
	double range_y_min = out -> y_min;
	double range_y_max = out -> y_max;
	
	if(range_y_max - range_y_min <= 0) return -3;
	if(range_x_max - range_x_min <= 0) return -2;
	if(range_x_min > p1 -> x || range_x_max < p1 -> x) return -9;
	if(range_y_min > p1 -> y || range_y_max < p1 -> y) return -9;
	if(range_x_min > p2 -> x || range_x_max < p2 -> x) return -9;
	if(range_y_min > p2 -> y || range_y_max < p2 -> y) return -9;
	
	double range_X_min;
	double range_Y_min;
	double range_X_max;
	double range_Y_max;
	
	if(p2 -> x >= p1 -> x){
		range_X_min =  p1 -> x;
		range_Y_min =  p1 -> y;
		range_X_max =  p2 -> x;
		range_Y_max =  p2 -> y;
	}else{
		range_X_min =  p2 -> x;
		range_Y_min =  p2 -> y;
		range_X_max =  p1 -> x;
		range_Y_max =  p1 -> y;
	}
	
	double X_scale = fg_get_scale(g -> pixel_width, range_x_max, range_x_min);
	double Y_scale = fg_get_scale(g -> pixel_height, range_y_max, range_y_min);
	fg_color **pix = g -> pix;
	double y;
	double Y_old;
	int start = 0;
	int i, j;
	if(range_X_max != range_X_min){
		double m = (range_Y_max - range_Y_min)/(range_X_max - range_X_min);
		for(i = range_X_min*X_scale; i < range_X_max*X_scale; i++){
			
			double x = (double)i/X_scale;

			y = m*x - m*range_X_min + range_Y_min;		
			
			int Y = (int) (y*Y_scale) - range_y_min*Y_scale;
			if(i > range_x_min*X_scale && i < range_x_max*X_scale){
				if(start){
					int h, l;
					h = MAX_Y(Y, Y_old);
					l = MIN_Y(Y, Y_old);
					for(j = l; j <= h; j++){
						if(j < g -> pixel_height 
						   && i - (int)(range_x_min*X_scale) < g -> pixel_width){ 
							if(j >= 0 && i - (int)(range_x_min*X_scale) >= 0){ 
								pix[j][i - (int)(range_x_min*X_scale)] = color;
							}
						}
					}
				}else start++;
			}
			Y_old = Y;
		}
	}else{
		fg_range range_y;
		range_y.min = range_Y_min;
		range_y.max = range_Y_max;
		
		fg_create_x_2(g, out, &range_y, range_X_min, color);  
	}
	return 1;
}
int fg_draw_point(fg_graph *g,
			 fg_area *out,
			 fg_point *p,
			 fg_color color){

	double range_x_min = out -> x_min;
	double range_x_max = out -> x_max;
	double range_y_min = out -> y_min;
	double range_y_max = out -> y_max;

	if(range_y_max - range_y_min <= 0) return -3;
	if(range_x_max - range_x_min <= 0) return -2;
	if(range_x_min > p -> x || range_x_max < p -> x) return -9;
	if(range_y_min > p -> y || range_y_max < p -> y) return -9;
	
	double x_scale = fg_get_scale(g -> pixel_width, range_x_max, range_x_min);
	double y_scale = fg_get_scale(g -> pixel_height, range_y_max, range_y_min);
	fg_color **pix = g -> pix;
	double x = p -> x * x_scale - range_x_min*x_scale;
	double y = p -> y * y_scale - range_y_min*y_scale;
		
	int j, k;
	for(j = (int)y - 2; j <= (int)y + 2; j++)
		for(k = (int)x - 2; k <= (int)x + 2; k++)
			if(j > 0 && j < g ->pixel_height) 
				pix[j][k] = color;
					
	return 1;
}
int fg_draw_graph_3(fg_graph *g,
			 fg_area *out,
			 double *x_axe,
			 double *y_axe,
			 int from,
			 int to,
			 fg_color color){

	double range_x_min = out -> x_min;
	double range_x_max = out -> x_max;
	double range_y_min = out -> y_min;
	double range_y_max = out -> y_max;

	if(range_y_max - range_y_min <= 0) return -3;
	if(range_x_max - range_x_min <= 0) return -2;
	int i;
	for(i = from; i < to; i++){

		if(range_x_min > x_axe[i] || range_x_max < x_axe[i]) return -10;
		if(range_y_min > y_axe[i] || range_y_max < y_axe[i]) return -10;
		if(range_x_min > x_axe[i + 1] || range_x_max < x_axe[i + 1]) return -10;
		if(range_y_min > y_axe[i + 1] || range_y_max < y_axe[i + 1]) return -10;

		fg_point p1;
		p1.x = x_axe[i];
		p1.y = y_axe[i];
		
		fg_point p2;
		p2.x = x_axe[i + 1];
		p2.y = y_axe[i + 1];

		fg_draw_line(g, out, &p1, &p2, color);

		fg_draw_point(g, out, &p1, color);
		fg_draw_point(g, out, &p2, color);
	}
	return 1;
}
/*initialice data*/
fg_graph *fg_init(int x, int y){
	struct fg_graph *g = (fg_graph *)malloc(sizeof(fg_graph));
	g -> pixel_width = x / 2;
	g -> pixel_height = y / 2;

	fg_color **pix = (fg_color **)malloc(sizeof(fg_color *) * y/2);
	int i = 0;
	for(i = 0; i < y/2; i++) pix[i] = (fg_color *)malloc(sizeof(fg_color) *  x/2);

	g -> pix = pix;
	g -> h = fg_fill_header(g -> pixel_width, g -> pixel_height);

	return g;
}
void fg_free(fg_graph *g){
	free(g -> pix);
	free(g);
}
