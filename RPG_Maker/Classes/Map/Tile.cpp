//************************************************/
//* @file  :Tile.cpp
//* @brief :マップタイル
//* @date  :2017/09/27
//* @author:S.Katou
//************************************************/
#include "Tile.h"
#include <SL_RandomNumber.h>
#include "../Data/DataBase.h"

//タイルの1辺の長さ
const float Tile::SIZE = 32.0f;

//何もないタイル
const int Tile::NONE = -1;

/// <summary>
/// 描画
/// </summary>
void Tile::Draw(const ShunLib::Vec2 & pos, const ShunLib::Vec2 & scale, RECT* rect)
{
	//情報が無ければ描画しない
	if (m_id == NONE)
	{
		return;
	}

	auto data = DB_Tile.GetData(m_id);

	if (data->texture != nullptr)
	{
		data->texture->Draw(pos, scale, rect);
	}
}
