#include "simp.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 *READS THE ACTION FILE AND STORES THE STRINGS IN CHAR** A
 *COUNTER COUNTS THE NUMBER OF LINES AND IS USED IN THE READMEME FUNCTION
 */
void readActionFile(char** a, FILE* readaction, int* counter1)
{
	int i;
	char* token;
	char* temp;
	temp = (char*)malloc(1000* sizeof(char));
	i = 0;
	while(1)
	{
			if(feof(readaction))
			{
				break;
			}
			fgets(temp, 1000, readaction);
			if(strstr(temp,":") == NULL)
			{
				break;
			}
			while (strlen(temp) == 1 || strlen(temp) == 0)
			{
				if(feof(readaction))
				{
					break;
				}
				fgets(temp, 1000, readaction);
				
			}
		
			if (strlen(temp) != 0)
			{
				token = strtok(temp, "\n");
				token = strtok(token, ":");
				token = strtok(NULL, ":");
				strcpy(a[i], token);
				i++;
			}
			
			if(feof(readaction))
			{
				break;
			}
	}
	free(temp);
	*counter1 = i;
}

/**
 *READS THE MEME FILE AND STORES THE STRINGS IN CHAR** m
 *COUNTER COUNTS THE NUMBER OF LINES AND IS USED IN THE READMEME FUNCTION
 */
void readMeme(char** m, char* meme, FILE* readmeme, int counter1)
{
	int i;
	char* token;
	char* temp;
	temp = (char*)malloc(1000* sizeof(char));
	
	for(i = 0; i <counter1; i++)
		{
			if(feof(readmeme))
			{
				break;
			}
			
			fgets(temp, 1000, readmeme);
			if(strlen(temp) == 0)
			{
				return;
			}
			
			while (strlen(temp) == 1 || strlen(temp) == 0)
			{
				if(feof(readmeme))
				{
					break;
				}
				fgets(temp, 1000, readmeme);
			}
			
			if(i >= 2)
			{
				if(feof(readmeme))
				{
					break;
				}
				token  = strstr(temp, meme);
				while(token == NULL)
				{
					if(feof(readmeme))
					{
						break;
					}
					fgets(temp, 1000, readmeme);
					token  = strstr(temp, meme);
				}
			}
			
			if (strlen(temp) != 0)
			{
				token = strtok(temp, "\n");
				token = strtok(token, ":");
				token = strtok(NULL, ":");
				strcpy(m[i], token);
			}
			
			
		}
		
		free(temp);
		return;
}

/**
 *READS EACH CHARACTER IN THE ROW ARRAY AND CROPS THE RESPECTIVE LETTERS FROM THE FONTIMAGE SIMP(STRUCT)
 *THE IMAGES ARE STORED IN THE ROWSIMP SIMP ARRAY
 *FONTDATA IS A CHAR ARRAY CONTAINING ALL THE DETAILS IN THE FONT FSF FILE
 */
int getLocation(char* row, char** fontdata, simp fontimage, simp* rowsimp, int counter)
{
	int i;
	int j;
	char tofind[11];
	char* temp;
	char* temp1;
	char character;
	char* token;
	
	int a,b,c,d;
	
	temp = (char*) malloc(1000* sizeof(char));
	temp1 = (char*) malloc(1000* sizeof(char));
	
	for(i = 0; i < strlen(row); i++)
	{
		strcpy(tofind, "");
		strcpy(tofind, "CHARACTER");
		character = row[i];
		tofind[9] = character;
		tofind[10] = '\0';

		
		j = 0;
		while(1)
		{
			token = strstr(fontdata[j],tofind);
			/* While the current line of font data doesnt contain CHARACTER*, the next line of fontdata is fetched, * is the letter to be found*/
			while(token == NULL && j != counter)
			{
				j++;
				token = strstr(fontdata[j],tofind);
			}
			
			
			break;

		}
		
		if(token != NULL)
		{
			strcpy(temp1,fontdata[j]);
			token = strtok(temp1,":");
			token = strtok(NULL,":");
			strcpy(temp, token);

			
			/* GETS THE COORDINATES*/
			sscanf( temp, "%d %d %d %d", &a, &b, &c, &d );
			
			/* TODO: CROP */
			rowsimp[i] = crop(fontimage, a,b,c,d);
		}
		
		if(token == NULL)
		{
			printf("COORDINATES NOT FOUND!\n");
			free(temp);
			free(temp1);
			return 1;
		}
	}
	
	free(temp);
	free(temp1);
	return 0;
}

