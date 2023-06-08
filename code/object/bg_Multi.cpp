//========================================
// 
// �}���`�w�i����
// 
//========================================
// *** bg_Multi.cpp ***
//========================================
#include "bg_Multi.h"
#include "bg.h"

// �ÓI�ϐ��錾
int CBgMulti::m_nNumBg = -1;


// �R���X�g���N�^
CBgMulti::CBgMulti(int nPriority) : CObject(nPriority)
{
	for (int nCntBg = 0; nCntBg < BG_MAX; nCntBg++)
	{
		m_apBg[nCntBg] = NULL;
	}
}

// �f�X�g���N�^
CBgMulti::~CBgMulti()
{

}

//========================================
// ����
//========================================
CBgMulti *CBgMulti::Create(D3DXVECTOR3 move, int nType)
{
	// ���d�X�N���[��2D
	CBgMulti *pBgMulti = NULL;

	// ���d�X�N���[��2D�̐���
	pBgMulti = new CBgMulti;

	pBgMulti->m_move = move;
	pBgMulti->m_nType = nType;

	// ����������
	pBgMulti->Init();

	return pBgMulti;
}

//========================================
// ������
//========================================
HRESULT CBgMulti::Init(void)
{
	m_nNumBg++;

	if (m_nNumBg < 0 || m_nNumBg >= BG_MAX)
	{
		return S_OK;
	}
	else
	{
		m_apBg[m_nNumBg] = CBg::Create(m_move, m_nType);
	}


	// ��ސݒ�
	SetType(TYPE_BG_MULTI);

	return S_OK;
}

//========================================
// �I��
//========================================
void CBgMulti::Uninit(void)
{
	// ���
	Release();
}

//========================================
//	�X�V
//========================================
void CBgMulti::Update(void)
{

}

//========================================
// �`��
//========================================
void CBgMulti::Draw(void)
{

}