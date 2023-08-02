//========================================
// 
// リザルト
// 
//========================================
// *** result.cpp ***
//========================================
#include "result.h"
#include "game.h"
#include "../object/UI/score.h"
#include "../object\model\model.h"
#include "../system/input.h"
#include "../object\UI\text2D.h"
#include "fade.h"
#include "../system/words/text.h"
#include "../system/words/font.h"

// 静的変数
CResult::VERDICT CResult::verdict = VERDICT_GAMECLEAR;

//========================================
// コンストラクタ
//========================================
CResult::CResult()
{

}

//========================================
// デストラクタ
//========================================
CResult::~CResult()
{

}

//========================================
// 初期化
//========================================
HRESULT CResult::Init(void)
{
	switch (verdict)
	{
	case CResult::VERDICT_GAMECLEAR:
	{
		CText::Create(CText::BOX_NORMAL,
			D3DXVECTOR3(640.0f, 100.0f, 0.0f),
			D3DXVECTOR2(640.0f, 100.0f),
			"ゲームクリア",
			CFont::FONT_DOTGOTHIC,
			40.0f,
			5, 10, -1,false);
	}
		break;
	case CResult::VERDICT_GAMEOVER:
	{
		CText::Create(CText::BOX_NORMAL,
			D3DXVECTOR3(540.0f, 100.0f, 0.0f),
			D3DXVECTOR2(640.0f, 100.0f),
			"ゲームオーバー",
			CFont::FONT_DOTGOTHIC,
			40.0f,
			5, 10, -1, false);
	}
		break;
	case CResult::VERDICT_MAX:
		break;
	}

	{// スコア
		CText2D *pObj = CText2D::Create();

		pObj->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 150, 0.0f));
		pObj->SetSize(48.0f, 48.0f);
		pObj->SetDisp(CText2D::DISPLAY_CENTER);

		char tex[TXT_MAX] = { "SCORE:" };
		char score[TXT_MAX];

		sprintf(score, "%d", CGame::GetScore()->GetScore());
		strcat(tex, score);
		pObj->SetString(tex);
	}

	CText::Create(CText::BOX_NORMAL,
		D3DXVECTOR3(640.0f, 600.0f, 0.0f),
		D3DXVECTOR2(1080.0f, 100.0f),
		"ENTERを押して始めてね!",
		CFont::FONT_DOTGOTHIC,
		20.0f,
		5, 10, -1);

	return S_OK;
}

//========================================
// 終了
//========================================
void CResult::Uninit(void)
{
	// モデル
	CModel::UninitModel();

	CObject::ReleaseAll(CObject::TYPE_TIME);
	CObject::ReleaseAll(CObject::TYPE_SCORE);
	CObject::ReleaseAll(CObject::TYPE_TEXT2D);
	CObject::ReleaseAll(CObject::TYPE_FONT);

}

//========================================
// 更新
//========================================
void CResult::Update(void)
{
	// --- 取得 ---------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// キーボード
	CMouse *pInputMouse = CManager::GetInputMouse();			// マウス
	CJoypad *pInputJoypad = CManager::GetInputJoypad();		// ジョイパット

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_A))
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			CManager::GetFade()->SetFade(MODE_TITLE);
		}
	}
}

//========================================
// 描画
//========================================
void CResult::Draw(void)
{

}

//========================================
// 生成
//========================================
CResult *CResult::Create(void)
{
	CResult *pResult = new CResult;

	pResult->Init();

	return pResult;
}