//************************************************/
//* @file  :Palyer.cpp
//* @brief :�v���C���[
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

	//�|�W�V�����̏�����
	pos = Vec2(160.0, 160.0);

	//�摜���̏�����
	scale = Vec2(1.0, 1.0);

	//�`���`
	rect = { 0, 0, 32, 32 };

	//�J�E���g�̏�����
	count = 0;

	//�ړ����
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
/// �ړ�
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
/// �`��
/// </summary>
void Player::Draw()
{
	//�������������ĕ`��
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
/// �ړ��̏�Ԃ̏���
/// </summary>
/// <returns>�J�E���g</returns>
bool Player::Movestate()
{
	return state;
}

/// <summary>
/// ���W�̏���
/// </summary>
/// <returns>���W</returns>
ShunLib::Vec2 Player::Getpos()
{
	return pos;
}

/// <summary>
/// �����̏���
/// </summary>
/// <returns>����</returns>
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
