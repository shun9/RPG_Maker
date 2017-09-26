//************************************************/
//* @file  :Tile.cpp
//* @brief :マップタイル
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#include "Tile.h"
#include <SL_RandomNumber.h>

//タイルの1辺の長さ
const float Tile::SIZE = 32.0f;

/// <summary>
/// マップタイルをリンクする
/// ゲーム開始時に使用
/// </summary>
void Tile::LinkTile(Tile ** map, int row, int column)
{
	using DIRECTION_2D = ShunLib::ConstantNumber::DIRECTION_2D;

	//縦
	for (int i = 0; i < column; i++)
	{
		//横
		for (int j = 0; j < row; j++)
		{
			//上
			if (i == 0)         map[i][j].SetContactTile(DIRECTION_2D::TOP, nullptr);
			else                map[i][j].SetContactTile(DIRECTION_2D::TOP, &map[i +1][j]);

			//下
			if (i == column - 1)map[i][j].SetContactTile(DIRECTION_2D::BOTTOM, nullptr);
			else                map[i][j].SetContactTile(DIRECTION_2D::BOTTOM, &map[i + 1][j]);

			//右
			if (j == 0)         map[i][j].SetContactTile(DIRECTION_2D::RIGHT, nullptr);
			else                map[i][j].SetContactTile(DIRECTION_2D::RIGHT, &map[i][j + 1]);

			//左
			if (j == row - 1)   map[i][j].SetContactTile(DIRECTION_2D::LEFT, nullptr);
			else                map[i][j].SetContactTile(DIRECTION_2D::LEFT, &map[i][j - 1]);
		}
	}
}


Tile::Tile() :
	m_texture(nullptr)
{
	m_texture = new ShunLib::Texture(L"Image\\brick.png");
}

Tile::~Tile()
{
	DELETE_POINTER(m_texture);
}

/// <summary>
/// 描画
/// </summary>
void Tile::Draw(const ShunLib::Vec2 & pos, const ShunLib::Vec2& scale)
{
	if (m_texture != nullptr)
	{
		m_texture->Draw(pos, scale);
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


/// <summary>
/// 指定方向のタイルの情報を設定
/// </summary>
void Tile::SetContactTile(ShunLib::ConstantNumber::DIRECTION_2D dir, Tile* tile)
{
	m_contactTile[dir] = tile;
}
