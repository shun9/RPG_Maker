#include <Windows.h>

#include "SL_Window.h"
#include "Classes\Editor\GameEditor.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam);

HRESULT InitWindow(HINSTANCE hInst);

/// <summary>
/// �G���g���[�|�C���g
/// �E��������v���O�������n�܂�
/// �E�E�B���h�E���쐬
/// �E���b�Z�[�W���[�v�̎���
/// </summary>
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmpShow)
{
	auto window = ShunLib::Window::GetInstance();

	//�G�f�B�^�[�ݒ�
	GameEditor editor;

	//�E�B���h�E�쐬
	if (SUCCEEDED(InitWindow(hInst)))
	{
		window->SetApp(&editor, ShunLib::Window::WINDOW_TYPE::EDITOR);

		//�쐬�ɐ��������烋�[�v
		window->Run();
	}
	ShunLib::Window::Destroy();

	//�I��
	return 0;
}


/// <summary>
/// �E�B���h�E�v���V�[�W��
/// </summary>
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam)
{
	auto window = ShunLib::Window::GetInstance();

	//�G�f�B�^�[�p
	return window->MsgProc(hWnd, iMag, wParam, lParam);
}


/// <summary>
/// �E�B���h�E������
/// </summary>
HRESULT InitWindow(HINSTANCE hInst)
{
	auto window = ShunLib::Window::GetInstance();

	//�E�B���h�E���ݒ�
	window->Width(800.0f);
	window->Height(600.0f);
	window->Name(L"RPG�c�N�[���c�N�[��");

	//�E�B���h�E�쐬
	if (SUCCEEDED(window->Create(hInst)))
	{
		//DirectX�֘A�̏�����
		if (SUCCEEDED(window->InitD3D()))
		{
			return S_OK;
		}
	}

	return E_FAIL;
}
