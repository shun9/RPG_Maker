#include "UIPlayer.h"
#include "../../Player/Player.h"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_dx11.h"

void UIPlayer::DrawUpdate()
{
	if (!Active)return;
	if (m_player == nullptr)return;

	//フォントサイズ変更
	ImGui::SetWindowFontScale(1.4f);

	ImGui::NewLine();
	ImGui::NewLine();

	// 名前入力欄
	float txtinitPos = 650.0f;
	float nextinitdir = 250.0f;

	ImGui::SameLine(300);
	ImGui::Text("pos :");

	ImGui::PushItemWidth(150.0f);
	ImGui::NewLine();
	ImGui::SameLine(300);
	UIVECTORDRAW(m_posInputBox, 0);
	ImGui::SameLine(300.0f+175.0f);
	UIVECTORDRAW(m_posInputBox, 1);
	m_player->PosOnMap(ShunLib::Vec2((float)m_playerPosX,(float)m_playerPosY));

	// param
	ImGui::SameLine(txtinitPos);
	ImGui::Text("HP :");
	ImGui::SameLine(txtinitPos + nextinitdir);
	ImGui::Text("MP :");
	ImGui::NewLine();
	ImGui::SameLine(300);
	ImGui::SameLine(txtinitPos);
	UIVECTORDRAW(m_paramInputBox, Player::PARAM::HP);
	ImGui::SameLine(txtinitPos + nextinitdir);
	UIVECTORDRAW(m_paramInputBox, Player::PARAM::MP);

	ImGui::NewLine();
	ImGui::NewLine();
	ImGui::SameLine(txtinitPos);
	ImGui::Text("ATK :");
	ImGui::SameLine(txtinitPos + nextinitdir);
	ImGui::Text("DEF :");
	ImGui::NewLine();
	ImGui::SameLine(txtinitPos);
	UIVECTORDRAW(m_paramInputBox, Player::PARAM::ATK);
	ImGui::SameLine(txtinitPos + nextinitdir);
	UIVECTORDRAW(m_paramInputBox, Player::PARAM::DEF);

	ImGui::NewLine();
	ImGui::NewLine();
	ImGui::SameLine(txtinitPos);
	ImGui::Text("DEX :");
	ImGui::SameLine(txtinitPos + nextinitdir);
	ImGui::Text("EVA :");
	ImGui::NewLine();
	ImGui::SameLine(txtinitPos);
	UIVECTORDRAW(m_paramInputBox, Player::PARAM::DEX);
	ImGui::SameLine(txtinitPos + nextinitdir);
	UIVECTORDRAW(m_paramInputBox, Player::PARAM::SPD);

	ImGui::NewLine();
	ImGui::NewLine();
	ImGui::SameLine(txtinitPos);
	ImGui::Text("EXP :");
	ImGui::SameLine(txtinitPos + nextinitdir);
	ImGui::Text("MONEY :");
	ImGui::NewLine();
	ImGui::SameLine(txtinitPos);
	UIVECTORDRAW(m_paramInputBox, Player::PARAM::EXP);
	ImGui::SameLine(txtinitPos + nextinitdir);
	UIVECTORDRAW(m_paramInputBox, Player::PARAM::MONEY);

}

void UIPlayer::UIUpdate()
{
	if (m_player == nullptr)return;
	auto playerPos = m_player->PosOnMap();
	m_playerPosX = (int)playerPos.m_x;
	m_playerPosY = (int)playerPos.m_y;

	m_posInputBox.resize(2);
	char title[16];
	sprintf_s(title, "X");
	m_posInputBox[0] = std::make_unique<UIInputIntBox>(title, &m_playerPosX);
	sprintf_s(title, "Y");
	m_posInputBox[1] = std::make_unique<UIInputIntBox>(title, &m_playerPosY);

	m_paramInputBox.resize(Player::PARAM::length);
	for (int i = 0; i < Player::PARAM::length; i++) {
		sprintf_s(title, "param_%d", i);
		m_paramInputBox[i] = std::make_unique<UIInputIntBox>(title, &m_player->GetParam()[i]);
	}

}
