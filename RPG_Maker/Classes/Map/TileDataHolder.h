//************************************************/
//* @file  :TileDataHolder.h
//* @brief :タイルの情報を保持する
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <memory>
#include <SL_Singleton.h>
#include <SL_Texture.h>
#include <SL_ConstantNumber.h>
#include "Tile.h"

class Enemy;
class Tile;

//タイルの情報
struct TileData {
	//タイル画像
	ShunLib::Texture* texture;

	//敵のエンカウント率
	int encountRate;

	//出現する敵の構成一覧
	Enemy** enemyGroup;

	//プレイヤーが歩くことが出来るかどうか
	//歩けるなら true
	bool canMove;
};


//タイルの情報を保持する
class TileDataHolder:public ShunLib::Singleton<TileDataHolder>
{
	friend ShunLib::Singleton<TileDataHolder>;

private:
	//タイル種類一覧
	std::vector<TileData> m_tileData;

public:
	TileDataHolder() {}
	~TileDataHolder() {}

	//データを追加する
	int AddData(TileData* data) {
		m_tileData.push_back(*data);
		return (int)(m_tileData.size()) - 1;
	}

	//データ情報を返す
	//無ければnullptr
	TileData* GetData(int id) {
		if (id > (int)(m_tileData.size()) - 1)return nullptr;
		if (id == Tile::NONE)return nullptr;
		return	&m_tileData[id];
	}

	// 全データ取得
	const std::vector<TileData>& GetTileList() {
		return m_tileData;
	}
};
