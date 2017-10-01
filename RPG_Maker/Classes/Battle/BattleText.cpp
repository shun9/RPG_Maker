//************************************************/
//* @file  :BattleText.cpp
//* @brief :バトル中のテキストを描画する
//* @date  :2017/10/01
//* @author:S.Katou
//************************************************/
#include "BattleText.h"
#include <string>
#include "../../SL_Window.h"

void BattleText::Update()
{
	//タイマーの更新
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

void BattleText::Draw(const ShunLib::Vec2 & pos)
{
	auto win = ShunLib::Window::GetInstance();


	//描画対象をエディター用のウィンドウに戻す
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
			size = m_text[i].size();

			//表示する割合
			rate=(int)((count / DRAWING_TIME)*size);
			tmp = m_text[i].substr(0, rate);
			ImGui::Text(tmp.c_str());
		}

		ImGui::End();
	}

	// Rendering
	//この上に描画処理を書く
	ImGui::Render();

	hw = win->WindouHandle(ShunLib::Window::EDITOR);
	ImGui_ImplDX11_Init(hw, win->Device(), win->DeviceContext());
}

/// <summary>
/// コマンドの表示
/// </summary>
void BattleText::CommandDraw(const ShunLib::Vec2 & pos)
{
	auto win = ShunLib::Window::GetInstance();

	//描画対象をエディター用のウィンドウに戻す
	win->SetDrawingWindow(ShunLib::Window::DEBUGGER);
	auto hw = win->WindouHandle(ShunLib::Window::DEBUGGER);
	ImGui_ImplDX11_Init(hw, win->Device(), win->DeviceContext());

	ImGui_ImplDX11_NewFrame();
	ImGui::SetNextWindowPos(ImVec2(pos.m_x, pos.m_y + 360.0f), ImGuiSetCond_Always);
	ImGui::SetNextWindowSize(ImVec2(170.0f, 210.0f), ImGuiSetCond_Always);

	if (ImGui::Begin("command", nullptr
		, ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoCollapse
		|ImGuiWindowFlags_NoResize ))
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
	//この上に描画処理を書く
	ImGui::Render();

	hw = win->WindouHandle(ShunLib::Window::EDITOR);
	ImGui_ImplDX11_Init(hw, win->Device(), win->DeviceContext());

}

bool BattleText::IsEnded()
{
	return false;
}

void BattleText::SetString(std::string str)
{
	m_text.push_back(str);
	m_timer.push_back(ShunLib::Timer());
	m_timer.back().SetTime(DRAWING_TIME);
}

BattleText::BattleText() :
	m_isEnded(false),
	DRAWING_TIME(120.0f)
{
	std::string str = "Player's Attack!! AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	this->SetString(str);
	str = "Enemy's Attack!! URWJVWKJVJWHJDSIVDSKVNSVHSBVB";
	this->SetString(str);
	str = "Player Win!! YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY";
	this->SetString(str);
}

BattleText::~BattleText()
{
}
