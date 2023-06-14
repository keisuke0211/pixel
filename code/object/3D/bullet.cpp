//========================================
// 
// バレット処理
// 
//========================================
// *** bullet.cpp ***
//========================================
#include "bullet.h"
#include "../../manager.h"
#include "../../renderer.h"
#include "enemy.h"
#include "../2D/score.h"
#include "../2D/effect2D.h"

// 静的メンバ変数
LPDIRECT3DTEXTURE9 CBullet::m_pTexture[MAX_TEXTURE] = {NULL};	// 共有テクスチャ
int CBullet::m_nTexture = -1;

// コンストラクタ
CBullet::CBullet(int nPriority) : CObject2D(nPriority)
{
	// 値をクリア
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.move = INIT_D3DXVECTOR3;
	m_Info.nType = 0;
	m_Info.nLife = 0;
	m_Info.fHeight = 0.0f;
	m_Info.fWidth = 0.0f;
}

// デストラクタ
CBullet::~CBullet()
{

}

//========================================
// テクスチャの読み込み
//========================================
HRESULT CBullet::Load(char *pPath)
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
void CBullet::Unload(void)
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
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,bool bShot)
{
	CBullet *pBullet = NULL;

	if (pBullet != NULL)
	{
		return pBullet;
	}

	// オブジェクト2Dの生成
	pBullet = new CBullet;

	if (bShot == true)
	{
		pBullet->m_Info.pos = D3DXVECTOR3(pos.x - 21, pos.y - 20, pos.z);
		pBullet->m_Info.nType = 0;
	}
	else
	{
		pBullet->m_Info.pos = D3DXVECTOR3(pos.x + 21, pos.y - 20, pos.z);
		pBullet->m_Info.nType = 1;
	}

	pBullet->m_Info.move = move;
	pBullet->m_Info.nLife = 70;
	pBullet->m_Info.bShot = bShot;

	// 初期化処理
	pBullet->Init();

	return pBullet;
}
//========================================
// 初期化
//========================================
HRESULT CBullet::Init(void)
{
	CObject2D::Init();

	m_Info.fWidth = 15.0f;
	m_Info.fHeight = 25.0f;

	// 種類の設定
	SetType(TYPE_BULLET);

	SetPos(m_Info.pos);
	SetSize(m_Info.fWidth, m_Info.fHeight);
	SetRot(m_Info.rot);
	SetColor(INIT_D3DXCOLOR);

	// テクスチャの割り当て
	BindTexture(m_Info.nType + 4);

	return S_OK;
}

//========================================
// 終了
//========================================
void CBullet::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================
// 更新
//========================================
void CBullet::Update(void)
{
	// 寿命の減衰
	if (--m_Info.nLife <= 0)
	{// 寿命が尽きた時

		// 弾の破棄
		Uninit();

		return;
	}

	// 移動量を代入
	m_Info.pos += m_Info.move;

	SetPos(m_Info.pos);

	CEffect2D *pObj = CEffect2D::Create();
	pObj->SetPos(m_Info.pos);
	pObj->SetRot(m_Info.rot);
	pObj->SetSize(10.0f, 15.0f);

	switch (m_Info.nType)
	{
	case 0:
		pObj->SetColor(D3DXCOLOR(0.1f, 0.5f, 1.0f, 1.0f));
		break;
	case 1:
		pObj->SetColor(D3DXCOLOR(0.1f, 1.0f, 0.25f, 1.0f));
		break;
	}
	pObj->SetLife(10);

	// 敵との当たり判定
	if(CollsionEnemy(m_Info.pos))
	{
		return;
	}

	CObject2D::Update();
}

//========================================
// 描画
//========================================
void CBullet::Draw(void)
{
	CObject2D::Draw();
}

//========================================
// 敵との当たり判定
//========================================
bool CBullet::CollsionEnemy(D3DXVECTOR3 pos)
{
	int nCntEnemy = 0;

	for (int nCntPriority = 0; nCntPriority < TYPE_MAX; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < GetNumAll(); nCntObj++)
		{
			CObject *pObj;

			// オブジェクトを取得
			pObj = GetObjectPointer(nCntPriority, nCntObj);

			if (pObj != NULL)
			{
				TYPE type;

				// 種類を取得
				type = pObj->GetType();

  				if (type == TYPE_ENEMY)
				{// 種類が敵の場合

					// ダイナミックキャストする
					CEnemy *pEnemy = dynamic_cast<CEnemy*>(pObj);


					// 敵と重なった
					if ((m_Info.pos.x + m_Info.fWidth) <= (pObj->GetPos().x + pObj->GetWidth()) &&
						(m_Info.pos.x - m_Info.fWidth) >= (pObj->GetPos().x - pObj->GetWidth()) &&
						(m_Info.pos.y + m_Info.fHeight) <= (pObj->GetPos().y + pObj->GetHeight()) &&
						(m_Info.pos.y - m_Info.fHeight) >= (pObj->GetPos().y - pObj->GetHeight()))
					{//敵と弾が当たった

						// 敵の破棄
						pEnemy->HitLife(1);

						// 弾の破棄
						Uninit();

						// スコアを加算

						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}