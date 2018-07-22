#include "draw.h"
#include "space.h"
#include "program.h"
#include "font.h"

#define SCREEN_X 1280
#define s 720

void flipBuffers(struct Graphics* g)
{
	SDL_UpdateWindowSurface(g->window);
}

/**
This is the main function that does the grunt work of drawing to both screens. It takes in the
Services structure that is constructed in program.c, which contains the pointer to the function
that is responsible for putting a pixel on the screen. By doing it this way, the OSScreenPutPixelEx function pointer is only
looked up once, at the program initialization, which makes successive calls to this pixel caller quicker.
**/
void putAPixel(struct Graphics* gr, int x, int y, int b, int g, int r)
{
	if (gr->flipColor)
	{
		int temp = r;
		r = b;
		b = temp;
	}

	int num = (r << 24) | (g << 16) | (b << 8) | 0;
	x *= 2;
	y *= 2;

	SDL_Rect rect;
	rect.x = x*1.5;
	rect.y = y*1.5;
	rect.w = 3;
	rect.h = 3;

	SDL_FillRect(gr->window_surface, &rect, SDL_MapRGBA(gr->window_surface->format, b, g, r, 0xFF));
}

void drawString(struct Graphics* g, int xi, int yi, char * string)
{
	// for every character in the string, if it's within range, render it at the current position
	// and move over 8 characters

	xi *= 6.25;
	yi *= 13;

	char next = -1;
	int i = 0;
	while (next != '\0')
	{
		next = string[i++];

		// actually draw this char pixel by pixel, if it's within range
		if (next >= 0 && next < 128)
		{
			char* bitmap = font[next];
			int x, y;
			for (x=0; x < 8; x++) {
				for (y=0; y < 8; y++) {
					if (bitmap[x] & 1 << y)
						putAPixel(g, xi+y+i*8, yi+x, 0xff, 0xff, 0xff);
				}
//				printf("\n");
			}
		}
	}
}

void fillScreen(struct Graphics* gr, char r,char g,char b,char a)
{
	SDL_FillRect(gr->window_surface, NULL, SDL_MapRGBA(gr->window_surface->format, b, g, r, a));
}

// draw black rect all at once
void fillRect(struct Graphics* gr, int ox, int oy, int width, int height, int r, int g, int b)
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
			putAPixel(gr, x, y, r, g, b);
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
void drawBitmap(struct Graphics* gr, int ox, int oy, int width, int height, void *inp, void *pal)
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

			// transparent pixels
			if (r == 0x27 && g == 0x27 && b == 0x27)
			{
				continue;
			}

			int x = ox + rx;
			int y = oy + ry;

			// do actual pixel drawing logic
			putAPixel(gr, x, y, r, g, b);
		}
	}
}

/**
This is primarly used for drawing the stars, and takes in a pixel map. It is similar to bitmap, but now
it takes the whole pixel map as well as which portion of it to actually draw. At the beginning, all of the stars
are drawn, but whenever the ship moves, only the stars underneath the ship need to be redrawn.
**/
void drawPixels(struct Graphics* g, struct Pixel pixels[200])
{
	int rx;
	for (rx=0; rx<200; rx++)
	{
		int x = pixels[rx].x;
		int y = pixels[rx].y;

		putAPixel(g, x, y, pixels[rx].r, pixels[rx].g, pixels[rx].b);
	}
}

void drawPixel(struct Graphics* gr, int x, int y, char r, char g, char b)
{
	putAPixel(gr, x, y, r, g, b);

}
