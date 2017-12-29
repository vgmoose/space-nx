#ifndef DRAW_H
#define DRAW_H
#include "program.h"

#ifdef __cplusplus
extern "C" {
#endif

// //! C wrapper for out C++ functions
//Function declarations for my graphics library
void flipBuffers();
void fillScreen(char r, char g, char b, char a);
void drawString(int x, int y, char * string);
void drawStringTv(int x, int y, char * string);
void drawRect(int x1, int y1, int x2, int y2, char r, char g, char b, char a);
void drawPixel(int x, int y, char r, char g, char b);

void drawPixels(struct Pixel pixels[200]);
void drawBitmap(int ox, int oy, int width, int height, void *inp, void *pal);
void fillRect(int ox, int oy, int width, int height, int r, int g, int b);

#ifdef __cplusplus
}
#endif

#endif /* DRAW_H */