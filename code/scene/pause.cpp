//========================================
// 
// ポーズ
// 
//========================================
// *** pause.h ***
//========================================
#include "pause.h"
#include "../system/input.h"
#include "../scene/fade.h"
#include "../system/words/text.h"

// 静的変数
bool CPause::m_bPause = false;

//========================================
// コンストラクタ
//========================================
CPause::CPause()
{
	m_Menu = false;
	m_nSelectMenu = 0;

	for (int nCnt = 0; nCnt < TEXT_MAX; nCnt++)
	{
		m_Text[nCnt] = NULL;
	}
}

//========================================
// デストラクタ
//========================================
CPause::~CPause()
{

}

//========================================
// 初期化
//========================================
HRESULT CPause::Init(void)
{

	return S_OK;
}

//========================================
// 終了
//========================================
void CPause::Uninit(void)
{

}

//========================================
// 更新
//========================================
void CPause::Update(void)
{
	if (m_bPause)
	{
		// メニュー生成
		MenuCreate();

		// メニュー
		Menu();
	}
}

//========================================
// 描画
//========================================
void CPause::Draw(void)
{

}

//========================================
// 生成
//========================================
CPause *CPause::Create(void)
{
	CPause *pPause = new CPause;

	pPause->Init();

	return pPause;
}

//========================================
// メニュー
//========================================
void CPause::Menu(void)
{
	// 色
	for (int nCnt = 0; nCnt < TEXT_MAX; nCnt++)
	{
		if (m_Text[nCnt] != NULL)
		{
			if (nCnt == m_nSelectMenu)
			{
				m_Text[nCnt]->SetBoxColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
			}
			else
			{
				m_Text[nCnt]->SetBoxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
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


	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_A))
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			switch (m_nSelectMenu)
			{
			case MENU_RESUME:
				m_bPause = false;
				break;
			case MENU_RESET:
				m_bPause = false;
				CManager::GetFade()->SetFade(MODE_GAME);
				break;
			case MENU_TITLE:
				m_bPause = false;
				CManager::GetFade()->SetFade(MODE_TITLE);
				break;
			}
		}
	}

	if (!m_bPause)
	{
		for (int nCnt = 0; nCnt < TEXT_MAX; nCnt++)
		{
			if (m_Text[nCnt] != NULL)
			{
				m_Text[nCnt]->Uninit();
				m_Text[nCnt] = NULL;
			}
		}
		m_Menu = false;
	}
}

//========================================
// メニュー生成
//========================================
void CPause::MenuCreate(void)
{
	if (!m_Menu)
	{
		{
			m_Text[0] = CText::Create(CText::BOX_NORMAL,
				D3DXVECTOR3(640.0f, 250.0f, 0.0f),
				D3DXVECTOR2(360.0f, 100.0f),
				"再開",
				CFont::FONT_MEIRIO,
				20.0f,
				5, 10, -1);
			m_Text[0]->SetTetPause(true);
		}

		{
			m_Text[1] = CText::Create(CText::BOX_NORMAL,
				D3DXVECTOR3(640.0f, 400.0f, 0.0f),
				D3DXVECTOR2(360.0f, 100.0f),
				"やり直す",
				CFont::FONT_MEIRIO,
				20.0f,
				5, 10, -1);
			m_Text[1]->SetTetPause(true);
		}
		{
			m_Text[2] = CText::Create(CText::BOX_NORMAL,
				D3DXVECTOR3(640.0f, 550.0f, 0.0f),
				D3DXVECTOR2(360.0f, 100.0f),
				"タイトルに戻る",
				CFont::FONT_MEIRIO,
				20.0f,
				5, 10, -1);
			m_Text[2]->SetTetPause(true);
		}
		{
			m_Text[3] = CText::Create(CText::BOX_NORMAL,
				D3DXVECTOR3(640.0f, 100.0f, 0.0f),
				D3DXVECTOR2(360.0f, 100.0f),
				"ポーズ",
				CFont::FONT_FZGONTA,
				40.0f,
				5, 10, -1,false);
			m_Text[3]->SetTetPause(true);
		}

		m_Menu = true;
	}
}