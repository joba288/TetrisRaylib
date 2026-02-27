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

	bool AssetManager::addShader(const std::string& assetName, const std::string& fsFilepath, const std::string& vsFilepath)
	{
		// Check if already in the map
		if (m_ShaderMap.find(assetName) != m_ShaderMap.end())
		{
			std::cout << "Shader already exists at key: " + assetName << std::endl;
			return false;
		}


		Shader s = LoadShader(fsFilepath.c_str(), vsFilepath.c_str());

		if (s.id <= 0)	// Load Failed
		{
			std::cout << "Failed to load shader " + assetName << std::endl;
			return false;
		}

		m_ShaderMap.emplace(assetName, std::make_shared<Shader>(s));
		return true;

	}
	bool AssetManager::addShaderFromMemory(const std::string& assetName, const std::string& vsText, const std::string& fsText)
	{
		// Check if already in the map
		if (m_TextureMap.find(assetName) != m_TextureMap.end())
		{
			std::cout << "Shader already exists at key: " + assetName << std::endl;
			return false;
		}


		Shader s = LoadShaderFromMemory(vsText.c_str(), fsText.c_str());
		

		if (s.id <= 0)	// Load Failed
		{
			std::cout << "Failed to load shader " + assetName << std::endl;
			return false;
		}

		m_ShaderMap.emplace(assetName, std::make_shared<Shader>(s));
		return true;

	}
	const Shader& AssetManager::getShader(const std::string& assetName)
	{
		auto iterator = m_ShaderMap.find(assetName);
		if (iterator != m_ShaderMap.end())
		{
			return *iterator->second;
		}
		else
		{
			return Shader();
		}
	}


	AssetManager::~AssetManager()
	{
		for (auto t : m_TextureMap)
			UnloadTexture(*t.second);
	}
}