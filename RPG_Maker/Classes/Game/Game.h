//************************************************/
//* @file  :Game.h
//* @brief :�G�f�B�^�[�ō쐬�����Q�[��
//* @date  :2017/09/29
//* @author:S.Katou
//************************************************/
#pragma once
#include "../AppBase/AppBase.h"
#include <SL_Vec2.h>

class Map;
class DebugMap;
class Player;
class BattleManager;

//�Q�[���N���X
//���s�{�^���ō쐬
//�G�f�B�^�[�Ƃ͕ʂ̃E�B���h�E�ɕ`��
class Game : public AppBase
{
private:
	DebugMap* m_map;
	Player* m_player;
	BattleManager* m_battle;

	//�X�N���[����
	ShunLib::Vec2 m_scrollNum;

	//���s�����ǂ���
	bool m_isPlaying;

	//�o�g�������ǂ���
	bool m_isDuringBattle;
public:
	Game();
	~Game();

	//��Ԃ̂��
	void Initialize()override;
	void Update    ()override;
	void Render    ()override;
	void Finalize  ()override;

	void SetMap(Map* map);

	void SetPlayer(Player* player);

	//���s�����ǂ���
	bool IsPlaying();
private:
	//�X�N���[���ʂ𐧌�
	void ClampScroll();

	//�t�B�[���h��ʂł̍X�V
	void FieldUpdate();

	//�o�g����ʂł̍X�V
	void BattleUpdate();

};