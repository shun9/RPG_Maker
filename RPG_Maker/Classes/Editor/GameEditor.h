//************************************************/
//* @file  :GameEditor.h
//* @brief :�G�f�B�^�[
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Texture.h>
#include "../AppBase/AppBase.h"
#include "../../SL_Window.h"
#include "../UI/Editor/UIMenuBar.h"
#include "../UI/Editor/UITileProperty.h"
#include "../UI/Editor/UITileCanvas.h"
#include "../UI/Editor/EnemyData/UIEnemyTable.h"
#include "../UI/Editor/UIUnderBar.h"
#include "../Map/Map.h"
#include "../../Utils/GameLoader.h"
#include "../../Utils/GameSaver.h"
#include "ShortCutKey.h"

#include <memory>

#include "../Player/Player.h"

class Game;

class GameEditor : public AppBase
{
private:
	// ���݊J���Ă���t�@�C����
	std::string m_fileName;

	Game* m_game;

	// UI
	std::unique_ptr<UIMenuBar> m_uiMenu;
	std::unique_ptr<UITileProperty> m_uiTileProperty;
	std::unique_ptr<UITileCanvas> m_uiTileCanvas;
	std::unique_ptr<UIEnemyTable> m_uiEnemyTable;
	std::unique_ptr<UIUnderBar> m_uiUnderBar;

	//	TODO:������
	Player * player;

	Map* m_map;

	ShortCutKey m_shortCutKey;

public:
	GameEditor();
	~GameEditor();

	//��Ԃ̂��
	void Initialize()override;
	void Update    ()override;
	void Render    ()override;
	void Finalize  ()override;

	void DataInitialize(const ShunLib::Window& win);

	// �t�@�C�����̐ݒ�
	std::string FileName() { return m_fileName; }
	void FileName(std::string fileName) { m_fileName = fileName; }

	// TODO:�̂��قǐ�p�N���X�Ɉړ�UI
	void UIChangeActive(UIBase& ui);
	void TilePropertyChangeActive() { UIChangeActive(*m_uiTileProperty.get()); }
	void EnemyTableChangeActive() { UIChangeActive(*m_uiEnemyTable.get()); }
	void SelectedCreateTileData();
	// �f�[�^�̃��[�h
	void LoadData() { GameLoader::GetInstance()->LoadGame(this); }
	// �f�[�^�̃Z�[�u
	void SaveDataAs() { GameSaver::GetInstance()->SaveGameFileSelect(this); }
	// �f�[�^�̏㏑���Z�[�u
	void SaveDataOverwrite() {
		if (m_fileName != "") GameSaver::GetInstance()->SaveGameCurrentData(this);;
	}

	Map* GetMap() { return m_map; }

private:
	void StartDebug();

	//�v���C���[���X�N���[���Ɠ���������
	void PlayerScroll();
};