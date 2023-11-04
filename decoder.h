#include<stdlib.h>
#include<stdio.h>


typedef struct 
{

	unsigned short signature;
	unsigned int file_size;
	unsigned short reserved1;
	unsigned short reserved2;
	unsigned int offset_pixel_array;

}__bmp_header;


typedef struct
{

unsigned int dib_header_size;
unsigned int bitmap_width;
unsigned int bitmap_height;
unsigned short color_planes;
unsigned short color_depth;
unsigned int compression_method;
unsigned int image_size;
float horizontal_resolution;
float verical_resolution;
unsigned int colors_in_palette;
unsigned int important_colors;

}__dib_header;


typedef struct
{

char *path;
FILE *STREAM;
__bmp_header bmp_header;
__dib_header dib_header;

}__bmp_file;

void read_bmp_header(__bmp_file* file);
void read_dib_header(__bmp_file* file );