//************************************************/
//* @file  :GameLoader.cpp
//* @brief :�Q�[������ǂݍ��ރN���X
//* @date  :2017/09/29
//* @author:S.Katou
//************************************************/
#include "GameLoader.h"

#include <assert.h>
#include "../Classes/Editor/GameEditor.h"
#include "../Classes/Map/TileDataHolder.h"

using namespace std;

//�Q�[����ǂݍ���
bool GameLoader::LoadGame(GameEditor* editor)
{
	//�ǂݍ��񂾃f�[�^��K�p����p
	m_editor = editor;

	//�t�@�C�����o�C�i���ǂݍ��݃��[�h�ŃI�[�v��
	ifstream file;
	file.open("RPG_Maker.rpgm", ios::in | ios::binary);

	//�t�@�C����������Γǂݍ��܂Ȃ�
	if (!file)return false;

	//�擪�̃^�C�g����ǂݍ���
	char tmp[10];
	file.read(tmp, 10);

	//�e�f�[�^��ǂݍ���
	if(!LoadTileData      (&file)) { return false; }
	if(!LoadMapData       (&file)) { return false; }
	if(!LoadPlayerData    (&file)) { return false; }
	if(!LoadEnemyData     (&file)) { return false; }
	if(!LoadEnemyGroupData(&file)) { return false; }

	return true;
}

/// <summary>
//�}�b�v�^�C���̏���ǂݍ���
/// </summary>
bool GameLoader::LoadTileData(ifstream * file)
{
	auto holder = TileDataHolder::GetInstance();

	//�擪�̃^�C�g������������
	char tmp[5];
	file->read(tmp, 5);

	//�f�[�^����ǂݍ���
	int containerSize = 0;
	file->read((char*)&containerSize, sizeof(int));

	//�f�[�^�ۑ��p
	std::wstring path;
	int size = 0;
	wchar_t tmpr[256];

	//�f�[�^���������[�v����
	for (int i = 0; i < containerSize; i++)
	{
		//�^�C���f�[�^���쐬
		std::unique_ptr<TileData> tileData;
		tileData = std::make_unique<TileData>();

		//�e�N�X�`���̃p�X�@�I�[����������̂�+1
		//path = data->texture->GetPath();
		file->read((char*)&size, sizeof(int));
		file->read((char*)tmpr, size);
		tileData->texture = std::make_unique<ShunLib::Texture>(tmpr);

		//�G���J�E���g��
		file->read((char*)&tileData->encountRate, sizeof(int));

		//�G�\���̎��
		file->read((char*)&size, sizeof(int));
		tileData->enemyGroup.resize(size);

		//�G�\��ID
		for (int i = 0; i < (int)(tileData->enemyGroup.size()); i++)
		{
			file->read((char*)&tileData->enemyGroup[i], sizeof(int));
		}

		//�����邩�ǂ����̃t���O
		file->read((char*)&tileData->canMove, sizeof(bool));

		//�f�[�^��ǉ�
		holder->AddData(move(tileData));
	}

	return true;
}

/// <summary>
//�}�b�v�̏���ǂݍ���
/// </summary>
bool GameLoader::LoadMapData(ifstream* file)
{
	auto map = m_editor->GetMap()->GetMapData();
	int h = 0;
	int w = 0;

	//�}�b�v�T�C�Y
	file->read((char*)&h, sizeof(int));
	file->read((char*)&w, sizeof(int));

	//�}�b�v�`�b�v���
	int id = 0;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			file->read((char*)&id, sizeof(int));
			(*map)[i][j].Id(id);
		}
	}

	return true;
}


/// /// <summary>
//�v���C���[�̏���ǂݍ���
/// </summary>
bool GameLoader::LoadPlayerData(ifstream * file)
{
	return true;
}


/// <summary>
//�G�̏���ǂݍ���
/// </summary>
bool GameLoader::LoadEnemyData(ifstream * file)
{
	return true;
}


/// <summary>
/// �G�̍\����ǂݍ���
/// </summary>
bool GameLoader::LoadEnemyGroupData(ifstream * file)
{
	return true;
}