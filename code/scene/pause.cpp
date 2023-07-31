//========================================
// 
// ポーズ
// 
//========================================
// *** pause.h ***
//========================================
#include "pause.h"
#include "../system/input.h"

// 静的変数
bool CPause::m_bPause = false;

//========================================
// コンストラクタ
//========================================
CPause::CPause()
{

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
	// -- 取得 -------------------------------------------
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// キーボード
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();		// ジョイパット

	// ポーズ
	if (pInputKeyboard->GetTrigger(DIK_P) || pInputJoypad->GetJoypadTrigger(CInputJoypad::JOYKEY_START))
	{
		if (m_bPause)
		{
			m_bPause = false;
		}
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