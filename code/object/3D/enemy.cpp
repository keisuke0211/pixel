//========================================
// 
// エネミー処理
// 
//========================================
// *** enemy.cpp ***
//========================================
#include "enemy.h"
#include "../../manager.h"
#include "../../renderer.h"
#include "../../sound.h"
#include "../object2D.h"
#include "../2D/score.h"
#include "../2D/particle2D.h"

// 静的メンバ変数
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture[CEnemy::MAX_TEXTURE] = { NULL };
int CEnemy::m_nTexture = -1;

// コンストラクタ
CEnemy::CEnemy(int nPriority) : CObject2D(nPriority)
{
	// 値をクリア
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.move = INIT_D3DXVECTOR3;
	m_Info.fWidth = INIT_FLOAT;
	m_Info.fHeight = INIT_FLOAT;
	m_Info.nType = 0;
	m_Info.nLife = 0;
}

// デストラクタ
CEnemy::~CEnemy()
{

}

//========================================
// テクスチャの読み込み
//========================================
HRESULT CEnemy::Load(char *pPath)
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
void CEnemy::Unload(void)
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
CEnemy *CEnemy::Create(D3DXVECTOR3 pos)
{
	CEnemy *pEnemy = NULL;

	if (pEnemy != NULL)
	{
		return pEnemy;
	}

	// オブジェクト2Dの生成
	pEnemy = new CEnemy;

	pEnemy->m_Info.pos = pos;
	pEnemy->m_Info.nLife = 1;

	// 初期化処理
	pEnemy->Init();

	return pEnemy;
}

//========================================
// 初期化
//========================================
HRESULT CEnemy::Init(void)
{
	CObject2D::Init();

	m_Info.fWidth = 50.0f;
	m_Info.fHeight = 50.0f;

	// 種類の設定
	SetType(TYPE_ENEMY);

	// 生成
	SetPos(m_Info.pos);
	SetSize(m_Info.fWidth, m_Info.fHeight);
	SetRot(m_Info.rot);
	SetColor(INIT_D3DXCOLOR);

	// テクスチャの割り当て
	BindTexture(6);

	return S_OK;
}

//========================================
// 終了
//========================================
void CEnemy::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================
// 更新
//========================================
void CEnemy::Update(void)
{
	CObject2D::Update();
}

//========================================
// 描画
//========================================
void CEnemy::Draw(void)
{
	/*CObject2D::Draw();*/
}

//========================================
// ヒット処理
//========================================
void CEnemy::HitLife(int nDamage)
{
	CSound *pSound = CManager::GetSound();

	m_Info.nLife -= nDamage;

	if (m_Info.nLife >= 0)
	{
		for (int nCntPtcl = 0; nCntPtcl < 16; nCntPtcl++) 
		{
			// エフェクト2D生成
			CParticle2D *pObj = CParticle2D::Create();

			// 位置設定
			pObj->SetPos(GetPos());

			// 向き設定
			pObj->SetRot(D3DXVECTOR3(0.0f, 0.0f, ((float)rand() / RAND_MAX) * D3DX_PI * 2.0f));

			// 移動量設定
			pObj->SetMove(5.0f + (5.0f * ((float)rand() / RAND_MAX)));

			// 寿命設定
			pObj->SetLife(8 + (rand() % 24));
		}

		// 敵の破棄
		Uninit();

		// スコア設定
		CScore::SetScore(300);

		pSound->PlaySound(3);

		return;
	}
	else
	{
		pSound->PlaySound(2);
	}
}