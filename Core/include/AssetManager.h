#pragma once
#include <map>
#include <string>
#include <memory>
#include <raylib.h>

namespace Core
{
	class AssetManager
	{
		public:
			AssetManager() = default;
			~AssetManager();
			bool addTexture(const std::string& assetName, const std::string& filepath);
			const Texture& getTexture(const std::string& assetName);
		private:
			std::map<std::string, std::shared_ptr<Texture>> m_TextureMap;
			std::map<std::string, std::shared_ptr<Shader>> m_ShaderMap;
	};
}
