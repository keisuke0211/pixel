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


// 静的変数
CEnemy::SetInfo *CEnemy::pSet = NULL;
int CEnemy::nNumSet = 0;

//========================================
// コンストラクタ
//========================================
CEnemy::CEnemy(int nPriority) : CObjectX(nPriority)
{
	// 値をクリア
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.move = INIT_D3DXVECTOR3;
	m_Info.nType = 0;
	m_Info.nLife = 0;
}

//========================================
// デストラクタ
//========================================
CEnemy::~CEnemy()
{

}

//========================================
// 生成
//========================================
CEnemy *CEnemy::Create(void)
{
	CEnemy *pEnemy = new CEnemy;

	pEnemy->SetModel(9);

	// 初期化処理
	pEnemy->Init();

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

	m_Info.pos = D3DXVECTOR3(0.0f, -20.0f, -150.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 3.14f, 0.0f);
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nLife = 1;
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
	CObjectX::Uninit();
}

//========================================
// 更新
//========================================
void CEnemy::Update(void)
{
	// 位置を代入
	m_Info.posOld = m_Info.pos;

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

	if (m_Info.nLife >= 0)
	{
		//for (int nCntPtcl = 0; nCntPtcl < 16; nCntPtcl++) 
		//{
		//	// エフェクト2D生成
		//	CParticle2D *pObj = CParticle2D::Create();
		//	// 位置設定
		//	pObj->SetPos(GetPos());
		//	// 向き設定
		//	pObj->SetRot(D3DXVECTOR3(0.0f, 0.0f, ((float)rand() / RAND_MAX) * D3DX_PI * 2.0f));
		//	// 移動量設定
		//	pObj->SetMove(5.0f + (5.0f * ((float)rand() / RAND_MAX)));
		//	// 寿命設定
		//	pObj->SetLife(8 + (rand() % 24));
		//}

		// 敵の破棄
		Uninit();

		// スコア設定
		CScore::SetScore(300);

		pSound->PlaySound(3);

		return;
	}
	else
	{
		pSound->PlaySound(2);
	}
}

//========================================
// 読み込み
//========================================

//void CEnemy::Load(void)
//{
//	CSVFILE<int> data;
//
//	// 読み込み
//	data.csv_read("data\\GAMEDATA\\BLOCK\\BLOCK_DATA.csv", true, true, ',');
//
//	// 動的確保
//	int nLineMax = data.cell.size() - 1;
//	pSet = new SetInfo[nLineMax];
//
//	for (int nLine = 0; nLine < data.cell.size(); nLine++)
//	{
//		int nRowMax = data.cell.at(nLine).size();
//
//		for (int nRow = 0; nRow < data.cell.at(nLine).size(); nRow++)
//		{
//			switch (nRow)
//			{
//				// 種類
//			case SET_TYPE:
//			{
//				pSet[nLine].nType = (int)data.cell.at(nLine).at(nRow);
//			}
//			break;
//
//			// 位置
//			case SET_POS:
//			{
//				pSet[nLine].pos.x = (int)data.cell.at(nLine).at(nRow); nRow++;
//				pSet[nLine].pos.y = (int)data.cell.at(nLine).at(nRow); nRow++;
//				pSet[nLine].pos.z = (int)data.cell.at(nLine).at(nRow);
//			}
//			break;
//
//			// 移動量
//			case SET_SPEED:
//			{
//				pSet[nLine].nSpeed = data.cell.at(nLine).at(nRow);
//			}
//			break;
//
//			// 部隊ID
//			case SET_UNIT:
//			{
//				pSet[nLine].nStage = (int)data.cell.at(nLine).at(nRow);
//			}
//			break;
//
//			// ステージID
//			case SET_STAGE:
//			{
//				pSet[nLine].nStage = (int)data.cell.at(nLine).at(nRow);
//			}
//			break;
//			}
//		}
//	}
//}

//========================================
// 配置
//========================================
void CEnemy::SetEnemy(int nStage, int nUnit)
{
	for (int nCntSet = 0; nCntSet < nNumSet; nCntSet++, pSet++)
	{
		if (!pSet->bSet && pSet->nStage == nStage && pSet->nUnit == nUnit)
		{


			pSet->bSet = true;
		}
	}
}