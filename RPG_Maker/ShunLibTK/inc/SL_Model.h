//************************************************/
//* @file  :SL_Model.h
//* @brief :DirectXTKのモデル用のラップクラス
//* @date  :2017/07/10
//* @author:S.Katou
//************************************************/
#pragma once
#include <d3d11.h>
#include <Model.h>
#include <Effects.h>
#include <CommonStates.h>
#include <SL_Matrix.h>
#include <map>

namespace ShunLib
{
	class Model
	{
		/*--静的変数--*/
	private:
		// デバイス
		static Microsoft::WRL::ComPtr<ID3D11Device>m_device;

		//デバイスコンテキスト
		static Microsoft::WRL::ComPtr<ID3D11DeviceContext>m_context;

	protected:
		static std::map<const wchar_t*, std::shared_ptr<DirectX::Model>> m_modelPool;

	//	/*--静的関数--*/
	public:
		//デバイスの設定
		static void SetDevice(Microsoft::WRL::ComPtr<ID3D11Device> device,
							  Microsoft::WRL::ComPtr<ID3D11DeviceContext> context);

		/*--メンバ変数--*/
	private:
		//モデルデータ
		std::shared_ptr<DirectX::Model> m_model;

		//エフェクトデータ
		std::unique_ptr<DirectX::EffectFactory> m_effect;

		//ステート
		std::unique_ptr<DirectX::CommonStates> m_state;

		//モデルのパス
		const wchar_t* m_path;

		/*--メンバ関数--*/
	public:

		//ファイル指定コンストラクタ
		Model(const wchar_t cmo[]);
		Model(const Model& model);

		//デストラクタ
		~Model();

		//｜描画
		void Draw(const Matrix& world,
				  const Matrix& view,
				  const Matrix& proj);
	};
}