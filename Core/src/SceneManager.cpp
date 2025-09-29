
#include "SceneManager.h"
#include <algorithm>

namespace Core
{


	SceneManager::SceneManager()
	{
		
	}

	SceneManager::~SceneManager()
	{
	}



	void SceneManager::NextScene()
	{
		m_CurrentScene = std::min(m_CurrentScene + 1, (int)m_Scenes.size());
	}

	void SceneManager::PreviousScene()
	{
		m_CurrentScene = std::max(m_CurrentScene - 1, (int)m_Scenes.size());
	}

	void SceneManager::GotoScene(int i)
	{
		m_CurrentScene = std::clamp(i, 0, (int)m_Scenes.size());
	}




	void SceneManager::OnUpdate()
	{
		if (m_Scenes.size() > 0)
			m_Scenes[m_CurrentScene]->OnUpdate();
	}

	void SceneManager::OnRender()
	{
		if (m_Scenes.size() > 0)
			m_Scenes[m_CurrentScene]->OnRender();
	}

}



