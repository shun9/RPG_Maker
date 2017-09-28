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
	player = new ShunLib::Texture(L"Image\\brick.png");

	//ポジションの初期化
	pos = Vec2(100.0, 100.0);

	//画像率の初期化
	scale = Vec2(1.0, 1.0);

	//描画矩形
	rect = { 0, 0, 32, 32 };
}

Player::~Player()
{
}

void Player::Move()
{
	if (KeyManager::GetInstance()->IsPushed(KeyManager::KEY_CODE::UP))
	{
		pos.m_y = pos.m_y - speed;
	}
	else if (KeyManager::GetInstance()->IsPushed(KeyManager::KEY_CODE::DOWN))
	{
		pos.m_y = pos.m_y + speed;
	}
	else if(KeyManager::GetInstance()->IsPushed(KeyManager::KEY_CODE::RIGHT))
	{
		pos.m_x = pos.m_x + speed;
	}
	else if (KeyManager::GetInstance()->IsPushed(KeyManager::KEY_CODE::LEFT))
	{
		pos.m_x = pos.m_x - speed;
	}
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	player->Draw(pos, scale, &rect);
}

ShunLib::Vec2 Player::Getpos()
{
	return pos;
}

ShunLib::ConstantNumber::DIRECTION_2D Player::Getdirection()
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
	return dir;
}
