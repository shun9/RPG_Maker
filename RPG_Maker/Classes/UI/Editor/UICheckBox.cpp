//************************************************/
//* @file  :UICheckBox.cpp
//* @brief :UICheckBox‚ÌƒNƒ‰ƒX
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#include "../../SL_Window.h"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_dx11.h"
#include "UICheckBox.h"

using namespace std;

UICheckBox::UICheckBox(const string& name, bool* check)
	:UIBase(name)
	,m_check(check)
{
}

UICheckBox::~UICheckBox()
{
}

void UICheckBox::DrawUpdate()
{
	ImGui::Checkbox(m_name.c_str(), m_check);

	//if (*m_check) {
	//	m_name = string("true");
	//}
	//else {
	//	m_name = string("false");
	//}
}
