//************************************************/
//* @file  :UIInputStringBox.cpp
//* @brief :UIInputStringBoxのクラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#include <SL_Texture.h>

#include "../../Game/Game.h"
#include "../../SL_Window.h"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_dx11.h"
#include "UIInputStringBox.h"

using namespace std;

UIInputStringBox::UIInputStringBox(const string& name, string* text, std::size_t size)
	:UIBase(name)
	, m_text(text)
	, m_size(size)
{

}

UIInputStringBox::~UIInputStringBox()
{
}

void UIInputStringBox::DrawUpdate()
{
	auto cstr = new char[1000]; // メモリ確保
	std::strcpy(cstr, m_text->c_str());        // コピー

	if(ImGui::InputText(m_name.c_str(), cstr, m_size))
	{ 
		*m_text = cstr;
	}

	delete[] cstr; // 解放
}

void UIInputStringBox::DrawMultiBoxUpdate(ShunLib::Vec2 size)
{
	auto cstr = new char[100000]; // メモリ確保
	std::strcpy(cstr, m_text->c_str());        // コピー

	if (ImGui::InputTextMultiline(m_name.c_str(), cstr, m_size, ImVec2(size.m_x, size.m_y)))
	{
		*m_text = cstr;
	}

	delete[] cstr; // 解放
}

