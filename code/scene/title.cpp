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
//#include "fade.h"
#include "../object\BG\bg_side.h"
#include "../object\BG\bg_ceiling.h"

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

	// 背景(側面)の生成
	CBgSide *pBgsky = CBgSide::Create();

	// 背景(天井)の生成
	CBgCeiling *pBgCeiling = CBgCeiling::Create();

	{// タイトル
		CText2D *pObj = CText2D::Create();

		pObj->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 100, 0.0f));
		pObj->SetSize(48.0f, 48.0f);
		pObj->SetDisp(CText2D::DISPLAY_CENTER);
		pObj->SetString("TITLE");
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
void CTitle::Uninit(void)
{
	CObject::ReleaseAll(CObject::TYPE_TEXT);
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
		//CManager::GetFade()->SetFade(MODE_GAME);
		CManager::SetMode(MODE_GAME);
	}
}

//========================================
// 描画
//========================================
void CTitle::Draw(void)
{

}