//========================================
//
// �X�R�A����
//
//========================================
// *** score2D.cpp ***
//========================================
#include "score.h"

// �ÓI�����o�ϐ���`
int CScore::m_nScore = 0;	// �X�R�A

//========================================
// �R���X�g���N�^
//========================================
CScore::CScore(int nPriority) : CText2D(nPriority)
{

}

//========================================
// �f�X�g���N�^
//========================================
CScore::~CScore(void) 
{

}

//========================================
// ��������
//========================================
CScore *CScore::Create(void)
{
	CScore *pScore = NULL;

	// �X�R�A�̐���
	pScore = new CScore;

	// ����������
	pScore->Init();

	return pScore;
}

//========================================
// ����������
//========================================
HRESULT CScore::Init(void)
{
	// ����������
	CText2D::Init();

	{// �X�R�A�𕶎���ɐݒ�
		char aString[TXT_MAX];
		sprintf(aString, "SCORE:%06d", m_nScore);
		SetString(aString);
	}

	// ��ސݒ�
	SetType(TYPE_SCORE);

	return S_OK;
}

//========================================
// �I������
//========================================
void CScore::Uninit(void)
{
	// �I������
	CText2D::Uninit();
}

//========================================
// �X�V����
//========================================
void CScore::Update(void)
{
	// �X�V����
	CText2D::Update();
}

//========================================
// �`�揈��
//========================================
void CScore::Draw(void)
{
	// �`�揈��
	CText2D::Draw();
}

//========================================
// �ݒ�
//========================================
void CScore::SetScore(int nScore)
{
	int nCntObj = 0;
	
	// �X�R�A���Z
	m_nScore += nScore;

	// �X�R�A�𕶎���ɐݒ�
	char aString[TXT_MAX];
	sprintf(aString, "SCORE:%06d", m_nScore);

	// �擪�I�u�W�F�N�g���擾
	CObject *pObj = CObject::GetTop(PRIO_UI);

	while (pObj != NULL)
	{// �g�p����Ă��鎞�A

		// ���̃I�u�W�F�N�g
		CObject *pObjNext = pObj->GetNext();

		TYPE type = pObj->GetType();	// ��ނ��擾

		if (type == TYPE_SCORE)
		{// ��ނ��X�R�A�̎��A
			CScore *pScore = pObj->GetScore(PRIO_UI, nCntObj);

			// NULL�łȂ���Ε�����ݒ�
			if (pScore != NULL)
			{
				pScore->SetString(aString);
			}

			nCntObj++;
		}
		pObj = pObjNext;	// ���̃I�u�W�F�N�g����
	}
}