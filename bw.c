#include <stdio.h>
#include <stdlib.h>
#include "simp.h"
#include <string.h>

int main(int argc, char** argv)
{
	char infile[256];
	char outfile[256];
	FILE* binary;
	int w;
	int h;
	
	unsigned char data;
	unsigned char data1;
	unsigned char data2;
	unsigned char data3;
	
	simp temp;
	
	simp newImage;
	
	pixel pix;
	
	int row;
	int col;
	
	if (argv[1] == NULL || argv[2] == NULL)
	{
		printf("INFILE OR OUTFILE NOT SPECIFIED\n");
		return 0;
	}
	strcpy(infile, argv[1]);
	strcpy(outfile, argv[2]);

	
	binary = fopen(infile, "rb");
	
	if( binary == 0)
	{
		printf("File not found!\n");
		return 0;
	}
	

	
	fread(&w, sizeof(int), 1, binary);
	fread(&h, sizeof(int), 1, binary);
	
/* ********* COPIES THE IMAGE TO A NEW SIMP FILE AND CHANGES THE COLOR TO B&W **** */
	temp = initSimp(w,h);
	
	copyImage(&temp, binary);
	
	fclose(binary);
	
	newImage = initSimp(w,h);

	for(row = 0; row < h; row++)
	{
			for(col = 0; col < w; col++)
			{
				unsigned char avg = (temp.pixArray[row][col].r + temp.pixArray[row][col].g + temp.pixArray[row][col].b)/3;
				pixel pix  = initPixel(avg,avg,avg,temp.pixArray[row][col].a);
				newImage.pixArray[row][col] = pix;
			}
	}
	
	
	
	
	writeBinary(outfile, &newImage);
	
	freeSimp(&temp);
	freeSimp(&newImage);
	return 0;
}