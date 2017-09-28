//************************************************/
//* @file  :Tile.cpp
//* @brief :�}�b�v�^�C��
//* @date  :2017/09/27
//* @author:S.Katou
//************************************************/
#include "Tile.h"
#include <SL_RandomNumber.h>
#include "TileDataHolder.h"

//�^�C����1�ӂ̒���
const float Tile::SIZE = 32.0f;

//�����Ȃ��^�C��
const int Tile::NONE = -1;

/// <summary>
/// �`��
/// </summary>
void Tile::Draw(const ShunLib::Vec2 & pos, const ShunLib::Vec2 & scale, RECT* rect)
{
	//��񂪖�����Ε`�悵�Ȃ�
	if (m_id == NONE)
	{
		return;
	}

	auto data = TileDataHolder::GetInstance()->GetData(m_id);

	if (data->texture != nullptr)
	{
		data->texture->Draw(pos, scale, rect);
	}
}
