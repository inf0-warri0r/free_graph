/*
*Author :Tharindra Galahena
*Project:free_fg_graph - fg_graph drawing library for c/c++ (linux)
*Date   :28/06/2012
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
int fg_create_y(struct fg_graph *g, 
			fg_range *range_y, 
			double y, 
			char color){ 

	double range_y_max = range_y -> max;
	double range_y_min = range_y -> min;
	
	if(range_y_max < y || range_y_min > y) return 0;
	if(range_y_max - range_y_min <= 0) return 0;
	char **pix = g -> pix;
	double scale = fg_get_scale(g -> pixel_height, range_y_max, range_y_min);
	int Y = (int)(y*scale - range_y_min*scale);
	int i;
	for(i = 0; i < g -> pixel_width; i++){
		pix[Y][i]	= color;
	}
	return 1;
}
/*create a line parelel to X axes smaller than leanth ofthe greaf*/
int fg_create_y_2(struct fg_graph *g, 
			fg_area  *out,
			fg_range *range_x,
			double y, 
			char color){
 
	double range_x_min = out -> x_min;
	double range_x_max = out -> x_max;
	double range_y_min = out -> y_min;
	double range_y_max = out -> y_max;

	double x_min = range_x -> min; 
	double x_max = range_x -> max;
			
	if(range_y_max < y || range_y_min > y) return 0;
	if(range_y_max - range_y_min <= 0 || range_x_max - range_x_min <= 0 || x_max - x_min <= 0) return 0;
	char **pix = g -> pix;
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
int fg_create_x(struct fg_graph *g, 
			fg_range *range_x, 
			double x, 
			char color){ 
				
	double range_x_max = range_x -> max;
	double range_x_min = range_x -> min;
	
	if(range_x_max < x || range_x_min > x) return 0;
	if(range_x_max - range_x_min <= 0) return 0;
	char **pix = g -> pix;
	double scale = fg_get_scale(g -> pixel_width, range_x_max, range_x_min);
	int X = (int)(x*scale - range_x_min*scale);
	int i;
	for(i = 0; i < g -> pixel_height; i++){
		pix[i][X]	= color;
	}
	return 1;
}
/*create a line parelel to Y axes smaller than leanth ofthe greaf*/
int fg_create_x_2(struct fg_graph *g, 
			fg_area *out,
			fg_range *range_y,
			double x, 
			char color){
 
	double range_x_min = out -> x_min;
	double range_x_max = out -> x_max;
	double range_y_min = out -> y_min;
	double range_y_max = out -> y_max;

	double y_min = range_y -> min; 
	double y_max = range_y -> max;
	
	if(range_x_max < x || range_x_min > x) return 0;
	if(range_y_max - range_y_min <= 0 || range_x_max - range_x_min <= 0 || y_max - y_min <= 0) return 0;
	char **pix = g -> pix;
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
void fg_write_bitmap(struct fg_graph *g, char *name){
	char **pix = g -> pix;

	FILE *fp = fopen(name, "w");
	fwrite ((char*)(g -> h), sizeof(struct bmp_header), 1, fp);
	fwrite (&pix[0][0], 1, 1, fp);
	int i, j, k;
	for(i = 0; i < g -> pixel_height; i++){
		for(j = 0; j < g -> pixel_width; j++){
			for(k = 0; k < 6; k++){
				fwrite (&pix[i][j], 1, 1, fp);			
			}
		}
		for(j = 0; j < g -> pixel_width; j++){
			for(k = 0; k < 6; k++){
				fwrite (&pix[i][j], 1, 1, fp);			
			}
			
		}	
	}
	fclose(fp);
}
/*draw set of horizontel lines in the fg_graph*/ 
void fg_draw_grid_y(struct fg_graph *g,
			 fg_range *range_y,
			 double iter,
			 char color){

	double range_y_max = range_y -> max;
	double range_y_min = range_y -> min;
	
	if(range_y_max - range_y_min <= 0) return;
	double i = 0;
	while(i < range_y_max){
		fg_create_y(g, range_y, i, color);
		i += iter;
	}
	i = 0;
	while(i > range_y_min){
		fg_create_y(g, range_y, i, color);
		i -= iter;
	}
}
/*draw set of vertical lines in the fg_graph*/ 
void fg_draw_grid_x(struct fg_graph *g,
			 fg_range *range_x,
			 double iter,
			 char color){
	
	double range_x_max = range_x -> max;
	double range_x_min = range_x -> min;
	
	if(range_x_max - range_x_min <= 0) return;
	double i = 0;
	while(i < range_x_max){
		fg_create_x(g, range_x, i, color);
		i += iter;
	}
	i = 0;
	while(i > range_x_min){
		fg_create_x(g, range_x, i, color);
		i -= iter;
	}
}
/*clear the fg_graph*/
void fg_clear_graph(struct fg_graph *g, char color){
	char **pix = g -> pix;
	int i, j;
	for(i = 0; i < g -> pixel_height; i++){
		for(j = 0; j < g -> pixel_width; j++){
			pix[i][j] = color;
		}	
	}
}
/*draw the fg_graph of an equation*/
void fg_draw_graph(struct fg_graph *g,
			 double (*f)(double),
			 fg_area *out,
			 char color){

	double range_x_min = out -> x_min;
	double range_x_max = out -> x_max;
	double range_y_min = out -> y_min;
	double range_y_max = out -> y_max;

	if(range_y_max - range_y_min <= 0 || range_x_max - range_x_min <= 0 ) return;

	double x_scale = fg_get_scale(g -> pixel_width, range_x_max, range_x_min);
	double y_scale = fg_get_scale(g -> pixel_height, range_y_max, range_y_min);
	char **pix = g -> pix;
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
					if(j > 0 && j < g ->pixel_height) 
						pix[j][i - (int)(range_x_min*x_scale)] = color;
		}else start++;
		Y_old = Y;
	}
}
/*draw the fg_graph of an equation between given x and y values*/
void fg_draw_graph_2(struct fg_graph *g,
			 double (*f)(double),
			 fg_area *out,
			 fg_area *in,
			 char color){
	

	double range_x_min = out -> x_min;
	double range_x_max = out -> x_max;
	double range_y_min = out -> y_min;
	double range_y_max = out -> y_max;
	double range_X_min =  in -> x_min;
	double range_X_max =  in -> x_max;
	double range_Y_min =  in -> y_min;
	double range_Y_max =  in -> y_max;

	if(range_y_max - range_y_min <= 0 || range_x_max - range_x_min <= 0 ) return;
	if(range_x_min > range_X_min ) range_X_min = range_x_min;
	if(range_x_max < range_X_max ) range_X_max = range_x_max;
	if(range_y_min > range_Y_min ) range_Y_min = range_y_min;
	if(range_y_max < range_Y_max ) range_Y_max = range_y_max;

	double X_scale = fg_get_scale(g -> pixel_width, range_x_max, range_x_min);
	double Y_scale = fg_get_scale(g -> pixel_height, range_y_max, range_y_min);
	char **pix = g -> pix;
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
						if(j > range_y_min*Y_scale - range_Y_min*Y_scale 
						&& j < range_y_max*Y_scale - range_Y_min*Y_scale){ 
							pix[j][i - (int)(range_x_min*X_scale)] = color;
							
						}
			}else start++;
		}
		Y_old = Y;
	}
}
void fg_draw_line(struct fg_graph *g,
			 fg_area *out,
			 fg_point *p1,
			 fg_point *p2,
			 char color){

	double range_x_min = out -> x_min;
	double range_x_max = out -> x_max;
	double range_y_min = out -> y_min;
	double range_y_max = out -> y_max;
	
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

	if(range_x_max - range_x_min <= 0 ) return;
	if(range_x_min > range_X_min ) range_X_min = range_x_min;
	if(range_x_max < range_X_max ) range_X_max = range_x_max;
	if(range_y_min > range_Y_min ) range_Y_min = range_y_min;
	if(range_y_max < range_Y_max ) range_Y_max = range_y_max;

	double X_scale = fg_get_scale(g -> pixel_width, range_x_max, range_x_min);
	double Y_scale = fg_get_scale(g -> pixel_height, range_y_max, range_y_min);
	char **pix = g -> pix;
	double y;
	double Y_old;
	int start = 0;
	int i, j;
	if(range_X_max != range_X_min){
		double m = (range_Y_max - range_Y_min)/(range_X_max - range_X_min);
		printf("%f %f m = %f\n", X_scale, range_Y_max, m);
		for(i = range_X_min*X_scale; i < range_X_max*X_scale; i++){
			
			double x = (double)i/X_scale;

			y = m*x - m*range_X_min + range_Y_min;		
			
			int Y = (int) (y*Y_scale) - range_y_min*Y_scale;
			if(m == -29) printf("%f %d\n", x, Y);
			if(i > range_x_min*X_scale && i < range_x_max*X_scale){
				if(start){
					int h, l;
					h = MAX_Y(Y, Y_old);
					l = MIN_Y(Y, Y_old);
					if(m == -15) printf("x\n");
					//if(h - l < 4 * (g ->  pixel_height) / 4)
						for(j = l; j <= h; j++)
							if(j < g -> pixel_height && i - (int)(range_x_min*X_scale) < g -> pixel_width){ 
								pix[j][i - (int)(range_x_min*X_scale)] = color;
								if(m == -15) printf("xxx\n");
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
}
void fg_draw_point(struct fg_graph *g,
			 fg_area *out,
			 fg_point *p,
			 char color){

	double range_x_min = out -> x_min;
	double range_x_max = out -> x_max;
	double range_y_min = out -> y_min;
	double range_y_max = out -> y_max;

	if(range_y_max - range_y_min <= 0 || range_x_max - range_x_min <= 0 ) return;
	double x_scale = fg_get_scale(g -> pixel_width, range_x_max, range_x_min);
	double y_scale = fg_get_scale(g -> pixel_height, range_y_max, range_y_min);
	char **pix = g -> pix;
	double x = p -> x * x_scale - range_x_min*x_scale;
	double y = p -> y * y_scale - range_y_min*y_scale;
		
	int j, k;
	for(j = (int)y - 2; j <= (int)y + 2; j++)
		for(k = (int)x - 2; k <= (int)x + 2; k++)
			if(j > 0 && j < g ->pixel_height) 
				pix[j][k] = color;
					
	
}
void fg_draw_graph_3(struct fg_graph *g,
			 fg_area *out,
			 double *x_axe,
			 double *y_axe,
			 int x_len,
			 int y_len,
			 char color){

	int i;
	for(i = 0; i < x_len - 1; i++){

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
}
/*initialice data*/
struct fg_graph *fg_init(int x, int y){
	struct fg_graph *g = (struct fg_graph *)malloc(sizeof(struct fg_graph));
	g -> pixel_width = x / 2;
	g -> pixel_height = y / 2;

	char **pix = (char **)malloc(sizeof(char *) * y/2);
	int i = 0;
	for(i = 0; i < y/2; i++) pix[i] = (char *)malloc(sizeof(char) *  x/2);

	g -> pix = pix;
	g -> h = fg_fill_header(g -> pixel_width, g -> pixel_height);

	return g;
}
