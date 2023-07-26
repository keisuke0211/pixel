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
	CText::Create(CText::BOX_NORMAL,
		D3DXVECTOR3(540.0f, 100.0f, 0.0f),
		D3DXVECTOR2(220.0f, 100.0f),
		"ゲームクリア",
		40.0f,
		5, 10, -1, false);

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
}

//========================================
// 更新
//========================================
void CResult::Update(void)
{
	// --- 取得 ---------------------------------
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// キーボード
	CInputMouse *pInputMouse = CManager::GetInputMouse();			// マウス
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();		// ジョイパット

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetJoypadTrigger(CInputJoypad::JOYKEY_A))
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