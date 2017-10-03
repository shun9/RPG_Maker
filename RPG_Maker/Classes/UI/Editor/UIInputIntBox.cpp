//************************************************/
//* @file  :UIInputIntBox.cpp
//* @brief :UIInputIntBox‚ÌƒNƒ‰ƒX
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#include <SL_Texture.h>

#include "../../Game/Game.h"
#include "../../SL_Window.h"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_dx11.h"
#include "UIInputIntBox.h"

using namespace std;

UIInputIntBox::UIInputIntBox(const string& name, int* num)
	:UIBase(name)
	,m_num(num)
	,m_min(0)
	,m_max(999)
{
}

void UIInputIntBox::DrawUpdate()
{
	if (!m_num)return;

	ImGui::InputInt(m_name.c_str(), m_num, 1, 100);

	if (*m_num < m_min) {
		*m_num = m_min;
	}
	else if (m_max < *m_num) {
		*m_num = m_max;
	}

}
