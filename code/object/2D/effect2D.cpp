//========================================
//
// エフェクト【 2D 】
//
//========================================
// *** effect2D.cpp ***
//========================================
#include "effect2D.h"
#include "../../manager.h"
#include "../../renderer.h"

// 静的メンバ変数
LPDIRECT3DTEXTURE9 CEffect2D::m_pTexture[MAX_TEXTURE] = { NULL };	// 共有テクスチャ
int CEffect2D::m_nTexture = -1;

// コンストラクタ
CEffect2D::CEffect2D(int nPriority) : CObject2D(nPriority)
{
	// 値をクリア
	m_color = INIT_D3DXCOLOR;
	m_nLife = 0;
	m_nLifeMax = 0;
}

// デストラクタ
CEffect2D::~CEffect2D()
{

}

//========================================
// テクスチャの読み込み
//========================================
HRESULT CEffect2D::Load(char *pPath)
{
	if (pPath != NULL)
	{
		m_nTexture++;	// テクスチャ数加算

		// デバイス取得
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// テクスチャの読み込み
		if (FAILED(D3DXCreateTextureFromFile(pDevice, pPath, &m_pTexture[m_nTexture])))
		{
			m_pTexture[m_nTexture] = NULL;
		}
	}

	return S_OK;
}

//========================================
// テクスチャの破棄
//========================================
void CEffect2D::Unload(void)
{
	// テクスチャの破棄
	for (int nCntTex = 0; nCntTex < m_nTexture; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}

//========================================
// 生成
//========================================
CEffect2D *CEffect2D::Create(void)
{
	// オブジェクト2D
	CEffect2D *pEffect2D = NULL;

	// オブジェクト2Dの生成
	pEffect2D = new CEffect2D;

	// 初期化処理
	pEffect2D->Init();

	// テクスチャ割り当て
	pEffect2D->BindTexture(m_pTexture[0]);

	return pEffect2D;
}

//========================================
// 初期化
//========================================
HRESULT CEffect2D::Init(void)
{
	// 初期化処理
	CObject2D::Init();

	// 種類設定
	SetType(TYPE_EFFECT);

	return S_OK;
}

//========================================
// 終了
//========================================
void CEffect2D::Uninit(void)
{
	// 終了処理
	CObject2D::Uninit();
}

//========================================
// 更新
//========================================
void CEffect2D::Update(void)
{
	if (--m_nLife <= 0)
	{// 寿命が尽きた時、
		Uninit();		// 終了処理
		return;
	}

	// 色を寿命に応じた透明度で再設定
	D3DXCOLOR setCol = m_color;
	setCol.a *= (float)m_nLife / m_nLifeMax;


	SetEffColor(setCol);
	CObject2D::Update();
}

//========================================
// 描画
//========================================
void CEffect2D::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// アルファブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 描画処理
	CObject2D::Draw();

	// アルファブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
