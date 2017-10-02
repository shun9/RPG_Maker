//************************************************/
//* @file  :DebugMap.cpp
//* @brief :デバッグ実行用マップ（タイルの集合体）
//* @date  :2017/10/01
//* @author:S.Katou
//************************************************/
#include "DebugMap.h"
#include <SL_RandomNumber.h>
#include "../Data/DataBase.h"

void DebugMap::DebugConvertScreenPos(int x, int y, Vec2 * buf)
{
	buf->m_x = x * Tile::SIZE;
	buf->m_y = y * Tile::SIZE;
}

void DebugMap::DebugConvertMapPos(const Vec2& pos, int * bufX, int * bufY)
{
	*bufX = (int)(pos.m_x / Tile::SIZE);
	*bufY = (int)(pos.m_y / Tile::SIZE);
}

bool DebugMap::DebugCanMoveSpecifiedDir(const Vec2& pos, DIRECTION_2D dir)
{
	const auto& holder = DB_Tile;

	//タイル座標取得
	int x, y;
	this->DebugConvertMapPos(pos, &x, &y);

	//指定方向のタイル
	switch (dir)
	{
	case ShunLib::ConstantNumber::TOP:
		y--;
		break;

	case ShunLib::ConstantNumber::BOTTOM:
		y++;
		break;

	case ShunLib::ConstantNumber::RIGHT:
		x++;
		break;

	case ShunLib::ConstantNumber::LEFT:
		x--;
		break;

	default:
		return false;
	}

	//マップ外なら進めない
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
	{
		return false;
	}

	int id = m_map[y][x].Id();

	auto data = holder.GetData(id);

	//タイルが無ければ進めない
	if (data == nullptr)
	{
		return false;
	}

	return data->canMove;
}

/// <summary>
/// エンカウントするかどうか
/// </summary>
/// <param name="pos">ワールド座標</param>
/// <returns>エンカウントしたらtrue</returns>
bool DebugMap::IsEncount(const Vec2& pos)
{
	const auto& holder = DB_Tile;

	//マップ上の座標を取得
	int x, y;
	this->DebugConvertMapPos(pos, &x, &y);

	//タイル情報を取得
	int id = m_map[y][x].Id();
	auto data = holder.GetData(id);

	//乱数取得
	ShunLib::RandomNumber rn;
	int rate = rn(0, 99);

	//エンカウントするかどうか
	if (data->encountRate > rate)
	{
		return true;
	}

	return false;
}

int DebugMap::GetRandamEnemy(const Vec2 & pos)
{
	const auto& holder = DB_Tile;

	//マップ上の座標を取得
	int x, y;
	this->DebugConvertMapPos(pos, &x, &y);

	//タイル情報を取得
	int id = m_map[y][x].Id();
	auto data = holder.GetData(id);
	int group = (int)data->enemyGroup.size();

	if (group > 0)
	{
		//乱数取得
		ShunLib::RandomNumber rn;
		int rate = rn(0, group - 1);
		return rate;
	}
	return -1;
}
