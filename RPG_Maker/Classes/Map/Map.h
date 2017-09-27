//************************************************/
//* @file  :Map.h
//* @brief :マップ（タイルの集合体）
//* @date  :2017/09/26
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
	ShunLib::Vec2 m_scrollNum;

public:
	Map();
	~Map();

	void SetTileId(int id, int x, int y) { m_map[y][x].Id(id); }
	//描画
	void Draw();

	/// <summary>
	/// 指定方向のタイルに移動できるかどうか
	/// </summary>
	/// <param name="dir">方向</param>
	/// <returns>移動可能 true</returns>
	bool CanMoveSpecifiedDir(Vec2 pos,DIRECTION_2D dir);

	//エンカウントするかどうか
	//タイルの上に移動したときに使用
	bool IsEncount();

	//敵グループからランダムに取得
	Enemy* GetRandamEnemy();

	//指定方向のタイルの情報を設定
	void SetContactTile(ShunLib::ConstantNumber::DIRECTION_2D, Tile*);


	//Get & Set
	//エンカウント率
	int EncountRate();
	void EncountRate(int rate);

	//移動可能か
	bool CanMove();
	void CanMove(bool isWalk);

	//画像
	void Texture(ShunLib::Texture* tex);

};