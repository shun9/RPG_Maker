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

	//win->CreateSecondWindow();

	m_button = make_shared<ButtonBase>();
}

//更新
void GameEditor::Update()
{
}

//描画
void GameEditor::Render()
{
	ImGui_ImplDX11_NewFrame();
	
	m_button->Draw(Vector2(0.0f, 0.0f));

	// Rendering
	//この上に描画処理を書く
	ImGui::Render();
}

//終了
void GameEditor::Finalize()
{
	ImGui_ImplDX11_Shutdown();
}

/// <summary>
/// デバッグ開始
/// </summary>
void GameEditor::StartDebug()
{
	ShunLib::Window::GetInstance()->SetApp(m_game, ShunLib::Window::WINDOW_TYPE::DEBUGGER);
}