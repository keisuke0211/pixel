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
#include "../../scene/title.h"
#include "../../scene/pause.h"
#include "../../system/words/text.h"
#include "../../system/words/words.h"
#include "../../system/words/font.h"

//========================================
// コンストラクタ
//========================================
CTime::CTime(int nPriority) : CText2D(nPriority)
{
	m_nTime = 0;			// タイム
	m_nCounter = 0;			// カウンター
	m_Digit = 0;			// 桁数
	m_bSetTime = false;		// 設定フラグ
	m_bUpdateTime = false;	// 更新フラグ
	m_Time = NULL;
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
	bool bStart = CTitle::IsStart();
	
	if (bStart)
	{
		bool bPause = CPause::IsPause();
		bool bCameraExit = CBlock::IsExitCamera();

		if (!bPause && bCameraExit)
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

		if (m_bUpdateTime)
		{
			// タイムを文字列に設定
			char aTime[TXT_MAX];
			int nNumSet = 0;

			sprintf(aTime, "%d", m_nTime);

			// 長さを取得
			m_Digit = strlen(aTime);

			for (int nTime = 0; nTime < m_Digit; nTime++)
			{
				if (m_Time->SetWords(&aTime[nTime], TIME_START_DEX + nTime, INIT_D3DXCOLOR))
				{
					nNumSet++;
				}
			}

			if (nNumSet == m_Digit)
			{
				m_bUpdateTime = false;
			}
		}
	}
}

//========================================
// 描画処理
//========================================
void CTime::Draw(void)
{

}

//========================================
// 設定
//========================================
void CTime::SetTime(int nTime)
{
	// 時間設定
	if (!m_bSetTime)
	{
		// タイム代入
		m_nTime = nTime;

		// タイムを文字列に設定
		char aString[TXT_MAX];
		sprintf(aString, "TIME ：%d", m_nTime);

		FormFont pFont = {
			INIT_D3DXCOLOR,
			11.0f,
			1,
			10,
			-1
		};

		FormShadow pShadow = {
			D3DXCOLOR(0.0f,0.0f,0.0f,1.0f),
			true,
			D3DXVECTOR3(2.0f,2.0f,0.0f),
			D3DXVECTOR2(1.0f,1.0f)
		};

		m_Time = CText::Create(CText::BOX_NORMAL,
			D3DXVECTOR3(SCREEN_WIDTH - 290.0f, 21.0f, 0.0f),
			D3DXVECTOR2(0.0f, 0.0f),
			aString,
			CFont::FONT_BESTTEN,
			&pFont,false,&pShadow);

		m_bSetTime = true;
	}
	else
	{
		m_bUpdateTime = true;
	}
}