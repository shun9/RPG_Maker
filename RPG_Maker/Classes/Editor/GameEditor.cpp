//************************************************/
//* @file  :GameEditor.cpp
//* @brief :�G�f�B�^�[
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#include "GameEditor.h"

#include <SL_Texture.h>

#include "../Game/Game.h"
#include "../../SL_Window.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx11.h"

GameEditor::GameEditor()
{

}

GameEditor::~GameEditor()
{
}

//������
void GameEditor::Initialize()
{
	auto win = ShunLib::Window::GetInstance();
	ShunLib::Texture::SetDevice(win->Device(), win->DeviceContext());
	ImGui_ImplDX11_Init(win->WindouHandle(ShunLib::Window::EDITOR), win->Device(), win->DeviceContext());
	ImGui_ImplDX11_NewFrame();

}

//�X�V
void GameEditor::Update()
{
}

//�`��
void GameEditor::Render()
{
	//���̏�ɕ`�揈��������
	ImGui::Render();
}

//�I��
void GameEditor::Finalize()
{
	ImGui_ImplDX11_Shutdown();
}

/// <summary>
/// �f�o�b�O�J�n
/// </summary>
void GameEditor::StartDebug()
{
	ShunLib::Window::GetInstance()->SetApp(m_game, ShunLib::Window::WINDOW_TYPE::DEBUGGER);
}