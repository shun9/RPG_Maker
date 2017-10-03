//************************************************/
//* @file  :GameEditor.cpp
//* @brief :�G�f�B�^�[
//* @date  :2017/09/28
//* @author:S.Katou
//************************************************/
#include <Windows.h>
#include <string>
#include <SL_Texture.h>
#include <SL_KeyManager.h>

#include "GameEditor.h"
#include "../Game/Game.h"
#include "../../SL_Window.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx11.h"

#include "../Data/DataBase.h"
#include "../Map/MapEditor.h"
#include "../../Utils/MouseManager.h"
#include "../../Utils/ImageLoader.h"
#include "../../Utils/ServiceManager.h"
#include "../../Utils/GameSaver.h"
#include "../Player/PlayerHolder.h"

using namespace std;
GameEditor::GameEditor()
	:m_map(nullptr)
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

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\meiryo.ttc", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

	//�v���C���[�̍쐬
	player = new Player();
	PlayerHolder::GetInstance()->Set(player);

	m_game = new Game();

	// SettingUI
	m_uiMenu = make_unique<UIMenuBar>(string("menu"));
	m_uiTileProperty = make_unique<UITileProperty>(string("Tile Property"));
	m_uiTileCanvas = make_unique<UITileCanvas>(string("Tile Canvas"));
	m_uiUnderBar = make_unique<UIUnderBar>(string("Under"));
	m_uiDataBase = make_unique<UIDataBase>("DataBase",player);
	m_uiDataBase->Active = false;

	// �f�[�^�̏����ݒ�
	DataInitialize(*win);

	{
		m_uiMenu->SetMenuItemFunc("File ", u8"1.�f�[�^�쐬(Ctl+C)", [this]() {DataInitialize(*ShunLib::Window::GetInstance()); });
		m_shortCutKey.Add(KEY::C, [this]() {DataInitialize(*ShunLib::Window::GetInstance()); });

		m_uiMenu->SetMenuItemFunc("File ", u8"2.�f�[�^�ǂݍ��� (Ctl+L)", [this]() { LoadData(); });
		m_shortCutKey.Add(KEY::L, [this]() {LoadData(); });

		m_uiMenu->SetMenuItemFunc("File ", u8"3.�㏑���ۑ� (Ctl+S)", [this]() {SaveDataOverwrite(); });
		m_shortCutKey.Add(KEY::S, [this]() {SaveDataOverwrite(); });

		m_uiMenu->SetMenuItemFunc("File ", u8"4.���O��t���ĕۑ� (Ctl+A)", [this]() {SaveDataAs(); });
		m_shortCutKey.Add(KEY::A, [this]() {SaveDataAs(); });

		m_uiMenu->SetMenuItemFunc("File ", u8"5.�^�C����ǂݍ���", [this]() {SelectedCreateTileData(); });

		m_uiMenu->SetMenuItemFunc("View ", "1.TileProperty (Ctl+T)", [this]() {TilePropertyChangeActive(); });
		m_shortCutKey.Add(KEY::T, [this]() {TilePropertyChangeActive(); });

		m_uiMenu->SetMenuItemFunc("View ", "2.DataBase (Ctl+D)", [this]() { DataBaseChangeActive(); });
		m_shortCutKey.Add(KEY::D, [this]() {DataBaseChangeActive(); });

		m_uiMenu->SetMenuItemFunc("Game ", "1.Play (Ctl+P)", [this]() {StartDebug(); });
		m_shortCutKey.Add(KEY::P, [this]() {StartDebug(); });
	}
}