/**
 *READS THE DATA IN THE FONT FSF FILE AND STORES IT IN THE FONT DATA CHAR ARRAY
 */
void readfontfile(char** a, char** m, char** fontdata, char** fontname, FILE* readfont, int* counter)
{
	char* token;
	int i;
	int insidecounter = 0;
	char* temp;
	temp = (char*) malloc(1000* sizeof(char));
	if (a[2] != NULL)
	{
		char* fontfilename;
		for(i = 0; i < strlen(a[2]); i++)
		{
			a[2][i] = tolower(a[2][i]);
		}
		strcpy(*fontname, a[2]);
		strcat(*fontname,".fsf");
		token  = strstr(m[1], *fontname);
		
		/* IF the font doesnt match the fonts found in the memes file*/
		if (token == NULL)
		{
			printf("FONT NOT FOUND!\n");
			free(temp);
			return;
		}
		
		/* FONT FOUND */
		strcpy(*fontname, token);
		
		readfont = fopen(*fontname, "r");
		if(readfont == 0)
		{
			return;
		}
		i = 0;
		while(!feof(readfont))
		{
			fgets(temp, 1000, readfont);
			if(strlen(temp) == 0)
			{
				break;
			}
			while(strlen(temp) == 1)
			{
				if(feof(readfont))
				{
					break;
				}
				fgets(temp, 1000, readfont);
			}
			
			
			token = strtok(temp,"\n");
			strcpy(fontdata[i], token);
			i++;
			insidecounter++;
		}
	}
	*counter = insidecounter;
	free(temp);
	fclose(readfont);
}

/**
 * OVERLAYS THE ROW SPECIFIED, IT CALLS THE OVERLAY METHOD FROM THE SIMP.C FILE
 */
void overlayrow(simp original, simp* row, int starty, int startx, int number)
{
	int i;
	int start = startx;
	for(i = 0; i < number; i++)
	{
		if (start > original.width)
		{
			return;
		}
		overlayfunction(&original, &row[i], starty, start);
		start = start + row[i].width;
		
	}
}


