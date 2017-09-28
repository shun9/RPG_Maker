//************************************************/
//* @file  :Palyer.cpp
//* @brief :ÉvÉåÉCÉÑÅ[
//* @date  :2017/09/27
//* @author:Y.mano
//************************************************/
#include "Player.h"

using namespace DirectX;
using namespace ShunLib;

std::unique_ptr<Keyboard> m_key;

Player::Player()
{

}

Player::~Player()
{
}

void Player::Move()
{
	auto kb = m_key->GetState();

	if (key.IsPushed)
	{
		pos.m_y = pos.m_y + speed;
	}
	else if (kb.Down)
	{
		pos.m_y = pos.m_y - speed;
	}
	else if(kb.Right)
	{
		pos.m_x = pos.m_x + speed;
	}
	else if (kb.Left)
	{
		pos.m_x = pos.m_x - speed;
	}
}

void Player::Draw()
{
}
