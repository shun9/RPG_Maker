//************************************************/
//* @file  :Map.h
//* @brief :マップ（タイルの集合体）
//* @date  :2017/09/27
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <SL_ConstantNumber.h>
#include <SL_Texture.h>
#include <SL_MacroConstants.h>
#include "Tile.h"

class Map
{
	using Vec2 = ShunLib::Vec2;
	using DIRECTION_2D = ShunLib::ConstantNumber::DIRECTION_2D;

public:
	//マップサイズ
	static const int WIDTH;
	static const int HEIGHT;

private:
	std::vector<std::vector<Tile>>m_map;

	//スクロールした値
	Vec2 m_scrollNum;

	//表示位置
	Vec2 m_firstPos;
	Vec2 m_displaySize;

public:
	Map();
	~Map();

	//キー入力でスクロールする
	void Update();

	//スクロールした値
	void Scroll(const Vec2& num) { m_scrollNum = num; }
	ShunLib::Vec2* Scroll() { return &m_scrollNum; }

	//タイルをセットする
	void SetTileId(int id, int x, int y);

	//描画
	void Draw();

	//スクリーン上の座標をマップの座標に変換する
	void ConvertMapPos(const Vec2& pos, int* bufX, int* bufY);

	/// 指定方向のタイルに移動できるかどうか
	bool CanMoveSpecifiedDir(Vec2 pos,DIRECTION_2D dir);

	////エンカウントするかどうか
	////タイルの上に移動したときに使用
	//bool IsEncount();

	////敵グループからランダムに取得
	//Enemy* GetRandamEnemy();

	void DisplayRange(const Vec2& leftTop, const Vec2& rightBottom) {
		m_firstPos = leftTop;
		m_displaySize = rightBottom;
	};

private:
	bool IsInRangeTile(int x, int y, int dirTile[]);

	void DrawEdgeTile(int x,int y,float edge[], DIRECTION_2D dir,int dirTile[]);

	void ClampScroll();
};