int main(int argc, char** argv)
{
	FILE* readmeme;
	FILE* readaction;
	FILE* readfont;
	FILE* readfontsimp;
	FILE* readimagesimp;
	
	char** fontdata;
	char* fontname;
	simp fontimage;
	simp image;
	simp** row;
	
	char** a;
	/*
	 *a[0] = OUTFILE
	 *a[1] = MEME
	 *a[2] = FONT
	 *a[3] = TOP
	 *a[4] = BOTTOM
	 */
	 
	char** m;
	/*
	 *m[0] = MEMES
	 *m[1] = FONTS
	 *m[2] = MEME FILE
	 *m[3] = TOP COORDINATES
	 *m[4] = BOTTOM COORDINATES
	 */
	 
	int i;
	int j;
	int k;
	int l;
	char* token;
	int w;
	int h;
	int counter;
	int starty = 0;
	int startx = 0;
	int counter1 = 0;
	
	if(argv[1] == NULL || argv[2] == NULL)
	{
		printf("MEME OR ACTION NOT SPECIFIED\n");
		return 0;
	}
	
	readmeme = fopen(argv[1], "r");
	readaction = fopen(argv[2], "r");
	
	/* *****ERROR CHECK***** */
	
	if( readmeme == 0 || readaction == 0)
	{
		printf("ONE OF THE FILES WAS NOT FOUND! EXITING!\n");
		return 0;
	}
	
	/* ********************* */
	
	
	/* *****MALLOC***** */

	
	a =(char**) malloc (1000*sizeof(char*));
	for(i = 0; i < 1000; i++)
	{
		a[i] = (char*) malloc(1000*sizeof(char));
	}
	
	m =(char**) malloc (1000*sizeof(char*));
	for(i = 0; i < 1000; i++)
	{
		m[i] = (char*) malloc(1000*sizeof(char));
	}
	
	fontdata = (char**) malloc (129* sizeof(char*));
	for(i = 0; i < 129; i++)
	{
		fontdata[i] = (char*)malloc(1000*sizeof(char));

	}
	
	fontname = malloc(1000*sizeof(char));
	
	/* ********************* */ 
	
	
	
	/* *******READS THE ACTION FILE******* */
	
	readActionFile(a, readaction, &counter1);
	fclose(readaction);
	
	/* IF the action file is missing any details, the program will exit! */
	for(i =0 ; i < 5; i++)
	{
		if(strlen(a[i]) == 0 || strlen(a[i]) == 1)
	{
		printf("Insufficient details in the act file! EXITING\n");
		for(i = 0; i < 1000; i++)
		{
			free(a[i]);
		}
		free(a);

		for(i = 0; i < 1000; i++)
		{
			free(m[i]);
		}
		free(m);
	
	
		for(i = 0; i < 129; i++)
		{
			free(fontdata[i]);
		}
		free(fontdata);
		
		free(fontname);
		fclose(readmeme);
		return 0;
	}
	}
	


	/* *********************************** */
	
	/* *******READS THE MEME FILE******* */
	
	/* Reads memes and fonts first */
	readMeme(m, a[1],readmeme, counter1);
	fclose(readmeme);
	/* IF the meme file is missing any details, the program will exit! */

	if(strlen(m[0]) == 0 || strlen(m[0]) == 1)
	{
		printf("Insufficient details in the meme file! EXITING\n");
		return 0;
	}
	
	
	
	/* READS THE FONT FILE */
	
	readfontfile(a, m, fontdata, &fontname, readfont, &counter);
	free(fontname);
	if(strlen(fontdata[0]) == 0 || strlen(fontdata[0]) == 1)
	{
		
		for(i = 0; i < 1000; i++)
		{
			free(a[i]);
		}
		free(a);

		for(i = 0; i < 1000; i++)
		{
			free(m[i]);
		}
		free(m);
	
	
		for(i = 0; i < 129; i++)
		{
			free(fontdata[i]);
		}
		free(fontdata);
		printf("Insufficient details in the font file! EXITING\n");
		return 0;
	}
	
	/* OPENS THE FONT SIMP */
	token = strtok(fontdata[1],":");
	token = strtok(NULL,":");
	readfontsimp = fopen(token, "rb");
	
	if(readfontsimp == 0)
	{
		printf("FONT SIMP NOT FOUND, EXITING!\n");
		for(i = 0; i < 1000; i++)
		{
			free(a[i]);
		}
		free(a);

		for(i = 0; i < 1000; i++)
		{
			free(m[i]);
		}
		free(m);
	
	
		for(i = 0; i < 129; i++)
		{
			free(fontdata[i]);
		}
		free(fontdata);
		
		return 0;
	}
	
	fread(&w,sizeof(int), 1, readfontsimp);
	fread(&h,sizeof(int), 1, readfontsimp);
	
	fontimage = initSimp(w,h);
	copyImage(&fontimage, readfontsimp);
	fclose(readfontsimp);
	
	/* MALLOC SIMP ARRAYS FOR TOP AND BOTTOM */
	row = (simp**)malloc( counter1 * sizeof(simp*));
	for(i = 0 ; i < counter1; i++)
	{
		row[i] = (simp*) malloc(1000 * sizeof(simp));
	}
	
	j = 0;
	for(i = 3; i < counter1; i++)
	{
		
		getLocation(a[i], fontdata, fontimage,row[j],counter);
		j++;
	}

	
	
	freeSimp(&fontimage);

	
	/* IF A LETTER IS NOT FOUND! */
	if(i == 1)
	{
		printf("A LETTER WAS NOT FOUND EXITING!\n");
		return 0;
	}
	
	
	
	/* OVERLAY */
	
	readimagesimp = fopen(m[2], "rb");
	
	if(readimagesimp == 0)
	{
		printf("IMAGE SIMP NOT FOUND!\n");
		return 0;
	}
	
	fread(&w, sizeof(int),1, readimagesimp);
	fread(&h, sizeof(int),1, readimagesimp);
	
	image = initSimp(w,h);
	copyImage(&image, readimagesimp);
	fclose(readimagesimp);
	

	/* WIDTH CALCULATION */
	l = 0;
	for(k = 3; k < counter1; k++)
	{
	sscanf( m[k], "%d %d", &startx, &starty);
	j = 0;
	for(i = 0; i < strlen(a[k]); i++)
	{
		j = j + row[l][i].width;
		
	}
	
	j = j/2;

	startx = startx-j;
	starty = starty-40;
	overlayrow(image, row[l], starty, startx, strlen(a[k]));
	l++;
	}
	/* *******************  */
	
	
	writeBinary(a[0],&image);
	

	/* ***************** */
	
	/* ***MEM FREEING*** */

	/* ************ */
	
	/* ********************************* */
	return 0;	
}
