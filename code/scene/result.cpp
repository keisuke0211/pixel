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
	{// タイトル
		CText2D *pObj = CText2D::Create();

		pObj->SetPos(D3DXVECTOR3(SCREEN_WIDTH, 100, 0.0f));
		pObj->SetSize(48.0f, 48.0f);
		pObj->SetDisp(CText2D::DISPLAY_CENTER);
		pObj->SetString("RESULT");
	}

	{// スコア
		CText2D *pObj = CText2D::Create();

		pObj->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, 0.0f));
		pObj->SetSize(48.0f, 48.0f);
		pObj->SetDisp(CText2D::DISPLAY_CENTER);

		char tex[TXT_MAX] = { "SCORE:" };
		char score[TXT_MAX];

		sprintf(score, "%d", CGame::GetScore());
		strcat(tex, score);
		pObj->SetString(tex);
	}

	{// 入力催促
		CText2D *pObj = CText2D::Create();

		pObj->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, 0.0f));
		pObj->SetSize(48.0f, 48.0f);
		pObj->SetDisp(CText2D::DISPLAY_CENTER);
		pObj->SetString("PRESS ENTER");
	}
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
	CObject::ReleaseAll(CObject::TYPE_TEXT);
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