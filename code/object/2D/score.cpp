//========================================
//
// スコア処理
//
//========================================
// *** score2D.cpp ***
//========================================
#include "score.h"

// 静的メンバ変数定義
int CScore::m_nScore = 0;	// スコア

//========================================
// コンストラクタ
//========================================
CScore::CScore(int nPriority) : CText2D(nPriority)
{

}

//========================================
// デストラクタ
//========================================
CScore::~CScore(void) 
{

}

//========================================
// 生成処理
//========================================
CScore *CScore::Create(void)
{
	CScore *pScore = NULL;

	// スコアの生成
	pScore = new CScore;

	// 初期化処理
	pScore->Init();

	return pScore;
}

//========================================
// 初期化処理
//========================================
HRESULT CScore::Init(void)
{
	// 初期化処理
	CText2D::Init();

	{// スコアを文字列に設定
		char aString[TXT_MAX];
		sprintf(aString, "SCORE:%06d", m_nScore);
		SetString(aString);
	}

	// 種類設定
	SetType(TYPE_SCORE);

	return S_OK;
}

//========================================
// 終了処理
//========================================
void CScore::Uninit(void)
{
	// 終了処理
	CText2D::Uninit();
}

//========================================
// 更新処理
//========================================
void CScore::Update(void)
{
	// 更新処理
	CText2D::Update();
}

//========================================
// 描画処理
//========================================
void CScore::Draw(void)
{
	// 描画処理
	CText2D::Draw();
}

//========================================
// 設定
//========================================
void CScore::SetScore(int nScore)
{
	// スコア加算
	m_nScore += nScore;

	// スコアを文字列に設定
	char aString[TXT_MAX];
	sprintf(aString, "SCORE:%06d", m_nScore);

	for (int nCntObj = 0; nCntObj < GetNumAll(); nCntObj++)
	{
		// オブジェクトを取得
		CObject *pObj = GetObjectPointer(PRIO_TEXT,nCntObj);

		if (pObj != NULL)
		{// 使用されている時、
			TYPE type = pObj->GetType();	// 種類を取得

			if (type == TYPE_SCORE)
			{// 種類がスコアの時、
				CScore *pScore = pObj->GetScore(PRIO_TEXT,nCntObj);

				// NULLでなければ文字列設定
				if (pScore != NULL)
				{
					pScore->SetString(aString);
				}
			}
		}
	}
}