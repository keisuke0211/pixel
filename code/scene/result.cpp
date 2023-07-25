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
	{// �^�C�g��
		CText2D *pObj = CText2D::Create();

		pObj->SetPos(D3DXVECTOR3(SCREEN_WIDTH, 100, 0.0f));
		pObj->SetSize(48.0f, 48.0f);
		pObj->SetDisp(CText2D::DISPLAY_CENTER);
		pObj->SetString("RESULT");
	}

	{// �X�R�A
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

	{// ���͍Ñ�
		CText2D *pObj = CText2D::Create();

		pObj->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100, 0.0f));
		pObj->SetSize(48.0f, 48.0f);
		pObj->SetDisp(CText2D::DISPLAY_CENTER);
		pObj->SetString("PRESS ENTER");
	}
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
	CObject::ReleaseAll(CObject::TYPE_TEXT);
}

//========================================
// �X�V
//========================================
void CResult::Update(void)
{
	// --- �擾 ---------------------------------
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CInputMouse *pInputMouse = CManager::GetInputMouse();			// �}�E�X
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();		// �W���C�p�b�g

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetJoypadTrigger(CInputJoypad::JOYKEY_A))
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