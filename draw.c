#include "draw.h"
#include "space.h"
#include "program.h"

void flipBuffers()
{
	//Grab the buffer size for each screen (TV and gamepad)
//	int buf0_size = OSScreenGetBufferSizeEx(0);
//	int buf1_size = OSScreenGetBufferSizeEx(1);
	
	//Flush the cache
//	DCFlushRange((void *)0xF4000000 + buf0_size, buf1_size);
//	DCFlushRange((void *)0xF4000000, buf0_size);
	
	//Flip the buffer
//	OSScreenFlipBuffersEx(0);
//	OSScreenFlipBuffersEx(1);
}

/**
This is the main function that does the grunt work of drawing to both screens. It takes in the 
Services structure that is constructed in program.c, which contains the pointer to the function
that is responsible for putting a pixel on the screen. By doing it this way, the OSScreenPutPixelEx function pointer is only
looked up once, at the program initialization, which makes successive calls to this pixel caller quicker.
**/
void putAPixel(int x, int y, int r, int g, int b)
{
	int num = (r << 24) | (g << 16) | (b << 8) | 0;
	x *= 2;
	y *= 2;

//	int ax, ay, az;
//	for (ax=0; ax<2; ax++)
//		for (ay=0; ay<2; ay++)
//			for (az=0; az<2; az++)
//				OSScreenPutPixelEx(ax, x + ay, y + az, num);
}

void drawString(int x, int y, char * string)
{
//	OSScreenPutFontEx(1, x, y, string);
}

void drawStringTv(int x, int y, char * string)
{
//	OSScreenPutFontEx(0, x, y, string);
}

void fillScreen(char r,char g,char b,char a)
{
	int num = (r << 24) | (g << 16) | (b << 8) | a;
	
//	OSScreenClearBufferEx(0, num);
//	OSScreenClearBufferEx(1, num);
}

// draw black rect all at once
void fillRect(int ox, int oy, int width, int height, int r, int g, int b)
{	
			
	int rx;
	for (rx=0; rx<width; rx++)
	{
		int ry;
		for (ry=0; ry<height; ry++)
		{
			int x = ox + rx;
			int y = oy + ry;
			
			// do actual pixel drawing logic
			putAPixel(x, y, r, g, b);
		}
	}
}

/**
This function draws a "bitmap" in a very particular fashion: it takes as input the matrix of chars to draw.
In this matrix, each char represents the index to look it up in the palette variable which is also passed. 
Alpha isn't used here, and instead allows the "magic color" of 0x272727 to be "skipped" when drawing.
By looking up the color in the palette, the bitmap can be smaller. Before compression was implemented, this was
more important. A potential speedup may be to integrate the three pixel colors into a matrix prior to this function.
**/
void drawBitmap(int ox, int oy, int width, int height, void *inp, void *pal)
{	
	unsigned char (*input)[width] = (unsigned char (*)[width])(inp);
	unsigned const char (*palette)[3] = (unsigned const char (*)[3])(pal);
	int rx;
	for (rx=0; rx<width; rx++)
	{
		int ry;
		for (ry=0; ry<height; ry++)
		{
			const unsigned char* color = palette[input[ry][rx]];
			char r = color[2];
			char g = color[1];
			char b = color[0];
			
//			// transparent pixels
			if (r == 0x27 && g == 0x27 && b == 0x27)
			{
				continue;
			}
			
			int x = ox + rx;
			int y = oy + ry;
			
			// do actual pixel drawing logic
			putAPixel(x, y, r, g, b);
		}
	}
}

/**
This is primarly used for drawing the stars, and takes in a pixel map. It is similar to bitmap, but now
it takes the whole pixel map as well as which portion of it to actually draw. At the beginning, all of the stars
are drawn, but whenever the ship moves, only the stars underneath the ship need to be redrawn.
**/
void drawPixels(struct Pixel pixels[200])
{	
	int rx;
	for (rx=0; rx<200; rx++)
	{
		int x = pixels[rx].x;
		int y = pixels[rx].y;
		
		putAPixel(x, y, pixels[rx].r, pixels[rx].g, pixels[rx].b);
	}
}

void drawPixel(int x, int y, char r, char g, char b)
{		
	putAPixel(x, y, r, g, b);

}