//========================================
// 
// �^�C�g��
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
// �}�N����`
//========================================
#define STAND_MAX	(20)
#define TEXT_TIME	(150)

//========================================
// �R���X�g���N�^
//========================================
CTitle::CTitle()
{
	nTextTime = 0;
	nStandTime = 0;
}

//========================================
// �f�X�g���N�^
//========================================
CTitle::~CTitle()
{

}

//========================================
// ������
//========================================
HRESULT CTitle::Init(void)
{
	// ���f��
	CModel::InitModel();

	CText::Create(CText::BOX_NORMAL,
		D3DXVECTOR3(540.0f, 100.0f, 0.0f),
		D3DXVECTOR2(220.0f, 100.0f),
		"�s�N�p�Y",
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
		"ENTER�������Ďn�߂Ă�!",
		CFont::FONT_DOTGOTHIC,
		20.0f,
		5, 10, -1);

	nTextTime = TEXT_TIME;
	nStandTime = STAND_MAX;

	return S_OK;
}

//========================================
// �I��
//========================================
void CTitle::Uninit(void)
{
	CObject::ReleaseAll(CObject::TYPE_TEXT2D);
	CObject::ReleaseAll(CObject::TYPE_FONT);
}

//========================================
// �X�V
//========================================
void CTitle::Update(void)
{
	// --- �擾 ---------------------------------
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CInputMouse *pInputMouse = CManager::GetInputMouse();			// �}�E�X
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();		// �W���C�p�b�g

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
				"ENTER�������Ďn�߂Ă�!",
				CFont::FONT_DOTGOTHIC,
				20.0f,
				5, 10, -1);

			nTextTime = TEXT_TIME;
			nStandTime = STAND_MAX;
		}
	}


}

//========================================
// �`��
//========================================
void CTitle::Draw(void)
{

}

//========================================
// ����
//========================================
CTitle *CTitle::Create(void)
{
	CTitle *pTitle = new CTitle;

	pTitle->Init();

	return pTitle;
}