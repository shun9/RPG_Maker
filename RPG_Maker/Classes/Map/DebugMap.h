//************************************************/
//* @file  :DebugMap.h
//* @brief :デバッグ実行用マップ（タイルの集合体）
//* @date  :2017/09/30
//* @author:S.Katou
//************************************************/
#pragma once
#include "Map.h"

class DebugMap :public Map
{
public:
	DebugMap() {}
	~DebugMap() {}

	//マップ座標をスクリーン座標に変換する
	void DebugConvertScreenPos(int x, int y, Vec2* buf);

	//スクリーン上の座標をマップの座標に変換する
	void DebugConvertMapPos(const Vec2& pos, int* bufX, int* bufY);

	//指定方向に進めるかどうか
	bool DebugCanMoveSpecifiedDir(Vec2 pos, DIRECTION_2D dir);

};