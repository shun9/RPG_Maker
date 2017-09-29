//************************************************/
//* @file  :UISlider.cpp
//* @brief :UISlider‚ÌƒNƒ‰ƒX
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#include "../../SL_Window.h"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_dx11.h"
#include "UISlider.h"

using namespace std;

UISlider::UISlider(const string& name,int* num, int min, int max)
	:UIBase(name)
	,m_sliderNum(num)
	,m_min(min)
	,m_max(max)
{
}

UISlider::~UISlider()
{
}

void UISlider::DrawUpdate()
{
	ImGui::SliderInt(m_name.c_str(), m_sliderNum, m_min, m_max);
}
