/**
 *CROP PROGRAM
 *RETURNS 0 if there is an error in the input
 */
#include <stdio.h>
#include <stdlib.h>
#include "simp.h"
#include <string.h>

int main(int argc, char** argv)
{
	int startx;
	int starty;
	int newwidth;
	int newheight;
	
	char infile[256];
	char outfile[256];
	
	int w;
	int h;
	
	unsigned char data;
	unsigned char data1;
	unsigned char data2;
	unsigned char data3;
	
	simp temp;
	FILE* binary;
	simp newSimp;
	int i;
	int j;
	
	if (argv[1] == NULL || argv[2] == NULL)
	{
		printf("INFILE OR OUTFILE NOT SPECIFIED\n");
		return 0;
	}
	strcpy(infile, argv[1]);
	strcpy(outfile, argv[2]);
	
	/* ERROR CHECK */
	if(argv[3] == NULL || argv[4] == NULL || argv[5] == NULL || argv[6] == NULL )
	{
		printf("INSUFFICIENT VALUES ENTERED\n");
		return 0;
	}
	
	
	startx = atoi(argv[3]);
		
	starty = atoi(argv[4]);

	newwidth = atoi(argv[5]);
		
	newheight = atoi(argv[6]);
			
	
		
		
	binary = fopen(infile, "rb");
	
	if( binary == 0)
	{
		printf("File not found!\n");
		return 0;
	}

	
	fread(&w, sizeof(int), 1, binary);
	fread(&h, sizeof(int), 1, binary);
	
	
	/* EXITS IF THE RANGE ENTERED IS OUT OF BOUNDS */
	if (newwidth > w || newheight > h || newwidth < 0 || newheight < 0 || startx > w || starty > h || startx < 0 || starty < 0)
	{
		printf("ONE OF THE RANGE VALUES ENTERED IS OUT OF BOUNDS, PROGRAM WILL NOW EXIT!\n");
		fclose(binary);
		return 0;
	}
	
	
	temp = initSimp(w,h);
	
	copyImage(&temp, binary);
	
	fclose(binary);
	
	/*CROPPING IS DONE HERE */
	newSimp = initSimp(newwidth, newheight);

	
	/* COPIES THE pixels that are cropped out to a new simp file */
	for(i = starty; i < starty + newheight; i++)
	{
		for(j = startx; j < startx + newwidth; j++)
		{
			newSimp.pixArray[i-starty][j-startx] = temp.pixArray[i][j] ;
		}
	}

	
	writeBinary(outfile, &newSimp);
	
	/* FREES THE TEMP IMAGE */
	freeSimp(&temp);
		
	/* FREES THE NEW IMAGE */
	freeSimp(&newSimp);
	
	return 0;
}
