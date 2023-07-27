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

#include "../system/words/text.h"

//========================================
// マクロ定義
//========================================
#define STAND_MAX	(20)
#define TEXT_TIME	(150)

//========================================
// コンストラクタ
//========================================
CTitle::CTitle()
{
	nTextTime = 0;
	nStandTime = 0;
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

	CText::Create(CText::BOX_NORMAL,
		D3DXVECTOR3(540.0f, 100.0f, 0.0f),
		D3DXVECTOR2(220.0f, 100.0f),
		"ピクパズ",
		CFont::FONT_MEIRIO,
		40.0f,
		20, 10, -1, false);


	CText::Create(CText::BOX_NORMAL,
		D3DXVECTOR3(640.0f, 600.0f, 0.0f),
		D3DXVECTOR2(1080.0f, 100.0f),
		" ",
		CFont::FONT_DOTGOTHIC,
		20.0f,
		1, 1, -1);

	CText::Create(CText::BOX_NORMAL,
		D3DXVECTOR3(640.0f, 600.0f, 0.0f),
		D3DXVECTOR2(1080.0f, 100.0f),
		"ENTERを押して始めてね!",
		CFont::FONT_DOTGOTHIC,
		20.0f,
		5, 10, -1);

	nTextTime = TEXT_TIME;
	nStandTime = STAND_MAX;

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

	if (--nTextTime <= 0)
	{
		nStandTime--;
		if (nStandTime == STAND_MAX)
		{
			CObject::Release(CObject::PRIO_TEXT, CObject::TYPE_FONT, 2);
		}
		if (nStandTime <= 0)
		{
			CText::Create(CText::BOX_NORMAL,
				D3DXVECTOR3(640.0f, 600.0f, 0.0f),
				D3DXVECTOR2(1080.0f, 100.0f),
				"ENTERを押して始めてね!",
				CFont::FONT_DOTGOTHIC,
				20.0f,
				5, 10, -1);

			nTextTime = TEXT_TIME;
			nStandTime = STAND_MAX;
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