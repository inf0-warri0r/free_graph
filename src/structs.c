typedef struct graph{
	struct bmp_header *h;
	int pixel_width;
	int pixel_height;
	char **pix;
} graph;

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
