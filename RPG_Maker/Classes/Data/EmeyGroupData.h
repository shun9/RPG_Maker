//************************************************/
//* @file  :EnemyGroupDataHolder.h
//* @brief :タイルの情報を保持する
//* @date  :2017/09/26
//* @author:K.Yamamoto
//************************************************/
#pragma once
#include "EnemyGroupAloneData.h"
#include <memory>
#include "DataHolder.h"

static const int GROUP_ENEMY_MAX = 3;

// 敵グループの情報
struct EnemyGroupData :public Data {

	// 画面表示座標とEnemyDataのリスト
	DataHolder<EnemyGroupAloneData> enemyList;
};