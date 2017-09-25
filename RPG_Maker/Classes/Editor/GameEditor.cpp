//************************************************/
//* @file  :GameEditor.cpp
//* @brief :エディター
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#include "GameEditor.h"
#include "../Game/Game.h"

GameEditor::GameEditor()
{
}

GameEditor::~GameEditor()
{
}

//初期化
void GameEditor::Initialize()
{
}

//更新
void GameEditor::Update()
{
}

//描画
void GameEditor::Render()
{
}

//終了
void GameEditor::Finalize()
{
}

/// <summary>
/// デバッグ開始
/// </summary>
void GameEditor::StartDebug()
{
	ShunLib::Window::GetInstance()->SetApp(m_game, ShunLib::Window::WINDOW_TYPE::DEBUGER);
}