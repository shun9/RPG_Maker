//************************************************/
//* @file  :Game.cpp
//* @brief :�G�f�B�^�[�ō쐬�����Q�[��
//* @date  :2017/09/28
//* @author:S.Katou
//************************************************/
#include "Game.h"
#include "../../SL_Window.h"
#include "../Map/Map.h"
#include "../Player/Player.h"

Game::Game()
{
}

Game::~Game()
{

}

//������
void Game::Initialize()
{
	if (m_map != nullptr)
	{
		//�}�b�v���v���C���[�̏����ʒu���X�N���[��
		m_map->Scroll();
	}
}

//�X�V
void Game::Update()
{
	//�v���C���[�̍X�V
	if (m_player != nullptr)
	{
		//�v���C���[����ɐi�߂邩�ǂ���
		if (m_map->CanMoveSpecifiedDir(m_player->Getpos(), m_player->Getdirection()) || m_player->Movestate())
		{
			m_player->Move();
		}

		m_player->Update();
	}

	//�}�b�v�̍X�V
	if (m_map != nullptr)
	{
		m_map->Scroll(m_player->Getpos());
	}
}

//�`��
void Game::Render()
{
	auto win = ShunLib::Window::GetInstance();

	//�`��Ώۂ��f�o�b�O�p�̃E�B���h�E�ɐ؂�ւ���
	win->SetDrawingWindow(ShunLib::Window::DEBUGGER);

	if (m_player != nullptr)
	{
		m_player->Draw();
	}

	if (m_map != nullptr)
	{
		m_map->Draw();
	}

	//�`��Ώۂ��G�f�B�^�[�p�̃E�B���h�E�ɖ߂�
	win->SetDrawingWindow(ShunLib::Window::EDITOR);
}

//�I��
void Game::Finalize()
{
}
