//========================================
// 
// 背景処理
// 
//========================================
// *** bg.cpp ***
//========================================
#include "../2D/bg2D.h"
#include "../../manager.h"
#include "../../renderer.h"
#include "../object2D.h"

//========================================
// コンストラクタ
//========================================
CBg::CBg(int nPriority) : CObject2D(nPriority)
{
	m_texPos = INIT_D3DXVECTOR3;
	m_texMove = INIT_D3DXVECTOR3;
	m_Type = 0;
}

//========================================
// デストラクタ
//========================================
CBg::~CBg()
{

}

//========================================
// 生成処理
//========================================
CBg *CBg::Create(D3DXVECTOR3 move, int nType)
{
	CBg *pBg = NULL;

	if (pBg != NULL)
	{
		return pBg;
	}

	// オブジェクト2Dの生成
	pBg = new CBg;

	pBg->m_texMove = move;
	pBg->m_Type = nType;

	// 初期化処理
	pBg->Init();

	return pBg;
}

//========================================
// 初期化
//========================================
HRESULT CBg::Init(void)
{
	CObject2D::Init();

	// 種類の設定
	SetType(TYPE_BG);

	// 生成
	SetPos(D3DXVECTOR3(SCREEN_WIDTH /2, SCREEN_HEIGHT / 2, 0.0f));
	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	SetRot(INIT_D3DXVECTOR3);
	SetColor(INIT_D3DXCOLOR);

	// テクスチャの割り当て
	BindTexture(m_Type);

	return S_OK;
}

//========================================
// 終了
//========================================
void CBg::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================
// 更新
//========================================
void CBg::Update(void)
{
	//テクスチャ座標の開始位置(V値)の更新
	m_texPos += m_texMove;


	VERTEX_2D *pVtx;	// 頂点情報へのポインタ
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffPolygon = GetVtxBuff();	// 頂点バッファ取得

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	// アニメーション処理
	Animation();

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(m_texPos.x, m_texPos.y);
	pVtx[1].tex = D3DXVECTOR2(m_texPos.x + 1.0f, m_texPos.y);
	pVtx[2].tex = D3DXVECTOR2(m_texPos.x, m_texPos.y + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_texPos.x + 1.0f, m_texPos.y + 1.0f);

	// テクスチャ座標更新
	m_texPos += m_texMove;

	// 頂点座標の設定
	SetVtxPos(pVtx);

	// 頂点バッファをアンロックする
	pVtxBuffPolygon->Unlock();
}

//========================================
// 描画
//========================================
void CBg::Draw(void)
{
	CObject2D::Draw();
}