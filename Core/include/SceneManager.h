#include <vector>
#include <stack>
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
				//m_Scenes.push_back(std::make_unique<TScene>());//
				m_SceneStack.push_back(std::make_shared<TScene>());
				m_SceneStack.back()->Init();
			}
			void PopScene()
			{
				m_SceneStack.pop_back();
			}

			template<typename TScene>
			requires(std::is_base_of_v<Scene, TScene>)
			inline void AddSceneToSequence()
			{
				m_ScenesSequence.push_back(std::make_shared<TScene>());
			}

		private:
			int m_CurrentScene = 0;
			std::vector<std::shared_ptr<Scene>> m_ScenesSequence;
			std::vector<std::shared_ptr<Scene>> m_SceneStack;
			
			
			
			
	
	
	};
}