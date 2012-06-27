#include <stdio.h>
#include <stdlib.h>

#define MAX_Y(a, b) ((a) > (b) ? (a) : (b))
#define MIN_Y(a, b) ((a) < (b) ? (a) : (b))


double get_scale(int a, double max, double min){
	return (double)a / (max - min);
}

struct bmp_header * fill_header(int pixel_width, int pixel_height){

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
extern int create_y(graph *g, double range_y_min, double range_y_max, double y, char color){ 
	if(range_y_max < y || range_y_min > y) return 0;
	if(range_y_max - range_y_min <= 0) return 0;
	char **pix = g -> pix;
	double scale = get_scale(g -> pixel_height, range_y_max, range_y_min);
	int Y = (int)(y*scale - range_y_min*scale);
	int i;
	for(i = 0; i < g -> pixel_width; i++){
		pix[Y][i]	= color;
	}
	return 1;
}
int create_x(graph *g, double range_x_min, double range_x_max, double x, char color){ 
	if(range_x_max < x || range_x_min > x) return 0;
	if(range_x_max - range_x_min <= 0) return 0;
	char **pix = g -> pix;
	double scale = get_scale(g -> pixel_width, range_x_max, range_x_min);
	int X = (int)(x*scale - range_x_min*scale);
	int i;
	for(i = 0; i < g -> pixel_height; i++){
		pix[i][X]	= color;
	}
	return 1;
}
void write_bitmap(graph *g, char *name){
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
void draw_grid_y(graph *g, double range_y_min, double range_y_max, double iter, char color){
	if(range_y_max - range_y_min <= 0) return;
	char **pix = g -> pix;
	double i = 0;
	while(i < range_y_max){
		create_y(g, range_y_min, range_y_max, i, color);
		i += iter;
	}
	i = 0;
	while(i > range_y_min){
		create_y(g, range_y_min, range_y_max, i, color);
		i -= iter;
	}
}
void draw_grid_x(graph *g, double range_x_min, double range_x_max, double iter, char color){
	if(range_x_max - range_x_min <= 0) return;
	char **pix = g -> pix;
	double i = 0;
	while(i < range_x_max){
		create_x(g, range_x_min, range_x_max, i, color);
		i += iter;
	}
	i = 0;
	while(i > range_x_min){
		create_x(g, range_x_min, range_x_max, i, color);
		i -= iter;
	}
}
double set_func(double (*f)(double), double x ) {
    return (*f)(x);
}
void clear_graph(graph *g){
	char **pix = g -> pix;
	int i, j;
	for(i = 0; i < g -> pixel_height; i++){
		for(j = 0; j < g -> pixel_width; j++){
			pix[i][j] = (char)0xFF;
		}	
	}
}
void draw_graph(graph *g,
			 double (*f)(double),
			 double range_x_min,
			 double range_x_max,
			 double range_y_min,
			 double range_y_max){
	
	if(range_y_max - range_y_min <= 0 || range_x_max - range_x_min <= 0 ) return;
	double x_scale = get_scale(g -> pixel_width, range_x_max, range_x_min);
	double y_scale = get_scale(g -> pixel_height, range_y_max, range_y_min);
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
			h = MAX(Y, Y_old);
			l = MIN(Y, Y_old);
			if(h - l < g -> pixel_height / 2)
				for(j = l; j <= h; j++)
					if(j > 0 && j < g ->pixel_height) 
						pix[j][i - (int)(range_x_min*x_scale)] = (char)0x00;
		}else start++;
		Y_old = Y;
	}
}
void draw_graph_2(graph *g,
			 double (*f)(double),
			 double range_x_min,
			 double range_x_max,
			 double range_y_min,
			 double range_y_max,
			 double range_X_min,
			 double range_X_max,
			 double range_Y_min,
			 double range_Y_max){
	
	if(range_y_max - range_y_min <= 0 || range_x_max - range_x_min <= 0 ) return;
	double X_scale = get_scale(g -> pixel_width, range_X_max, range_X_min);
	double Y_scale = get_scale(g -> pixel_height, range_Y_max, range_Y_min);
	char **pix = g -> pix;
	double y;
	double Y_old;
	int start = 0;
	int i, j;
	for(i = range_X_min*X_scale; i < range_X_max*X_scale; i++){
		
		double x = (double)i/X_scale;

		y = (*f)(x);		

		int Y = (int) (y*Y_scale) - range_Y_min*Y_scale;
		if(i > range_x_min*X_scale && i < range_x_max*X_scale){
			if(start){
				int h, l;
				h = MAX(Y, Y_old);
				l = MIN(Y, Y_old);
				if(h - l < g -> pixel_height / 2)
					for(j = l; j <= h; j++)
						if(j > range_y_min*Y_scale - range_Y_min*Y_scale 
						&& j < range_y_max*Y_scale - range_Y_min*Y_scale){ 
							pix[j][i - (int)(range_X_min*X_scale)] = (char)0x00;
						}
			}else start++;
		}
		Y_old = Y;
	}
}
void draw_graph_in_x(graph *g,
			 double (*f)(double),
			 double range_x_min,
			 double range_x_max,
			 double range_y_min,
			 double range_y_max,
			 double range_X_min,
			 double range_X_max,
			 double range_Y_min,
			 double range_Y_max){
	
	if(range_y_max - range_y_min <= 0 || range_x_max - range_x_min <= 0 ) return;
	double X_scale = get_scale(g -> pixel_width, range_X_max, range_X_min);
	double Y_scale = get_scale(g -> pixel_height, range_Y_max, range_Y_min);
	char **pix = g -> pix;
	double y;
	double Y_old;
	int start = 0;
	int i, j;
	for(i = range_X_min*X_scale; i < range_X_max*X_scale; i++){
		double x = (double)i/X_scale;

		y = (*f)(x);		

		int Y = (int) (y*Y_scale) - range_Y_min*Y_scale;
		if(i < range_x_min*X_scale || i > range_x_max*X_scale){
			if(start){
				int h, l;
				h = MAX_Y(Y, Y_old);
				l = MIN_Y(Y, Y_old);
				if(h - l < g -> pixel_height / 2)
					for(j = l; j <= h; j++)
						if(j > range_y_min*Y_scale - range_Y_min*Y_scale 
						&& j < range_y_max*Y_scale - range_Y_min*Y_scale){ 
							pix[j][i - (int)(range_X_min*X_scale)] = (char)0x00;
						}
			}else start++;
		}
		Y_old = Y;
	}
}
graph *init(int x, int y){
	graph *g = (graph *)malloc(sizeof(graph));
	g -> pixel_width = x / 2;
	g -> pixel_height = y / 2;

	char **pix = (char **)malloc(sizeof(char *) * y/2);
	int i = 0;
	for(i = 0; i < y/2; i++) pix[i] = (char *)malloc(sizeof(char) *  x/2);

	g -> pix = pix;
	g -> h = fill_header(g -> pixel_width, g -> pixel_height);

	return g;
}
