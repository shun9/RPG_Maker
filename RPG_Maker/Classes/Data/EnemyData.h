//************************************************/
//* @file  :EnemyDataHolder.h
//* @brief :ƒ^ƒCƒ‹‚Ìî•ñ‚ğ•Û‚·‚é
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

// “G‚Ìî•ñ
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

	// “G‰æ‘œ
	std::unique_ptr<ShunLib::Texture> Texture;

	std::vector<int> Param;
};