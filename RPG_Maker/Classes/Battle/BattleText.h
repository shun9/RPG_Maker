//************************************************/
//* @file  :BattleText.h
//* @brief :�o�g�����̃e�L�X�g��`�悷��
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
	//�`�悪�I���������ǂ���
	bool m_isEnded;

	//��s��`�悷��̂ɂ����鎞��
	const float DRAWING_TIME;

	//�`�悷��e�L�X�g�ƑΉ�����^�C�}�[
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