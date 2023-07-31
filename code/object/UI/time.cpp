//========================================
//
// スコア処理
//
//========================================
// *** score2D.cpp ***
//========================================
#include "time.h"
#include "../model/block.h"
#include "../../scene/game.h"
#include "../../scene/pause.h"

//========================================
// コンストラクタ
//========================================
CTime::CTime(int nPriority) : CText2D(nPriority)
{
	m_nTime = 0;	// タイム
	m_nCounter = 0;	// カウンター
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
	CTime *pTime = new CTime;

	 // 初期化処理
	pTime->Init();

	return pTime;
}

//========================================
// 初期化処理
//========================================
HRESULT CTime::Init(void)
{
	// 初期化処理
	CText2D::Init();

	m_nTime = 0;	// タイム
	m_nCounter = 0;	// カウンター

	{// スコアを文字列に設定
		char aString[TXT_MAX];
		sprintf(aString, "TIME:%d", m_nTime);
		SetString(aString);
	}

	// 種類設定
	SetType(TYPE_TIME);

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
	bool bPause = CPause::IsPause();
	bool bStart = CGame::IsStart();
	bool bCameraExit = CBlock::IsExitCamera();

	if (bStart)
	{
		if (!bPause || bCameraExit)
		{
			// 更新処理
			CText2D::Update();

			if (m_nTime > 0)
			{// タイムが0以上の時、

				// カウンターが0になった時、
				m_nCounter = (m_nCounter + 1) % 60;
				if (m_nCounter == 0)
				{
					m_nTime--;			// タイムを減算
					SetTime(m_nTime);	// タイム設定
				}
			}
		}
	}
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
	// タイム代入
	m_nTime = nTime;

	// タイムを文字列に設定
	char aString[TXT_MAX];
	sprintf(aString, "TIME :%d", m_nTime);
	SetString(aString);
}