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
CObject *CObject::m_apTop[] = {};
CObject* CObject::m_apCir[] = {};

//========================================
// コンストラクタ
//========================================
CObject::CObject(int nPriority)
{
	m_pNext = NULL;
	m_pPrev = NULL;
	m_type = TYPE_NONE;

	// 先頭オブジェクトがNULLか
	if (m_apTop[nPriority] == NULL)
	{
		m_apTop[nPriority] = this;	// 自分自身を代入(先頭)
		m_apCir[nPriority] = this;	// 自分自身を代入(最後尾)
	}
	else
	{
		this->m_pPrev = m_apCir[nPriority];	// 最後尾のオブジェクトを代入
		m_apCir[nPriority]->m_pNext = this;	// 自分自身を代入
		m_apCir[nPriority] = this;			// 自分自身を代入
	}
	m_nPriority = nPriority;		// 自分自身の優先順位を代入
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
	// 自分自身
	CObject *pObj = this;

	if (pObj == NULL)
	{// 消す奴が使われているかどうか、
		return;
	}
	else if (m_pPrev == NULL && m_pNext == NULL)
	{// オブジェクトが１つしかない時、
		m_apTop[m_nPriority] = NULL;
		m_apCir[m_nPriority] = NULL;
	}
	else if (m_pPrev == NULL)
	{// Topが消えた時、
		m_apTop[m_nPriority] = pObj->m_pNext;	// 先頭のポインタを代入
		m_apTop[m_nPriority]->m_pPrev = NULL;	// 前のポインタを NULL
	}
	else if (m_pNext == NULL)
	{// Cirが消えた時、
		m_apCir[m_nPriority] = pObj->m_pPrev;	// 最後尾のポインタを代入
		m_apCir[m_nPriority]->m_pNext = NULL;	// 次のポインタを NULL
	}
	else
	{// 間のオブジェクトが消えた時、
		pObj->m_pPrev->m_pNext = pObj->m_pNext;	// 次のポインタを代入
		pObj->m_pNext->m_pPrev = pObj->m_pPrev;	// 前のポインタを代入
	}

	delete pObj;
	pObj = NULL;
}

//========================================
// 全体の破棄
//========================================
void CObject::ReleaseAll(void)
{
	for (int nPrio = 0; nPrio < PRIO_MAX; nPrio++)
	{
		// 先頭オブジェクト
		CObject *pObj = m_apTop[nPrio];

		// オブジェクト分の回す
		while (pObj != NULL)
		{
			// 次のオブジェクトがあるか
			if (pObj->m_pNext == NULL)
			{
				// 終了処理
				pObj->Uninit();
				break;
			}
			else
			{
				// 次のオブジェクト
				CObject *pObjNext = pObj->m_pNext;

				// 終了処理
				pObj->Uninit();

				// 一時的の処理
				// ※ 原因　テキストcppの オブジェクト配列　一個目のポインタで全て破棄して
				//			２個目から何もないまま処理を通ってエラーが出る
				if (nPrio == PRIO_UI)
				{
					break;
				}

				pObj = pObjNext;	// 次のオブジェクトポインタを代入
			}
		}
	}
}

//========================================
// 全て破棄(種類毎)
//========================================
void CObject::ReleaseAll(TYPE type)
{
	for (int nPrio = 0; nPrio < PRIO_MAX; nPrio++)
	{
		// 先頭オブジェクト
		CObject *pObj = m_apTop[nPrio];

		// オブジェクト分の回す
		while (pObj != NULL)
		{
			// 次のオブジェクト
			CObject *pObjNext = pObj->m_pNext;

			// 指定した種類かどうか
			if (pObj->GetType() == type)
			{
				// 次のオブジェクトがあるか
				if (pObj->m_pNext == NULL)
				{
					// 終了処理
					pObj->Uninit();
				}
				else
				{
					// 終了処理
					pObj->Uninit();
				}
			}
			pObj = pObjNext;	// 次のオブジェクトポインタを代入
		}
	}
}

//========================================
// 全体の更新
//========================================
void CObject::UpdateAll(void)
{
	for (int nPrio = 0; nPrio < PRIO_MAX; nPrio++)
	{
		// 先頭オブジェクト
		CObject *pObj = m_apTop[nPrio];

		// オブジェクト分の回す
		while (pObj != NULL)
		{
			// 次のオブジェクト
			CObject *pObjNext = pObj->m_pNext;

			// 更新処理
			pObj->Update();

			// 次のオブジェクトを代入
			pObj = pObjNext;
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

	for (int nPrio = 0; nPrio < PRIO_MAX; nPrio++)
	{
		// 先頭オブジェクト
		CObject *pObj = m_apTop[nPrio];

		// オブジェクト分の回す
		while (pObj != NULL)
		{
			// 描画処理
			pObj->Draw();

			// 次のオブジェクトがあるかどうか、
			if (pObj->m_pNext == NULL)
			{
				break;
			}
			else
			{
				// 次のオブジェクトを代入
				pObj = pObj->m_pNext;
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
CScore *CObject::GetScore(int nPrio,int Idx)
{
	int nIdx = 0;

	// 先頭オブジェクト
	CObject *pObj = m_apTop[nPrio];

	if (pObj == NULL)
	{
		return NULL;
	}

	while (pObj != NULL)
	{
		if (pObj->m_type == TYPE_SCORE)
		{
			if (pObj->m_pNext == NULL)
			{
				return NULL;
			}
			else
			{
				if (nIdx == Idx)
				{
					break;
				}
				nIdx++;
			}
		}
		pObj = pObj->m_pNext;
	}
	
	return (CScore*)pObj;
}

//========================================
// Time情報取得
//========================================
CTime *CObject::GetTime(int nPrio, int Idx)
{
	int nIdx = 0;

	// 先頭オブジェクト
	CObject *pObj = m_apTop[nPrio];

	if (pObj == NULL)
	{
		return NULL;
	}
	else if (pObj->m_type != TYPE_TIME)
	{
		return NULL;
	}

	while (pObj != NULL)
	{
		if (pObj->m_pNext == NULL)
		{
			return NULL;
		}
		else
		{
			pObj = pObj->m_pNext;

			if (nIdx == Idx)
			{
				break;
			}
			nIdx++;
		}
	}

	return (CTime*)pObj;
}