//************************************************/
//* @file  :GameEditor.cpp
//* @brief :エディター
//* @date  :2017/09/28
//* @author:S.Katou
//************************************************/
#include "GameEditor.h"
#include <Windows.h>
#include <SL_Texture.h>
#include <SL_KeyManager.h>
#include "../Game/Game.h"
#include "../../SL_Window.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx11.h"

#include <string>

#include "../../Utils/MouseManager.h"
#include "../Map/TileDataHolder.h"
#include "../Map/MapEditor.h"
#include "../../Utils/ImageLoader.h"

using namespace std;

GameEditor::GameEditor()
{

}

GameEditor::~GameEditor()
{
	//ゲームは最後まで保持しておく
	DELETE_POINTER(m_game);
}

//初期化
void GameEditor::Initialize()
{
	auto win = ShunLib::Window::GetInstance();
	ShunLib::Texture::SetDevice(win->Device(), win->DeviceContext());
	auto hw = win->WindouHandle(ShunLib::Window::EDITOR);
	
	ImGui_ImplDX11_Init(hw, win->Device(), win->DeviceContext());

	//auto Il = ImageLoader::GetInstance();
	//auto str = Il->OpenLoadingDialog();

	m_tmp = new ShunLib::Texture(L"Image\\tile\\tile130.png");
	m_tmp2 = new ShunLib::Texture(L"Image\\tile\\tile1.png");

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\meiryo.ttc", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

	TileData data;
	data.canMove = true;
	data.encountRate = 40;
	data.enemyGroup = nullptr;
	data.texture = m_tmp;

	TileData data2;
	data2.canMove = false;
	data2.encountRate = 40;
	data2.enemyGroup = nullptr;
	data2.texture = m_tmp2;

	//win->CreateSecondWindow();

	int id = TileDataHolder::GetInstance()->AddData(&data);
	int id2 = TileDataHolder::GetInstance()->AddData(&data2);

	m_map = new Map();
	m_map->DisplayRange(Vec2(0.0f, 0.0f), Vec2(1200.0f, 800.0f));

	// SettingUI
	m_uiMenu = make_shared<UIMenuBar>(string("menu"));
	m_uiTileProperty = make_shared<UITileProperty>(string("Tile Property"));

	{
		m_uiMenu->SetMenuItemFunc("File", "Load");
		m_uiMenu->SetMenuItemFunc("File", "Save");

		m_uiMenu->SetMenuItemFunc("View", "TileWindow");
		m_uiMenu->SetMenuItemFunc("View", "TileProperty", [this]() {TilePropertyChangeActive(); });
		m_uiMenu->SetMenuItemFunc("View", "Map");
		
		m_uiMenu->SetMenuItemFunc("DataBase", "EnemyData");
		m_uiMenu->SetMenuItemFunc("DataBase", "TileData");
		
		m_uiMenu->SetMenuItemFunc("CreateMode", "MapCreate");
		m_uiMenu->SetMenuItemFunc("CreateMode", "EventCreate");
		
		m_uiMenu->SetMenuItemFunc("Scaling", "1/1");
		m_uiMenu->SetMenuItemFunc("Scaling", "1/2");
		m_uiMenu->SetMenuItemFunc("Scaling", "1/4");
		
		m_uiMenu->SetMenuItemFunc("DrawMode", "Pencil");
		
		m_uiMenu->SetMenuItemFunc("Game", "Play");
	}

	auto r= TileDataHolder::GetInstance();
	int id = r->AddData(&data);
	m_map = new Map();
	for (int i = 0; i < Map::HEIGHT; i++)
	{
		for (int j = 0; j < Map::WIDTH; j++)
		{
			m_map->SetTileId(id,i,j);
		}
	}

	int id = TileDataHolder::GetInstance()->AddData(&data);
	int id2 = TileDataHolder::GetInstance()->AddData(&data2);

	m_map = new Map();
	m_map->DisplayRange(Vec2(0.0f, 0.0f), Vec2(1200.0f, 800.0f));

	//プレイヤーの作成
	player = new Player();

	m_game = new Game();
}

//更新
void GameEditor::Update()
{
	auto edi = MapEditor::GetInstance();
	edi->Map(m_map);

	auto mouse = MouseManager::GetInstance();
	mouse->Update();

	// UIウインドウがアクティブでない時
	if (!ImGui::IsAnyWindowHovered()&& 
		!ImGui::IsAnyItemActive())
	{
		if (mouse->GetMouseButton(MouseButton::leftButton))
		{
			edi->Id(0);
			auto p = mouse->GetMousePosition();
			edi->ChangeTile(p);
		}
		else if (mouse->GetMouseButton(MouseButton::rightButton))
		{
			edi->Id(1);
			auto p = mouse->GetMousePosition();
			edi->ChangeTile(p);
		}
	}
	else if (mouse->GetMouseButtonDown(MouseButton::middleButton))
	{
		StartDebug();
	}
	//m_map->Update();

	//プレイヤーが先に進めるかどうか
	if (m_map->CanMoveSpecifiedDir(player->Getpos(),player->Getdirection()))
	{
		player->Move();
	}
}

//描画
void GameEditor::Render()
{
	auto mouse = MouseManager::GetInstance();
	auto win = ShunLib::Window::GetInstance();

	//描画対象をエディター用のウィンドウに戻す
	win->SetDrawingWindow(ShunLib::Window::EDITOR);

	ImGui_ImplDX11_NewFrame();

	ImGui::Text("scroll x : %.3f", m_map->Scroll()->m_x);
	ImGui::Text("scroll y : %.3f", m_map->Scroll()->m_y);

	m_uiMenu->DrawUpdate();
	m_uiTileProperty->DrawUpdate();

	m_map->Draw();

	// Rendering
	//この上に描画処理を書く
	ImGui::Render();

	//プレイヤーの描画
	player->Draw();
}

//終了
void GameEditor::Finalize()
{
	ImGui_ImplDX11_Shutdown();
	DELETE_POINTER(m_map);
	DELETE_POINTER(m_tmp);
	DELETE_POINTER(m_tmp2);
	DELETE_POINTER(player);
}

void GameEditor::UIChangeActive(UIBase & ui)
{
	ui.Active = !ui.Active;
}

/// <summary>
/// デバッグ開始
/// </summary>
void GameEditor::StartDebug()
{
	m_game->SetMap(m_map);
	ShunLib::Window::GetInstance()->SetApp(m_game, ShunLib::Window::WINDOW_TYPE::DEBUGGER);
	auto win = ShunLib::Window::GetInstance();

	//デバッグ用ウィンドウ作成
	win->CreateSecondWindow();

}