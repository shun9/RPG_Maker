//************************************************/
//* @file  :UIButton.cpp
//* @brief :UIButton�̃N���X
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#include <SL_Texture.h>

#include "../../Game/Game.h"
#include "../../SL_Window.h"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_dx11.h"
#include "UIButton.h"

using namespace std;

UIButton::UIButton(const string& name, std::function<void()> func, const Vector2& size)
	:UIBase(name)
	,m_size(size.m_x,size.m_y)
{
	// �����ݒ肪�����ꍇ�f�o�b�O�p�C�x���g
	m_func = func ? func : [=]() {OutputDebugStringW(L"press button\n"); };
}

UIButton::~UIButton()
{
}

void UIButton::DrawUpdate()
{
	// �{�^���̕`��Ɖ����ꂽ�Ƃ��̏���
	if (ImGui::Button(m_name.c_str(), m_size))
	{
		m_func();
	}
}

void UIButton::DrawUpdate(const string & name)
{
	m_name = name;
	DrawUpdate();
}
