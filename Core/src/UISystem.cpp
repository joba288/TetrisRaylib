#include "UISystem.h"
#include <iostream>





namespace Core
{
	UIComponent::UIComponent(const UIComponentData& UIComponentData) 
		: m_Data(UIComponentData)
	{
		m_Color = m_Data.defaultColor;
	}

	void UIComponent::OnUpdate(float ts)
	{
		if (IsHovered())
		{
			m_Color = m_Data.hoveredColor;
		}
		else
		{
			m_Color = m_Data.defaultColor;
		}


	}

	void UIComponent::Draw()
	{
		if (m_Data.visible)
		{
			DrawRectangle(m_Data.posX - m_Data.width / 2,
				m_Data.posY - m_Data.height / 2,
				m_Data.width,
				m_Data.height,
				m_Color);
			DrawText(m_Data.text.c_str(),
					m_Data.posX - (m_Data.fontSize * m_Data.text.size())/4, // Temporary
					m_Data.posY ,
					m_Data.fontSize,
					m_Data.textColor);
			
		}
	}

	bool UIComponent::IsHovered()
	{
		int minX = m_Data.posX - m_Data.width / 2;
		int minY = m_Data.posY - m_Data.height / 2;
		int maxX = m_Data.posX + m_Data.width / 2;
		int maxY = m_Data.posY + m_Data.height / 2;

		int mx = GetMouseX(); int my = GetMouseY();

		if ((minX <= mx && mx <= maxX) && (minY <= my && my <= maxY))
			return true;
		return false;
	}

	bool UIComponent::IsClicked()
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			return IsHovered();
		return false;
	}

	// UI SYSTEM
	void UISystem::OnUpdate(float ts)
	{
		for (auto iterator : m_Components)
			iterator.second->OnUpdate(ts);
	}

	void UISystem::Draw()
	{
		for (auto iterator : m_Components)
			iterator.second->Draw();
	}
}