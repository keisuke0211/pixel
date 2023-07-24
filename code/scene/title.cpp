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

	return S_OK;
}

//========================================
// �I��
//========================================
void CTitle::Uninit(void)
{

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