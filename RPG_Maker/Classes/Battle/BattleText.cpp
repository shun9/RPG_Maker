//************************************************/
//* @file  :BattleText.cpp
//* @brief :�o�g�����̃e�L�X�g��`�悷��
//* @date  :2017/10/01
//* @author:S.Katou
//************************************************/
#include "BattleText.h"
#include <string>
#include <SL_KeyManager.h>
#include "../../SL_Window.h"
#include "BattleTextPreset.h"

/// <summary>
/// �X�V
/// </summary>
void BattleText::Update()
{
	//�^�C�}�[�̍X�V
	for (int i = 0; i < (int)(m_timer.size()); i++)
	{
		if (i == 0)
		{
			m_timer[i].Update();
		}
		else {
			if (m_timer[i - 1].IsEnded())
			{
				m_timer[i].Update();
			}
		}
	}
}

/// <summary>
/// �e�L�X�g�̕`��
/// </summary>
void BattleText::Draw(const ShunLib::Vec2 & pos)
{
	auto win = ShunLib::Window::GetInstance();


	//�`��Ώۂ��G�f�B�^�[�p�̃E�B���h�E�ɖ߂�
	win->SetDrawingWindow(ShunLib::Window::DEBUGGER);
	auto hw = win->WindouHandle(ShunLib::Window::DEBUGGER);
	ImGui_ImplDX11_Init(hw, win->Device(), win->DeviceContext());

	ImGui_ImplDX11_NewFrame();
	ImGui::SetNextWindowPos(ImVec2(pos.m_x, pos.m_y + 360.0f), ImGuiSetCond_Always);
	ImGui::SetNextWindowSize(ImVec2(750.0f, 205.0f), ImGuiSetCond_Always);

	if (ImGui::Begin("text", nullptr
		, ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoResize))
	{
		float fontScale = 1.8f;
		float space = 1.0f;
		std::string tmp;
		int rate = 0;
		int count = 0;
		int size = 0;
		for (int i = 0; i < (int)(m_text.size()); i++)
		{
			ImGui::SetWindowFontScale(space);
			ImGui::Text("");
			ImGui::SetWindowFontScale(fontScale);

			count = m_timer[i].GetNowCount();
			size = m_text[i].size()/3;

			//�\�����銄��
			rate = (int)((count / DRAWING_TIME)*size)*3;

			tmp = m_text[i].substr(0, rate);
			ImGui::Text((tmp.c_str()));
		}
		ImGui::End();
	}

	// Rendering
	//���̏�ɕ`�揈��������
	ImGui::Render();

	hw = win->WindouHandle(ShunLib::Window::EDITOR);
	ImGui_ImplDX11_Init(hw, win->Device(), win->DeviceContext());
}

/// <summary>
/// �R�}���h�̕\��
/// </summary>
void BattleText::CommandDraw(const ShunLib::Vec2 & pos)
{
	auto win = ShunLib::Window::GetInstance();

	//�`��Ώۂ��G�f�B�^�[�p�̃E�B���h�E�ɖ߂�
	win->SetDrawingWindow(ShunLib::Window::DEBUGGER);
	auto hw = win->WindouHandle(ShunLib::Window::DEBUGGER);
	ImGui_ImplDX11_Init(hw, win->Device(), win->DeviceContext());

	ImGui_ImplDX11_NewFrame();
	ImGui::SetNextWindowPos(ImVec2(pos.m_x, pos.m_y + 360.0f), ImGuiSetCond_Always);
	ImGui::SetNextWindowSize(ImVec2(170.0f, 210.0f), ImGuiSetCond_Always);

	if (ImGui::Begin("command", nullptr
		, ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoResize))
	{
		float fontScale = 1.8f;
		float space = 1.0f;
		ImGui::SetWindowFontScale(space);
		ImGui::Text("");
		ImGui::SetWindowFontScale(fontScale);
		ImGui::Text("    Attack");
		ImGui::SetWindowFontScale(space);
		ImGui::Text("");
		ImGui::SetWindowFontScale(fontScale);
		ImGui::Text("    Defence");
		ImGui::SetWindowFontScale(space);
		ImGui::Text("");
		ImGui::SetWindowFontScale(fontScale);
		ImGui::Text("    Escape");
		ImGui::End();
	}

	// Rendering
	//���̏�ɕ`�揈��������
	ImGui::Render();

	hw = win->WindouHandle(ShunLib::Window::EDITOR);
	ImGui_ImplDX11_Init(hw, win->Device(), win->DeviceContext());

}

/// <summary>
/// �`�悪�I����Ă��邩�ǂ���
/// </summary>
/// <returns></returns>
bool BattleText::IsEnded()
{
	bool isEnd = false;
	auto key = ShunLib::KeyManager::GetInstance();
	if (key->IsTracker(ShunLib::KeyManager::KEY_CODE::SPACE))
	{
		isEnd = m_timer.back().IsEnded();
	}

	//�Ō�̃^�C�}�[���I�����Ă�����I����Ă���
	return isEnd;
}

//�`�悷��e�L�X�g��`��
void BattleText::SetString(std::string str)
{
	m_text.push_back(str);
	m_timer.push_back(ShunLib::Timer());
	m_timer.back().SetTime(DRAWING_TIME);
}

void BattleText::Reset()
{
	m_timer.clear();
	m_timer.shrink_to_fit();
	m_text.clear();
	m_text.shrink_to_fit();
}

BattleText::BattleText() :
	m_isEnded(false),
	DRAWING_TIME(30.0f)
{

}

BattleText::~BattleText()
{
}
