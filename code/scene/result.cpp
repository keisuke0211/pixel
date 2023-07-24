//========================================
// 
// リザルト
// 
//========================================
// *** result.cpp ***
//========================================
#include "result.h"
#include "../object\model\model.h"
#include "../system/input.h"
#include "../object\UI\text2D.h"

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

		pObj->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 100, 0.0f));
		pObj->SetSize(48.0f, 48.0f);
		pObj->SetDisp(CText2D::DISPLAY_CENTER);
		pObj->SetString("RESULT");
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
	// --- 取得 ---------------------------------
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// キーボード
	CInputMouse *pInputMouse = CManager::GetInputMouse();			// マウス
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();		// ジョイパット

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetJoypadTrigger(CInputJoypad::JOYKEY_A))
	{
		// モデル
		CModel::UninitModel();

		CObject::ReleaseAll(CObject::TYPE_PLAYER);
	}
}

//========================================
// 更新
//========================================
void CResult::Update(void)
{
	CManager::SetMode(MODE_TITLE);
}

//========================================
// 描画
//========================================
void CResult::Draw(void)
{

}