//************************************************/
//* @file  :Tile.cpp
//* @brief :マップタイル
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#include "Tile.h"
#include <SL_RandomNumber.h>

/// <summary>
/// マップタイルをリンクする
/// </summary>
void Tile::LinkTile(Tile ** map, int row, int column)
{
	for (int i = 0; i < column; i++)
	{
		for (int j = 0; j < row; j++)
		{
			map[column][row];
		}
	}
}

/// <summary>
/// エンカウントするかどうか
/// </summary>
/// <returns>エンカウントしたら true</returns>
bool Tile::IsEncount()
{
	ShunLib::RandomNumber rn;

	//0 ～ 100をランダムに取得
	int rate = rn(0, 100);

	//エンカウント率
	if (rate <= m_encountRate)
	{
		return true;
	}

	return false;
}

/// <summary>
/// 敵グループからランダムに取得
/// </summary>
Enemy * Tile::GetRandamEnemy()
{
	return nullptr;
}

/// <summary>
/// 指定方向のタイルに移動できるかどうか
/// </summary>
/// <param name="dir">方向</param>
/// <returns>移動可能 true</returns>
bool Tile::CanMoveSpecifiedDir(ShunLib::ConstantNumber::DIRECTION_2D dir)
{
	//指定方向のタイル
	Tile* tile = m_contactTile[dir];

	//タイルが無ければ進めない
	if (tile == nullptr)
	{
		return false;
	}

	return tile->CanMove();
}
