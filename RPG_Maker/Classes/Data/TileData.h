//************************************************/
//* @file  :TileDataHolder.h
//* @brief :タイルの情報を保持する
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <memory>
#include <SL_Texture.h>
#include "Data.h"

//タイルの情報
struct TileData :public Data{
	//タイル画像
	std::unique_ptr<ShunLib::Texture> texture;

	//敵のエンカウント率
	int encountRate;

	//出現する敵の構成一覧 ID
	std::vector<int> enemyGroup;

	//プレイヤーが歩くことが出来るかどうか
	//歩けるなら true
	bool canMove;
};