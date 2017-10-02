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

class Enemy;

// “G‚Ìî•ñ
struct EnemyGroupAloneData :public Data{
	int Id;
	ShunLib::Vec2 Pos;
};