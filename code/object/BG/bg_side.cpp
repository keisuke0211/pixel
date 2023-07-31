//========================================
// 
// 背景（側面）【 3D_MULTI 】処理
// 
//========================================
// *** bg_side.h ***
//========================================
#include "bg_side.h"
#include "../../manager.h"
#include "../../system/renderer.h"
#include "../../system/texture.h"
#include "../../scene/pause.h"

// 静的変数
float CBgSide::m_aTexV[3] = { 0.0f };

//****************************************
// マクロ定義
//****************************************

// 頂点フォーマット【3D_MULTI】
#define FVF_VERTEX_3D_MULTI (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX3)

#define BG_HEIGHT			(500.0f)	// 高さ
#define BG_RADIUS			(1080.0f)	// 半径
#define BG_DIVISION_WIDTH	(32)		// 分割幅
#define BG_DIVISION_HEIGHT	(1)			// 分割高さ
#define BG_POS				(D3DXVECTOR3(-100.0f,200.0f,100.0f))	// 位置

//****************************************
// コンストラクタ
//****************************************
CBgSide::CBgSide(int nPriority) : CObject(nPriority)
{
	m_pos = INIT_D3DXVECTOR3;
	m_rot = INIT_D3DXVECTOR3;
	m_color = INIT_D3DXCOLOR;
}
//****************************************
// デストラクタ
//****************************************
CBgSide::~CBgSide()
{

}

//========================================
// 生成処理
//========================================
CBgSide *CBgSide::Create(void)
{
	CBgSide *pObj = new CBgSide;

	if (pObj != NULL)
	{
		// 初期化処理
		pObj->Init();
	}

	return pObj;
}

//========================================
// 初期化処理
//========================================
HRESULT CBgSide::Init(void)
{
	m_pos = BG_POS;

	SetType(TYPE_BG);

	// デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D_MULTI) * ((BG_DIVISION_WIDTH + 1) * (BG_DIVISION_HEIGHT + 1)),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D_MULTI,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D_MULTI *pVtx;	// 設定用ポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標/法線ベクトル/テクスチャ座標の設定
	for (int nCntHeight = 0; nCntHeight < BG_DIVISION_HEIGHT + 1; nCntHeight++)
	{
		for (int nCntWidth = 0; nCntWidth < BG_DIVISION_WIDTH + 1; nCntWidth++)
		{
			// 位置
			pVtx[(nCntHeight * (BG_DIVISION_WIDTH + 1)) + nCntWidth].pos
				= D3DXVECTOR3(
					sinf(-D3DX_PI + (nCntWidth * ((D3DX_PI * 2) / BG_DIVISION_WIDTH))) * BG_RADIUS,
					BG_HEIGHT - (nCntHeight * (BG_HEIGHT / BG_DIVISION_HEIGHT)),
					cosf(-D3DX_PI + (nCntWidth * ((D3DX_PI * 2) / BG_DIVISION_WIDTH))) * BG_RADIUS);

			// 法線ベクトル
			pVtx[(nCntHeight * (BG_DIVISION_WIDTH + 1)) + nCntWidth].nor
				= D3DXVECTOR3(
					sinf(-D3DX_PI + (nCntWidth * ((D3DX_PI * 2) / BG_DIVISION_WIDTH))),
					0.0f,
					cosf(-D3DX_PI + (nCntWidth * ((D3DX_PI * 2) / BG_DIVISION_WIDTH))));;

			// テクスチャ１
			pVtx[(nCntHeight * (BG_DIVISION_WIDTH + 1)) + nCntWidth].tex1
				= D3DXVECTOR2(
					nCntWidth * (8.0f / (float)BG_DIVISION_WIDTH),
					nCntHeight * (1.0f / (float)BG_DIVISION_HEIGHT));

			// テクスチャ2
			pVtx[(nCntHeight * (BG_DIVISION_WIDTH + 1)) + nCntWidth].texM
				= D3DXVECTOR2(
					nCntWidth * (8.0f / (float)BG_DIVISION_WIDTH),
					nCntHeight * (1.0f / (float)BG_DIVISION_HEIGHT));

			// テクスチャ3
			pVtx[(nCntHeight * (BG_DIVISION_WIDTH + 1)) + nCntWidth].texM2
				= D3DXVECTOR2(
					nCntWidth * (8.0f / (float)BG_DIVISION_WIDTH),
					nCntHeight * (1.0f / (float)BG_DIVISION_HEIGHT));
		}
	}

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * ((BG_DIVISION_HEIGHT * 2 * (BG_DIVISION_WIDTH + 1)) + ((BG_DIVISION_HEIGHT - 1) * 2)),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuf,
		NULL);

	WORD *pIdx;	// インデックス情報へのポインタ

	// インデックスバッファをロックし、頂点番号データへのポインタを取得
	m_pIdxBuf->Lock(0, 0, (void**)&pIdx, 0);

	// 頂点番号データの設定
	int nCntIdx = 0;	// インデックスのカウント

	for (int nCntDepth = 0; nCntDepth < BG_DIVISION_HEIGHT; nCntDepth++)
	{
		for (int nCntWidth = 0; nCntWidth < BG_DIVISION_WIDTH + 1; nCntWidth++)
		{
			pIdx[nCntIdx] = (nCntWidth + ((BG_DIVISION_WIDTH + 1) * (nCntDepth + 1)));
			pIdx[nCntIdx + 1] = nCntWidth + ((BG_DIVISION_WIDTH + 1) * nCntDepth);
			nCntIdx += 2;
		}

		if (nCntDepth < BG_DIVISION_HEIGHT - 1)
		{
			pIdx[nCntIdx] = ((BG_DIVISION_WIDTH + 1) * (nCntDepth + 1)) - 1;
			pIdx[nCntIdx + 1] = (BG_DIVISION_WIDTH + 1) * (nCntDepth + 2);
			nCntIdx += 2;
		}
	}

	// インデックスバッファをアンロックする
	m_pIdxBuf->Unlock();

	for (int nCntVtx = 0; nCntVtx < ((BG_DIVISION_WIDTH + 1) * (BG_DIVISION_HEIGHT + 1)); nCntVtx++)
	{
		// 頂点カラーの設定
		pVtx[nCntVtx].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	// テクスチャ設定
	CTexture *pTexture = CManager::GetTexture();

	m_pTextureMeshfield1 = pTexture->GetAddress(CTexture::TEX_SKY01);
	m_pTextureMeshfield2 = pTexture->GetAddress(CTexture::TEX_SKY02);
	m_pTextureMeshfield3 = pTexture->GetAddress(CTexture::TEX_SKY03);

	return S_OK;
}

