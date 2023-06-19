//========================================
//
// �X�R�A����
//
//========================================
// *** score2D.cpp ***
//========================================
#include "time.h"

// �ÓI�����o�ϐ���`
int CTime::m_nTime = 0;	// �^�C��

//========================================
// �R���X�g���N�^
//========================================
CTime::CTime(int nPriority) : CText2D(nPriority)
{

}

//========================================
// �f�X�g���N�^
//========================================
CTime::~CTime(void)
{

}

//========================================
// ��������
//========================================
CTime *CTime::Create(void)
{
	CTime *pScore = NULL;

	// �X�R�A�̐���
	pScore = new CTime;

	// ����������
	pScore->Init();

	return pScore;
}

//========================================
// ����������
//========================================
HRESULT CTime::Init(void)
{
	// ����������
	CText2D::Init();

	{// �X�R�A�𕶎���ɐݒ�
		char aString[TXT_MAX];
		sprintf(aString, "TIME:%02d", m_nTime);
		SetString(aString);
	}

	// ��ސݒ�
	SetType(TYPE_SCORE);

	return S_OK;
}

//========================================
// �I������
//========================================
void CTime::Uninit(void)
{
	// �I������
	CText2D::Uninit();
}

//========================================
// �X�V����
//========================================
void CTime::Update(void)
{
	// �X�V����
	CText2D::Update();
}

//========================================
// �`�揈��
//========================================
void CTime::Draw(void)
{
	// �`�揈��
	CText2D::Draw();
}

//========================================
// �ݒ�
//========================================
void CTime::SetTime(int nTime)
{
	// �X�R�A���Z
	m_nTime += nTime;

	// �X�R�A�𕶎���ɐݒ�
	char aString[TXT_MAX];
	sprintf(aString, "TIME:%02d", nTime);

	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	{
		// �I�u�W�F�N�g���擾
		CObject *pObj = GetObjectPointer(TYPE_TIME, nCntObj);

		if (pObj != NULL)
		{// �g�p����Ă��鎞�A
			TYPE type = pObj->GetType();	// ��ނ��擾

			if (type == TYPE_TIME)
			{// ��ނ��X�R�A�̎��A
				CTime *pTime = pObj->GetTime(TYPE_TIME, nCntObj);

				// NULL�łȂ���Ε�����ݒ�
				if (pTime != NULL)
				{
					pTime->SetString(aString);
				}
			}
		}
	}
}