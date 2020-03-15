#include <stdio.h>
#include "gfx.h"
#include "../src/bmpreader.h"

int main()
{
	char c;
	char* image=readbmp("./Berinjela.bmp");
	if(!image)return -1;
	int ysize,xsize,x,y;
	double alpha;
	hwfromsize(sizebmp("./Berinjela.bmp"),xsize,ysize);
	// Open a new window for drawing.
	gfx_open(xsize,ysize,"bmpreader test");

	for(y=0;y<ysize;y++)
	{
		for(x=0;x<xsize;x++)
		{
			alpha=(unsigned char)image[(x+(y*xsize))*4]/255.0;
			gfx_color(image[(x+(y*xsize))*4+1]*alpha,image[(x+(y*xsize))*4+2]*alpha,image[(x+(y*xsize))*4+3]*alpha);
			gfx_point(x,y);
		}
	}
	// Set the current drawing color to green.
	gfx_color(0,200,100);

	// Draw a triangle on the screen.
	gfx_line(100,100,200,100);
	gfx_line(200,100,150,150);
	gfx_line(150,150,100,100);

	while(1) {
		// Wait for the user to press a character.
		c = gfx_wait();

		// Quit if it is the letter q.
		if(c=='q') break;
	}

	return 0;
}
