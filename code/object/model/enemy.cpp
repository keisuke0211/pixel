//========================================
// 
// エネミー処理
// 
//========================================
// *** enemy.cpp ***
//========================================
#include "enemy.h"
#include "../../scene/pause.h"
#include "../../manager.h"
#include "../../system/renderer.h"
#include "../../system/sound.h"
#include "../UI/score.h"
#include "../EFFECT/particleX.h"
#include "block.h"
#include "bullet_cube.h"
#include "../../system/input.h"

// 静的変数
CEnemy::SetInfo *CEnemy::pSet = NULL;
int CEnemy::m_nNumAll = 0;

//========================================
// コンストラクタ
//========================================
CEnemy::CEnemy(int nPriority) : CObjectX(nPriority)
{
	// 値をクリア
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.posOld = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.rotOld = INIT_D3DXVECTOR3;
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.move = INIT_D3DXVECTOR3;
	m_Info.nType = 0;
	m_Info.nLife = 0;
	m_Info.state = STATE_NORMAL;
	m_Info.nCntState = 0;
	m_Info.nCntTime = 0;
	m_nNumAll++;
}

//========================================
// デストラクタ
//========================================
CEnemy::~CEnemy()
{
	m_nNumAll--;
}

//========================================
// 生成
//========================================
CEnemy *CEnemy::Create(int nType, int nMove, D3DXVECTOR3 pos)
{
	CEnemy *pEnemy = new CEnemy;

	pEnemy->SetModel(MODEL_ENEMY_00 + nType);

	// 初期化処理
	pEnemy->Init();

	pEnemy->m_Info.pos = pos;
	pEnemy->m_Info.nMove = nMove;
	pEnemy->SetPos(pEnemy->m_Info.pos);
	pEnemy->SetRot(pEnemy->m_Info.rot);
	pEnemy->SetColor(pEnemy->m_Info.col);

	if (pEnemy->m_Info.nMove == 1)
	{
		pEnemy->m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 3.0f);
	}

	return pEnemy;
}

//========================================
// 初期化
//========================================
HRESULT CEnemy::Init(void)
{
	CObjectX::Init();

	// 種類の設定
	SetType(TYPE_ENEMY);

	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 3.14f, 0.0f);
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nLife = 3;
	m_Info.nType = 0;

	// 生成
	SetPos(m_Info.pos);
	SetRot(m_Info.rot);
	SetColor(m_Info.col);

	return S_OK;
}

//========================================
// 終了
//========================================
void CEnemy::Uninit(void)
{
	CSound *pSound = CManager::GetSound();

	pSound->StopSound();

	CObjectX::Uninit();
}

//========================================
// 更新
//========================================
void CEnemy::Update(void)
{
	bool bPause = CPause::IsPause();

	if (!bPause)
	{

		// 過去の位置・向きの更新
		m_Info.posOld = m_Info.pos;
		m_Info.rotOld = m_Info.rot;

		// 状態推移
		StateShift();

		// 移動量の代入
		m_Info.pos.x += m_Info.move.x;

		// 当たり判定
		if (Collsion(VECTOR_X, m_Info.pos))
		{

		}

		// 移動量の代入
		m_Info.pos.z += m_Info.move.z;

		if (Collsion(VECTOR_Z, m_Info.pos))
		{

		}

		// 仮の移動処理
		if (++m_Info.nCntTime >= 240 && m_Info.nMove == 1)
		{
			m_Info.move.z *= -1;
			m_Info.nCntTime = 0;

			if (m_Info.rot.y == 0.0f)
			{
				m_Info.rot.y = 3.14f;
			}
			else if (m_Info.rot.y = 3.14f)
			{
				m_Info.rot.y = 0.0f;
			}
			SetRot(m_Info.rot);
		}

		CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// キーボード

		SetPos(m_Info.pos);
		SetColor(m_Info.col);

		CObjectX::Update();
	}
}

