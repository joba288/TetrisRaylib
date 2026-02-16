#include "Application.h"
#include "SceneManager.h"
#include <raylib.h>
#include <algorithm>

namespace Core
{

	static Application* s_Application = nullptr;

	Application::Application(const ApplicationSpec& specification) : m_Specification(specification)
	{
		s_Application = this;

		InitWindow(m_Specification.ScreenWidth, m_Specification.ScreenHeight, m_Specification.Name.c_str());
		SetTargetFPS(60);


	}

	Application::~Application()
	{
		CloseWindow();
		s_Application = nullptr;
	}

	Application& Application::Get()
	{
		return *s_Application;
	}


	void Application::Run()
	{
		m_Running = true;

		float lastTime = GetTime();
		while (m_Running)
		{

			if (WindowShouldClose())
			{
				Stop();
				break;
			}

			float currentTime = GetTime();
			float timestep = std::clamp(currentTime - lastTime, 0.001f, 0.1f);
			lastTime = currentTime;

			//Update
			m_SceneManager.OnUpdate(timestep);
			//Render
			BeginDrawing();
			m_SceneManager.OnRender();
			EndDrawing();

		}

	}

	void Application::Stop()
	{
		m_Running = false;
	}

	void Application::NextScene()
	{
		m_SceneManager.NextScene();
	}
	void Application::PreviousScene()
	{
		m_SceneManager.PreviousScene();
	}

	void Application::GotoScene(int i)
	{
		m_SceneManager.GotoScene(i);
	}

}