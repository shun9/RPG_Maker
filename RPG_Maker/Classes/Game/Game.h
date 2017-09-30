//************************************************/
//* @file  :Game.h
//* @brief :エディターで作成したゲーム
//* @date  :2017/09/29
//* @author:S.Katou
//************************************************/
#pragma once
#include "../AppBase/AppBase.h"
#include <SL_Vec2.h>

class Map;
class DebugMap;
class Player;

//ゲームクラス
//実行ボタンで作成
//エディターとは別のウィンドウに描画
class Game : public AppBase
{
private:
	DebugMap* m_map;
	Player* m_player;

	//スクロール量
	ShunLib::Vec2 m_scrollNum;

	//実行中かどうか
	bool m_isPlaying;

public:
	Game();
	~Game();

	//定番のやつ
	void Initialize()override;
	void Update    ()override;
	void Render    ()override;
	void Finalize  ()override;

	void SetMap(Map* map);

	void SetPlayer(Player* player);

	//実行中かどうか
	bool IsPlaying();
private:
	//スクロール量を制限
	void ClampScroll();

};