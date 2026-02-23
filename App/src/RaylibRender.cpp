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

void Tetris::RaylibRenderer::drawTexture(const char* filePath, int x, int y, float size, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    // TODO Very crude, I will fix the problems of this with an asset manager but will do for now
    
    DrawTextureEx(tex, Vector2{(float)x, (float)y}, 0, size, 
        Color{
            (unsigned char)r,
            (unsigned char)g,
            (unsigned char)b,
            (unsigned char)a
        });
}

void Tetris::RaylibRenderer::LoadTexture(const char* filePath)
{
    tex = LoadTextureFromImage(LoadImage(filePath));
}