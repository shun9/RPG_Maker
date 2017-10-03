//************************************************/
//* @file  :UITileCanvas.cpp
//* @brief :UIキャンバスクラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#include <SL_Texture.h>
#include <vector>

#include "UITileCanvas.h"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_dx11.h"
#include "../../Map/MapEditor.h"
#include "../../../Utils/MouseManager.h"
#include "../../Data/DataBase.h"
#include "../../Map/Tile.h"

using namespace std;
using namespace ShunLib;

namespace {
	static const int CANVAS_WIDTH = 8;
	static const int CANVAS_HEIGHT = 10;
	static const Vec2 PADDING = Vec2(3.0f, 3.0f);
	static const Vec2 IMAGE_SIZE = Vec2(340.0f, 540.0f);
}

UITileCanvas::UITileCanvas(const string& name)
	:UIBase(name)
{
	m_texture = make_unique<ShunLib::Texture>(L"Image\\tile_canvas_bg.png");

	m_Pos = Vec2(5.0f, 55.0f);
}

UITileCanvas::~UITileCanvas()
{
}

void UITileCanvas::DrawUpdate()
{
	RECT rect = { (LONG)m_Pos.m_x,(LONG)m_Pos.m_y,(LONG)IMAGE_SIZE.m_x + (LONG)m_Pos.m_x,(LONG)IMAGE_SIZE.m_y + (LONG)m_Pos.m_y };

	m_texture->Draw(m_Pos, Vec2::One, &rect);

	int x = 0, y = 0;

	for each (const auto& data in DB_Tile.GetList())
	{
		Vec2 pos(x*Tile::SIZE + (x + 1)*PADDING.m_x, y*Tile::SIZE + (y + 1)*PADDING.m_y);
		data->texture->Draw(m_Pos + pos, Vec2::One);

		x++;
		if (CANVAS_WIDTH < x) {
			x = 0;
			y++;
		}

		if (CANVAS_HEIGHT + 1 < y) {
			break;
		}
	}

	ImGui::SetNextWindowPos(ImVec2(m_Pos.m_x, m_Pos.m_y), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(IMAGE_SIZE.m_x, IMAGE_SIZE.m_y), ImGuiSetCond_Once);

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

void UITileCanvas::SelectTile()
{
	if (MouseManager::GetInstance()->GetMouseButtonDown(MouseButton::leftButton))
	{
		// 左クリック時
		auto pos = MouseManager::GetInstance()->GetMousePosition();

		int* id = nullptr;

		if (CollisionTile(pos, id)) {
			auto tileListSize = DB_Tile.GetList().size();

			if (*id <= (int)tileListSize - 1)
			{
				// タイルが当たっているとき
				MapEditor::GetInstance()->Id(*id);
			}
		}

		delete id;
	}
}

/// スクリーン上の座標をCanvasの座標に変換する
void UITileCanvas::ConvertCanvasPos(const Vec2& pos, int& bufX, int& bufY)
{
	auto localPos = Vec2(pos.m_x - m_Pos.m_x, pos.m_y - m_Pos.m_y);

	if (localPos.m_x < 0||
		localPos.m_y < 0
		) 
	{
		bufX = -1;
		bufY = -1;
		return;
	}

	bufX = (int)(localPos.m_x / (Tile::SIZE + PADDING.m_x));
	bufY = (int)(localPos.m_y / (Tile::SIZE + PADDING.m_y));
}

bool UITileCanvas::CollisionTile(const Vec2& pos,int*& id)
{
	int x = 0, y = 0;
	ConvertCanvasPos(pos, x, y);

	//マップのサイズを超えていたら抜ける
	if (x > CANVAS_WIDTH || 
		y > CANVAS_HEIGHT - 1||
		x < 0||
		y < 0)
	{
		return false;
	}

	id = new int(x + y * CANVAS_WIDTH + y);

	return true;
}
