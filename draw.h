#ifndef DRAW_H
#define DRAW_H
#include "program.h"

// //! C wrapper for out C++ functions
//Function declarations for my graphics library
void flipBuffers(struct Graphics* g);
void fillScreen(struct Graphics* gr, char r, char g, char b, char a);
void drawString(struct Graphics* g, int x, int y, char * string);
void drawRect(struct Graphics* gr, int x1, int y1, int x2, int y2, char r, char g, char b, char a);
void drawPixel(struct Graphics* gr, int x, int y, char r, char g, char b);

void drawPixels(struct Graphics* g, struct Pixel pixels[200]);
void drawBitmap(struct Graphics* g, int ox, int oy, int width, int height, void *inp, void *pal);
void fillRect(struct Graphics* gr, int ox, int oy, int width, int height, int r, int g, int b);

#endif /* DRAW_H */