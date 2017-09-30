//************************************************/
//* @file  :Palyer.h
//* @brief :�v���C���[
//* @date  :2017/09/27
//* @author:Y.mano
//************************************************/
#pragma once
#include <d3d11.h>
#include "../../ShunLib/inc/SL_Vec2.h"
#include <SL_Texture.h>
#include "../Map/Map.h"
#include <SL_ConstantNumber.h>

//�v���C���[�N���X

class Player
{
public:
	Player();
	~Player();

	void Update();

	void Move();
	void Draw();

	bool Movestate();

	//���W�̏���
	ShunLib::Vec2 PosOnMap() { return m_posOnMap; }
	void PosOnMap(const ShunLib::Vec2& pos) { m_posOnMap = pos; }

	//���W�̏���
	ShunLib::Vec2 Getpos();
	void Setpos(const ShunLib::Vec2&);

	ShunLib::ConstantNumber::DIRECTION_2D Getdirection();
private:
	//�}�b�v���W��̈ʒu
	ShunLib::Vec2 m_posOnMap;

	//x���W,y���W
	ShunLib::Vec2 pos;

	//�g�嗦
	ShunLib::Vec2 scale;

	//�`���`
	RECT rect;

	//�X�s�[�h�̐ݒ�
	const int SPEED = 1;

	//�摜�̃f�[�^
	ShunLib::Texture* player;

	//����
	ShunLib::ConstantNumber::DIRECTION_2D dir;

	//�J�E���g
	int count;

	//�ړ��̏��
	bool state;

	//�}�X�̑傫��
	const int TROUT = 32;

	//�A�j���J�E���g
	int animecount;

public:
	void operator=(const Player& p);
};