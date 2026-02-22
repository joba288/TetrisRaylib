#include <RendererAdapter.h>
#include <raylib.h>

namespace Tetris
{ 
	class RaylibRenderer : public Core::RendererAdapter
	{
		public:
			RaylibRenderer() {};
			void drawRectangle(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b, unsigned char a) override;
			virtual void drawText(const char* text, int x, int y, int size, unsigned char r, unsigned char g, unsigned char b, unsigned char a) override;
	};
}