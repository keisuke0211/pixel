//========================================
// 
// オブジェクト処理
// 
//========================================
// *** object.cpp ***
//========================================
#include "../manager.h"
#include "object.h"
#include "../renderer.h"
#include "../camera.h"

// 静的変数
int CObject::m_nNumAll = 0;													// オブジェクト総数
CObject *CObject::m_apObject[CObject::PRIO_MAX][CObject::MAX_OBJECT] = {};	// オブジェクトのポインタ

//========================================
// コンストラクタ
//========================================
CObject::CObject(int nPriority)
{
	if (nPriority == CObject::TYPE_NONE)
	{
		nPriority = CObject::TYPE_NONE;
	}

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nPriority][nCntObject] == NULL)
		{
			m_apObject[nPriority][nCntObject] = this;	// 自分自身を代入
			m_nPriority = nPriority;					// 自分自身の優先順位を代入
			m_nID = nCntObject;							// 自分自身のIDを代入
			m_nNumAll++;								// 総数の加算
			break;
		}
	}
}

//========================================
// デストラクタ
//========================================
CObject::~CObject()
{
	
}

//========================================
// 破棄
//========================================
void CObject::Release(void)
{
	int nIdx = m_nID;
	int nPri = m_nPriority;

	if (m_apObject[nPri][nIdx] != NULL)
	{
		if (m_apObject[nPri][nIdx])
		{
			delete m_apObject[nPri][nIdx];
			m_apObject[nPri][nIdx] = NULL;
			m_nNumAll--;				// 総数のカウントダウン
		}
	}
}

//========================================
// 全体の破棄
//========================================
void CObject::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIO_MAX; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				m_apObject[nCntPriority][nCntObject]->Uninit();
			}
		}
	}
}

//========================================
// 全体の更新
//========================================
void CObject::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIO_MAX; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				m_apObject[nCntPriority][nCntObject]->Update();
			}
		}
	}
}

//========================================
// 全体の描画
//========================================
void CObject::DrawAll(void)
{
	CCamera *pCamera = CManager::GetCamera();

	// デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// カメラの設定
	pCamera->SetCamera();

	for (int nCntPriority = 0; nCntPriority < PRIO_MAX; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				m_apObject[nCntPriority][nCntObject]->Draw();
			}
		}
	}
}

//========================================
// 種類の設定
//========================================
void CObject::SetType(TYPE type)
{
	m_type = type;
}

//========================================
// Score情報取得
//========================================
CScore *CObject::GetScore(int nPriority,int nIdx)
{
	if (m_apObject[nPriority][nIdx] == NULL)
	{
		return NULL;
	}
	else if (m_apObject[nPriority][nIdx]->m_type != TYPE_SCORE)
	{
		return NULL;
	}

	return (CScore*)m_apObject[nPriority][nIdx];
}

//========================================
// Time情報取得
//========================================
CTime *CObject::GetTime(int nPriority, int nIdx)
{
	if (m_apObject[nPriority][nIdx] == NULL)
	{
		return NULL;
	}
	else if (m_apObject[nPriority][nIdx]->m_type != TYPE_TIME)
	{
		return NULL;
	}

	return (CTime*)m_apObject[nPriority][nIdx];
}