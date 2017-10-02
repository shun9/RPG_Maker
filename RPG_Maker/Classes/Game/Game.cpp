//************************************************/
//* @file  :Game.cpp
//* @brief :�G�f�B�^�[�ō쐬�����Q�[��
//* @date  :2017/09/28
//* @author:S.Katou
//************************************************/
#include "Game.h"
#include <SL_MacroConstants.h>
#include "../../SL_Window.h"
#include "../Map/DebugMap.h"
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "../Battle/BattleManager.h"

Game::Game():
	m_isPlaying(false)
{
	m_map = new DebugMap();
	auto win = ShunLib::Window::GetInstance();
	m_map->DisplayRange(ShunLib::Vec2(0.0f, 0.0f), ShunLib::Vec2(win->DebugWidth(),win->DebugHeight()));
	m_player = new Player();

	m_battle = BattleManager::GetInstance();

}

Game::~Game()
{
	DELETE_POINTER(m_map);
	DELETE_POINTER(m_player);
}

//������
void Game::Initialize()
{
	auto win = ShunLib::Window::GetInstance();

	if (m_map != nullptr && m_player != nullptr)
	{
		//�v���C���[�̏����ʒu������
		ShunLib::Vec2 pos = m_player->PosOnMap();
		m_map->DebugConvertScreenPos((int)pos.m_x,(int)pos.m_y,&pos);
		m_player->Setpos(pos);
	}

	m_isPlaying = true;
	m_isDuringBattle = false;
}

//�X�V
void Game::Update()
{
	//�f�o�b�O�E�B���h�E���A�N�e�B�u�łȂ��ꍇ�X�V���Ȃ�
	auto win = ShunLib::Window::GetInstance();
	if (GetActiveWindow() != win->WindouHandle(ShunLib::Window::WINDOW_TYPE::DEBUGGER))
	{
		return;
	}

	if (!m_isDuringBattle)
	{
		//�t�B�[���h��ʂł̍X�V
		FieldUpdate();
	}
	else
	{
		//�o�g����ʂł̍X�V
		BattleUpdate();
	}
}

//�`��
void Game::Render()
{
	auto win = ShunLib::Window::GetInstance();

	//�`��Ώۂ��f�o�b�O�p�̃E�B���h�E�ɐ؂�ւ���
	win->SetDrawingWindow(ShunLib::Window::DEBUGGER);

	if (m_map != nullptr)
	{
		m_map->Draw();
	}

	if (m_player != nullptr)
	{
		m_player->Draw();
	}

	if (m_isDuringBattle)
	{
		m_battle->Draw(ShunLib::Vec2(25.0f, 17.5f));
	}
	//�`��Ώۂ��G�f�B�^�[�p�̃E�B���h�E�ɖ߂�
	win->SetDrawingWindow(ShunLib::Window::EDITOR);
}

//�I��
void Game::Finalize()
{
	m_isPlaying = false;
}


void Game::SetMap(Map* map)
{
	int id = 0;
	auto data = m_map->GetMapData();
	auto copy = map->GetMapData();
	for (int i = 0; i < Map::HEIGHT; i++)
	{
		for (int j = 0; j < Map::WIDTH; j++)
		{
			id = (*copy)[i][j].Id();
			(*data)[i][j].Id(id);
		}
	}
}

/// <summary>
/// �v���C���[�̐ݒ�
/// </summary>
/// <param name="player"></param>
void Game::SetPlayer(Player * player)
{

	(*m_player) = (*player);
}

/// <summary>
/// ���s�����ǂ���
/// </summary>
bool Game::IsPlaying()
{
	return m_isPlaying;
}


/// <summary>
/// �X�N���[���ʂ̐���
/// </summary>
void Game::ClampScroll()
{
	auto win = ShunLib::Window::GetInstance();
	float scrollX = m_player->Getpos().m_x - win->DebugWidth() / 2;
	float scrollY = m_player->Getpos().m_y - win->DebugHeight() / 2;
	float maxX = Tile::SIZE*Map::WIDTH;
	float maxY = Tile::SIZE*Map::HEIGHT;

	//���[�𐧌�
	if (scrollX < 0.0f)
	{
		scrollX = 0.0f;
	}

	//��[�𐧌�
	if (scrollY < 0.0f)
	{
		scrollY = 0.0f;
	}

	//�E�[�𐧌�
	if (scrollX > maxX)
	{
		scrollX = maxX;
	}

	//���[�𐧌�
	if (scrollY > maxY)
	{
		scrollY = maxY;
	}
	m_scrollNum.m_x = scrollX;
	m_scrollNum.m_y = scrollY;
}

/// <summary>
/// �t�B�[���h��ʂł̍X�V
/// </summary>
void Game::FieldUpdate()
{
	//�v���C���[�̍X�V
	if (m_player != nullptr)
	{
		//�v���C���[����ɐi�߂邩�ǂ���
		if (m_map->DebugCanMoveSpecifiedDir(m_player->Getpos(), m_player->Getdirection()) || m_player->Movestate())
		{
			m_player->Move();
		}

		m_player->Update();
		ClampScroll();
		m_player->Scroll(m_scrollNum);
	}

	//�}�b�v�̍X�V
	if (m_map != nullptr)
	{
		m_map->Scroll(m_scrollNum);
	}

	//�G���J�E���g����
	if (m_player != nullptr && m_map != nullptr)
	{
		if (m_player->IsEndMoveMoment() && m_map->IsEncount(m_player->Getpos()))
		{
			int enemyID = m_map->GetRandamEnemy(m_player->Getpos());

			{
				m_isDuringBattle = true;
				m_battle->SetPlayer(m_player);
				m_battle->BattleStart();
			}
		}
	}

}

/// <summary>
/// �o�g����ʂł̍X�V
/// </summary>
void Game::BattleUpdate()
{
	m_battle->Update();

	//�I��������t�B�[���h�ɖ߂�
	if (m_battle->IsEnded())
	{
		m_player->Revive();
		m_isDuringBattle = false;
	}
}
