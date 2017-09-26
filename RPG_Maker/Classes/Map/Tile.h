//************************************************/
//* @file  :Tile.h
//* @brief :マップタイル
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once

#include <SL_ConstantNumber.h>

class Enemy;

class Tile
{
	//タイルを繋げる
	//ゲーム開始時に使用
	static void LinkTile(Tile** map,int row,int column);

private:
	//敵のエンカウント率
	int m_encountRate;

	//出現する敵の構成一覧
	Enemy** m_enemyGroup;

	//接しているタイル　上下左右
	Tile* m_contactTile[ShunLib::ConstantNumber::DIRECTION_2D::num];

	//プレイヤーが歩くことが出来るかどうか
	//歩けるなら true
	bool m_canMove;

public:
	Tile() {}
	~Tile() {}

	//エンカウントするかどうか
	//タイルの上に移動したときに使用
	bool IsEncount();

	//敵グループからランダムに取得
	Enemy* GetRandamEnemy();

	//指定した方向に移動できるかどうか
	//タイルの上から移動しようとしたときに使用
	bool CanMoveSpecifiedDir(ShunLib::ConstantNumber::DIRECTION_2D);

	//指定方向のタイルの情報を設定
	void SetContactTile(ShunLib::ConstantNumber::DIRECTION_2D,Tile*);

	//Get & Set
	int EncountRate() { return m_encountRate; }
	void EncountRate(int rate) {
		m_encountRate = rate;
		if (m_encountRate > 100){
			m_encountRate = 100;
		}
	}

	bool CanMove() { return m_canMove; }
	void CanMove(bool isWalk) { m_canMove = isWalk; }
};
