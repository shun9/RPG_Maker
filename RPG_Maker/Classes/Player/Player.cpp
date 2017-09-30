//************************************************/
//* @file  :Palyer.cpp
//* @brief :プレイヤー
//* @date  :2017/09/27
//* @author:Y.mano
//************************************************/
#include "Player.h"
#include <SL_KeyManager.h>
#include <SL_Texture.h>

using namespace DirectX;
using namespace ShunLib;

Player::Player()
{
	player = new ShunLib::Texture(L"Image\\charcter.png");

	//ポジションの初期化
	m_posOnMap = Vec2(0, 0);
	m_scrollNum = Vec2(0, 0);

	//ポジションの初期化
	pos = Vec2(0.0, 0.0);

	//画像率の初期化
	scale = Vec2(1.0, 1.0);

	//描画矩形
	rect = { 0, 0, 32, 32 };

	//カウントの初期化
	count = 0;

	//移動状態
	state = false;

	//アニメカウントの初期化
	animecount = 0;
}

Player::~Player()
{
}

void Player::Update()
{
	if (state == true)
	{
		count += SPEED;
	}
	if (count == TROUT)
	{
		count = 0;
		state = false;
	}

	if (animecount == 32)
	{
		animecount = 0;
	}

}


/// <summary>
/// 移動
/// </summary>
void Player::Move()
{

	if (KeyManager::GetInstance()->IsPushed(KeyManager::KEY_CODE::UP) && state==false || dir == ConstantNumber::TOP && state)
	{
		state = true;
		animecount += SPEED;
		pos.m_y = pos.m_y - SPEED;
	}
	else if (KeyManager::GetInstance()->IsPushed(KeyManager::KEY_CODE::DOWN) && state == false || dir == ConstantNumber::BOTTOM && state)
	{
		state = true;
		animecount += SPEED;
		pos.m_y = pos.m_y + SPEED;
	}
	else if(KeyManager::GetInstance()->IsPushed(KeyManager::KEY_CODE::RIGHT) && state == false || dir == ConstantNumber::RIGHT && state)
	{
		state = true;
		animecount += SPEED;
		pos.m_x = pos.m_x + SPEED;
	}
	else if (KeyManager::GetInstance()->IsPushed(KeyManager::KEY_CODE::LEFT) && state == false || dir == ConstantNumber::LEFT && state)
	{
		state = true;
		animecount += SPEED;
		pos.m_x = pos.m_x - SPEED;
	}
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	//向きを所得して描画
	switch (dir)
	{
	case ShunLib::ConstantNumber::TOP:
		if (animecount < 8)
		{
			rect = { 0, 32, 32, 32 * 2 };
			break;
		}
		else if (animecount < 16)
		{
			rect = { 32, 32, 32 * 2, 32 * 2 };
			break;
		}
		else if (animecount < 24)
		{
			rect = { 32 * 2, 32, 32 * 3, 32 * 2 };
			break;
		}
		else
		{
			rect = { 32 * 3, 32, 32 * 4, 32 * 2 };
			break;
		}
	case ShunLib::ConstantNumber::BOTTOM:
		if (animecount < 8)
		{
			rect = { 0, 0, 32, 32 };
			break;
		}
		else if (animecount < 16)
		{
			rect = { 32, 0, 32 * 2, 32 };
			break;
		}
		else if (animecount < 24)
		{
			rect = { 32 * 2, 0, 32 * 3, 32 };
			break;
		}
		else
		{
			rect = { 32 * 3, 0, 32 * 4, 32 };
			break;
		}
	case ShunLib::ConstantNumber::RIGHT:
		if (animecount < 8)
		{
			rect = { 0, 32 * 3, 32, 32 * 4 };
			break;
		}
		else if (animecount < 16)
		{
			rect = { 32, 32 * 3, 32 * 2, 32 * 4 };
			break;
		}
		else if (animecount < 24)
		{
			rect = { 32 * 2, 32 * 3, 32 * 3, 32 * 4 };
			break;
		}
		else
		{
			rect = { 32 * 3, 32 * 3, 32 * 4, 32 * 4 };
			break;
		}
	case ShunLib::ConstantNumber::LEFT:
		if (animecount < 8)
		{
			rect = { 0, 32 * 2, 32, 32 * 3 };
			break;
		}
		else if (animecount < 16)
		{
			rect = { 32, 32 * 2, 32 * 2, 32 * 3 };
			break;
		}
		else if (animecount < 24)
		{
			rect = { 32 * 2, 32 * 2, 32 * 3, 32 * 3 };
			break;
		}
		else
		{
			rect = { 32 * 3, 32 * 2, 32 * 4, 32 * 3 };
			break;
		}
	default:
		break;
	}
	player->Draw(pos-m_scrollNum, scale, &rect);
}

/// <summary>
/// 移動の状態の所得
/// </summary>
/// <returns>カウント</returns>
bool Player::Movestate()
{
	return state;
}

/// <summary>
/// 座標の所得
/// </summary>
/// <returns>座標</returns>
ShunLib::Vec2 Player::Getpos()
{
	return pos;
}

/// <summary>
/// 座標の設定
/// </summary>
/// <param name="pos">座標</param>
void Player::Setpos(const ShunLib::Vec2& pos)
{
	this->pos = pos;
}

/// <summary>
/// 向きの所得
/// </summary>
/// <returns>向き</returns>
ShunLib::ConstantNumber::DIRECTION_2D Player::Getdirection()
{
	if (state == false)
	{
		if (KeyManager::GetInstance()->IsPushed(KeyManager::KEY_CODE::UP))
		{
			dir = ConstantNumber::TOP;
		}
		else if (KeyManager::GetInstance()->IsPushed(KeyManager::KEY_CODE::DOWN))
		{
			dir = ConstantNumber::BOTTOM;
		}
		else if (KeyManager::GetInstance()->IsPushed(KeyManager::KEY_CODE::RIGHT))
		{
			dir = ConstantNumber::RIGHT;
		}
		else if (KeyManager::GetInstance()->IsPushed(KeyManager::KEY_CODE::LEFT))
		{
			dir = ConstantNumber::LEFT;
		}
	}

	return dir;
}

void Player::operator=(const Player& p)
{
	//マップ座標上の位置
	this->m_posOnMap = p.m_posOnMap;

	//x座標,y座標
	this->pos = p.pos;

	//拡大率
	this->scale = p.scale;

	//向き
	this->dir = p.dir;

	//カウント
	this->count = p.count;

	//移動の状態
	this->state = p.state;

	//アニメカウント
	this->animecount = p.animecount;
}
