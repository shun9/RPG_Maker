//************************************************/
//* @file  :BattleText.h
//* @brief :バトル中のテキストを描画する
//* @date  :2017/10/01
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Vec2.h>
#include <SL_Singleton.h>
#include <SL_Timer.h>
#include <vector>
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx11.h"

class BattleText:public ShunLib::Singleton<BattleText>
{
	friend ShunLib::Singleton<BattleText>;
private:
	//描画が終了したかどうか
	bool m_isEnded;

	//一行を描画するのにかかる時間
	const float DRAWING_TIME;

	//描画するテキストと対応するタイマー
	std::vector<ShunLib::Timer>m_timer;
	std::vector<std::string>m_text;

public:
	void Update();
	void Draw(const ShunLib::Vec2& pos);
	void CommandDraw(const ShunLib::Vec2 & pos);

	bool IsEnded();

	void SetString(std::string str);

	void Reset();
private:
	BattleText();
	~BattleText();


};