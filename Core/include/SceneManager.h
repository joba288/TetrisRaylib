#include <vector>
#include <memory>
#include <type_traits>

#pragma once

namespace Core {

	class Scene
	{
		public:
			virtual ~Scene() = default;

			virtual void Init() {}
			virtual void OnRender() {}
			virtual void OnUpdate(float ts) {}

	};


	class SceneManager
	{
	
		public:
			SceneManager();
			~SceneManager();

			void NextScene();
			void PreviousScene();
			void GotoScene(int i);

			void OnRender();
			void OnUpdate(float ts);

			template<typename TScene>
			requires(std::is_base_of_v<Scene, TScene>)
			inline void PushScene() 
			{
				m_Scenes.push_back(std::make_unique<TScene>());
			}

		private:
			int m_CurrentScene = 0;
			std::vector<std::unique_ptr<Scene>> m_Scenes;
			
			
			
	
	
	};
}