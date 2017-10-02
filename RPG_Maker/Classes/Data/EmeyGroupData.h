//************************************************/
//* @file  :EnemyGroupDataHolder.h
//* @brief :タイルの情報を保持する
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include "EnemyData.h"
#include <map>

// 敵グループの情報
struct EnemyGroupData :public Data {

	// 画面表示座標とEnemyDataのリスト
	std::vector<std::map<int, ShunLib::Vec2>> enemyList;
};
