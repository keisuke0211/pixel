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

	return S_OK;
}

//========================================
// 終了
//========================================
void CTitle::Uninit(void)
{

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
		CManager::SetMode(MODE_GAME);
	}
}

//========================================
// 描画
//========================================
void CTitle::Draw(void)
{

}