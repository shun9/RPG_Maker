//************************************************/
//* @file  :UISlider.h
//* @brief :UISlider�̃N���X
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <SL_Vec2.h>
#include "UIBase.h"
#include <list>
#include <memory>
#include <string>
#include <functional>

class UISlider :public UIBase
{
	using Vector2 = ShunLib::Vec2;
private:
	int* m_sliderNum;

	int m_max;
	int m_min;
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	UISlider(const std::string& name, int* num, int min = 0, int max = 100);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~UISlider() override;

	void DrawUpdate() override;
};
