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

class Enemy;

// 敵の情報
struct EnemyGroupAloneData :public Data{
	int Id;
	ShunLib::Vec2 Pos;
};