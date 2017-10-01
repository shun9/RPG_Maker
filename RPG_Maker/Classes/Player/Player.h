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
#include "../Battle/Action.h"

//プレイヤークラス
class Player
{
public:
	enum PARAM {
		HP,
		MP,
		ATK,
		DEF,
		DEX,
		SPD,
		EXP,
		MONEY,
		length
	};

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

	ShunLib::Vec2 Scroll() { return m_scrollNum; }
	void Scroll(ShunLib::Vec2 num) { m_scrollNum = num; }

	//座標の所得
	ShunLib::Vec2 Getpos();
	void Setpos(const ShunLib::Vec2&);

	ShunLib::ConstantNumber::DIRECTION_2D Getdirection();

	ActionList& GetActionList() { return m_actionList; }
	std::vector<int>& GetParam() { return m_param; }

	bool IsEndMoveMoment() { return m_endMoveMoment; }

private:
	//マップ座標上の位置
	ShunLib::Vec2 m_posOnMap;

	//スクロール量
	ShunLib::Vec2 m_scrollNum;

	//x座標,y座標
	ShunLib::Vec2 pos;

	//拡大率
	ShunLib::Vec2 scale;

	//描画矩形
	RECT rect;

	//スピードの設定
	const int SPEED = 4;

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

	std::vector<int> m_param;
	ActionList m_actionList;

	//移動が終わった瞬間のみtrue
	bool m_endMoveMoment;
public:
	void operator=(const Player& p);
};