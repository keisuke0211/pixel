//========================================
// 
// 爆発処理
// 
//========================================
// *** explosion.cpp ***
//========================================
#include "explosion.h"
#include "../manager.h"
#include "../renderer.h"
#include "object2D.h"
#include "3D\bullet.h"

// 静的メンバ変数
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture[CExplosion::MAX_TEXTURE] = { NULL };
int CExplosion::m_nTexture = -1;

// コンストラクタ
CExplosion::CExplosion(int nPriority) : CObject2D(nPriority)
{
	// 値をクリア
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nCounterAnim = 0;
	m_Info.nPatternAnim = 0;
	m_Info.nLife = 0;
}

// デストラクタ
CExplosion::~CExplosion()
{

}

//========================================
// テクスチャの読み込み
//========================================
HRESULT CExplosion::Load(char *pPath)
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
void CExplosion::Unload(void)
{
	// テクスチャの破棄
	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; ++nCntTex)
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
CExplosion *CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion *pExplosion = NULL;

	if (pExplosion != NULL)
	{
		return pExplosion;
	}

	// オブジェクト2Dの生成
	pExplosion = new CExplosion;

	pExplosion->m_Info.pos = pos;

	// 初期化処理
	pExplosion->Init();

	return pExplosion;
}

//========================================
// 初期化
//========================================
HRESULT CExplosion::Init(void)
{
	CObject2D::Init();

	// 種類の設定
	SetType(TYPE_EFFECT);

	// 生成
	SetPos(m_Info.pos);
	SetSize(50.0f,50.0f);
	SetRot(INIT_D3DXVECTOR3);
	SetColor(INIT_D3DXCOLOR);
	SetPtnInfo(8, 1, 8, true, 5);

	m_Info.nLife = 40;

	// テクスチャの割り当て
	BindTexture(m_pTexture[0]);

	return S_OK;
}

//========================================
// 終了
//========================================
void CExplosion::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================
// 更新
//========================================
void CExplosion::Update(void)
{
	if (--m_Info.nLife <= 0)
	{
		Release();
		return;
	}
	CObject2D::Update();

	// アニメ―ション処理
	Animation();
}

//========================================
// 描画
//========================================
void CExplosion::Draw(void)
{
	CObject2D::Draw();
}