//************************************************/
//* @file  :Game.h
//* @brief :エディターで作成したゲーム
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include "../AppBase/AppBase.h"

class Map;
class Player;

//ゲームクラス
//実行ボタンで作成
//エディターとは別のウィンドウに描画
class Game : public AppBase
{
private:
	Map* m_map;
	Player* m_player;

public:
	Game();
	~Game();

	//定番のやつ
	void Initialize()override;
	void Update    ()override;
	void Render    ()override;
	void Finalize  ()override;

	void SetMap(Map* map) {
		m_map = map;
	}
	void Player(Player* player) { m_player = player; }
private:

};