//�X�V
void GameEditor::Update()
{
	//�G�f�B�^�[�E�B���h�E���A�N�e�B�u�łȂ��ꍇ�X�V���Ȃ�
	auto win = ShunLib::Window::GetInstance();
	if (GetActiveWindow() != win->WindouHandle(Window::WINDOW_TYPE::EDITOR))
	{
		return;
	}

	auto edi = MapEditor::GetInstance();

	auto mouse = MouseManager::GetInstance();
	mouse->Update();

	m_shortCutKey.Update();

	// TIle�̐ݒ�
	m_uiTileCanvas->SelectTile();
	m_uiTileProperty->IdObservation();

	// UI�E�C���h�E���A�N�e�B�u�łȂ���
	if (!ImGui::IsAnyWindowHovered()&&
		!ImGui::IsAnyItemActive())
	{
		if (mouse->GetMouseButton(MouseButton::leftButton))
		{
			auto p = mouse->GetMousePosition();
			edi->ChangeTile(p);
		}
		else if (mouse->GetMouseButton(MouseButton::rightButton))
		{
			// �����S���@�\
			auto p = mouse->GetMousePosition();
			MapEditor::GetInstance()->EraserTile(p);
		}

	}
	m_map->Update();

	PlayerScroll();

	m_map->SetChoiseId(edi->Id());
}

//�`��
void GameEditor::Render()
{
	auto mouse = MouseManager::GetInstance();
	auto win = ShunLib::Window::GetInstance();


	//�`��Ώۂ��G�f�B�^�[�p�̃E�B���h�E�ɖ߂�
	win->SetDrawingWindow(ShunLib::Window::EDITOR);

	ImGui_ImplDX11_NewFrame();

	//�^�C�����W�擾
	int mapX, mapY;
	m_map->ConvertMapPos(mouse->GetMousePosition(), &mapX, &mapY);

	m_map->Draw();

	//�v���C���[�̕`��
	player->Draw();

	m_uiMenu->DrawUpdate();
	UIACTIVEDRAW(m_uiTileProperty);
	UIACTIVEDRAW(m_uiTileCanvas);
	UIACTIVEDRAW(m_uiDataBase);
	m_uiUnderBar->DrawUpdate(m_fileName, mapX, mapY);

	// Rendering
	//���̏�ɕ`�揈��������
	ImGui::Render();

	m_uiDataBase->DrawImage();
}

//�I��
void GameEditor::Finalize()
{
	ImGui_ImplDX11_Shutdown();
	PlayerHolder::Destroy();
	DELETE_POINTER(m_map);
	DELETE_POINTER(player);
}

// �f�[�^�쐬���̐ݒ�
void GameEditor::DataInitialize(const Window& win)
{
	FileName("");

	// �f�[�^�x�[�X�̏�����
	DB->Reset();

	DELETE_POINTER(m_map);
	m_map = new Map();
	m_map->DisplayRange(Vec2(350.0f, 55.0f), Vec2(1658, 917));

	//����ւ���}�b�v��ݒ�
	auto edi = MapEditor::GetInstance();
	edi->Map(m_map);

	MapEditor::GetInstance()->Id(-1);
	m_uiTileProperty->SetID(-1);
}

void GameEditor::UIChangeActive(UIBase & ui)
{
	ui.Active = !ui.Active;
}

void GameEditor::SelectedCreateTileData()
{
	auto Il = ImageLoader::GetInstance();
	auto str = Il->OpenLoadingDialog();

	if (str.c_str() != wstring(Tile::PATH))
	{
		DB_Tile.AddData(SVC_Tile->CreateTileData(str));
	}
}

/// <summary>
/// �f�o�b�O�J�n
/// </summary>
void GameEditor::StartDebug()
{
	m_game->SetMap(m_map);
	m_game->SetPlayer(player);
	ShunLib::Window::GetInstance()->SetApp(m_game, ShunLib::Window::WINDOW_TYPE::DEBUGGER);
	auto win = ShunLib::Window::GetInstance();

	//�f�o�b�O�p�E�B���h�E�쐬
	win->CreateSecondWindow();

}

/// <summary>
/// �v���C���[���X�N���[���Ɠ���������
/// </summary>
void GameEditor::PlayerScroll()
{
	Vec2 playerPos;
	Vec2 tmp = player->PosOnMap();
	m_map->ConvertScreenPos((int)tmp.m_x, (int)tmp.m_y, &playerPos);
	player->Setpos(playerPos);
}
