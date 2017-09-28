//************************************************/
//* @file  :Palyer.h
//* @brief :�v���C���[
//* @date  :2017/09/27
//* @author:Y.mano
//************************************************/
#pragma once
#include <d3d11.h>
#include <Keyboard.h>
#include "../../ShunLibTK/inc/SL_KeyManager.h"
#include "../../ShunLib/inc/SL_Vec2.h"
#include "../../ShunLibTK/inc/SL_Texture.h"

//�v���C���[�N���X

class Player
{
public:
	Player();
	~Player();

	void Move();
	void Draw();

private:

	//x���W,y���W
	ShunLib::Vec2 pos;

	//�g�嗦
	float scale;

	//�`���`
	RECT * rect;

	//�X�s�[�h�̐ݒ�
	const int speed = 4;

	//�L�[�{�[�h�̐錾
	//ShunLib::KeyManager key;

};