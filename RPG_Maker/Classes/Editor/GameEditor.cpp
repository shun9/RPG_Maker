//************************************************/
//* @file  :GameEditor.cpp
//* @brief :エディター
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#include "GameEditor.h"

#include <SL_Texture.h>

#include "../Game/Game.h"
#include "../../SL_Window.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx11.h"
#include "../UI/Editor/UIWindow.h"

#include <string>

#include "../../Utils/MouseManager.h"
#include "../Map/TileDataHolder.h"
using namespace std;

GameEditor::GameEditor()
{

}

GameEditor::~GameEditor()
{

}

//初期化
void GameEditor::Initialize()
{
	auto win = ShunLib::Window::GetInstance();
	ShunLib::Texture::SetDevice(win->Device(), win->DeviceContext());
	auto hw = win->WindouHandle(ShunLib::Window::EDITOR);
	ImGui_ImplDX11_Init(hw, win->Device(), win->DeviceContext());
	m_tmp = new ShunLib::Texture(L"Image\\brick.png");

	TileData data;
	data.canMove = true;
	data.encountRate = 40;
	data.enemyGroup = nullptr;
	data.texture= m_tmp;

	//win->CreateSecondWindow();

	m_button = make_shared<UIWindow>(string("tab"),Vector2(330.0f,100.0f));
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

	//win->CreateSecondWindow();
}

//更新
void GameEditor::Update()
{
	auto mouse = MouseManager::GetInstance();
	mouse->Update();
	if (mouse->GetMouseButton(MouseButton::leftButton))
	{
		auto p=mouse->GetMousePosition();
	}
}

//描画
void GameEditor::Render()
{
	auto mouse = MouseManager::GetInstance();
	auto win = ShunLib::Window::GetInstance();

	ImGui_ImplDX11_NewFrame();
	
	m_button->DrawUpdate();


	m_map->Draw();

	// Rendering
	//この上に描画処理を書く
	ImGui::Render();
}

//終了
void GameEditor::Finalize()
{
	ImGui_ImplDX11_Shutdown();
	DELETE_POINTER(m_map);
	DELETE_POINTER(m_tmp);
}

/// <summary>
/// デバッグ開始
/// </summary>
void GameEditor::StartDebug()
{
	ShunLib::Window::GetInstance()->SetApp(m_game, ShunLib::Window::WINDOW_TYPE::DEBUGGER);
}