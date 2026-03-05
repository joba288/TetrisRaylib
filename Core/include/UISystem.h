#pragma once
#include <vector>
#include <memory>
#include <string>
#include <raylib.h>
#include <map>
#include <iostream>


namespace Core
{

	struct UIComponentData
	{
		int posX;
		int posY; // Screenspace coords (centre)
		int width;
		int height;
		int rotation;

		bool visible = true;

		std::string text;
		int fontSize;
		Color textColor;
		Color defaultColor;
		Color hoveredColor;
	};


	class UIComponent
	{
	public:
		UIComponent(const UIComponentData& UIComponentData = UIComponentData());
		void OnUpdate(float ts);
		void Draw();
		bool IsClicked();
		bool IsHovered();
		void SetData(const UIComponentData& data) { m_Data = data; }
		UIComponentData GetData() { return m_Data; };
	private:
		UIComponentData m_Data;
		Color m_Color;

	};

	class UISystem
	{
	public:
		UISystem() = default;
		void OnUpdate(float ts);
		void Draw();
		bool AddComponent(const std::string& componentName, const UIComponent& component)
		{
			// Check if already in the map
			if (m_Components.find(componentName) != m_Components.end())
			{
				std::cout << "Component already exists at key: " + componentName << std::endl;
				return false;
			}

			m_Components.emplace(componentName, std::make_shared<UIComponent>(component));
		}

		const UIComponent& GetComponent(const std::string& componentName)
		{
			auto iterator = m_Components.find(componentName);
			if (iterator != m_Components.end())
			{
				return *iterator->second;
			}
			else
			{
				return UIComponent();
			}
		}
	private:
		std::map<std::string, std::shared_ptr<UIComponent>> m_Components;
	};
}