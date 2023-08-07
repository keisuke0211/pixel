//========================================
// 
// タイトル
// 
//========================================
// *** title.cpp ***
//========================================
#include "title.h"
#include "../object\model\model.h"
#include "../system/input.h"
#include "../object\UI\text2D.h"
#include "fade.h"
#include "../object/model/block.h"

#include "../system/words/text.h"
#include "../system/words/font.h"
#include "../system/words/words.h"

// 静的変数
bool CTitle::m_bStart = false;
bool CTitle::m_bClear = false;
bool CTitle::m_bExit = false;

//========================================
// コンストラクタ
//========================================
CTitle::CTitle()
{
	m_nTextTime = 0;
	m_nStandTime = 0;

	m_nSelectMenu = 0;
	Title = TITLE_OUTSET;

	for (int nCnt = 0; nCnt < WORDS_MAX; nCnt++)
	{
		m_Words[nCnt] = NULL;
		m_bMove[nCnt] = false;
	}

	for (int nCnt = 0; nCnt < TEXT_MAX; nCnt++)
	{
		m_Text[nCnt] = NULL;
	}
}

//========================================
// デストラクタ
//========================================
CTitle::~CTitle()
{

}

//========================================
// 初期化
//========================================
HRESULT CTitle::Init(void)
{
	m_bStart = false;
	m_bClear = false;
	m_bExit = false;

	CModel::InitModel();	// モデル
	CBlock::Load();			// ブロック

	m_Words[0] = CWords::Create("ブ", D3DXVECTOR3(440.0f, -60.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CFont::FONT_FZGONTA);
	m_Words[1] = CWords::Create("レ", D3DXVECTOR3(560.0f, -60.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CFont::FONT_FZGONTA);
	m_Words[2] = CWords::Create("パ", D3DXVECTOR3(680.0f, -60.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CFont::FONT_FZGONTA);
	m_Words[3] = CWords::Create("ズ", D3DXVECTOR3(800.0f, -60.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CFont::FONT_FZGONTA);

	m_bMove[0] = true;

	m_Text[0] = CText::Create(CText::BOX_NORMAL,
		D3DXVECTOR3(640.0f, 600.0f, 0.0f),
		D3DXVECTOR2(1080.0f, 100.0f),
		" ",
		CFont::FONT_DOTGOTHIC,
		20.0f,
		1, 1, -1);

	m_Text[1] = CText::Create(CText::BOX_NORMAL,
		D3DXVECTOR3(640.0f, 600.0f, 0.0f),
		D3DXVECTOR2(1080.0f, 100.0f),
		"ENTERを押して始めてね!",
		CFont::FONT_DOTGOTHIC,
		20.0f,
		5, 10, -1,false);

	m_nTextTime = TEXT_TIME;
	m_nStandTime = STAND_MAX;

	return S_OK;
}

//========================================
// 終了
//========================================
void CTitle::Uninit(void)
{
	CObject::ReleaseAll(CObject::TYPE_TEXT2D);
	CObject::ReleaseAll(CObject::TYPE_FONT);
}

//========================================
// 更新
//========================================
void CTitle::Update(void)
{
	// タイトルアニメーション
	if (Title == TITLE_OUTSET)
	{
		TitleAnime();
	}

	// メニュー
	if (Title == TITLE_MENU)
	{
		Menu();
	}


	// --- 取得 ---------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// キーボード
	CMouse *pInputMouse = CManager::GetInputMouse();			// マウス
	CJoypad *pInputJoypad = CManager::GetInputJoypad();		// ジョイパット

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_A))
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			switch (Title)
			{
			case CTitle::TITLE_OUTSET:
			{
				TextClear(WORDS_MAX, 2, TITLE_MENU);

				// メニュー生成
				MenuCreate();
			}
				break;
			case CTitle::TITLE_MENU:
			{
				TextClear(1, TEXT_MAX, TITLE_NEXT);


				switch (m_nSelectMenu)
				{
				case MENU_GAME:
					CManager::GetFade()->SetFade(MODE_GAME);
					break;
				case MENU_TUTORIAL:
					CManager::GetFade()->SetFade(MODE_TUTORIAL);
					break;
				case MENU_END:
					CManager::GetFade()->SetFade(MODE_TITLE);
					break;
				}
			}
				break;
			}
		}
		else if (CFade::GetFade() == CFade::FADE_IN)
		{

		}
	}
}

//========================================
// 描画
//========================================
void CTitle::Draw(void)
{

}

//========================================
// 生成
//========================================
CTitle *CTitle::Create(void)
{
	CTitle *pTitle = new CTitle;

	pTitle->Init();

	return pTitle;
}

