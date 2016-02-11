#include <stdio.h>
#include <stdlib.h>
#include "simp.h"

pixel initPixel(unsigned char x, unsigned char y,unsigned char z ,unsigned char w)
{
	
	pixel newPixel;
	newPixel.r = x;
	newPixel.g = y;
	newPixel.b = z;
	newPixel.a = w;
	
	return newPixel;
}

simp initSimp(int w, int h)
{
	int i;
	simp image;
	image.width = w;
	image.height = h;
	image.pixArray = malloc (h * sizeof(pixel*));
	for (i = 0; i < h; i++)
	{
		image.pixArray[i] = (pixel*) malloc( w * sizeof(pixel) );
	}

	return image;
}

simp crop(simp a, int startx, int starty, int width, int height)
{
	int i;
	int j;
	simp newSimp = initSimp(width, height);
	for(i = starty; i < starty + height; i++)
	{
		for(j = startx; j < startx + width; j++)
		{
			newSimp.pixArray[i-starty][j-startx] = a.pixArray[i][j] ;
		}
	}
	
	return newSimp;
}

void overlayfunction(simp* first, simp* second, int starty, int startx)
{
	int i;
	int j;
	int counter;
	int k;
	int l;
	
	int innerstartx;
	int innerstarty;
	int ydifference;
	
	innerstartx = startx;
	innerstarty = starty;
	
	if(innerstarty > first->height)
	{
		return;
	}
	
	if(innerstartx > first->width)
	{
		return;
	}
	
	if(innerstarty < 0 && innerstartx < 0)
	{
		int difference;
		difference = 0 - innerstartx;
		ydifference = 0 - innerstarty;
		if(difference > second->width || ydifference > second->height)
		{
			return;
		}
		
		k = ydifference;
		for(i = 0; i < second->height - ydifference; i++)
		{
			l = difference;
			for(j = 0; j < second->width - difference ; j++)
			{
				unsigned char r1 = first->pixArray[i][j].r;
				unsigned char g1 = first->pixArray[i][j].g;
				unsigned char b1 = first->pixArray[i][j].b;
				unsigned char a1 = first->pixArray[i][j].a;
			
				unsigned char r2 = second->pixArray[k][l].r;
				unsigned char g2 = second->pixArray[k][l].g;
				unsigned char b2 = second->pixArray[k][l].b;
				unsigned char a2 = second->pixArray[k][l].a;

				if (a2 == 255)
				{
					first->pixArray[i][j].r = r2;
					first->pixArray[i][j].g = g2;
					first->pixArray[i][j].b = b2;
				}
				
				if (a2 < 255 && a2 > -1)
				{
	
					unsigned char newr = ( ( (a2) * (r2) ) /255.0 ) +  ((( a1 * r1) * (255 - a2))/65025.0);
					unsigned char newg = ( ( (a2) * (g2) ) /255.0 ) +  ((( a1 * g1) * (255 - a2))/65025.0);
					unsigned char newb = ( ( (a2) * (b2) ) /255.0 ) +  ((( a1 * b1) * (255 - a2))/65025.0);
					unsigned char newa = ( ( (a2) /255.0 )  + (((255 - a2) * a1)/65025.0 ) ) * 255;
					pixel newpixel = initPixel(newr,newg,newb,newa);
					first->pixArray[i][j] = newpixel;
				}
				l++;
			}
			k++;
		}
		return;
	}
	
	if(innerstartx < 0)
	{
		int difference;
		difference = 0 - innerstartx;
		if(difference > second->width)
		{
			return;
		}
		
		for(i = innerstarty; i < innerstarty + second->height; i++)
		{
			k = difference;
			for(j = 0; j < second->width - difference; j++)
			{
				unsigned char r1 = first->pixArray[i][j].r;
				unsigned char g1 = first->pixArray[i][j].g;
				unsigned char b1 = first->pixArray[i][j].b;
				unsigned char a1 = first->pixArray[i][j].a;
			
				unsigned char r2 = second->pixArray[i-innerstarty][k].r;
				unsigned char g2 = second->pixArray[i-innerstarty][k].g;
				unsigned char b2 = second->pixArray[i-innerstarty][k].b;
				unsigned char a2 = second->pixArray[i-innerstarty][k].a;

				if (a2 == 255)
				{
					first->pixArray[i][j].r = r2;
					first->pixArray[i][j].g = g2;
					first->pixArray[i][j].b = b2;
				}
				
				if (a2 < 255 && a2 > -1)
				{
	
					unsigned char newr = ( ( (a2) * (r2) ) /255.0 ) +  ((( a1 * r1) * (255 - a2))/65025.0);
					unsigned char newg = ( ( (a2) * (g2) ) /255.0 ) +  ((( a1 * g1) * (255 - a2))/65025.0);
					unsigned char newb = ( ( (a2) * (b2) ) /255.0 ) +  ((( a1 * b1) * (255 - a2))/65025.0);
					unsigned char newa = ( ( (a2) /255.0 )  + (((255 - a2) * a1)/65025.0 ) ) * 255;
					pixel newpixel = initPixel(newr,newg,newb,newa);
					first->pixArray[i][j] = newpixel;
				}
				k++;
			}
		}
		return;
	}
	
	if(innerstarty < 0)
	{
		int difference;
		difference = 0 - innerstarty;
		if(difference > second->height)
		{
			return;
		}
		
		k = difference;
		for(i = 0; i < second->height - difference; i++)
		{
			for(j = innerstartx; j < innerstartx + second->width ; j++)
			{
				unsigned char r1 = first->pixArray[i][j].r;
				unsigned char g1 = first->pixArray[i][j].g;
				unsigned char b1 = first->pixArray[i][j].b;
				unsigned char a1 = first->pixArray[i][j].a;
			
				unsigned char r2 = second->pixArray[k][j-innerstartx].r;
				unsigned char g2 = second->pixArray[k][j-innerstartx].g;
				unsigned char b2 = second->pixArray[k][j-innerstartx].b;
				unsigned char a2 = second->pixArray[k][j-innerstartx].a;

				if (a2 == 255)
				{
					first->pixArray[i][j].r = r2;
					first->pixArray[i][j].g = g2;
					first->pixArray[i][j].b = b2;
				}
				
				if (a2 < 255 && a2 > -1)
				{
	
					unsigned char newr = ( ( (a2) * (r2) ) /255.0 ) +  ((( a1 * r1) * (255 - a2))/65025.0);
					unsigned char newg = ( ( (a2) * (g2) ) /255.0 ) +  ((( a1 * g1) * (255 - a2))/65025.0);
					unsigned char newb = ( ( (a2) * (b2) ) /255.0 ) +  ((( a1 * b1) * (255 - a2))/65025.0);
					unsigned char newa = ( ( (a2) /255.0 )  + (((255 - a2) * a1)/65025.0 ) ) * 255;
					pixel newpixel = initPixel(newr,newg,newb,newa);
					first->pixArray[i][j] = newpixel;
				}
			}
			k++;
		}
		return;
	}
	
	
	for(i = innerstarty; i < starty + second->height && i < first->height; i++)
	{
		for(j = innerstartx; j < innerstartx + second->width && j < first->width; j++)
		{
			unsigned char r1;
			unsigned char g1;
			unsigned char b1;
			unsigned char a1;
			
			unsigned char r2;
			unsigned char g2;
			unsigned char b2;
			unsigned char a2;
		
			if(j >= first->width)
			{
				return;
			}
			
			r1 = first->pixArray[i][j].r;
			g1 = first->pixArray[i][j].g;
			b1 = first->pixArray[i][j].b;
			a1 = first->pixArray[i][j].a;
			
			r2 = second->pixArray[i-innerstarty][j-innerstartx].r;
			g2 = second->pixArray[i-innerstarty][j-innerstartx].g;
			b2 = second->pixArray[i-innerstarty][j-innerstartx].b;
			a2 = second->pixArray[i-innerstarty][j-innerstartx].a;

			if (second->pixArray[i-innerstarty][j-innerstartx].a == 255)
			{
				first->pixArray[i][j].r = r2;
				first->pixArray[i][j].g = g2;
				first->pixArray[i][j].b = b2;
			}
			
			if (second->pixArray[i-innerstarty][j-innerstartx].a < 255 && second->pixArray[i-innerstarty][j-innerstartx].a > -1)
			{

				unsigned char newr = ( ( (a2) * (r2) ) /255.0 ) +  ((( a1 * r1) * (255 - a2))/65025.0);
				unsigned char newg = ( ( (a2) * (g2) ) /255.0 ) +  ((( a1 * g1) * (255 - a2))/65025.0);
				unsigned char newb = ( ( (a2) * (b2) ) /255.0 ) +  ((( a1 * b1) * (255 - a2))/65025.0);
				unsigned char newa = ( ( (a2) /255.0 )  + (((255 - a2) * a1)/65025.0 ) ) * 255;
				pixel newpixel = initPixel(newr,newg,newb,newa);
				first->pixArray[i][j] = newpixel;
			}
		
		}
	}
}

