//========================================
// 
// モーションモデル処理
// 
//========================================
// *** motion_model.cpp ***
//========================================
#include "motion.h"
#include "motion_model.h"
#include "../manager.h"
#include "../renderer.h"


//========================================
// コンストラクタ
//========================================
CMotionModel::CMotionModel(int nPriority) : CObject(nPriority)
{
	m_pMotion = NULL;				// モーション情報
	m_mtxWorld = D3DXMATRIX();		// ワールドマトリックス
	m_pos = INIT_D3DXVECTOR3;		// 位置
	m_posOld = INIT_D3DXVECTOR3;	// 過去位置
	m_rot = INIT_D3DXVECTOR3;		// 向き
	m_size = INIT_D3DXVECTOR3;		// 大きさ
}

//========================================
// デストラクタ
//========================================
CMotionModel::~CMotionModel()
{

}

//========================================
// 生成
//========================================
CMotionModel * CMotionModel::Create()
{
	CMotionModel *pMotionModel = NULL;

	pMotionModel = new CMotionModel;


	// 数値の初期化
	pMotionModel->Init();

	// インスタンスを返す
	return pMotionModel;
}

//========================================
// 初期化
//========================================
HRESULT CMotionModel::Init()
{
	// 変数の初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 位置
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// 過去位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 向き
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);				// スケール
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);					// 当たり判定
	m_quat = { 0.0f,0.0f,0.0f,1.0f };
	SetIsColor(false);
	SetColor({ 1.0f,1.0f,1.0f,1.0f });					// 色
	D3DXVECTOR3 vecY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXQuaternionRotationAxis(&m_quat, &vecY, D3DX_PI);
	return S_OK;
}

//========================================
// 終了
//========================================
void CMotionModel::Uninit()
{
	if (m_pMotion != NULL)
	{// 終了処理
		m_pMotion->Uninit();

		// メモリの解放
		delete m_pMotion;
		m_pMotion = NULL;
	}

	// オブジェクトの解放
	Release();
}

//========================================
// 更新
//========================================
void CMotionModel::Update()
{
	if (m_pMotion != NULL)
	{// モーション番号の設定
		m_pMotion->Update();
	}
}

//========================================
// 描画
//========================================
void CMotionModel::Draw()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (m_Stencil)
	{
		// ステンシルバッファ -> 有効
		pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

		// ステンシルバッファと比較する参照値設定 -> ref
		pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

		// ステンシルバッファの値に対してのマスク設定 -> 0xff(全て真)
		pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

		// ステンシルテストの比較方法 ->
		// （参照値 >= ステンシルバッファの参照値）なら合格
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATEREQUAL);

		// ステンシルテストの結果に対しての反映設定
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);		// Zとステンシル成功
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);			// Zとステンシル失敗
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);			// Zのみ失敗
	}
	else
	{
		// ステンシルバッファ -> 無効
		pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	}

	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxRotQuat, mtxScale;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);									// 行列初期化関数

	// クォータニオンの使用した姿勢の設定
	D3DXMatrixRotationQuaternion(&mtxRotQuat, &m_quat);					// クオータニオンによる行列回転

	D3DXMatrixScaling(&mtxScale, m_scale.y, m_scale.x, m_scale.z);		// スケール拡縮行列
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);			// 行列掛け算関数 

	// 向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);	// 行列回転関数

	D3DXMatrixMultiply(&mtxRot, &mtxRot, &mtxRotQuat);					// 行列掛け算関数 
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);				// 行列掛け算関数 

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);		// 行列移動関数
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);			// 行列掛け算関数

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	if (m_pMotion != NULL)
	{// パーツの描画設定
		m_pMotion->SetParts(m_mtxWorld, m_bcolor, m_color);
	}

	// ステンシルバッファ -> 無効
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}


//========================================
// モーションの設定
//========================================
void CMotionModel::SetMotion(const char * pName)
{
	if (m_pMotion != nullptr)
	{// 終了処理
		m_pMotion->Uninit();

		// メモリの解放
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	// モーション情報
	m_pMotion = new CMotion(pName);
	assert(m_pMotion != nullptr);

	// モーションの初期設定
	m_pMotion->SetMotion(0);

	// モーション番号の設定
	m_pMotion->SetNumMotion(0);
}

//========================================
// 色設定
//========================================
void CMotionModel::ChangeColar(D3DXCOLOR color)
{
	SetColor(color);
	SetIsColor(true);
}