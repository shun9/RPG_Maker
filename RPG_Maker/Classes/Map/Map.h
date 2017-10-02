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
protected:
	using Vec2 = ShunLib::Vec2;
	using DIRECTION_2D = ShunLib::ConstantNumber::DIRECTION_2D;

public:
	//マップサイズ
	static const int WIDTH;
	static const int HEIGHT;

protected:
	// グリッド背景
	std::unique_ptr<ShunLib::Texture> m_bgTile;

	std::vector<std::vector<Tile>>m_map;

	//スクロールした値
	Vec2 m_scrollNum;

	//表示位置
	Vec2 m_firstPos;
	Vec2 m_displaySize;

	//選択されているID
	int m_choiceId;

	//強調するの際使用する画像のデータ
	std::unique_ptr<ShunLib::Texture> m_emphasisMap;

public:
	Map();
	virtual ~Map();

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

	//マップ座標をスクリーン座標に変換する
	void ConvertScreenPos(int X, int Y, Vec2* buf);

	/// 指定方向のタイルに移動できるかどうか
	bool CanMoveSpecifiedDir(Vec2 pos,DIRECTION_2D dir);

	std::vector<std::vector<Tile>>* GetMapData() { return &m_map; }

	void DisplayRange(const Vec2& leftTop, const Vec2& rightBottom) {
		m_firstPos = leftTop;
		m_displaySize = rightBottom;
	};

	//選択されているIDのセット
	void SetChoiseId(int id) { m_choiceId = id; }

	//選択されているマップの協調
	void EmphasisMapDraw(int id, const ShunLib::Vec2& pos, const ShunLib::Vec2& scale, RECT* rect = nullptr);

private:
	bool IsInRangeTile(int x, int y, int dirTile[]);

	void DrawEdgeTile(int x,int y,float edge[], DIRECTION_2D dir,int dirTile[]);

	virtual void ClampScroll();

public:
	void operator=(const Map& m);

};