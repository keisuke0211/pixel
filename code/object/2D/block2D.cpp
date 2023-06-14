//========================================
// 
// ブロック処理
// 
//========================================
//  *** block2D.cpp ***
//========================================
#include "block2D.h"
#include "../../manager.h"
#include "../../renderer.h"

// 静的変数宣言
LPDIRECT3DTEXTURE9 CBlock2D::m_pTexture = { NULL };

// コンストラクタ
CBlock2D::CBlock2D(int nPriority) : CObject2D(nPriority)
{
	// 値をクリア
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.fWidth = INIT_FLOAT;
	m_Info.fHeight = INIT_FLOAT;
}

// デストラクタ
CBlock2D::~CBlock2D()
{

}

//========================================
// テクスチャ読み込み
//========================================
HRESULT CBlock2D::Load(char *pPath)
{
	if (pPath != NULL)
	{
		//m_nTexture++;	// テクスチャ数加算

		// デバイス取得
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// テクスチャの読み込み
		if (FAILED(D3DXCreateTextureFromFile(pDevice, pPath, &m_pTexture)))
		{
			m_pTexture = NULL;
		}
	}

	return S_OK;
}

//========================================
// テクスチャ破棄
//========================================
void CBlock2D::Unload(void)
{
	// テクスチャの破棄
	for (int nCntTex = 0; nCntTex < 1; nCntTex++)
	{
		if (m_pTexture != NULL)
		{
			m_pTexture->Release();
			m_pTexture = NULL;
		}
	}
}

//========================================
// 生成
//========================================
CBlock2D *CBlock2D::Create(D3DXVECTOR3 pos)
{
	CBlock2D *pBlock = NULL;

	if (pBlock != NULL)
	{
		return pBlock;
	}

	// オブジェクト2Dの生成
	pBlock = new CBlock2D;

	pBlock->m_Info.pos = pos;

	// 初期化処理
	pBlock->Init();

	return pBlock;
}

//========================================
// 初期化
//========================================
HRESULT CBlock2D::Init(void)
{
	CObject2D::Init();

	// 種類の設定
	SetType(TYPE_BLOCK);

	m_Info.fWidth = 50.0f;
	m_Info.fHeight = 50.0f;

	// 生成
	SetPos(m_Info.pos);
	SetSize(m_Info.fWidth, m_Info.fHeight);
	SetColor(INIT_D3DXCOLOR);

	// テクスチャの割り当て
	BindTexture(9);

	return S_OK;
}

//========================================
// 終了
//========================================
void CBlock2D::Uninit(void)
{
	CObject2D::Uninit();
}


//========================================
// 更新
//========================================
void CBlock2D::Update(void)
{
	CObject2D::Update();
}

//========================================
// 描画
//========================================
void CBlock2D::Draw(void)
{
	/*CObject2D::Draw();*/
}