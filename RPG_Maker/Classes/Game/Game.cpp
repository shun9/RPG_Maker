//************************************************/
//* @file  :Game.cpp
//* @brief :エディターで作成したゲーム
//* @date  :2017/09/28
//* @author:S.Katou
//************************************************/
#include "Game.h"
#include <SL_MacroConstants.h>
#include "../../SL_Window.h"
#include "../Map/Map.h"
#include "../Player/Player.h"

Game::Game():
	m_isPlaying(false)
{
	m_map = new Map();
	m_player = new Player();
}

Game::~Game()
{
	DELETE_POINTER(m_map);
	DELETE_POINTER(m_player);
}

//初期化
void Game::Initialize()
{
	if (m_map != nullptr)
	{
		//マップをプレイヤーの初期位置分スクロール
		m_map->Scroll();
	}

	m_isPlaying = true;
}

//更新
void Game::Update()
{
	//デバッグウィンドウがアクティブでない場合更新しない
	auto win = ShunLib::Window::GetInstance();
	if (GetActiveWindow() != win->WindouHandle(ShunLib::Window::WINDOW_TYPE::DEBUGGER))
	{
		return;
	}

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
		//m_map->Scroll(m_player->Getpos());
	}
}

//描画
void Game::Render()
{
	auto win = ShunLib::Window::GetInstance();

	//描画対象をデバッグ用のウィンドウに切り替える
	win->SetDrawingWindow(ShunLib::Window::DEBUGGER);

	if (m_map != nullptr)
	{
		m_map->Draw();
	}

	if (m_player != nullptr)
	{
		m_player->Draw();
	}


	//描画対象をエディター用のウィンドウに戻す
	win->SetDrawingWindow(ShunLib::Window::EDITOR);
}

//終了
void Game::Finalize()
{
	m_isPlaying = false;
}


void Game::SetMap(Map* map)
{
	(*m_map) = (*map);
}

void Game::SetPlayer(Player * player)
{

	(*m_player) = (*player);
}

/// <summary>
/// 実行中かどうか
/// </summary>
bool Game::IsPlaying()
{
	return m_isPlaying;
}