//========================================
// タイトルアニメーション
//========================================
void CTitle::TitleAnime(void)
{
	for (int nCnt = 0; nCnt < WORDS_MAX; nCnt++)
	{
		if (m_Words[nCnt] != NULL)
		{
			D3DXVECTOR3 pos = m_Words[nCnt]->GetPos();

			if (pos.y <= 110.0f && m_bMove[nCnt])
			{
				D3DXVECTOR3 move;

				move.y = 3.0f;

				m_Words[nCnt]->SetMove(D3DXVECTOR3(0.0f, move.y, 0.0f));

				if (pos.y >= 100.0f)
				{
					move.y = 0.0f;

					m_Words[nCnt]->SetMove(D3DXVECTOR3(0.0f, move.y, 0.0f));
				}
				else if (pos.y >= 20 && nCnt != 3 && !m_bMove[nCnt + 1])
				{
					m_bMove[nCnt + 1] = true;
				}
			}
		}
	}

	// 入力催促テキスト
	if (--m_nTextTime <= 0)
	{
		if (m_nStandTime == STAND_MAX)
		{
			if (m_Text[1] != NULL)
			{
				m_Text[1]->Uninit();

				m_Text[1] = NULL;
			}
		}
		m_nStandTime--;
		if (m_nStandTime <= 0)
		{
			m_Text[1] = CText::Create(CText::BOX_NORMAL,
				D3DXVECTOR3(640.0f, 600.0f, 0.0f),
				D3DXVECTOR2(1080.0f, 100.0f),
				"ENTERを押して始めてね!",
				CFont::FONT_DOTGOTHIC,
				20.0f,
				5, 10, -1, false);

			m_nTextTime = TEXT_TIME;
			m_nStandTime = STAND_MAX;
		}
	}
}

//========================================
// メニュー
//========================================
void CTitle::Menu(void)
{
	// 色
	for (int nCnt = 0; nCnt < TEXT_MAX; nCnt++)
	{
		if (m_Text[nCnt] != NULL)
		{
			if (nCnt == m_nSelectMenu)
			{
				m_Text[nCnt]->SetBoxColor(D3DXCOLOR(0.0f,1.0f,0.0f,1.0f));
			}
			else
			{
				m_Text[nCnt]->SetBoxColor(INIT_D3DXCOLOR);
			}
		}
	}


	// --- 取得 ---------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// キーボード
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// ジョイパット

	// -- メニュー選択 ---------------------------
	if (pInputKeyboard->GetTrigger(DIK_W) || pInputKeyboard->GetTrigger(DIK_UP) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_UP) || pInputJoypad->GetStick(0).aAngleTrigger[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_UP])
	{
		m_nSelectMenu--;
	}
	else if (pInputKeyboard->GetTrigger(DIK_S) || pInputKeyboard->GetTrigger(DIK_DOWN) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_DOWN) || pInputJoypad->GetStick(0).aAngleTrigger[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_DOWN])
	{
		m_nSelectMenu++;
	}

	if (m_nSelectMenu > (MENU_MAX - 1))
	{// メニューの最前線に移動
		m_nSelectMenu = 0;
	}
	else if (m_nSelectMenu < 0)
	{// メニューの最後尾に移動
		m_nSelectMenu = (MENU_MAX - 1);
	}
}

//========================================
// メニュー生成
//========================================
void CTitle::MenuCreate(void)
{
	{
		m_Text[0] = CText::Create(CText::BOX_NORMAL,
			D3DXVECTOR3(640.0f, 150.0f, 0.0f),
			D3DXVECTOR2(360.0f, 100.0f),
			"ゲーム",
			CFont::FONT_FZGONTA,
			20.0f,
			5, 10, -1);
	}

	{
		m_Text[1] = CText::Create(CText::BOX_NORMAL,
			D3DXVECTOR3(640.0f, 300.0f, 0.0f),
			D3DXVECTOR2(360.0f, 100.0f),
			"チュートリアル",
			CFont::FONT_FZGONTA,
			20.0f,
			5, 10, -1);
	}
	{
		m_Text[2] = CText::Create(CText::BOX_NORMAL,
			D3DXVECTOR3(640.0f, 450.0f, 0.0f),
			D3DXVECTOR2(360.0f, 100.0f),
			"EXIT",
			CFont::FONT_MEIRIO,
			20.0f,
			5, 10, -1);
	}
}

//========================================
// テキスト削除
//========================================
void CTitle::TextClear(int nWords, int nText, TITLE aTitle)
{
	for (int nCnt = 0; nCnt < nWords; nCnt++)
	{
		if (m_Words[nCnt] != NULL)
		{
			m_Words[nCnt]->Uninit();
			m_Words[nCnt] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < nText; nCnt++)
	{
		if (m_Text[nCnt] != NULL)
		{
			m_Text[nCnt]->Uninit();
			m_Text[nCnt] = NULL;
		}
	}

	Title = aTitle;
}