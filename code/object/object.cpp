//========================================
// 
// �I�u�W�F�N�g����
// 
//========================================
// *** object.cpp ***
//========================================
#include "../manager.h"
#include "object.h"
#include "../renderer.h"

// �ÓI�ϐ�
int CObject::m_nNumAll = 0;													// �I�u�W�F�N�g����
CObject *CObject::m_apObject[CObject::TYPE_MAX][CObject::MAX_OBJECT] = {};	// �I�u�W�F�N�g�̃|�C���^

// �R���X�g���N�^
CObject::CObject(int nPriority)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nPriority][nCntObject] == NULL)
		{
			m_apObject[nPriority][nCntObject] = this;	// �������g����
			m_nPriority = nPriority;					// �������g�̗D�揇�ʂ���
			m_nID = nCntObject;							// �������g��ID����
			m_nNumAll++;								// �����̉��Z
			break;
		}
	}
}

// �f�X�g���N�^
CObject::~CObject()
{
	
}
//========================================
// �j��
//========================================
void CObject::Release(void)
{
	int nIdx = m_nID;
	int nPri = m_nPriority;

	if (m_apObject[nPri][nIdx] != NULL)
	{
		if (m_apObject[nPri][nIdx])
		{
			delete m_apObject[nPri][nIdx];
			m_apObject[nPri][nIdx] = NULL;
			m_nNumAll--;				// �����̃J�E���g�_�E��
		}
	}
}

//========================================
// �S�̂̔j��
//========================================
void CObject::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < TYPE_MAX; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				m_apObject[nCntPriority][nCntObject]->Uninit();
			}
		}
	}
}

//========================================
// �S�̂̍X�V
//========================================
void CObject::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < TYPE_MAX; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				m_apObject[nCntPriority][nCntObject]->Update();
			}
		}
	}
}

//========================================
// �S�̂̕`��
//========================================
void CObject::DrawAll(void)
{
	// �f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCntPriority = 0; nCntPriority < TYPE_MAX; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				m_apObject[nCntPriority][nCntObject]->Draw();
			}
		}
	}
}

//========================================
// ��ނ̐ݒ�
//========================================
void CObject::SetType(TYPE type)
{
	m_type = type;
}

//========================================
// Score���擾
//========================================
CScore *CObject::GetScore(int nPriority,int nIdx)
{
	if (m_apObject[nPriority][nIdx] == NULL)
	{
		return NULL;
	}
	else if (m_apObject[nPriority][nIdx]->m_type != TYPE_SCORE)
	{
		return NULL;
	}

	return (CScore*)m_apObject[nPriority][nIdx];
}