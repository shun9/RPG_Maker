//************************************************/
//* @file  :UITileCanvas.h
//* @brief :UI�̃^�C���L�����o�X�N���X
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
#include "../../Map/TileDataHolder.h"
#include <SL_Texture.h>

class UITileCanvas :public UIBase
{
	using Vector2 = ShunLib::Vec2;

private:
	std::unique_ptr<ShunLib::Texture> m_texture;

	//�\���ʒu
	Vector2 m_Pos;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	UITileCanvas(const std::string& name);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~UITileCanvas() override;

	virtual void DrawUpdate() override;

	// �I�����ꂽ�^�C�����L��
	void SelectTile();

	void ConvertCanvasPos(const Vector2 & pos, int& bufX, int& bufY);

	// Tile�̂����蔻��
	bool CollisionTile(const Vector2& pos, int*& id);

};