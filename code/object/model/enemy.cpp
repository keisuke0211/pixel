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

//****************************************
// マクロ定義
//****************************************
#define ROT_DIAMETER	(0.075f)		// 回転倍率

//========================================
// コンストラクタ
//========================================
CEnemy::CEnemy(int nPriority) : CObjectX(nPriority)
{
	// 値をクリア
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.posOld = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.moveRot = INIT_D3DXVECTOR3;
	m_Info.targetRot = INIT_D3DXVECTOR3;
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.move = INIT_D3DXVECTOR3;
	m_Info.nType = 0;
	m_Info.nLife = 0;
	m_Info.nLifeMax = 0;
	m_Info.state = STATE_NORMAL;
	m_Info.nCntState = 0;
	m_Info.nCntTime = 0;
	m_Info.nStandTime = 0;
	m_Info.bRotMove = false;
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
CEnemy *CEnemy::Create(int nType, int nMove, D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nCntTime)
{
	CEnemy *pEnemy = new CEnemy;

	pEnemy->SetModel(MODEL_ENEMY_00 + nType);
	pEnemy->m_Info.nType = nType;

	// 初期化処理
	pEnemy->Init();

	pEnemy->m_Info.pos = pos;
	pEnemy->m_Info.rot = rot;
	pEnemy->m_Info.moveRot = rot;
	pEnemy->m_Info.nMove = nMove;
	pEnemy->m_Info.nTimeMax = nCntTime;
	pEnemy->SetPos(pEnemy->m_Info.pos);
	pEnemy->SetRot(pEnemy->m_Info.rot);
	pEnemy->SetColor(pEnemy->m_Info.col);

	if (nMove != 0)
	{
		pEnemy->m_Info.move.x = sinf(pEnemy->m_Info.moveRot.y) * -3;
		pEnemy->m_Info.move.z = cosf(pEnemy->m_Info.moveRot.y) * -3;
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
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.moveRot = D3DXVECTOR3(0.0f,0.0f, 0.0f);
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nLife = m_Info.nType + 1;
	m_Info.nLifeMax = m_Info.nLife;

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
		bool bCube = false;	// キューブに当たったか

		// 過去の位置・向きの更新
		m_Info.posOld = m_Info.pos;

		// 状態推移
		StateShift();

		if (m_Info.state != STATE_STAND)
		{
			// 移動量の代入
			m_Info.pos.x += m_Info.move.x;
		}

		// 当たり判定
		if (Collision(PRIO_OBJECT, TYPE_PLAYER, VECTOR_X, m_Info.pos)) {}
		if (Collision(PRIO_BLOCK, TYPE_BLOCK, VECTOR_X,m_Info.pos)){ }
		if (Collision(PRIO_CUBE, TYPE_CUBE, VECTOR_X, m_Info.pos)) { bCube = true; }

		if (m_Info.state != STATE_STAND)
		{
			// 移動量の代入
			m_Info.pos.z += m_Info.move.z;
		}

		if (Collision(PRIO_OBJECT, TYPE_PLAYER, VECTOR_Z, m_Info.pos)) {}
		if (Collision(PRIO_BLOCK, TYPE_BLOCK, VECTOR_Z, m_Info.pos)){ }
		if (Collision(PRIO_CUBE, TYPE_CUBE, VECTOR_Z, m_Info.pos)) { bCube = true; }

		// 移動処理
		if (m_Info.state != STATE_STAND && !bCube && !m_Info.bRotMove)
		{
			// 当たり判定
			if (!Collision(PRIO_OBJECT, TYPE_PLAYER, VECTOR_X, m_Info.pos)||
				!Collision(PRIO_BLOCK, TYPE_BLOCK, VECTOR_X, m_Info.pos) ||
				!Collision(PRIO_CUBE, TYPE_CUBE, VECTOR_X, m_Info.pos) ||
				!Collision(PRIO_OBJECT, TYPE_PLAYER, VECTOR_Z, m_Info.pos) ||
				!Collision(PRIO_BLOCK, TYPE_BLOCK, VECTOR_Z, m_Info.pos) ||
				!Collision(PRIO_CUBE, TYPE_CUBE, VECTOR_Z, m_Info.pos))
			{
				if (++m_Info.nCntTime >= m_Info.nTimeMax && m_Info.nMove != 0)
				{
					// 待機状態にする
					SetState(STATE_STAND);

					m_Info.nCntTime = 0;
					m_Info.nStandTime = 0;

					switch (m_Info.nMove)
					{
					break;
					case 1:
					{
						if (m_Info.rot.y == 0.0f)
						{
							m_Info.moveRot.y = 3.14f;
						}
						else if (m_Info.rot.y = 3.14f)
						{
							m_Info.moveRot.y = 0.0f;
						}
					}
					break;
					case 2:
					{
						if (m_Info.rot.y == 1.57f)
						{
							m_Info.moveRot.y = -1.57f;
						}
						else if (m_Info.rot.y = -1.57f)
						{
							m_Info.moveRot.y = 1.57f;
						}
					}
					break;
					case 3:
					{
						m_Info.moveRot.y += 1.57f;
						ControlAngle(&m_Info.rot.y);
					}
					break;
					case 4:
					{
						m_Info.moveRot.y -= 1.57f;
						ControlAngle(&m_Info.rot.y);
					}
					break;
					default:
						break;
					}

					// 目標向きに移動向きを代入
					m_Info.targetRot = m_Info.moveRot;
					m_Info.bRotMove = true;

					m_Info.move.x = sinf(m_Info.moveRot.y) * -3;
					m_Info.move.z = cosf(m_Info.moveRot.y) * -3;
				}
			}
		}
		else if (m_Info.state == STATE_STAND && m_Info.bRotMove)
		{
			RotControl(&m_Info.rot);
			RotControl(&m_Info.moveRot);
			RotControl(&m_Info.targetRot);

			// 角度を目標角度に向けて推移する
			m_Info.rot.y += AngleDifference(m_Info.rot.y, m_Info.targetRot.y) * ROT_DIAMETER;

			// 範囲内に入ったら
			if (m_Info.rot.y > m_Info.targetRot.y - 0.05f && m_Info.rot.y < m_Info.targetRot.y + 0.05f)
			{
				m_Info.rot.y = m_Info.targetRot.y;
				m_Info.bRotMove = false;
			}
			SetRot(m_Info.rot);
		}

		CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// キーボード

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
bool CEnemy::Collision(PRIO nPrio, TYPE nType, VECTOR vector, D3DXVECTOR3 pos)
{
	// 先頭オブジェクトを取得
	CObject *pObj = CObject::GetTop(nPrio);

	bool bHit = false;

	while (pObj != NULL)
	{// 使用されている時、

		// 次のオブジェクト
		CObject *pObjNext = pObj->GetNext();

		// 種類を取得
		TYPE type = pObj->GetType();

		// エネミーの各パーツの取得
		D3DXVECTOR3 PosOld = GetPosOld();	// 位置(過去)
		D3DXVECTOR3 RotOld = GetRotOld();	// 向き(過去)

		float fWidth = 30;		// 幅
		float fHeight = 10;		// 高さ
		float fDepth = 15;		// 奥行き

		if (TYPE_BLOCK == nType)
		{
			fHeight = 1;
		}

		// 各種類の当たり判定
		if (type == nType)
		{
			// 相手の取得
			D3DXVECTOR3 PairPos = pObj->GetPos();		// 位置
			D3DXVECTOR3 PairPosOld = pObj->GetPosOld();	// 位置(過去)
			float fPairWidth = pObj->GetWidth();		// 幅
			float fPairHeight = pObj->GetHeight();		// 高さ
			float fPairDepth = pObj->GetDepth();		// 奥行き

			fPairWidth = round(fPairWidth);
			fPairHeight = round(fPairHeight);
			fPairDepth = round(fPairDepth);

			if (nType == TYPE_PLAYER)
			{
				fPairWidth = 20;
				fPairHeight = 10;
				fPairDepth = 20;
			}

			switch (vector)
			{
			case VECTOR_X: {	/* X方向 */

				if (CollsionX(pos, PairPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
				{// 奥辺と手前辺が相手の幅の内側の時、

					if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_LEFT))
					{// 左からめり込んでいる時
						bHit = true;
						pos.x = (PairPos.x - fPairWidth) - fWidth;
					}
					else if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_RIGHT))
					{// 右からめり込んでいる時
						bHit = true;
						pos.x = (PairPos.x + fPairWidth) + fWidth;
					}
				}
			}
						   break;
			case VECTOR_Y: {	/* Y方向 */

				if (CollsionY(pos, PairPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
				{// 左辺と右辺が相手の幅の内側の時、

					if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_DOWN))
					{// 下からめり込んでいる時
						bHit = true;
						pos.y = (PairPos.y - fPairHeight) - fHeight;
					}
					else if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_UP))
					{// 上からめり込んでいる時
						bHit = true;
						pos.y = (PairPos.y + fPairHeight) + fHeight;
						m_Info.move.y = 0.0f;
					}
				}
			}
						   break;
			case VECTOR_Z: {	/* Z方向 */

				if (CollsionZ(pos, PairPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
				{// 奥辺と手前辺が相手の幅の内側の時、

					if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_BACK))
					{// 後ろからめり込んでいる時
						bHit = true;
						pos.z = (PairPos.z - fPairDepth) - fDepth;
					}
					else if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_FRONT))
					{// 前からめり込んでいる時
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

			}
			m_Info.pos = pos;
			return TRUE;
		}
		pObj = pObjNext;	// 次のオブジェクトを代入
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

		int nScore = (100 * m_Info.nLifeMax) * nDamage;

		// スコア設定
		CScore::SetScore(nScore);

		// 爆発のSE再生
		pSound->PlaySound(CSound::TYPE_EXPLOSIO);

		return;
	}
	else
	{
		// ヒットSEの再生
		pSound->PlaySound(CSound::TYPE_HIT);

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
	case STATE_NORMAL: { /* 通常 */

		 // 状態の設定
		m_Info.state = STATE_NORMAL;

		// ダメージ色の設定
		m_Info.col = D3DXCOLOR(1.0f, 1.0f, 1.1f, 1.0f);
	}
	   break;

	case STATE_DAMAGE: { /* ダメージ */

		m_Info.state = STATE_DAMAGE;	// 状態設定
		m_Info.nCntState = 10;			// 時間

		// ダメージ色の設定
		m_Info.col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	}
	   break;
	case STATE_STAND: {/* 待機 */
		m_Info.state = STATE_STAND;
		m_Info.nCntState = STAND_TIME;
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
	case STATE_STAND: { /* 待機 */
		if (--m_Info.nCntState <= 0)
		{
			if (!m_Info.bRotMove)
			{
				// 通常状態にする
				SetState(STATE_NORMAL);
			}
		}
	}
	   break;
	}
}