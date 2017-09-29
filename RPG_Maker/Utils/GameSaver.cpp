//************************************************/
//* @file  :GameSaver.cpp
//* @brief :�Q�[������ۑ�����N���X
//* @date  :2017/09/28
//* @author:S.Katou
//************************************************/
#include "GameSaver.h"
#include "../Classes/Map/TileDataHolder.h"

bool GameSaver::SaveGame(GameEditor* editor)
{
	//�t�@�C�����o�C�i���������݃��[�h�ŃI�[�v��
	FILE* file;
	fopen_s(&file," ", "rb");

	if(!SaveTileData      (file)){fclose(file);return false;}
	if(!SaveMapData       (file)){fclose(file);return false;}
	if(!SavePlayerData    (file)){fclose(file);return false;}
	if(!SaveEnemyData     (file)){fclose(file);return false;}
	if(!SaveEnemyGroupData(file)){fclose(file);return false;}

	//�t�@�C�������
	fclose(file);
	return true;
}


/// <summary>
/// �^�C�����̏�������
/// </summary>
bool GameSaver::SaveTileData(FILE * file)
{
	auto holder = TileDataHolder::GetInstance();

	//�f�[�^������������
	int size = holder->GetContainerSize();
	fwrite(&size, sizeof(int), 1, file);

	//�f�[�^�擾�p
	TileData* data;

	//�f�[�^���������[�v����
	for (int i = 0; i < size; i++)
	{
		data = holder->GetData(i);

	}

	return true;
}


/// <summary>
/// �^�C�����̏�������
/// </summary>
bool GameSaver::SaveMapData(FILE * file)
{
	return true;
}


/// <summary>
/// �^�C�����̏�������
/// </summary>
bool GameSaver::SavePlayerData(FILE * file)
{
	return true;
}


/// <summary>
/// �^�C�����̏�������
/// </summary>
bool GameSaver::SaveEnemyData(FILE * file)
{
	return true;
}


/// <summary>
/// �G�\�����̏�������
/// </summary>
bool GameSaver::SaveEnemyGroupData(FILE * file)
{
	return true;
}
