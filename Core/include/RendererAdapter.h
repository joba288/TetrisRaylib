#pragma once
#include <string>

namespace Core
{

	class RendererAdapter
	{
	public:
		~RendererAdapter() = default;
		virtual void drawRectangle(int x, int y, int w, int h, float rot, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {}
		virtual void drawText(const char* text, int x, int y, int size, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {}
		virtual void drawTexture(int x, int y, float scale, float rot, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {}
		virtual void drawTexture(int x, int y, int w, int h, float scale, float rot, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {}
		virtual void LoadTexture(const std::string& assetName) {}

	};
}
