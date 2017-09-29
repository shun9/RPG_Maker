//************************************************/
//* @file  :GameEditor.cpp
//* @brief :�G�f�B�^�[
//* @date  :2017/09/28
//* @author:S.Katou
//************************************************/
#include "GameEditor.h"
#include <Windows.h>
#include <SL_Texture.h>
#include <SL_KeyManager.h>
#include "../Game/Game.h"
#include "../../SL_Window.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx11.h"

#include <string>

#include "../../Utils/MouseManager.h"
#include "../Map/TileDataHolder.h"
#include "../Map/MapEditor.h"
#include "../../Utils/ImageLoader.h"
#include "../../Utils/ServiceManager.h"
#include "../../Utils/GameSaver.h"
#include "../../Utils/GameLoader.h"

using namespace std;

GameEditor::GameEditor()
{

}

GameEditor::~GameEditor()
{
	//�Q�[���͍Ō�܂ŕێ����Ă���
	DELETE_POINTER(m_game);
}

//������
void GameEditor::Initialize()
{
	auto win = ShunLib::Window::GetInstance();
	ShunLib::Texture::SetDevice(win->Device(), win->DeviceContext());
	auto hw = win->WindouHandle(ShunLib::Window::EDITOR);

	ImGui_ImplDX11_Init(hw, win->Device(), win->DeviceContext());

	std::unique_ptr<TileData> data=std::make_unique<TileData>();
	data->texture = std::make_unique<Texture>(L"Image\\grass.png");
	data->canMove = true;
	data->encountRate = 20;
	TileDataHolder::GetInstance()->AddData(move(data));

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\meiryo.ttc", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	m_map = new Map();
	m_map->DisplayRange(Vec2(0.0f, 0.0f), Vec2(1200.0f, 800.0f));
	auto edi = MapEditor::GetInstance();
	edi->Map(m_map);

	//�v���C���[�̍쐬
	player = new Player();

	m_game = new Game();

	auto loader = GameLoader::GetInstance();
	loader->LoadGame(this);

	// SettingUI
	m_uiMenu = make_unique<UIMenuBar>(string("menu"));
	m_uiTileProperty = make_unique<UITileProperty>(string("Tile Property"), MapEditor::GetInstance()->Id());
	m_uiTileCanvas = make_unique<UITileCanvas>(string("Tile Canvas"));

	{
		m_uiMenu->SetMenuItemFunc("File ", "Map Load");
		m_uiMenu->SetMenuItemFunc("File ", "Map Save");
		m_uiMenu->SetMenuItemFunc("File ", "Tile Load", [this]() {SelectedCreateTileData(); });
		m_uiMenu->SetMenuItemFunc("File ", "Tile Save");

		m_uiMenu->SetMenuItemFunc("View ", "TileWindow");
		m_uiMenu->SetMenuItemFunc("View ", "TileProperty", [this]() {TilePropertyChangeActive(); });
		m_uiMenu->SetMenuItemFunc("View ", "Map  ");

		m_uiMenu->SetMenuItemFunc("DataBase", "EnemyData");
		m_uiMenu->SetMenuItemFunc("DataBase", "TileData");

		m_uiMenu->SetMenuItemFunc("CreateMode", "MapCreate");
		m_uiMenu->SetMenuItemFunc("CreateMode", "EventCreate");

		m_uiMenu->SetMenuItemFunc("Scaling", "1/1");
		m_uiMenu->SetMenuItemFunc("Scaling", "1/2");
		m_uiMenu->SetMenuItemFunc("Scaling", "1/4");

		m_uiMenu->SetMenuItemFunc("DrawMode", "Pencil");

		m_uiMenu->SetMenuItemFunc("Game ", "Play");
	}
}

//�X�V
void GameEditor::Update()
{
	auto edi = MapEditor::GetInstance();
	auto mouse = MouseManager::GetInstance();
	mouse->Update();

	// TIle�̐ݒ�
	m_uiTileCanvas->SelectTile();
	m_uiTileProperty->IdObservation();

	// UI�E�C���h�E���A�N�e�B�u�łȂ���
	if (!ImGui::IsAnyWindowHovered()&&
		!ImGui::IsAnyItemActive())
	{
		if (mouse->GetMouseButton(MouseButton::leftButton))
		{
			edi->Id(0);
			auto p = mouse->GetMousePosition();
			edi->ChangeTile(p);
		}
		else if (mouse->GetMouseButton(MouseButton::rightButton))
		{
			edi->Id(1);
			auto p = mouse->GetMousePosition();
			edi->ChangeTile(p);
		}
	}
	else if (mouse->GetMouseButtonDown(MouseButton::middleButton))
	{
		StartDebug();
	}
	//m_map->Update();

	//�v���C���[����ɐi�߂邩�ǂ���
	if (m_map->CanMoveSpecifiedDir(player->Getpos(), player->Getdirection()) || player->Movestate())
	{
		player->Move();
	}
	player->Update();
}

//�`��
void GameEditor::Render()
{
	auto mouse = MouseManager::GetInstance();
	auto win = ShunLib::Window::GetInstance();

	//�`��Ώۂ��G�f�B�^�[�p�̃E�B���h�E�ɖ߂�
	win->SetDrawingWindow(ShunLib::Window::EDITOR);

	ImGui_ImplDX11_NewFrame();

	ImGui::Text("scroll x : %.3f", m_map->Scroll()->m_x);
	ImGui::Text("scroll y : %.3f", m_map->Scroll()->m_y);

	ImGui::Text("mouse x : %.3f", mouse->GetMousePosition().m_x);
	ImGui::Text("mouse y : %.3f", mouse->GetMousePosition().m_y);

	ImGui::Text("tile list : %d", (int)TileDataHolder::GetInstance()->GetTileList().size());

	m_uiMenu->DrawUpdate();
	m_uiTileProperty->DrawUpdate();
	m_uiTileCanvas->DrawUpdate();

	m_map->Draw();

	// Rendering
	//���̏�ɕ`�揈��������
	ImGui::Render();

	//�v���C���[�̕`��
	player->Draw();
}

//�I��
void GameEditor::Finalize()
{
	auto saver = GameSaver::GetInstance();
	saver->SaveGame(this);

	ImGui_ImplDX11_Shutdown();
	DELETE_POINTER(m_map);
	DELETE_POINTER(player);
}

void GameEditor::UIChangeActive(UIBase & ui)
{
	ui.Active = !ui.Active;
}

void GameEditor::SelectedCreateTileData()
{
	auto Il = ImageLoader::GetInstance();
	auto str = Il->OpenLoadingDialog();

	if (str.c_str() != wstring(L"Image\\"))
	{
		TileDataHolder::GetInstance()->AddData(SVC_Tile->CreateTileData(str));
	}
}

/// <summary>
/// �f�o�b�O�J�n
/// </summary>
void GameEditor::StartDebug()
{
	m_game->SetMap(m_map);
	ShunLib::Window::GetInstance()->SetApp(m_game, ShunLib::Window::WINDOW_TYPE::DEBUGGER);
	auto win = ShunLib::Window::GetInstance();

	//�f�o�b�O�p�E�B���h�E�쐬
	win->CreateSecondWindow();

}