//************************************************/
//* @file  :SL_Window.h
//* @brief :�E�B���h�E�֘A�̍쐬�A�Ǘ�
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include <Windows.h>
#include <SL_Singleton.h>
#include <d3d11.h>
#include <d3dcompiler.h>

class AppBase;

namespace ShunLib
{
	class Window :public Singleton<Window>
	{
		friend Singleton<Window>;

	public:
		enum WINDOW_TYPE{
			EDITOR = 0,
			DEBUGGER,
			typeNum,
		};

	private:
		//�E�B���h�E�T�C�Y
		float m_width[typeNum];         //��
		float m_height[typeNum];        //�c
		WCHAR* m_name[typeNum];//�E�B���h�E��
		HWND m_hWnd[typeNum];  //�E�B���h�E�n���h��
		HINSTANCE m_instApp;   //���̃E�B���h�E���쐬�����A�v���P�[�V����

		//�S�̂łP��
		ID3D11Device* m_device;
		ID3D11DeviceContext* m_deviceContext;
		ID3D11Texture2D* m_texture2D;
		DXGI_SWAP_CHAIN_DESC m_sd;//�X���b�v�`�F�C���̐ݒ�
		D3D11_TEXTURE2D_DESC m_descDepth;//�[�x�X�e���V���r���[�̐ݒ�

		//�E�B���h�E�̐������K�v
		IDXGISwapChain* m_swapChain[typeNum];
		ID3D11RenderTargetView* m_renderTargetView[typeNum];
		ID3D11DepthStencilView* m_depthStencilView[typeNum];

		//�G�f�B�^�[�ƍ쐬�����Q�[��
		AppBase* m_game[typeNum];

	public:
		//�E�B���h�E�쐬
		HRESULT Create(HINSTANCE);

		//��ڈȍ~�̃E�B���h�E�쐬
		HRESULT CreateSecondWindow();

		//DirectX�֘A�̏�����
		HRESULT InitD3D();

		//�󂯎��p�v���V�[�W��
		LRESULT CALLBACK MsgProc(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam);

		//�G�f�B�^�[�p
		LRESULT CALLBACK MsgProcEditor(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam);

		//�f�o�b�K�[�p�v���V�[�W��
		LRESULT CALLBACK MsgProcDebugger(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam);

		//���b�Z�[�W���[�v
		void Run();

		//�`�悷��E�B���h�E�̐ݒ�
		void SetDrawingWindow(WINDOW_TYPE);

		//Setter
		void Width(float width) { m_width[EDITOR] = width; }
		void Height(float height) { m_height[EDITOR] = height; }
		void Name(WCHAR* name,WINDOW_TYPE type) { m_name[type] = name; }
		void SetApp(AppBase* game, WINDOW_TYPE type);

		//Getter
		float Width() { return m_width[EDITOR]; }
		float Height() { return m_height[EDITOR]; }
		WCHAR* Name(WINDOW_TYPE type) { return m_name[type]; }
		HWND WindouHandle(WINDOW_TYPE type) { return m_hWnd[type]; }  //�E�B���h�E�n���h��

		ID3D11Device* Device() { return m_device; }
		ID3D11DeviceContext* DeviceContext() { return m_deviceContext; }


		//�f�o�b�K�[������
		void DestroyDebugger();

	private:
		//�R���X�g���N�^���f�X�g���N�^
		//�V���O���g���̂��߉B��
		Window();

		~Window();

		//�Q�[���̍X�V
		void GameUpdate();
		void GameRender();

		//��ʃN���A
		void Clear();

		HRESULT MakeWindow(WINDOW_TYPE type);

	};
}