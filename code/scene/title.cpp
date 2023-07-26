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

#include "../system/words/font.h"
#include "../system/words/words.h"
#include "../system/words/text.h"

//========================================
// コンストラクタ
//========================================
CTitle::CTitle()
{

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
	// モデル
	CModel::InitModel();

	{// タイトル
		CText2D *pObj = CText2D::Create();

		pObj->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 100, 0.0f));
		pObj->SetSize(48.0f, 48.0f);
		pObj->SetDisp(CText2D::DISPLAY_CENTER);
		pObj->SetString("TITLE");
	}

	CText::Create(CText::BOX_NORMAL, 500, 5, "ENTERを押して始めてね!");

	return S_OK;
}

//========================================
// 終了
//========================================
void CTitle::Uninit(void)
{
	CObject::ReleaseAll(CObject::TYPE_TEXT);
	CObject::ReleaseAll(CObject::TYPE_FONT);
}

//========================================
// 更新
//========================================
void CTitle::Update(void)
{
	// --- 取得 ---------------------------------
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// キーボード
	CInputMouse *pInputMouse = CManager::GetInputMouse();			// マウス
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();		// ジョイパット

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetJoypadTrigger(CInputJoypad::JOYKEY_A))
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			CManager::GetFade()->SetFade(MODE_GAME);
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