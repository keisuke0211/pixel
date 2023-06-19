//========================================
//
// スコア処理
//
//========================================
// *** score2D.cpp ***
//========================================
#include "time.h"

// 静的メンバ変数定義
int CTime::m_nTime = 0;	// タイム

//========================================
// コンストラクタ
//========================================
CTime::CTime(int nPriority) : CText2D(nPriority)
{

}

//========================================
// デストラクタ
//========================================
CTime::~CTime(void)
{

}

//========================================
// 生成処理
//========================================
CTime *CTime::Create(void)
{
	CTime *pScore = NULL;

	// スコアの生成
	pScore = new CTime;

	// 初期化処理
	pScore->Init();

	return pScore;
}

//========================================
// 初期化処理
//========================================
HRESULT CTime::Init(void)
{
	// 初期化処理
	CText2D::Init();

	{// スコアを文字列に設定
		char aString[TXT_MAX];
		sprintf(aString, "TIME:%02d", m_nTime);
		SetString(aString);
	}

	// 種類設定
	SetType(TYPE_SCORE);

	return S_OK;
}

//========================================
// 終了処理
//========================================
void CTime::Uninit(void)
{
	// 終了処理
	CText2D::Uninit();
}

//========================================
// 更新処理
//========================================
void CTime::Update(void)
{
	// 更新処理
	CText2D::Update();
}

//========================================
// 描画処理
//========================================
void CTime::Draw(void)
{
	// 描画処理
	CText2D::Draw();
}

//========================================
// 設定
//========================================
void CTime::SetTime(int nTime)
{
	// スコア加算
	m_nTime += nTime;

	// スコアを文字列に設定
	char aString[TXT_MAX];
	sprintf(aString, "TIME:%02d", nTime);

	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		// オブジェクトを取得
		CObject *pObj = GetObjectPointer(TYPE_TIME, nCntObj);

		if (pObj != NULL)
		{// 使用されている時、
			TYPE type = pObj->GetType();	// 種類を取得

			if (type == TYPE_TIME)
			{// 種類がスコアの時、
				CTime *pTime = pObj->GetTime(TYPE_TIME, nCntObj);

				// NULLでなければ文字列設定
				if (pTime != NULL)
				{
					pTime->SetString(aString);
				}
			}
		}
	}
}