//========================================
// 描画
//========================================
void CEnemy::Draw(void)
{
	CObjectX::Draw();
}

//========================================
// 当たり判定
//========================================
bool CEnemy::Collsion(VECTOR vector, D3DXVECTOR3 pos)
{
	bool bHit = false;

	for (int nCntPrio = 0; nCntPrio < PRIO_MAX; nCntPrio++)
	{
		// 先頭オブジェクトを取得
		CObject *pObj = CObject::GetTop(nCntPrio);

		while (pObj != NULL)
		{// 使用されている時、

			// 次のオブジェクト
			CObject *pObjNext = pObj->GetNext();

			// 種類を取得
			TYPE type = pObj->GetType();

			// エネミーの各パーツの取得
			D3DXVECTOR3 PosOld = GetPosOld();	// 位置(過去)
			D3DXVECTOR3 RotOld = GetRotOld();	// 向き(過去)
			float fWidth = GetWidth();			// 幅
			float fHeight = GetHeight();		// 高さ
			float fDepth = GetDepth();			// 奥行き

			// 各種類の当たり判定
			if (type == TYPE_BLOCK)
			{// ブロックだったら

				// ブロックの取得
				D3DXVECTOR3 PairPos = pObj->GetPos();		// 位置
				D3DXVECTOR3 PairPosOld = pObj->GetPosOld();	// 位置(過去)
				float fPairWidth = pObj->GetWidth();		// 幅
				float fPairHeight = pObj->GetHeight();		// 高さ
				float fPairDepth = pObj->GetDepth();		// 奥行き

				switch (vector)
				{
				case VECTOR_X: {	/* X方向 */

					if ((pos.z + fDepth) > (PairPos.z - fPairDepth) &&
						(pos.z - fDepth) < (PairPos.z + fPairDepth) &&
						(pos.y + fHeight) > (PairPos.y - fPairHeight) &&
						(pos.y - fHeight) < (PairPos.y + fPairHeight))
					{// 奥辺と手前辺がブロックの幅の内側の時、

						if ((pos.x + fWidth) >= (PairPos.x - fPairWidth) &&
							(PosOld.x + fWidth) <= (PairPos.x - fPairWidth))
						{// 左からめり込んでいる時

							bHit = true;
							pos.x = (PairPos.x - fPairWidth) - fWidth;
						}
						else if ((pos.x - fWidth) <= (PairPos.x + fPairWidth) &&
							(PosOld.x - fWidth) >= (PairPos.x + fPairWidth))
						{// 右からめり込んでいる時

							bHit = true;
							pos.x = (PairPos.x + fPairWidth) + fWidth;
						}
					}
				}
				   break;
				case VECTOR_Y: {	/* Y方向 */

					if ((pos.x + fWidth) > (PairPos.x - fPairWidth) &&
						(pos.x - fWidth) < (PairPos.x + fPairWidth) &&
						(pos.z + fDepth) > (PairPos.z - fPairDepth) &&
						(pos.z - fDepth) < (PairPos.z + fPairDepth))
					{// 左辺と右辺が相手の幅の内側の時、

						if ((pos.y + fHeight) > (PairPos.y - fPairHeight) &&
							(PosOld.y + fHeight) <= (PairPos.y - fPairHeight))
						{// 下からめり込んでいる時

							bHit = true;
							pos.y = (PairPos.y - fPairHeight) - fHeight;
						}
						else if ((pos.y - fHeight) < (PairPos.y + fPairHeight) &&
							(PosOld.y - fHeight) >= (PairPos.y + fPairHeight))
						{// 上からめり込んでいる時

							bHit = true;
							pos.y = (PairPos.y + fPairHeight) + fHeight;
						}
					}
				}
				   break;
				case VECTOR_Z: {	/* Z方向 */

					if ((pos.x + fWidth) > (PairPos.x - fPairWidth) &&
						(pos.x - fWidth) < (PairPos.x + fPairWidth) &&
						(pos.y + fHeight) > (PairPos.y - fPairHeight) &&
						(pos.y - fHeight) < (PairPos.y + fPairHeight))
					{// 左辺と右辺が相手の幅の内側の時、

						if ((pos.z + fDepth) >= (PairPos.z - fPairDepth) &&
							(PosOld.z + fDepth) <= (PairPos.z - fPairDepth))
						{// 前からめり込んでいる時

							bHit = true;
							pos.z = (PairPos.z - fPairDepth) - fDepth;
						}
						else if ((pos.z - fDepth) <= (PairPos.z + fPairDepth) &&
							(PosOld.z - fDepth) >= (PairPos.z + fPairDepth))
						{// 奥からめり込んでいる時

							bHit = true;
							pos.z = (PairPos.z + fPairDepth) + fDepth;
						}
					}
				}
				   break;
				}

			}
			else if (type == TYPE_CUBE)
			{// キューブだったら

				 // キューブの取得
				D3DXVECTOR3 PairPos = pObj->GetPos();		// 位置
				D3DXVECTOR3 PairPosOld = pObj->GetPosOld();	// 位置(過去)
				float fPairWidth = pObj->GetWidth();		// 幅
				float fPairHeight = pObj->GetHeight();		// 高さ
				float fPairDepth = pObj->GetDepth();		// 奥行き

				switch (vector)
				{
				case VECTOR_X: {	/* X方向 */

					if ((pos.z + fDepth) > (PairPos.z - fPairDepth) &&
						(pos.z - fDepth) < (PairPos.z + fPairDepth) &&
						(pos.y + fHeight) > (PairPos.y - fPairHeight) &&
						(pos.y - fHeight) < (PairPos.y + fPairHeight))
					{// 奥辺と手前辺がブロックの幅の内側の時、

						if ((pos.x + fWidth) >= (PairPos.x - fPairWidth) &&
							(PosOld.x + fWidth) <= (PairPos.x - fPairWidth))
						{// 左からめり込んでいる時

							bHit = true;
							pos.x = (PairPos.x - fPairWidth) - fWidth;
						}
						else if ((pos.x - fWidth) <= (PairPos.x + fPairWidth) &&
							(PosOld.x - fWidth) >= (PairPos.x + fPairWidth))
						{// 右からめり込んでいる時

							bHit = true;
							pos.x = (PairPos.x + fPairWidth) + fWidth;
						}
					}
				}
				   break;
				case VECTOR_Y: {	/* Y方向 */

					if ((pos.x + fWidth) > (PairPos.x - fPairWidth) &&
						(pos.x - fWidth) < (PairPos.x + fPairWidth) &&
						(pos.z + fDepth) > (PairPos.z - fPairDepth) &&
						(pos.z - fDepth) < (PairPos.z + fPairDepth))
					{// 左辺と右辺が相手の幅の内側の時、

						if ((pos.y + fHeight) > (PairPos.y - fPairHeight) &&
							(PosOld.y + fHeight) <= (PairPos.y - fPairHeight))
						{// 下からめり込んでいる時

							bHit = true;
							pos.y = (PairPos.y - fPairHeight) - fHeight;
						}
						else if ((pos.y - fHeight) < (PairPos.y + fPairHeight) &&
							(PosOld.y - fHeight) >= (PairPos.y + fPairHeight))
						{// 上からめり込んでいる時

							bHit = true;
							pos.y = (PairPos.y + fPairHeight) + fHeight;
						}
					}
				}
				   break;
				case VECTOR_Z: {	/* Z方向 */

					if ((pos.x + fWidth) > (PairPos.x - fPairWidth) &&
						(pos.x - fWidth) < (PairPos.x + fPairWidth) &&
						(pos.y + fHeight) > (PairPos.y - fPairHeight) &&
						(pos.y - fHeight) < (PairPos.y + fPairHeight))
					{// 左辺と右辺が相手の幅の内側の時、

						if ((pos.z + fDepth) >= (PairPos.z - fPairDepth) &&
							(PosOld.z + fDepth) <= (PairPos.z - fPairDepth))
						{// 前からめり込んでいる時

							bHit = true;
							pos.z = (PairPos.z - fPairDepth) - fDepth;
						}
						else if ((pos.z - fDepth) <= (PairPos.z + fPairDepth) &&
							(PosOld.z - fDepth) >= (PairPos.z + fPairDepth))
						{// 奥からめり込んでいる時

							bHit = true;
							pos.z = (PairPos.z + fPairDepth) + fDepth;
						}
					}
				}
				   break;
				}
			}

			if (bHit)
			{
				if (type == TYPE_BLOCK)
				{

				}
				else if (type == TYPE_CUBE)
				{
					// ダイナミックキャストする
					CCube *pCube = dynamic_cast<CCube*>(pObj);

					pCube->SetCubeLife(1);
				}
				return TRUE;
			}
			pObj = pObjNext;	// 次のオブジェクトを代入
		}
	}
	return FALSE;
}

