//************************************************/
//* @file  :SL_Model.cpp
//* @brief :DirectXTKのモデル用のラップクラス
//* @date  :2017/07/10
//* @author:S.Katou
//************************************************/
#include <SL_Model.h>
#include <SL_Matrix.h>
#include <SL_ConversionTK.h>
#include <SL_MacroConstants.h>
#include <SimpleMath.h>


using namespace ShunLib;

// デバイス
Microsoft::WRL::ComPtr<ID3D11Device>Model::m_device;

//デバイスコンテキスト
Microsoft::WRL::ComPtr<ID3D11DeviceContext>Model::m_context;

std::map<const wchar_t*, std::shared_ptr<DirectX::Model>> Model::m_modelPool;

//＋ーーーーーーーーーーーーーー＋
//｜機能  :デバイスの設定
//｜引数  :デバイス
//｜引数  :デバイスコンテキスト
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void ShunLib::Model::SetDevice(Microsoft::WRL::ComPtr<ID3D11Device> device,
							   Microsoft::WRL::ComPtr<ID3D11DeviceContext> context)
{
	m_device  = device;
	m_context = context;
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :ファイル指定コンストラクタ
//｜引数  :cmoファイルの名前(wchar_t[])
//＋ーーーーーーーーーーーーーー＋
Model::Model(const wchar_t cmo[]):
	m_path(cmo)
{
	//ステート作成
	m_state = std::make_unique<DirectX::CommonStates>(m_device.Get());

	//エフェクト作成
	m_effect = std::make_unique<DirectX::EffectFactory>(m_device.Get());

	//テクスチャの場所を指定
	m_effect->SetDirectory(L"CModel");

	//モデルの作成
	m_modelPool.insert(std::make_pair(m_path, DirectX::Model::CreateFromCMO(m_device.Get(), m_path, *m_effect)));

	m_model = m_modelPool[m_path];
}

ShunLib::Model::Model(const Model & model):
	m_path(model.m_path)
{
	//ステート作成
	m_state = std::make_unique<DirectX::CommonStates>(m_device.Get());

	//エフェクト作成
	m_effect = std::make_unique<DirectX::EffectFactory>(m_device.Get());

	//テクスチャの場所を指定
	m_effect->SetDirectory(L"CModel");

	//モデルの作成
	m_modelPool.insert(std::make_pair(m_path, DirectX::Model::CreateFromCMO(m_device.Get(), m_path, *m_effect)));

	m_model = m_modelPool[m_path];

}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ
//＋ーーーーーーーーーーーーーー＋
Model::~Model()
{

}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :モデルの描画
//｜引数  :ワールド行列	(Matrix)
//｜引数  :ビュー行列	(Matrix)
//｜引数  :射影行列		(Matrix)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void Model::Draw(const Matrix& world,
				 const Matrix& view,
				 const Matrix& proj)
{
	DirectX::SimpleMath::Matrix w = ShunLib::ConvertTK(world);	// ワールド
	DirectX::SimpleMath::Matrix v = ShunLib::ConvertTK(view);	// ビュー
	DirectX::SimpleMath::Matrix p = ShunLib::ConvertTK(proj);	// プロジェクション

	// 描画		 コンテキスト,ステート,ワールド,ビュー,プロジェクション
	m_model->Draw(m_context.Get(), *m_state, w, v, p);
}
