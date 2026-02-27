#include <AssetManager.h>
#include <raylib.h>
#include <iostream>

namespace Core
{
	bool AssetManager::addTexture(const std::string& assetName, const std::string& filepath)
	{
		// Check if already in the map
		if (m_TextureMap.find(assetName) != m_TextureMap.end())
		{
			std::cout << "Texture already exists at key: " + assetName << std::endl;
			return false;
		}

		
		Texture t = LoadTexture(filepath.c_str());

		if (t.id <= 0)	// Load Failed
		{
			std::cout << "Failed to load texture " + assetName << std::endl;
			return false;
		}
		
		m_TextureMap.emplace(assetName, std::make_shared<Texture>(t));
		return true;
		
	}

	const Texture& AssetManager::getTexture(const std::string& assetName)
	{
		auto iterator = m_TextureMap.find(assetName);
		if (iterator != m_TextureMap.end())
		{
			return *iterator->second;
		}
		else
		{
			return Texture();
		}
	}


	AssetManager::~AssetManager()
	{
		for (auto t : m_TextureMap)
			UnloadTexture(*t.second);
	}
}