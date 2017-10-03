//************************************************/
//* @file  :UITileProperty.h
//* @brief :UI�̃^�C���v���p�e�B�E�C���h�E�N���X
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <vector>
#include <memory>
#include <string>
#include "../../imgui/imgui.h"

#include "UICheckBox.h"
#include "UISlider.h"
#include "UITilePropertyEGroup.h"
#include "../../Data/TileData.h"
#include "UIButton.h"

class UITileProperty :public UIBase
{
	using Vector2 = ShunLib::Vec2;

private:
	int m_currentTileId;

	TileData* m_tileData;

	std::unique_ptr<UISlider> m_encountSlider;

	std::unique_ptr<UICheckBox> m_checkBoxIsMove;

	std::unique_ptr<UICheckBox> m_checkBoxIsEmphasis;

	// �X�N���[��
	std::unique_ptr<UITilePropertyEGroup> m_groupSlider;

	// �摜�ύX
	std::unique_ptr<UIButton> m_textureChangeButton;

	// �ǉ��{�^��
	std::unique_ptr<UIButton> m_addGroupButton;

	// �폜�{�^��
	std::unique_ptr<UIButton> m_removeGroupButton;
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	UITileProperty(const std::string& name);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~UITileProperty() override;

	void SetID(int id);
	void UIUpdate();
	void UIErase();

	virtual void DrawUpdate() override;

	void UIDrawUpdate();

	void IdObservation();

	void ChangeTexture();
};