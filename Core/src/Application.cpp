#include "Application.h"
#include <raylib.h>

namespace Core
{

	static Application* s_Application = nullptr;

	Application::Application(const ApplicationSpec& specification) : m_Specification(specification)
	{
		InitWindow(m_Specification.ScreenWidth, m_Specification.ScreenHeight, m_Specification.Name.c_str());
		SetTargetFPS(60);

		s_Application = this;
	
	}
	
	Application::~Application()
	{
		CloseWindow();
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
			}


			//Update


			//Render
			BeginDrawing();

			ClearBackground(RAYWHITE);

			EndDrawing();



		
		}
	
	}

	void Application::Stop()
	{
		m_Running = false;
	}


}