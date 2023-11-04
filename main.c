#define SDL_MAIN_HANDLED
#include<SDL2/SDL.h>
#include<stdio.h>
#include "decoder.h"


int main(int argc, char** argv)
{

SDL_SetMainReady();
SDL_Init(SDL_INIT_EVERYTHING);

 __bmp_file bmp_file;
 bmp_file.path=argv[1];
 read_bmp_header(&bmp_file);

 printf("File signature %c%c\n",bmp_file.bmp_header.signature,bmp_file.bmp_header.signature>>8);
 printf("File size %d bytes (%d KB)\n",bmp_file.bmp_header.file_size,(bmp_file.bmp_header.file_size/1000));
 printf("Reserved for use #1 %d\n",bmp_file.bmp_header.reserved1);
 printf("Reserved for use #2 %d\n",bmp_file.bmp_header.reserved2);
 printf("Offset to pixel array %d\n",bmp_file.bmp_header.offset_pixel_array);
 getchar();

 read_dib_header(&bmp_file);
 printf("Size of header %d\n",bmp_file.dib_header.dib_header_size);
 printf("Bitmap width in pixels %d\n",bmp_file.dib_header.bitmap_width);
 printf("Bitmap height in pixels %d\n",bmp_file.dib_header.bitmap_height);
 printf("Number of color planes %d\n",bmp_file.dib_header.color_planes);
 printf("Number of bits per pixel (color depth) %d\n",bmp_file.dib_header.color_depth);
 printf("Compression method being used %d\n",bmp_file.dib_header.compression_method);
 printf("Image size %d\n",bmp_file.dib_header.image_size);
 printf("Horizontal resolution of the image %f\n",bmp_file.dib_header.horizontal_resolution);
 printf("Vertical resolution of the image %f\n",bmp_file.dib_header.verical_resolution);
 printf("Number of colors in the color palette %d\n",bmp_file.dib_header.colors_in_palette);
 printf("Number of important colors used %d\n",bmp_file.dib_header.important_colors);
if(bmp_file.dib_header.bitmap_width%4)
   bmp_file.dib_header.bitmap_width=((8*bmp_file.dib_header.bitmap_width+31)/32)*4;
unsigned char image[bmp_file.dib_header.bitmap_width*bmp_file.dib_header.bitmap_height];

FILE *STREAM;
STREAM=fopen(bmp_file.path,"r");
fseek(STREAM,bmp_file.bmp_header.offset_pixel_array,SEEK_SET);
fread(image,(bmp_file.dib_header.bitmap_width)*(bmp_file.dib_header.bitmap_height),1,STREAM);
fclose(STREAM);



unsigned char revimage[bmp_file.dib_header.bitmap_width*bmp_file.dib_header.bitmap_height];
int x=bmp_file.dib_header.bitmap_width,y=bmp_file.dib_header.bitmap_height-1,c=0,column=0;
while(c<bmp_file.dib_header.bitmap_width*bmp_file.dib_header.bitmap_height){
   if(column==bmp_file.dib_header.bitmap_width){
      column=0;
      y--;
   }

revimage[(y*x)+(column++)]=image[c++];
}

 SDL_Window *window;

    window = SDL_CreateWindow("DARKview", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,bmp_file.dib_header.bitmap_width,bmp_file.dib_header.bitmap_height,SDL_WINDOW_RESIZABLE);
SDL_Surface * Screen= SDL_GetWindowSurface(window);

SDL_Surface * Image = SDL_CreateRGBSurfaceFrom(revimage, bmp_file.dib_header.bitmap_width, bmp_file.dib_header.bitmap_height, bmp_file.dib_header.color_depth, 1*bmp_file.dib_header.bitmap_width,0,0,0,0);


//SDL_Delay(5000);


STREAM=fopen(bmp_file.path,"r");
fseek(STREAM,54,SEEK_SET);
SDL_Color * color=Image->format->palette->colors;
for(int i=0;i<256;i++){
   fread(&color[i].b,1,1,STREAM);
   fread(&color[i].g,1,1,STREAM);
   fread(&color[i].r,1,1,STREAM);
   fread(&color[i].a,1,1,STREAM);
}
fclose(STREAM);

SDL_BlitSurface(Image, NULL, Screen, NULL);
SDL_UpdateWindowSurface(window);
 getchar();
 SDL_Quit();
 return 0;

}