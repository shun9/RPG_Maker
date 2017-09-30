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
	m_posOnMap = Vec2(0, 0);
	m_scrollNum = Vec2(0, 0);

	//�|�W�V�����̏�����
	pos = Vec2(0.0, 0.0);

	//�摜���̏�����
	scale = Vec2(1.0, 1.0);

	//�`���`
	rect = { 0, 0, 32, 32 };

	//�J�E���g�̏�����
	count = 0;

	//�ړ����
	state = false;

	//�A�j���J�E���g�̏�����
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
/// �ړ�
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
/// �`��
/// </summary>
void Player::Draw()
{
	//�������������ĕ`��
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
/// ���W�̐ݒ�
/// </summary>
/// <param name="pos">���W</param>
void Player::Setpos(const ShunLib::Vec2& pos)
{
	this->pos = pos;
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

void Player::operator=(const Player& p)
{
	//�}�b�v���W��̈ʒu
	this->m_posOnMap = p.m_posOnMap;

	//x���W,y���W
	this->pos = p.pos;

	//�g�嗦
	this->scale = p.scale;

	//����
	this->dir = p.dir;

	//�J�E���g
	this->count = p.count;

	//�ړ��̏��
	this->state = p.state;

	//�A�j���J�E���g
	this->animecount = p.animecount;
}
