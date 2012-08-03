/*
*Author :Tharindra Galahena
*Project:free_graph - graph drawing library for c/c++ (linux)
*Date   :28/06/2012
*/

/*store bitmap data*/
typedef struct fg_graph{
	struct bmp_header *h;
	int pixel_width;
	int pixel_height;
	char **pix;
} fg_graph;

typedef struct fg_area{
	double x_min;
	double x_max;
	double y_min; 
	double y_max; 
} fg_area;

typedef struct fg_point{
	double x;
	double y; 
} fg_point;

typedef struct fg_range{
	double min;
	double max;
} fg_range;

/*bitmap header information*/
#pragma pack(push, 1)
struct bmp_header {
    short BM;
    long size_of_file;
    long reserve;
    long offset_of_pixle_data;
    long size_of_header;
    long width;
    long hight;
    short num_of_colour_plane;
    short num_of_bit_per_pix;
    long compression;
    long size_of_pix_data;
    long h_resolution;
    long v_resolution;
    long num_of_colour_in_palette;
    long important_colours;
};
#pragma pack(pop)
