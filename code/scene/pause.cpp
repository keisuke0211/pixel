//========================================
// 
// �|�[�Y
// 
//========================================
// *** pause.h ***
//========================================
#include "pause.h"
#include "../system/input.h"

// �ÓI�ϐ�
bool CPause::m_bPause = false;

//========================================
// �R���X�g���N�^
//========================================
CPause::CPause()
{

}

//========================================
// �f�X�g���N�^
//========================================
CPause::~CPause()
{

}

//========================================
// ������
//========================================
HRESULT CPause::Init(void)
{

	return S_OK;
}

//========================================
// �I��
//========================================
void CPause::Uninit(void)
{

}

//========================================
// �X�V
//========================================
void CPause::Update(void)
{
	// -- �擾 -------------------------------------------
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();		// �W���C�p�b�g

	// �|�[�Y
	if (pInputKeyboard->GetTrigger(DIK_P) || pInputJoypad->GetJoypadTrigger(CInputJoypad::JOYKEY_START))
	{
		if (m_bPause)
		{
			m_bPause = false;
		}
	}
}

//========================================
// �`��
//========================================
void CPause::Draw(void)
{

}

//========================================
// ����
//========================================
CPause *CPause::Create(void)
{
	CPause *pPause = new CPause;

	pPause->Init();

	return pPause;
}