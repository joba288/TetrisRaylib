#include <RaylibRenderer.h>
#include <raylib.h>
#include <Application.h>



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

void Tetris::RaylibRenderer::drawTexture(int x, int y, float scale, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    
    float w = tex.width * scale;
    float h = tex.height * scale;
    
    Rectangle source{ 0,0,(float)tex.width,(float)tex.height };
    
    Vector2 origin{ w / 2.0f, h / 2.0f };
    
    Rectangle dest{
        x + origin.x,
        y + origin.y,
        w,
        h
    };
    
    DrawTexturePro(
        tex,
        source,
        dest,
        origin,
        0.0f,
        Color{ r,g,b,a }
    );
    
}

void Tetris::RaylibRenderer::LoadTexture(const std::string& assetName)
{
    tex = Core::Application::Get().getTexture(assetName);
}