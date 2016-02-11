#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct pixel_struct
 {
	char letter;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
 } pixel;

 
typedef struct simp_struct
{
	int width;
	int height;
 	pixel** pixArray ;
} simp;
 
pixel initPixel(unsigned char x, unsigned char y,unsigned char z ,unsigned char w);

simp initSimp(int w, int h);

simp crop(simp a, int startx, int starty, int width, int height);

void overlay(simp* first, simp* second, int starty, int startx);

simp* copyImage(simp *first, FILE *binary);

void writeBinary(char* outfile, simp *first);

void freeSimp(simp *first);