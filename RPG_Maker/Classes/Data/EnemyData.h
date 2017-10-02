//************************************************/
//* @file  :EnemyDataHolder.h
//* @brief :タイルの情報を保持する
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <memory>
#include <SL_Texture.h>
#include "Data.h"
#include "../Battle/Action.h"

class Enemy;

// 敵の情報
struct EnemyData :public Data{
public:
	enum Param {
		HP,
		MP,
		ATK,
		DEF,
		DEX,
		EVA,
		EXP,
		MONEY,
		length
	};

	// 敵画像
	std::unique_ptr<ShunLib::Texture> Texture;

	std::vector<int> Param;
};