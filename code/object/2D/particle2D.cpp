//========================================
//
// パーティクル【 2D 】
//
//========================================
// *** particle2D.cpp ***
//========================================
#include "particle2D.h"
#include "effect2D.h"

// コンストラクタ
CParticle2D::CParticle2D(int nPriority) : CObject(nPriority)
{
	// 値をクリア
	m_fMove = 0.0f;
	m_nLife = 0;
	m_nLifeMax = 0;
	m_pos = INIT_D3DXVECTOR3;
	m_rot = INIT_D3DXVECTOR3;
}

// デストラクタ
CParticle2D::~CParticle2D()
{

}

//========================================
// 生成
//========================================
CParticle2D *CParticle2D::Create(void)
{
	// パーティクル2D
	CParticle2D *pParticle2D = NULL;

	// パーティクル2Dの生成
	pParticle2D = new CParticle2D;

	// 初期化処理
	pParticle2D->Init();

	return pParticle2D;
}
//========================================
// 初期化
//========================================
HRESULT CParticle2D::Init(void)
{
	// 種類設定
	SetType(TYPE_PARTICLE);

	return S_OK;
}

//========================================
// 終了
//========================================
void CParticle2D::Uninit(void)
{
	Release();
}

//========================================
// 更新
//========================================
void CParticle2D::Update(void)
{
	if (--m_nLife <= 0)
	{// 寿命が尽きた時、
		Uninit();		// 終了処理
		return;
	}

	// エフェクト設定
	SetEffect();

	// 位置更新
	float fRate = (float)m_nLife / m_nLifeMax;
	m_pos.x += sinf(m_rot.z) * m_fMove * fRate;
	m_pos.y += cosf(m_rot.z) * m_fMove * fRate;
}

//========================================
// 描画
//========================================
void CParticle2D::Draw(void)
{

}

//========================================
// エフェクト生成
//========================================
void CParticle2D::SetEffect(void)
{
	// エフェクト2D生成
	CEffect2D *pObj = CEffect2D::Create();

	// 位置設定
	pObj->SetPos(m_pos);

	// 向き設定
	pObj->SetRot(m_rot);

	// 位置更新
	float fRate = (float)m_nLife / m_nLifeMax;

	// サイズ設定
	pObj->SetSize(8.0f, 8.0f);

	// 色
	pObj->SetColor(D3DXCOLOR(0.1f, 0.5f, 1.0f, 1.0f));

	// 寿命設定
	pObj->SetLife(8);
}
