//************************************************/
//* @file  :UITileCanvas.cpp
//* @brief :UIキャンバスクラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#include <SL_Texture.h>

#include "../../Game/Game.h"
#include "../../SL_Window.h"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_dx11.h"
#include <vector>
#include "UITileCanvas.h"
#include "../../Map/TileDataHolder.h"
#include "../../Map/MapEditor.h"

using namespace std;
using namespace ShunLib;

namespace {
	static const Vec2 PADDING = Vec2(3.0f, 3.0f);
}

UITileCanvas::UITileCanvas(const string& name)
	:UIBase(name)
{
	m_texture = make_unique<ShunLib::Texture>(L"Image\\tile_canvas_bg.png");

	m_Pos = Vec2(25.0f, 85.0f);
}

UITileCanvas::~UITileCanvas()
{
}

void UITileCanvas::DrawUpdate()
{
	m_texture->Draw(m_Pos, Vec2::One);

	const auto dataList = TileDataHolder::GetInstance()->GetTileList();

	int x = 0, y = 0;
	for each (const auto& data in dataList)
	{
		Vec2 pos(x*Tile::SIZE + (x + 1)*PADDING.m_x, y*Tile::SIZE + (y + 1)*PADDING.m_y);
		data.texture->Draw(m_Pos + pos, Vec2::One);

		x++;
		if (9 < x) {
			x = 0;
			y++;
		}
	}

	ImGui::SetNextWindowPos(ImVec2(m_Pos.m_x, m_Pos.m_y), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(324, 540), ImGuiSetCond_Once);

	auto& style = ImGui::GetStyle();
	auto oldAlpha = style.Alpha;

	style.Alpha = 0.1f;

	if (ImGui::Begin(m_name.c_str(), nullptr
		, ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoMove
		//| ImGuiWindowFlags_NoSavedSettings
		| ImGuiWindowFlags_NoCollapse))
	{
		ImGui::End();
	}

	style.Alpha = oldAlpha;
}