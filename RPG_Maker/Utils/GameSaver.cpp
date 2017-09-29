//************************************************/
//* @file  :GameSaver.cpp
//* @brief :�Q�[������ۑ�����N���X
//* @date  :2017/09/28
//* @author:S.Katou
//************************************************/
#include "GameSaver.h"
#include <iostream>
#include <fstream>
#include "../Classes/Editor/GameEditor.h"
#include "../Classes/Map/TileDataHolder.h"

using namespace std;

bool GameSaver::SaveGame(GameEditor* editor)
{
	//�ۑ�����f�[�^
	m_editor = editor;

	//�t�@�C�����o�C�i���������݃��[�h�ŃI�[�v��
	ofstream file;
	file.open("RPG_Maker.rpgm", ios::out | ios::binary | ios::trunc);


	//�擪�̃^�C�g������������
	char tmp[] = "RPG_Maker";
	file.write(tmp, 10);

	//�e�f�[�^��ۑ�
	if(!SaveTileData      (&file)){return false;}
	if(!SaveMapData       (&file)){return false;}
	if(!SavePlayerData    (&file)){return false;}
	if(!SaveEnemyData     (&file)){return false;}
	if(!SaveEnemyGroupData(&file)){return false;}

	return true;
}


/// <summary>
/// �^�C�����̏�������
/// </summary>
bool GameSaver::SaveTileData(ofstream* file)
{

	//�擪�̃^�C�g������������
	char tmp[] = "Tile";
	file->write(tmp, 5);


	//�f�[�^������������
	auto holder = TileDataHolder::GetInstance();
	int containerSize = holder->GetContainerSize();
	file->write((char*)&containerSize, sizeof(int));

	//�f�[�^�擾�p
	TileData* data;
	std::wstring texture;
	wchar_t* path;
	int size =0;

	//�f�[�^���������[�v����
	for (int i = 0; i < containerSize; i++)
	{
		data = holder->GetData(i);

		//�e�N�X�`���̃p�X�@�I�[����������̂�+1
		texture = data->texture->GetPath();
		size = (texture.length() + 1) * 2;
		path = const_cast<wchar_t*>(texture.c_str());
		file->write((char*)&size, sizeof(size));
		file->write((char*)path, size);

		//�G���J�E���g��
		file->write((char*)&data->encountRate, sizeof(int));

		//�G�\���̎��
		size = data->enemyGroup.size();
		file->write((char*)&size, sizeof(int));

		//�G�\��ID
		for (int i = 0; i < size; i++)
		{
			file->write((char*)&data->enemyGroup[i], sizeof(int));
		}

		//�����邩�ǂ����̃t���O
		file->write((char*)&data->canMove, sizeof(bool));
	}

	return true;
}


/// <summary>
/// �}�b�v���̏�������
/// </summary>
bool GameSaver::SaveMapData(ofstream * file)
{
	auto map = m_editor->GetMap()->GetMapData();
	int h = Map::HEIGHT;
	int w = Map::WIDTH;

	//�}�b�v�T�C�Y
	file->write((char*)&h, sizeof(int));
	file->write((char*)&w, sizeof(int));

	int id = 0;
	//�}�b�v�`�b�v���
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			id = map[i][j].Id();

			file->write((char*)&id, sizeof(int));
		}
	}

	return true;
}


/// <summary>
/// �v���C���[���̏�������
/// </summary>
bool GameSaver::SavePlayerData(ofstream * file)
{
	return true;
}


/// <summary>
/// �G���̏�������
/// </summary>
bool GameSaver::SaveEnemyData(ofstream * file)
{
	return true;
}


/// <summary>
/// �G�\�����̏�������
/// </summary>
bool GameSaver::SaveEnemyGroupData(ofstream * file)
{
	return true;
}
