//************************************************/
//* @file  :GameSaver.cpp
//* @brief :�Q�[������ۑ�����N���X
//* @date  :2017/09/28
//* @author:S.Katou
//************************************************/
#include "GameSaver.h"
#include <iostream>
#include <fstream>
#include <string>
#include "../Classes/Editor/GameEditor.h"
#include "../Classes/Data/DataBase.h"
#include "../SL_Window.h"

using namespace std;
using namespace ShunLib;

bool GameSaver::SaveGame(const string & fileName)
{
	if (fileName == "")return false;

	//�t�@�C�����o�C�i���������݃��[�h�ŃI�[�v��
	ofstream file;
	auto openName = fileName + string(".rpgm");
	file.open(openName.c_str(), ios::out | ios::binary | ios::trunc);

	const auto tmp = fileName.c_str();

	file.write(tmp, 10);

	//�e�f�[�^��ۑ�
	if (!SaveTileData(&file)) { return false; }
	if (!SaveMapData(&file)) { return false; }
	if (!SavePlayerData(&file)) { return false; }
	if (!SaveEnemyData(&file)) { return false; }
	if (!SaveEnemyGroupData(&file)) { return false; }

	return true;
}

bool GameSaver::SaveGameCurrentData(GameEditor * editor)
{
	m_editor = editor;
	auto fileName = editor->FileName();

	return SaveGame(fileName);
}

bool GameSaver::SaveGameFileSelect(GameEditor * editor)
{
	//�ۑ�����f�[�^
	m_editor = editor;
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
	ofn.Flags = OFN_PATHMUSTEXIST
		| OFN_OVERWRITEPROMPT;

	if(GetSaveFileName(&ofn))
	MessageBox(Window::GetInstance()->WindouHandle(Window::EDITOR),(LPWSTR) szFile, TEXT("Save as"), MB_OK);

	// �J�����t�@�C�������}���`�o�C�g�����ɕύX
	wstring wfullpath = wstring(ofn.lpstrFile);
	string fullpath;
	char *mbs = new char[wfullpath.length() *MB_CUR_MAX + 1];
	wcstombs(mbs, wfullpath.c_str(), wfullpath.length() * MB_CUR_MAX + 1);
	fullpath = mbs;
	delete[]mbs;

	int path_i = fullpath.find_last_of("\\") + 1;
	int ext_i = fullpath.find_last_of(".");

	// �t�@�C�������擾
	std::string fileName = fullpath.substr(path_i, ext_i - path_i);

	editor->FileName(fileName);

	return SaveGame(fileName);
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
	const auto& holder = DB_Tile;
	int containerSize = holder.GetContainerSize();
	file->write((char*)&containerSize, sizeof(int));

	//�f�[�^�擾�p
	std::wstring texture;
	wchar_t* path;
	int size =0;

	//�f�[�^���������[�v����
	for (int i = 0; i < containerSize; i++)
	{
		auto data = holder.GetData(i);

		//�e�N�X�`���̃p�X�@�I�[����������̂�+1
		texture = data->texture->GetPath();
		size = (texture.length() + 1) * 2;
		path = const_cast<wchar_t*>(texture.c_str());
		file->write((char*)&size, sizeof(size));
		file->write((char*)path, size);

		//�G���J�E���g��
		file->write((char*)&data->encountRate, sizeof(int));

		//�G�\���̎��
		size = (int)(data->enemyGroup.size());
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
			id = (*map)[i][j].Id();

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
