//************************************************/
//* @file  :Palyer.h
//* @brief :プレイヤー
//* @date  :2017/09/27
//* @author:Y.mano
//************************************************/
#pragma once
#include <d3d11.h>
#include "../../ShunLib/inc/SL_Vec2.h"
#include <SL_Texture.h>
#include "../Map/Map.h"
#include <SL_ConstantNumber.h>

//プレイヤークラス

class Player
{
public:
	Player();
	~Player();

	void Update();

	void Move();
	void Draw();

	bool Movestate();

	//座標の所得
	ShunLib::Vec2 PosOnMap() { return m_posOnMap; }
	void PosOnMap(const ShunLib::Vec2& pos) { m_posOnMap = pos; }

	//座標の所得
	ShunLib::Vec2 Getpos();
	void Setpos(const ShunLib::Vec2&);

	ShunLib::ConstantNumber::DIRECTION_2D Getdirection();
private:
	//マップ座標上の位置
	ShunLib::Vec2 m_posOnMap;

	//x座標,y座標
	ShunLib::Vec2 pos;

	//拡大率
	ShunLib::Vec2 scale;

	//描画矩形
	RECT rect;

	//スピードの設定
	const int SPEED = 1;

	//画像のデータ
	ShunLib::Texture* player;

	//向き
	ShunLib::ConstantNumber::DIRECTION_2D dir;

	//カウント
	int count;

	//移動の状態
	bool state;

	//マスの大きさ
	const int TROUT = 32;

	//アニメカウント
	int animecount;

public:
	void operator=(const Player& p);
};