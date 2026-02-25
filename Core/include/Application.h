#pragma once

#include <string>
#include <SceneManager.h>
#include <AssetManager.h>


namespace Core
{
	struct ApplicationSpec
	{
		std::string Name = "Application";
		int ScreenWidth = 1080;
		int ScreenHeight = 720;
	};

	class Application
	{
		public:
			Application(const ApplicationSpec& specification = ApplicationSpec());
			~Application();

			void Run();
			void Stop();
			static Application& Get();
			ApplicationSpec GetSpec() { return m_Specification; };

			// Scene Manager
			void NextScene();
			void PreviousScene();
			void GotoScene(int i);
			SceneManager& GetSceneManager() { return m_SceneManager; }

			// Asset Manager
			bool addTexture(const std::string& assetName, const std::string& filepath);
			const Texture& getTexture(const std::string& assetName);
			AssetManager& GetAssetManager() { return m_AssetManager;  }

		private:
			ApplicationSpec m_Specification;
			bool m_Running = false;

			SceneManager m_SceneManager;
			AssetManager m_AssetManager;
	};

}