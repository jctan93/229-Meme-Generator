#include "simp.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
	char infile[256];
	char outfile[256];
	int length ;
	FILE* binary ;
	int w;
	int h;
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;
	pixel pix;
	int row;
	int col;
	simp temp;
	int i;
	int j;
	FILE* copy;
	
	if (argv[1] == NULL || argv[2] == NULL)
	{
		printf("INFILE OR OUTFILE NOT SPECIFIED\n");
		return 0;
	}
	else
	{
		strcpy(infile, argv[1]);
		strcpy(outfile, argv[2]);
	}
	
	/* ******* ERROR CHECKS ******* */
	if(argv[3] == NULL)
	{
		printf("NO COLORSHIFT PARAMETER\n");
		return 0;
	}
	
	length = strlen(argv[3]);
	
	if(length < 2 || length > 3)
	{
		printf("INVALID COLORSHIFT PAREMETER ENTERED! %s  %d\n",argv[3], length);
		return 0;
	}
	
	if(strcmp(argv[3], "rg") != 0 && strcmp(argv[3], "RG") != 0 && strcmp(argv[3], "gr") != 0 && strcmp(argv[3], "GR") != 0 &&
		strcmp(argv[3],"rb") != 0 && strcmp(argv[3],"RB") != 0 && strcmp(argv[3],"BR") != 0 && strcmp(argv[3],"br") != 0 &&
		strcmp(argv[3],"gb") != 0 && strcmp(argv[3],"GB") != 0 && strcmp(argv[3],"BG") != 0 && strcmp(argv[3],"bg") != 0 &&
	    strcmp(argv[3], "rgb") != 0 && strcmp(argv[3], "RGB") != 0 && strcmp(argv[3], "gbr") != 0 && strcmp(argv[3], "GBR") != 0 && strcmp(argv[3], "brg") != 0 && strcmp(argv[3], "BRG") != 0 &&
		strcmp(argv[3], "RBG") != 0 && strcmp(argv[3], "rbg") != 0 && strcmp(argv[3], "BGR") != 0 && strcmp(argv[3], "bgr") != 0 && strcmp(argv[3], "GRB") != 0 && strcmp(argv[3], "grb") != 0
	   )
	{
		printf("INVALID COLORSHIFT PAREMETER ENTERED! %s  \n",argv[3]);
		return 0;
	}
	
	

	/* **************************** */
	
	binary = fopen(infile, "rb");
	
	if( binary == 0)
	{
		printf("File not found!\n");
		return 0;
	}
	
	
	
	fread(&w, sizeof(int), 1, binary);
	fread(&h, sizeof(int), 1, binary);
	
/* ********* COPIES THE IMAGE TO A NEW SIMP FILE AND CHANGES THE COLOR  **** */
	temp = initSimp(w,h);
		
	for(row = 0; row < h; row++)
	{
		if(feof(binary))
		{
			break;
		}
			for(col = 0; col < w; col++)
			{
				if(feof(binary))
				{
					break;
				}
				fread(&red, 1, 1, binary);
				fread(&green, 1, 1, binary);
				fread(&blue, 1, 1, binary);
				fread(&alpha, 1, 1, binary);
				
				
				if(length == 2)
				{
					if(strcmp(argv[3], "rg") == 0 || strcmp(argv[3], "RG") == 0 || strcmp(argv[3], "gr") == 0 || strcmp(argv[3], "GR") == 0)
					{
		
						pix  = initPixel(green,red,blue, alpha);
					}
					
					if(strcmp(argv[3],"rb") == 0 || strcmp(argv[3],"RB") == 0 || strcmp(argv[3],"BR") == 0 || strcmp(argv[3],"br") == 0)
					{
						
						pix = initPixel(blue,green,red,alpha);
					}
					
					if(strcmp(argv[3],"gb") == 0 || strcmp(argv[3],"GB") == 0 || strcmp(argv[3],"BG") == 0 || strcmp(argv[3],"bg") == 0)
					{	
						
						pix = initPixel(red,blue,green,alpha);
					}
				}	
			
				
				if (length == 3)
				{
					if(strcmp(argv[3], "rgb") == 0 || strcmp(argv[3], "RGB") == 0 || strcmp(argv[3], "gbr") == 0 || strcmp(argv[3], "GBR") == 0 || strcmp(argv[3], "brg") == 0 || strcmp(argv[3], "BRG") == 0)
					{
						
						pix = initPixel(blue,red,green,alpha);
					}
					
					if(strcmp(argv[3], "RBG") == 0 || strcmp(argv[3], "rbg") == 0 || strcmp(argv[3], "BGR") == 0 || strcmp(argv[3], "bgr") == 0 || strcmp(argv[3], "GRB") == 0 || strcmp(argv[3], "grb") == 0)
					{
						
						pix = initPixel(green,blue,red,alpha);
					}
					
				}
				
				
				temp.pixArray[row][col] = pix;
			}
		}
	
	fclose(binary);
	
/* *************** WRITES TO TEH OUTFILE ******************* */
	copy = fopen(outfile, "wb");
	
	fwrite(&temp.width, sizeof(int), 1, copy);
	fwrite(&temp.height, sizeof(int), 1, copy);
	
	
	for(i = 0; i < temp.height; i++)
	{
		for(j = 0; j < temp.width; j++)
		{
			fwrite(&temp.pixArray[i][j].r , 1, 1, copy);
			fwrite(&temp.pixArray[i][j].g , 1 ,1, copy);
			fwrite(&temp.pixArray[i][j].b , 1 ,1, copy);
			fwrite(&temp.pixArray[i][j].a , 1 ,1, copy);
		}
	}
	
	fclose(copy);
	
	freeSimp(&temp);
	
	return 0;
}