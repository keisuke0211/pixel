//========================================
// 
// マルチ背景処理
// 
//========================================
// *** bg_Multi.cpp ***
//========================================
#include "bg_Multi.h"
#include "bg.h"

// 静的変数宣言
int CBgMulti::m_nNumBg = -1;


// コンストラクタ
CBgMulti::CBgMulti(int nPriority) : CObject(nPriority)
{
	for (int nCntBg = 0; nCntBg < BG_MAX; nCntBg++)
	{
		m_apBg[nCntBg] = NULL;
	}
}

// デストラクタ
CBgMulti::~CBgMulti()
{

}

//========================================
// 生成
//========================================
CBgMulti *CBgMulti::Create(D3DXVECTOR3 move, int nType)
{
	// 多重スクロール2D
	CBgMulti *pBgMulti = NULL;

	// 多重スクロール2Dの生成
	pBgMulti = new CBgMulti;

	pBgMulti->m_move = move;
	pBgMulti->m_nType = nType;

	// 初期化処理
	pBgMulti->Init();

	return pBgMulti;
}

//========================================
// 初期化
//========================================
HRESULT CBgMulti::Init(void)
{
	m_nNumBg++;

	if (m_nNumBg < 0 || m_nNumBg >= BG_MAX)
	{
		return S_OK;
	}
	else
	{
		m_apBg[m_nNumBg] = CBg::Create(m_move, m_nType);
	}


	// 種類設定
	SetType(TYPE_BG_MULTI);

	return S_OK;
}

//========================================
// 終了
//========================================
void CBgMulti::Uninit(void)
{
	// 解放
	Release();
}

//========================================
//	更新
//========================================
void CBgMulti::Update(void)
{

}

//========================================
// 描画
//========================================
void CBgMulti::Draw(void)
{

}