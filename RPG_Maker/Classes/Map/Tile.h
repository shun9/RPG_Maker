//************************************************/
//* @file  :Tile.h
//* @brief :マップタイル
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_ConstantNumber.h>
#include <SL_Texture.h>
#include <SL_MacroConstants.h>

class TileData;

class Tile
{
public:
	//タイルの1辺の長さ
	static const float SIZE;

	//タイルを繋げる
	//ゲーム開始時に使用
	static void LinkTile(Tile** map,int row,int column);

private:
	int m_id;

public:
	Tile();
	~Tile();

	//描画
	void Draw(const ShunLib::Vec2& pos, const ShunLib::Vec2& scale);

	//エンカウントするかどうか
	//タイルの上に移動したときに使用
	bool IsEncount();

	////敵グループからランダムに取得
	//Enemy* GetRandamEnemy();

	////指定した方向に移動できるかどうか
	////タイルの上から移動しようとしたときに使用
	//bool CanMoveSpecifiedDir(ShunLib::ConstantNumber::DIRECTION_2D);

	////指定方向のタイルの情報を設定
	//void SetContactTile(ShunLib::ConstantNumber::DIRECTION_2D,Tile*);


	////Get & Set
	////エンカウント率
	//int EncountRate() { return m_encountRate; }
	//void EncountRate(int rate) {
	//	m_encountRate = rate;
	//	if (m_encountRate > 100){
	//		m_encountRate = 100;
	//	}
	//}

	////移動可能か
	//bool CanMove() { return m_canMove; }
	//void CanMove(bool isWalk) { m_canMove = isWalk; }

	////画像
	//void Texture(ShunLib::Texture* tex) { m_texture = tex; }
};
