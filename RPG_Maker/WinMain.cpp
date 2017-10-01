#include <Windows.h>
#include <SL_KeyManager.h>
#include "SL_Window.h"

#include "Classes\Editor\GameEditor.h"
#include "Utils\ImageLoader.h"
#include "Classes\Battle\BattleManager.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam);

HRESULT InitWindow(HINSTANCE hInst);

/// <summary>
/// エントリーポイント
/// ・ここからプログラムが始まる
/// ・ウィンドウを作成
/// ・メッセージループの実装
/// </summary>
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmpShow)
{
	auto window = ShunLib::Window::GetInstance();

	//エディター設定
	GameEditor editor;

	//ウィンドウ作成
	if (SUCCEEDED(InitWindow(hInst)))
	{
		window->SetApp(&editor, ShunLib::Window::WINDOW_TYPE::EDITOR);

		//作成に成功したらループ
		window->Run();
	}

	BattleManager::Destroy();
	ImageLoader::Destroy();
	ShunLib::KeyManager::Destroy();
	ShunLib::Window::Destroy();

	//終了
	return 0;
}


/// <summary>
/// ウィンドウプロシージャ
/// </summary>
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam)
{
	auto window = ShunLib::Window::GetInstance();

	//エディター用
	return window->MsgProc(hWnd, iMag, wParam, lParam);
}


/// <summary>
/// ウィンドウ初期化
/// </summary>
HRESULT InitWindow(HINSTANCE hInst)
{
	auto window = ShunLib::Window::GetInstance();

	//ウィンドウ情報設定
	window->Width(1664.0f);
	window->Height(936.0f);
	window->Name(L"RPGツクールツクール", window->WINDOW_TYPE::EDITOR);
	window->Name(L"実行中", window->WINDOW_TYPE::DEBUGGER);

	//ウィンドウ作成
	if (SUCCEEDED(window->Create(hInst)))
	{
		//DirectX関連の初期化
		if (SUCCEEDED(window->InitD3D()))
		{
			return S_OK;
		}
	}

	return E_FAIL;
}