//========================================
// 終了処理
//========================================
void CBgSide::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// インデックスバッファの破棄
	if (m_pIdxBuf != NULL)
	{
		m_pIdxBuf->Release();
		m_pIdxBuf = NULL;
	}
}

//========================================
// 更新処理
//========================================
void CBgSide::Update(void)
{
	bool bPause = CPause::IsPause();

	if (!bPause)
	{
		VERTEX_3D_MULTI *pVtx;	// 設定用ポインタ

		// 頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャ座標の開始位置(X軸)の更新
		m_aTexV[0] += 0.0006f;
		m_aTexV[1] += 0.0004f;
		m_aTexV[2] += 0.0003f;

		// テクスチャ座標の更新
		for (int nCntHeight = 0; nCntHeight < BG_DIVISION_HEIGHT + 1; nCntHeight++)
		{
			for (int nCntWidth = 0; nCntWidth < BG_DIVISION_WIDTH + 1; nCntWidth++)
			{
				// テクスチャ１
				pVtx[(nCntHeight * (BG_DIVISION_WIDTH + 1)) + nCntWidth].tex1
					= D3DXVECTOR2(
						m_aTexV[0] + (nCntWidth * (8.0f / (float)BG_DIVISION_WIDTH)),
						nCntHeight * (1.0f / (float)BG_DIVISION_HEIGHT));

				// テクスチャ2
				pVtx[(nCntHeight * (BG_DIVISION_WIDTH + 1)) + nCntWidth].texM
					= D3DXVECTOR2(
						m_aTexV[1] + (nCntWidth * (8.0f / (float)BG_DIVISION_WIDTH)),
						nCntHeight * (1.0f / (float)BG_DIVISION_HEIGHT));

				// テクスチャ3
				pVtx[(nCntHeight * (BG_DIVISION_WIDTH + 1)) + nCntWidth].texM2
					= D3DXVECTOR2(
						m_aTexV[2] + (nCntWidth * (8.0f / (float)BG_DIVISION_WIDTH)),
						nCntHeight * (1.0f / (float)BG_DIVISION_HEIGHT));
			}
		}

		// 頂点バッファをアンロックする
		m_pVtxBuff->Unlock();
	}
}

//========================================
// 描画処理
//========================================
void CBgSide::Draw(void)
{
	// デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX	mtxRot, mtxTrans;	// 計算用マトリックス

	// ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// テクスチャステージステートの設定		

	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_BLENDTEXTUREALPHA);
	pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
	pDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
	pDevice->SetTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	pDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_BLENDTEXTUREALPHA);
	pDevice->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_CURRENT);
	pDevice->SetTextureStageState(2, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
	pDevice->SetTextureStageState(2, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D_MULTI));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuf);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D_MULTI);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTextureMeshfield1);
	pDevice->SetTexture(1, m_pTextureMeshfield2);
	pDevice->SetTexture(2, m_pTextureMeshfield3);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		((BG_DIVISION_WIDTH + 1) * (BG_DIVISION_HEIGHT + 1)),
		0,
		((BG_DIVISION_WIDTH * BG_DIVISION_HEIGHT) * 2) + (4 * (BG_DIVISION_HEIGHT - 1)));

	// テクスチャステージステートを戻す
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	pDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	pDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
	pDevice->SetTextureStageState(2, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(2, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(2, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// ライティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}