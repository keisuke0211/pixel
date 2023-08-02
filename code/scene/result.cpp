//========================================
// 
// ���U���g
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

// �ÓI�ϐ�
CResult::VERDICT CResult::verdict = VERDICT_GAMECLEAR;

//========================================
// �R���X�g���N�^
//========================================
CResult::CResult()
{

}

//========================================
// �f�X�g���N�^
//========================================
CResult::~CResult()
{

}

//========================================
// ������
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
			"�Q�[���N���A",
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
			"�Q�[���I�[�o�[",
			CFont::FONT_DOTGOTHIC,
			40.0f,
			5, 10, -1, false);
	}
		break;
	case CResult::VERDICT_MAX:
		break;
	}

	{// �X�R�A
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
		"ENTER�������Ďn�߂Ă�!",
		CFont::FONT_DOTGOTHIC,
		20.0f,
		5, 10, -1);

	return S_OK;
}

//========================================
// �I��
//========================================
void CResult::Uninit(void)
{
	// ���f��
	CModel::UninitModel();

	CObject::ReleaseAll(CObject::TYPE_TIME);
	CObject::ReleaseAll(CObject::TYPE_SCORE);
	CObject::ReleaseAll(CObject::TYPE_TEXT2D);
	CObject::ReleaseAll(CObject::TYPE_FONT);

}

//========================================
// �X�V
//========================================
void CResult::Update(void)
{
	// --- �擾 ---------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CMouse *pInputMouse = CManager::GetInputMouse();			// �}�E�X
	CJoypad *pInputJoypad = CManager::GetInputJoypad();		// �W���C�p�b�g

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_A))
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			CManager::GetFade()->SetFade(MODE_TITLE);
		}
	}
}

//========================================
// �`��
//========================================
void CResult::Draw(void)
{

}

//========================================
// ����
//========================================
CResult *CResult::Create(void)
{
	CResult *pResult = new CResult;

	pResult->Init();

	return pResult;
}