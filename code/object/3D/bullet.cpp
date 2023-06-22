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
#include "block.h"
#include "../2D/score.h"
#include "../2D/effect2D.h"

//========================================
// コンストラクタ
//========================================
CBullet::CBullet(int nPriority) : CObjectX(nPriority)
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
//========================================
// デストラクタ
//========================================
CBullet::~CBullet()
{

}

//========================================
// 生成
//========================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CBullet *pBullet = NULL;

	if (pBullet != NULL)
	{
		return pBullet;
	}

	// バレットの生成
	pBullet = new CBullet;

	pBullet->m_Info.pos = pos;
	pBullet->m_Info.move = move;
	pBullet->m_Info.nLife = 70;

	// 初期化処理
	pBullet->Init();

	return pBullet;
}
//========================================
// 初期化
//========================================
HRESULT CBullet::Init(void)
{
	CObjectX::Init();

	m_Info.fWidth = 15.0f;
	m_Info.fHeight = 25.0f;

	// 種類の設定
	SetType(TYPE_BULLET);

	SetPos(m_Info.pos);
	SetRot(m_Info.rot);
	SetColor(INIT_D3DXCOLOR);

	return S_OK;
}

//========================================
// 終了
//========================================
void CBullet::Uninit(void)
{
	CObjectX::Uninit();
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

	/*CEffect2D *pObj = CEffect2D::Create();
	pObj->SetPos(m_Info.pos);
	pObj->SetRot(m_Info.rot);
	pObj->SetSize(10.0f, 15.0f);
	pObj->SetLife(10);*/

	// 敵との当たり判定
	if(Collsion(m_Info.pos))
	{
		return;
	}
	CObjectX::Update();
}

//========================================
// 描画
//========================================
void CBullet::Draw(void)
{
	CObjectX::Draw();
}

//========================================
// 当たり判定
//========================================
bool CBullet::Collsion(D3DXVECTOR3 pos)
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

  				if (type == TYPE_BLOCK)
				{// 種類が敵の場合

					// バレットの取得
					D3DXVECTOR3 PosOld = GetPosOld();	// 位置(過去)
					float Width = GetWidth();		// 幅
					float Height = GetHeight();		// 高さ
					float Depth = GetDepth();		// 奥行き


					// ブロックの取得
					D3DXVECTOR3 BlockPos = pObj->GetPos();	// 位置
					float BlockWidth = pObj->GetWidth();	// 幅
					float BlockHeight = pObj->GetHeight();	// 高さ
					float BlockDepth = pObj->GetDepth();	// 奥行き


					// 敵と重なった
					if ((m_Info.pos.x + Width) <= (BlockPos.x + BlockWidth) &&
						(PosOld.x - Width) >= (BlockPos.x - BlockWidth) &&
						(m_Info.pos.y + Height) <= (BlockPos.y + BlockHeight) &&
						(PosOld.y - Height) >= (BlockPos.y - BlockHeight) &&
						(m_Info.pos.z + Depth) <= (BlockPos.z + BlockDepth) &&
						(PosOld.z - Depth) >= (BlockPos.z - BlockDepth))
					{//弾とブロックが当たった

						// ブロックを生成
						CBlock::Create(D3DXVECTOR3(pObj->GetPos().x, m_Info.pos.y , pObj->GetPos().z + 10));

						// 弾の破棄
						Uninit();

						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}