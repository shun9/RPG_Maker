//************************************************/
//* @file  :Game.cpp
//* @brief :エディターで作成したゲーム
//* @date  :2017/09/28
//* @author:S.Katou
//************************************************/
#include "Game.h"
#include "../../SL_Window.h"
#include "../Map/Map.h"
#include "../Player/Player.h"

Game::Game()
{
}

Game::~Game()
{

}

//初期化
void Game::Initialize()
{
	if (m_map != nullptr)
	{
		//マップをプレイヤーの初期位置分スクロール
		m_map->Scroll();
	}
}

//更新
void Game::Update()
{
	//プレイヤーの更新
	if (m_player != nullptr)
	{
		//プレイヤーが先に進めるかどうか
		if (m_map->CanMoveSpecifiedDir(m_player->Getpos(), m_player->Getdirection()) || m_player->Movestate())
		{
			m_player->Move();
		}

		m_player->Update();
	}

	//マップの更新
	if (m_map != nullptr)
	{
		m_map->Scroll(m_player->Getpos());
	}
}

//描画
void Game::Render()
{
	auto win = ShunLib::Window::GetInstance();

	//描画対象をデバッグ用のウィンドウに切り替える
	win->SetDrawingWindow(ShunLib::Window::DEBUGGER);

	if (m_player != nullptr)
	{
		m_player->Draw();
	}

	if (m_map != nullptr)
	{
		m_map->Draw();
	}

	//描画対象をエディター用のウィンドウに戻す
	win->SetDrawingWindow(ShunLib::Window::EDITOR);
}

//終了
void Game::Finalize()
{
}
