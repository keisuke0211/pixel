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
#include "../2D/score.h"
#include "particleX.h"


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
CEnemy *CEnemy::Create(D3DXVECTOR3 pos)
{
	CEnemy *pEnemy = new CEnemy;

	pEnemy->SetModel(MODEL_ENEMY_00);

	// 初期化処理
	pEnemy->Init();

	pEnemy->m_Info.pos = pos;
	pEnemy->SetPos(pEnemy->m_Info.pos);
	pEnemy->SetRot(pEnemy->m_Info.rot);
	pEnemy->SetColor(pEnemy->m_Info.col);
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

	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, -0.0f);
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
	// 過去の位置・向きの更新
	m_Info.posOld = m_Info.pos;
	m_Info.rotOld = m_Info.rot;

	// 状態推移
	StateShift();

	SetPos(m_Info.pos);
	SetRot(m_Info.rot);
	SetColor(m_Info.col);

	CObjectX::Update();
}

//========================================
// 描画
//========================================
void CEnemy::Draw(void)
{
	CObjectX::Draw();
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

//========================================
// 読み込み
//========================================
void CEnemy::Load(void)
{
	//// 読み込み

	//// 動的確保

	//for (int nRow1 = 0; nRow1 < 0; nRow1++)
	//{
	//	for (int nLine = 0; nLine < 0; nLine++)
	//	{
	//		switch (nLine)
	//		{
	//			// 種類
	//		case SET_TYPE:
	//		{
	//			pSet[nRow1].nType = 0;
	//		}
	//		break;

	//		// 位置
	//		case SET_POS:
	//		{
	//			pSet[nRow1].pos.x = 0.0f; nLine++;
	//			pSet[nRow1].pos.y = 0.0f; nLine++;
	//			pSet[nRow1].pos.z = 0.0f;
	//		}
	//		break;

	//		// 移動量
	//		case SET_SPEED:
	//		{
	//			pSet[nRow1].nSpeed = 0;
	//		}
	//		break;

	//		// 部隊ID
	//		case SET_UNIT:
	//		{
	//			pSet[nRow1].nStage = 0;
	//		}
	//		break;

	//		// ステージID
	//		case SET_STAGE:
	//		{
	//			pSet[nRow1].nStage = 0;
	//		}
	//		break;
	//		}
	//	}
	//}
}

//========================================
// 配置
//========================================
void CEnemy::SetEnemy(int nStage, int nUnit)
{
	for (int nCntSet = 0; nCntSet < m_nNumAll; nCntSet++, pSet++)
	{
		if (!pSet->bSet && pSet->nStage == nStage && pSet->nUnit == nUnit)
		{


			pSet->bSet = true;
		}
	}
}