//************************************************/
//* @file  :GameEditor.cpp
//* @brief :エディター
//* @date  :2017/09/28
//* @author:S.Katou
//************************************************/
#include <Windows.h>
#include <string>
#include <SL_Texture.h>
#include <SL_KeyManager.h>

#include "GameEditor.h"
#include "../Game/Game.h"
#include "../../SL_Window.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx11.h"

#include "../Data/DataBase.h"
#include "../Map/MapEditor.h"
#include "../../Utils/MouseManager.h"
#include "../../Utils/ImageLoader.h"
#include "../../Utils/ServiceManager.h"
#include "../../Utils/GameSaver.h"
#include "../../Utils/GameLoader.h"

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

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\meiryo.ttc", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	m_map = new Map();
	m_map->DisplayRange(Vec2(350.0f, 66.0f), Vec2(win->Width(), win->Height()));

	//張り替えるマップを設定
	auto edi = MapEditor::GetInstance();
	edi->Map(m_map);

	//プレイヤーの作成
	player = new Player();

	m_game = new Game();

	auto loader = GameLoader::GetInstance();
	loader->LoadGame(this);

	// SettingUI
	m_uiMenu = make_unique<UIMenuBar>(string("menu"));
	m_uiTileProperty = make_unique<UITileProperty>(string("Tile Property"), MapEditor::GetInstance()->Id());
	m_uiTileCanvas = make_unique<UITileCanvas>(string("Tile Canvas"));
	m_uiEnemyTable = make_unique<UIEnemyTable>(string("Enemy DataBase"));
	EnemyTableChangeActive();

	{
		m_uiMenu->SetMenuItemFunc("File ", "Map Load");
		m_uiMenu->SetMenuItemFunc("File ", "Map Save");
		m_uiMenu->SetMenuItemFunc("File ", "Tile Load", [this]() {SelectedCreateTileData(); });
		m_uiMenu->SetMenuItemFunc("File ", "Tile Save");

		m_uiMenu->SetMenuItemFunc("View ", "TileWindow");
		m_uiMenu->SetMenuItemFunc("View ", "TileProperty", [this]() {TilePropertyChangeActive(); });
		m_uiMenu->SetMenuItemFunc("View ", "Map  ");

		m_uiMenu->SetMenuItemFunc("DataBase", "EnemyData", [this]() {EnemyTableChangeActive(); });
		m_uiMenu->SetMenuItemFunc("DataBase", "TileData");

		m_uiMenu->SetMenuItemFunc("CreateMode", "MapCreate");
		m_uiMenu->SetMenuItemFunc("CreateMode", "EventCreate");

		m_uiMenu->SetMenuItemFunc("Scaling", "1/1");
		m_uiMenu->SetMenuItemFunc("Scaling", "1/2");
		m_uiMenu->SetMenuItemFunc("Scaling", "1/4");

		m_uiMenu->SetMenuItemFunc("DrawMode", "Pencil");

		m_uiMenu->SetMenuItemFunc("Game ", "Play");
	}
}

//更新
void GameEditor::Update()
{
	auto edi = MapEditor::GetInstance();
	auto mouse = MouseManager::GetInstance();
	mouse->Update();

	// TIleの設定
	m_uiTileCanvas->SelectTile();
	m_uiTileProperty->IdObservation();

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
	m_map->Update();

	PlayerScroll();
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

	ImGui::Text("mouse x : %.3f", mouse->GetMousePosition().m_x);
	ImGui::Text("mouse y : %.3f", mouse->GetMousePosition().m_y);

	ImGui::Text("tile list : %d", DB_Tile.GetContainerSize());

	m_map->Draw();

	//プレイヤーの描画
	player->Draw();

	m_uiMenu->DrawUpdate();
	m_uiTileProperty->DrawUpdate();
	m_uiTileCanvas->DrawUpdate();
	m_uiEnemyTable->DrawUpdate();

	// Rendering
	//この上に描画処理を書く
	ImGui::Render();
}

//終了
void GameEditor::Finalize()
{
	auto saver = GameSaver::GetInstance();
	saver->SaveGame(this);

	ImGui_ImplDX11_Shutdown();
	DELETE_POINTER(m_map);
	DELETE_POINTER(player);
}

void GameEditor::UIChangeActive(UIBase & ui)
{
	ui.Active = !ui.Active;
}

void GameEditor::SelectedCreateTileData()
{
	auto Il = ImageLoader::GetInstance();
	auto str = Il->OpenLoadingDialog();

	if (str.c_str() != wstring(L"Image\\"))
	{
		DB_Tile.AddData(SVC_Tile->CreateTileData(str));
	}
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

/// <summary>
/// プレイヤーをスクロールと同期させる
/// </summary>
void GameEditor::PlayerScroll()
{
	Vec2 playerPos;
	Vec2 tmp = player->PosOnMap();
	m_map->ConvertScreenPos((int)tmp.m_x, (int)tmp.m_y, &playerPos);
	player->Setpos(playerPos);
}
