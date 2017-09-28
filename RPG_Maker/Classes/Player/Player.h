//************************************************/
//* @file  :Palyer.h
//* @brief :プレイヤー
//* @date  :2017/09/27
//* @author:Y.mano
//************************************************/
#pragma once
#include <d3d11.h>
#include <Keyboard.h>
#include "../../ShunLibTK/inc/SL_KeyManager.h"
#include "../../ShunLib/inc/SL_Vec2.h"
#include "../../ShunLibTK/inc/SL_Texture.h"

//プレイヤークラス

class Player
{
public:
	Player();
	~Player();

	void Move();
	void Draw();

private:

	//x座標,y座標
	ShunLib::Vec2 pos;

	//拡大率
	float scale;

	//描画矩形
	RECT * rect;

	//スピードの設定
	const int speed = 4;

	//キーボードの宣言
	//ShunLib::KeyManager key;

};