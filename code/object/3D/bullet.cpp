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
// マクロ定義
//========================================
#define BULLET_SPEED (2.5f)	// 弾の速度

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
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBullet *pBullet = NULL;

	if (pBullet != NULL)
	{
		return pBullet;
	}

	// バレットの生成
	pBullet = new CBullet;

	pBullet->m_Info.pos = pos;
	pBullet->m_Info.rot = rot;
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

	m_Info.move.x = sinf(m_Info.rot.y) * BULLET_SPEED;
	m_Info.move.z = cosf(m_Info.rot.y) * BULLET_SPEED;

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
	SetRot(m_Info.rot);

	/*CEffect2D *pObj = CEffect2D::Create();
	pObj->SetPos(m_Info.pos);
	pObj->SetRot(m_Info.rot);
	pObj->SetSize(10.0f, 15.0f);
	pObj->SetLife(10);*/

	// 当たり判定
	if(Collsion(m_Info.pos))
	{
		return;
	}
	/*CObjectX::Update();*/
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
	int nRot = 0;
	bool bHit = false;

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
					float fWidth = GetWidth();			// 幅
					float fHeight = GetHeight();		// 高さ
					float fDepth = GetDepth();			// 奥行き


					// ブロックの取得
					D3DXVECTOR3 BlockPos = pObj->GetPos();	// 位置
					float fBlockWidth = pObj->GetWidth();	// 幅
					float fBlockHeight = pObj->GetHeight();	// 高さ
					float fBlockDepth = pObj->GetDepth();	// 奥行き

					// プレイヤーがブロックの手前～奥の間にいる時
					if ((pos.z + fDepth) > (BlockPos.z - fBlockDepth) &&
						(pos.z - fDepth) < (BlockPos.z + fBlockDepth))
					{
						if ((pos.x + fWidth) >= (BlockPos.x - fBlockWidth) &&
							(PosOld.x + fWidth) <= (BlockPos.x - fBlockWidth))
						{// 左からめり込んでいる時

							bHit = true;			// フラグを真にする
							nRot = DIRECTION_LEFT;	// 方向指定
						}
						else if ((pos.x - fWidth) <= (BlockPos.x + fBlockWidth) &&
							(PosOld.x - fWidth) >= (BlockPos.x + fBlockWidth))
						{// 右からめり込んでいる時

							bHit = true;			// フラグを真にする
							nRot = DIRECTION_RIGHT;	// 方向指定
						}
					}

					// プレイヤーがブロックの左辺～右辺の間にいる時

					if ((pos.x + fWidth) > (BlockPos.x - fBlockWidth) &&
						(pos.x - fWidth) < (BlockPos.x + fBlockWidth))
					{
						if ((pos.z + fDepth) >= (BlockPos.z - fBlockDepth) &&
							(PosOld.z + fDepth) <= (BlockPos.z - fBlockDepth))
						{// 前からめり込んでいる時

							bHit = true;			// フラグを真にする
							nRot = DIRECTION_FRONT;	// 方向指定
						}
						else if ((pos.z - fDepth) <= (BlockPos.z + fBlockDepth) &&
							(PosOld.z - fDepth) >= (BlockPos.z + fBlockDepth))
						{// 奥からめり込んでいる時

							bHit = true;			// フラグを真にする
							nRot = DIRECTION_BACK;	// 方向指定
						}
					}

					// 当たっていれば
					if (bHit)
					{
						// ブロックの生成
						switch (nRot)
						{
						case DIRECTION_LEFT:	// 左
							CBlock::Create(1, D3DXVECTOR3(pObj->GetPos().x - fBlockWidth, m_Info.pos.y, pObj->GetPos().z));
							break;

						case DIRECTION_RIGHT:	// 右
							CBlock::Create(1, D3DXVECTOR3(pObj->GetPos().x + fBlockWidth, m_Info.pos.y, pObj->GetPos().z));
							break;

						case DIRECTION_FRONT:	// 前
							CBlock::Create(1, D3DXVECTOR3(pObj->GetPos().x, m_Info.pos.y, pObj->GetPos().z + fBlockDepth));
							break;

						case DIRECTION_BACK:	// 奥
							CBlock::Create(1, D3DXVECTOR3(pObj->GetPos().x, m_Info.pos.y, pObj->GetPos().z - fBlockDepth));
							break;
						}

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