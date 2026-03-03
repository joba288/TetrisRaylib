
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
		m_CurrentScene = std::min(m_CurrentScene + 1, (int)m_ScenesSequence.size());
		m_SceneStack.empty();
		m_SceneStack.push_back(m_ScenesSequence[m_CurrentScene]);
		m_SceneStack.back()->Init();
	}

	void SceneManager::PreviousScene()
	{
		m_CurrentScene = std::max(m_CurrentScene - 1, (int)m_ScenesSequence.size());
		m_SceneStack.empty();
		m_SceneStack.push_back(m_ScenesSequence[m_CurrentScene]);
		m_SceneStack.back()->Init();
	}

	void SceneManager::GotoScene(int i)
	{
		m_CurrentScene = std::clamp(i, 0, (int)m_ScenesSequence.size());
		m_SceneStack.empty();
		m_SceneStack.push_back(m_ScenesSequence[m_CurrentScene]);
		m_SceneStack.back()->Init();
	}



	void SceneManager::OnUpdate(float ts)
	{
		if (m_SceneStack.size() > 0)
			m_SceneStack.back()->OnUpdate(ts);
	}

	void SceneManager::OnRender()
	{
		for (auto& scene : m_SceneStack)
			m_SceneStack.back()->OnRender();
	}

}



