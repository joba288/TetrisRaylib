#pragma once

namespace Core
{

	class RendererAdapter
	{
	public:
		virtual ~RendererAdapter() = default;
		virtual void drawRectangle(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {}
		virtual void drawText(const char* text, int x, int y, int size, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {}


	};
}