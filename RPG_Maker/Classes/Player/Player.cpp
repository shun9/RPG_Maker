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
	pos = Vec2(160.0, 160.0);

	//画像率の初期化
	scale = Vec2(1.0, 1.0);

	//描画矩形
	rect = { 0, 0, 32, 32 };

	//カウントの初期化
	count = 0;

	//移動状態
	state = false;
}

Player::~Player()
{
}

void Player::Update()
{
	if (state == true)
	{
		count++;
	}
	if (count == TROUT)
	{
		count = 0;
		state = false;
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
		pos.m_y = pos.m_y - SPEED;
	}
	else if (KeyManager::GetInstance()->IsPushed(KeyManager::KEY_CODE::DOWN) && state == false || dir == ConstantNumber::BOTTOM && state)
	{
		state = true;
		pos.m_y = pos.m_y + SPEED;
	}
	else if(KeyManager::GetInstance()->IsPushed(KeyManager::KEY_CODE::RIGHT) && state == false || dir == ConstantNumber::RIGHT && state)
	{
		state = true;
		pos.m_x = pos.m_x + SPEED;
	}
	else if (KeyManager::GetInstance()->IsPushed(KeyManager::KEY_CODE::LEFT) && state == false || dir == ConstantNumber::LEFT && state)
	{
		state = true;
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
		rect = { 0, 32, 32, 32 * 2 };
		break;
	case ShunLib::ConstantNumber::BOTTOM:
		rect = { 0, 0, 32, 32 };
		break;
	case ShunLib::ConstantNumber::RIGHT:
		rect = { 0, 32 * 3, 32, 32 * 4 };
		break;
	case ShunLib::ConstantNumber::LEFT:
		rect = { 0, 32 * 2, 32, 32 * 3 };
		break;
	default:
		break;
	}
	player->Draw(pos, scale, &rect);
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
