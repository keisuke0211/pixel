//========================================
// 
// オブジェクト【 Xファイル 】処理
// 
//========================================
// *** objectX.cpp ***
//========================================
#include "objectX.h"
#include "../manager.h"
#include "../renderer.h"
#include "../texture.h"


//========================================
// コンストラクタ
//========================================
CObjectX::CObjectX(int nPriority)
{
	// 値をクリアする
	m_pos = INIT_D3DXVECTOR3;		// 位置
	m_posOld = INIT_D3DXVECTOR3;	// 位置(過去)
	m_rot = INIT_D3DXVECTOR3;		// 向き
	m_color = INIT_D3DXCOLOR;		// 色
	m_fHeight = INIT_FLOAT;			// 高さ
	m_fWidth = INIT_FLOAT;			// 幅
	m_fDepth = INIT_FLOAT;			// 奥行き
}

//========================================
// デストラクタ
//========================================
CObjectX::~CObjectX()
{

}

//========================================
// 生成
//========================================
CObjectX *CObjectX::Create(void)
{
	CObjectX *pObj3D = NULL;

	if (pObj3D != NULL)
	{
		return pObj3D;
	}

	// オブジェクト3Dの生成
	pObj3D = new CObjectX;

	// 初期化処理
	pObj3D->Init();

	return pObj3D;
}
//========================================
// 初期化
//========================================
HRESULT CObjectX::Init(void)
{
	// デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCntType = 0; nCntType < 1; nCntType++)
	{
		//Xファイルの読み込み
		D3DXLoadMeshFromX("data/OBJECT3D/Luna.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat,
			NULL,
			&m_dwNumMat,
			&m_pMesh);

		D3DXMATERIAL *pMat;	// マテリアルのポインタ

		// 必要な数のポインタを動的に確保する
		if (m_dwNumMat >= 1)
		{
			m_pTexture = new LPDIRECT3DTEXTURE9[m_dwNumMat];
		}
		else
		{
			m_pTexture = NULL;
		}


		// マテリアル情報に対するポインタを取得
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{// テクスチャファイルが存在する

			 // テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &m_pTexture[nCntMat]);
			}
		}
	}

	return S_OK;
}

//========================================
// 終了
//========================================
void CObjectX::Uninit(void)
{
	//メッシュの破棄
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;

	}

	//頂点バッファの破棄
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;

	}
	//テクスチャの破棄
	for (int nCnt = 0; nCnt < m_dwNumMat; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}

	// テクスチャポインタの破棄
	delete[] m_pTexture;
}

//========================================
// 更新
//========================================
void CObjectX::Update(void)
{

}

//========================================
// 描画
//========================================
void CObjectX::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス
	D3DMATERIAL9 matDef;			// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;				// マテリアルデータへのポインタ

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	for (int nCntItem = 0; nCntItem < 1; nCntItem++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxWorld);

		//モデルのサイズを変更
		/*D3DXMatrixScaling(&m_mtxWorld, m_fWidth, m_fHeight, m_fDepth);*/

		// 向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
		{
			// マテリアルの取得
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// テクスチャの設定
			pDevice->SetTexture(0, m_pTexture[nCntMat]);

			// モデル(パーツ)の描画
			m_pMesh->DrawSubset(nCntMat);
		}
	}

	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}
