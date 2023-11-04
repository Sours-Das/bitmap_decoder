#include "decoder.h"

void read_bmp_header(__bmp_file* file)
{

	file->STREAM=fopen(file->path,"r");
	fread(&(file->bmp_header).signature,2,1,file->STREAM);
	fread(&(file->bmp_header).file_size,4,1,file->STREAM);
    fread(&(file->bmp_header).reserved1,2,1,file->STREAM);
    fread(&(file->bmp_header).reserved2,2,1,file->STREAM);
    fread(&(file->bmp_header).offset_pixel_array,4,1,file->STREAM);
    fclose(file->STREAM);
    
}


void read_dib_header(__bmp_file* file)
{

    file->STREAM=fopen(file->path,"r");
    fseek(file->STREAM,14,SEEK_SET);
    fread(&file->dib_header.dib_header_size,4,1,file->STREAM);
    fread(&file->dib_header.bitmap_width,4,1,file->STREAM);
    fread(&file->dib_header.bitmap_height,4,1,file->STREAM);
    fread(&file->dib_header.color_planes,2,1,file->STREAM);
    fread(&file->dib_header.color_depth,2,1,file->STREAM);
    fread(&file->dib_header.compression_method,4,1,file->STREAM);
    fread(&file->dib_header.image_size,4,1,file->STREAM);
    fread(&file->dib_header.horizontal_resolution,4,1,file->STREAM);
    fread(&file->dib_header.verical_resolution,4,1,file->STREAM);
    fread(&file->dib_header.colors_in_palette,4,1,file->STREAM);
    fread(&file->dib_header.important_colors,4,1,file->STREAM);
    fclose(file->STREAM);

}