//========================================
// ヒット処理
//========================================
void CEnemy::HitLife(int nDamage)
{
	CSound *pSound = CManager::GetSound();

	m_Info.nLife -= nDamage;

	if (m_Info.nLife <= 0)
	{
		// パーティクル生成
		CParticleX *pObj = CParticleX::Create();
		pObj->Par_SetPos(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 20, m_Info.pos.z));
		pObj->Par_SetRot(INIT_D3DXVECTOR3);
		pObj->Par_SetMove(D3DXVECTOR3(10.0f, 3.0f, 10.0f));
		pObj->Par_SetType(0);
		pObj->Par_SetLife(100);
		pObj->Par_SetCol(D3DXCOLOR(0.3f, 0.8f, 0.8f, 1.0f));
		pObj->Par_SetForm(15);

		// 敵の破棄
		Uninit();

		// スコア設定
		CScore::SetScore(300);

		// 爆発のSE再生
		pSound->PlaySound(3);

		return;
	}
	else
	{
		// ヒットSEの再生
		pSound->PlaySound(2);

		// ダメージ状態
		SetState(STATE_DAMAGE);


		// パーティクル生成
		CParticleX *pObj = CParticleX::Create();
		pObj->Par_SetPos(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 20, m_Info.pos.z));
		pObj->Par_SetRot(INIT_D3DXVECTOR3);
		pObj->Par_SetMove(D3DXVECTOR3(10.0f, 3.0f, 10.0f));
		pObj->Par_SetType(0);
		pObj->Par_SetLife(50);
		pObj->Par_SetCol(D3DXCOLOR(0.3, 0.8f, 0.8f, 1.0f));
		pObj->Par_SetForm(15);
	}
}

//========================================
// 状態設定
//========================================
void CEnemy::SetState(STATE state)
{
	// 状態
	switch (state)
	{
	case STATE_NORMAL: { /* 通常状態 */

		 // 状態の設定
		m_Info.state = STATE_NORMAL;

		// ダメージ色の設定
		m_Info.col = D3DXCOLOR(1.0f, 1.0f, 1.1f, 1.0f);
	}
	   break;

	case STATE_DAMAGE: { /* ダメージ状態 */

		m_Info.state = STATE_DAMAGE;	// 状態設定
		m_Info.nCntState = 10;			// 時間

		// ダメージ色の設定
		m_Info.col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	}
	   break;
	}
}

//========================================
// 状態推移
//========================================
void CEnemy::StateShift(void)
{
	// 状態
	switch (m_Info.state)
	{
	case STATE_NORMAL: { /* 通常状態 */

	}
	   break;
	case STATE_DAMAGE: { /* ダメージ状態 */

		 // 状態を切替える
		if (--m_Info.nCntState <= 0)
		{
			// 通常状態にする
			SetState(STATE_NORMAL);
		}
	}
	   break;
	}
}