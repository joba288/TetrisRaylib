#include <RaylibRenderer.h>
#include <raylib.h>



typedef unsigned int uint;

void Tetris::RaylibRenderer::drawRectangle(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    DrawRectangle(x, y, w, h,
        Color{
            (unsigned char)r,
            (unsigned char)g,
            (unsigned char)b,
            (unsigned char)a
        });
}

void Tetris::RaylibRenderer::drawText(const char* text, int x, int y, int size, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    DrawText(text, x, y, size, 
        Color{
            (unsigned char)r,
            (unsigned char)g,
            (unsigned char)b,
            (unsigned char)a
        });
}

