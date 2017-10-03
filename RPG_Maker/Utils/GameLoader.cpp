//************************************************/
//* @file  :GameLoader.cpp
//* @brief :�Q�[������ǂݍ��ރN���X
//* @date  :2017/09/29
//* @author:S.Katou
//************************************************/
#include "GameLoader.h"

#include <assert.h>
#include "../Classes/Editor/GameEditor.h"
#include "../Classes/Data/DataBase.h"
#include "../Classes/Player/PlayerHolder.h"

using namespace std;

//�Q�[����ǂݍ���
bool GameLoader::LoadGame(GameEditor* editor)
{
	//�ǂݍ��񂾃f�[�^��K�p����p
	m_editor = editor;

	//�t�@�C�����o�C�i���ǂݍ��݃��[�h�ŃI�[�v��

	OPENFILENAME ofn;
	char szFile[MAX_PATH] = "";
	char szFileTitle[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrFilter =
		TEXT("RPGM(*.rpgm)\0*.rpgm\0");
	ofn.lpstrFileTitle = (LPWSTR)szFileTitle;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrFile = (LPWSTR)szFile;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	GetOpenFileName(&ofn);

	// �J����path���}���`�o�C�g�����ɕύX
	wstring wfullpath = wstring(ofn.lpstrFileTitle);
	string fullpath;
	char *mbs = new char[wfullpath.length() *MB_CUR_MAX + 1];
	wcstombs(mbs, wfullpath.c_str(), wfullpath.length() * MB_CUR_MAX + 1);
	fullpath = mbs;
	delete[]mbs;

	// �t�@�C�������擾
	int path_i = fullpath.find_last_of("\\") + 1;
	int ext_i = fullpath.find_last_of(".");
	std::string fileName = fullpath.substr(path_i, ext_i - path_i);
	auto openName = fileName + string(".rpgm");	// �g���q����
	editor->FileName(fileName);					// �g���q�Ȃ���ۑ�

	// �t�@�C���I�[�v��
	ifstream file;
	file.open(ofn.lpstrFileTitle, ios::in | ios::binary);

	//�t�@�C����������Γǂݍ��܂Ȃ�
	if (!file)return false;

	//������f�[�^�����Z�b�g
	DB->Reset();

	//�擪�̃^�C�g����ǂݍ���
	char tmp[10];
	file.read(tmp, 10);

	//�e�f�[�^��ǂݍ���
	if(!LoadTileData      (&file)) { return false; }
	if(!LoadMapData       (&file)) { return false; }
	if(!LoadEnemyData     (&file)) { return false; }
	if(!LoadEnemyGroupData(&file)) { return false; }
	if (!LoadPlayerData(&file)) { return false; }

	return true;
}

/// <summary>
//�}�b�v�^�C���̏���ǂݍ���
/// </summary>
bool GameLoader::LoadTileData(ifstream * file)
{
	auto& holder = DB_Tile;

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
		holder.AddData(move(tileData));
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

/// <summary>
//�G�̏���ǂݍ���
/// </summary>
bool GameLoader::LoadEnemyData(ifstream * file)
{
	//�擪�̃^�C�g����ǂݍ���
	char tmp[6];
	file->read(tmp, 6);

	auto& holder = DB_Enemy;
	int containerSize;
	file->read((char*)&containerSize, sizeof(int));

	std::wstring texture;
	wchar_t path[255];
	int size = 0;
	char nameBuf[255];

	bool isTexture = true;
	for (int i = 0; i < containerSize; i++)
	{
		//�G�f�[�^���쐬
		std::unique_ptr<EnemyData> data;
		data = std::make_unique<EnemyData>();

		//�G�̖��O
		file->read((char*)&size, sizeof(size));
		file->read((char*)nameBuf, size);
		data->Name = nameBuf;

		//�e�N�X�`��������Γǂݍ���
		file->read((char*)&isTexture, sizeof(isTexture));
		if (isTexture)
		{
			//�e�N�X�`���̃p�X
			file->read((char*)&size, sizeof(size));
			file->read((char*)path, size);
			data->Texture = std::make_unique<ShunLib::Texture>(path);
		}

		//�\�͒l
		data->Param.resize(EnemyData::Param::length);
		for (int j = 0; j < (int)data->Param.size(); j++)
		{
			file->read((char*)&data->Param[j], sizeof(int));
		}

		holder.AddData(move(data));
	}

	return true;
}


/// <summary>
/// �G�̍\����ǂݍ���
/// </summary>
bool GameLoader::LoadEnemyGroupData(ifstream * file)
{
	auto& holder = DB_EnemyGroup;
	int containerSize;
	file->read((char*)&containerSize, sizeof(int));

	int groupSize = 0;
	int size = 0;
	char nameBuf[255];
	int id = 0;
	ShunLib::Vec2 pos;
	for (int i = 0; i < containerSize; i++)
	{
		//�G�O���[�v�f�[�^���쐬
		std::unique_ptr<EnemyGroupData> data;
		data = std::make_unique<EnemyGroupData>();

		//���O
		file->read((char*)&size, sizeof(size));
		file->read(nameBuf, size);
		data->Name = nameBuf;

		//�\��
		file->read((char*)&groupSize, sizeof(int));

		for (int j = 0; j < groupSize; j++)
		{
			file->read((char*)&id, sizeof(int));
			file->read((char*)&pos, sizeof(ShunLib::Vec2));
			data->enemyList.GetList().at(j)->Id = id;
			data->enemyList.GetList().at(j)->Pos = pos;
		}

		holder.AddData(move(data));
	}

	return true;
}


/// /// <summary>
//�v���C���[�̏���ǂݍ���
/// </summary>
bool GameLoader::LoadPlayerData(ifstream * file)
{
	auto player = PlayerHolder::GetInstance()->Get();

	//�ʒu
	ShunLib::Vec2 pos;
	file->read((char*)&(pos.m_x), sizeof(float));
	file->read((char*)&(pos.m_y), sizeof(float));
	player->PosOnMap(pos);

	for (int i = 0; i < Player::PARAM::length; i++)
	{
		file->read((char*)&(player->GetParam()[i]), sizeof(int));
	}

	return true;
}
