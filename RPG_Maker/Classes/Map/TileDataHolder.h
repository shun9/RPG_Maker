//************************************************/
//* @file  :TileDataHolder.h
//* @brief :タイルの情報を保持する
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include "../Map/Tile.h"

class Enemy;

//タイルの情報
struct TileData {
	//タイル画像
	ShunLib::Texture* m_texture;

	//敵のエンカウント率
	int m_encountRate;

	//出現する敵の構成一覧
	Enemy** m_enemyGroup;

	//接しているタイル　上下左右
	Tile* m_contactTile[ShunLib::ConstantNumber::DIRECTION_2D::num];

	//プレイヤーが歩くことが出来るかどうか
	//歩けるなら true
	bool m_canMove;
};

//タイルの情報を保持する
class TileDataHolder
{
private:
	//タイル一覧
	std::vector<TileData*> m_tileData;

public:
	TileDataHolder() {}
	~TileDataHolder() {}

	TileData* TileData(int id) { return m_tileData[id]; }
};
