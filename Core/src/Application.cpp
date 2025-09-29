#include "Application.h"
#include "SceneManager.h"
#include <raylib.h>

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

		while (m_Running)
		{
		
			if (WindowShouldClose())
			{
				Stop();
				break;
			}


			//Update
			m_SceneManager.OnUpdate();
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


}