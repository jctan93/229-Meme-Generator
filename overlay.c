#include "simp.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
	
	int startx;
	int starty;
	FILE* binary;
	FILE* binary1;
	int i;
	int j;
	char outfile[256];
	int w;
	int h;
	simp first;
	simp second;
	
	/* **************ERROR CHECKS************** */
	if(argv[3] == NULL)
	{
		printf("NO OUTFILE ENTERED!\n");
		return 0;
	}
	else
	{
	strcpy(outfile, argv[3]);
	}
	
	if(argv[4] == NULL || argv[5] == NULL)
	{
		printf("START POSITION NOT SPECIFIED!\n");
		return 0;
	}
	
	/* ****************************************** */
	
	
	/*  **** CHECKS IF THE INPUT FILES EXIST **** */

	binary = fopen(argv[1], "rb");
	if(binary == 0)
	{
		printf("File 1 not found!\n");
		return 0;
	}
	
	binary1 = fopen(argv[2], "rb");
	if(binary1 == 0)
	{
		printf("File 2 not found!\n");
		return 0;
	}
	/*  *************************************** */
	
	

	
	startx = atoi(argv[4]);
	starty = atoi(argv[5]);

	
	fread(&w, sizeof(int), 1, binary);
	fread(&h, sizeof(int), 1, binary);
	
	/* **************ERROR CHECKS************** */
	if(startx < 0 || starty < 0  || startx > w || starty > h)
	{
		printf("SPECIFIED POSITION IS OUT OF BOUNDS! \n");
		fclose(binary1);
		fclose(binary);
		return 0;

	}
	
	/* ***************************************** */
	
	
	
	
	/* ***** COPIES THE FIRST IMAGE **** */
	first = initSimp(w,h);
	copyImage(&first,binary);
	fclose(binary);
	/* ******************************** */
	
	
	
	
	/* ***** COPIES THE SECOND IMAGE **** */
	
	fread(&w, sizeof(int), 1, binary1);
	fread(&h, sizeof(int), 1, binary1);
	second = initSimp(w,h);
	
	copyImage(&second,binary1);
	fclose(binary1);
	/* ******************************** */
	
	/* ***********OVERLAYING OCCURS HERE *************/

	for(i = starty; i < starty + second.height; i++)
	{
		for(j = startx; j < startx + second.width; j++)
		{
			unsigned char r1 = first.pixArray[i][j].r;
			unsigned char g1 = first.pixArray[i][j].g;
			unsigned char b1 = first.pixArray[i][j].b;
			unsigned char a1 = first.pixArray[i][j].a;
			
			unsigned char r2 = second.pixArray[i-starty][j-startx].r;
			unsigned char g2 = second.pixArray[i-starty][j-startx].g;
			unsigned char b2 = second.pixArray[i-starty][j-startx].b;
			unsigned char a2 = second.pixArray[i-starty][j-startx].a;

			if (second.pixArray[i-starty][j-startx].a == 255)
			{
				first.pixArray[i][j].r = r2;
				first.pixArray[i][j].g = g2;
				first.pixArray[i][j].b = b2;
			}
			
			if (second.pixArray[i-starty][j-startx].a < 255 && second.pixArray[i-starty][j-startx].a > -1)
			{

				unsigned char newr = ( ( (a2) * (r2) ) /255.0 ) +  ((( a1 * r1) * (255 - a2))/65025.0);
				unsigned char newg = ( ( (a2) * (g2) ) /255.0 ) +  ((( a1 * g1) * (255 - a2))/65025.0);
				unsigned char newb = ( ( (a2) * (b2) ) /255.0 ) +  ((( a1 * b1) * (255 - a2))/65025.0);
				unsigned char newa = ( ( (a2) /255.0 )  + (((255 - a2) * a1)/65025.0 ) ) * 255;
				pixel newpixel = initPixel(newr,newg,newb,newa);
				first.pixArray[i][j] = newpixel;
			}
		
		}
	}
	
	
	/* WRITES THE NEW IMAGE TO A BINARY FILE */
	
	writeBinary(outfile, &first);
	freeSimp(&first);
	freeSimp(&second);
	
	return;
}