simp* copyImage(simp *first, FILE *binary)
{
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
	int row;
	int col;
	pixel pix;

	for(row = 0; row < first->height; row++)
	{
		if(feof(binary))
		{
			break;
		}
			for(col = 0; col < first->width; col++)
			{
				if(feof(binary))
				{
					break;
				}
				fread(&a, 1, 1, binary);
				fread(&b, 1, 1, binary);
				fread(&c, 1, 1, binary);
				fread(&d, 1, 1, binary);
				pix = initPixel(a,b,c,d);
				first->pixArray[row][col] = pix;
			}
		}

	return first;
}

void writeBinary(char* outfile, simp *first)
{
	int i;
	int j;
	
	
	FILE* copy = fopen(outfile, "wb");
	
	fwrite(&first->width, sizeof(int), 1, copy);
	fwrite(&first->height, sizeof(int), 1, copy);
	
	
	for(i = 0; i < first->height; i++)
	{
		for(j = 0; j < first->width; j++)
		{
			fwrite(&first->pixArray[i][j].r, 1, 1, copy);
			fwrite(&first->pixArray[i][j].g, 1, 1, copy);
			fwrite(&first->pixArray[i][j].b, 1, 1, copy);
			fwrite(&first->pixArray[i][j].a, 1, 1, copy);
		}
	}
	
	fclose(copy);
}

void freeSimp(simp *first)
{
	int i;
	for(i = 0; i < first->height; i++)
	{
		free(first->pixArray[i]);
	}
	free(first->pixArray);
}
