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

//========================================
// �R���X�g���N�^
//========================================
CTitle::CTitle()
{

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

	{// �^�C�g��
		CText2D *pObj = CText2D::Create();

		pObj->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, 100, 0.0f));
		pObj->SetSize(48.0f, 48.0f);
		pObj->SetDisp(CText2D::DISPLAY_CENTER);
		pObj->SetString("TITLE");
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
void CTitle::Uninit(void)
{
	CObject::ReleaseAll(CObject::TYPE_TEXT);
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
		CManager::SetMode(MODE_GAME);
	}
}

//========================================
// �`��
//========================================
void CTitle::Draw(void)
{

}