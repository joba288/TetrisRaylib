#pragma once

#include <string>
#include "SceneManager.h"

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

			SceneManager& GetSceneManager() { return m_SceneManager; }
			

		private:
			ApplicationSpec m_Specification;
			bool m_Running = false;

			SceneManager m_SceneManager;

			


	};

}