//========================================
// 
// オブジェクト【 3D 】処理
// 
//========================================
// *** object3D.cpp ***
//========================================
#include "../manager.h"
#include "object3D.h"
#include "../renderer.h"
#include "../texture.h"

// コンストラクタ
CObject3D::CObject3D()
{
	// 値をクリアする
	m_pos = INIT_D3DXVECTOR3;
	m_size = INIT_D3DXVECTOR2;
	m_nTexture = 0;
	m_fAngle = INIT_FLOAT;
	m_fLength = INIT_FLOAT;
	m_fRotY = INIT_FLOAT;
}

// デストラクタ
CObject3D::~CObject3D()
{

}
//========================================
// 生成処理
//========================================
CObject3D *CObject3D::Create(void)
{
	CObject3D *pObj3D = NULL;

	if (pObj3D != NULL)
	{
		return pObj3D;
	}

	// オブジェクト2Dの生成
	pObj3D = new CObject3D;

	// 初期化処理
	pObj3D->Init();

	return pObj3D;
}

//========================================
// 初期化処理
//========================================
HRESULT CObject3D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 設定用ポインタ
	VERTEX_3D *pVtx;

	// 頂点バッファのロックと頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	// 頂点座標を設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, -0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, -0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, -0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, -0.0f);

	// 頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファの破棄
	m_pVtxBuff->Unlock();

	return S_OK;
}

//========================================
// 終了処理
//========================================
void CObject3D::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//========================================
// 更新処理
//========================================
void CObject3D::Update(void)
{

}

//========================================
// 描画処理
//========================================
void CObject3D::Draw(void)
{
	// デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;										//計算用マトリックス


	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	////向きを反映
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

	//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	////位置を反映
	//D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	CTexture* pTexture = CManager::GetTexture();

	// テクスチャ設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//========================================
// 位置設定
//========================================
void CObject3D::SetPos(const D3DXVECTOR3& pos)
{
	// 位置の代入
	m_pos = pos;

	// 設定用ポインタ
	VERTEX_2D *pVtx;

	// 頂点バッファのロックと頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	// 頂点座標を設定
	pVtx[0].pos.x = m_pos.x + sinf(m_fRotY + m_fAngle + -D3DX_PI) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_fRotY + m_fAngle + -D3DX_PI) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_fRotY + -m_fAngle + D3DX_PI) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_fRotY + -m_fAngle + D3DX_PI) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_fRotY + m_fAngle * -1.0f) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_fRotY + m_fAngle * -1.0f) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_fRotY + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_fRotY + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	// 頂点バッファの破棄
	m_pVtxBuff->Unlock();
}

//========================================
// 向き設定
//========================================
void CObject3D::SetRot(const float& rotY)
{
	// Y軸の代入
	m_fRotY = rotY;

	//　位置設定
	SetPos(m_pos);
}

//========================================
// サイズ設定
//========================================
void CObject3D::SetSize(const D3DXVECTOR2& size)
{
	// サイズの代入
	m_size = size;

	// 長さ・角度の設定
	m_fLength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y) * 0.5f;
	m_fAngle = atan2f(m_size.x, m_size.y);

	// 位置の設定
	SetPos(m_pos);
}

//========================================
// 色設定
//========================================
void CObject3D::SetColor(const D3DXCOLOR& color)
{
	// サイズの代入
	m_color = color;

	// 設定用ポインタ
	VERTEX_2D *pVtx;

	// 頂点バッファのロックと頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	// 頂点カラー
	pVtx[0].col = D3DXCOLOR(m_color.r, m_color.g, m_color.b, m_color.a);
	pVtx[1].col = D3DXCOLOR(m_color.r, m_color.g, m_color.b, m_color.a);
	pVtx[2].col = D3DXCOLOR(m_color.r, m_color.g, m_color.b, m_color.a);
	pVtx[3].col = D3DXCOLOR(m_color.r, m_color.g, m_color.b, m_color.a);

	// 頂点バッファの破棄
	m_pVtxBuff->Unlock();
}

//=============================================================================
// テクスチャの割り当て
//=============================================================================
void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 m_pTexture1)
{
	m_pTexture = m_pTexture1;
}

//========================================
// テクスチャ設定
//========================================
void CObject3D::SetTex(PositionVec4 tex)
{
	VERTEX_2D *pVtx; //頂点へのポインタ

					 //頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(tex.P0, tex.P2);
	pVtx[1].tex = D3DXVECTOR2(tex.P1, tex.P2);
	pVtx[2].tex = D3DXVECTOR2(tex.P0, tex.P3);
	pVtx[3].tex = D3DXVECTOR2(tex.P1, tex.P3);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}