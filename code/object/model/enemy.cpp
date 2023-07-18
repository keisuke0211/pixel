//========================================
// 
// �G�l�~�[����
// 
//========================================
// *** enemy.cpp ***
//========================================
#include "enemy.h"
#include "../../manager.h"
#include "../../renderer.h"
#include "../../sound.h"
#include "../2D/score.h"
#include "particleX.h"


// �ÓI�ϐ�
CEnemy::SetInfo *CEnemy::pSet = NULL;
int CEnemy::m_nNumAll = 0;

//========================================
// �R���X�g���N�^
//========================================
CEnemy::CEnemy(int nPriority) : CObjectX(nPriority)
{
	// �l���N���A
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.posOld = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.rotOld = INIT_D3DXVECTOR3;
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.move = INIT_D3DXVECTOR3;
	m_Info.nType = 0;
	m_Info.nLife = 0;
	m_Info.state = STATE_NORMAL;
	m_Info.nCntState = 0;
	m_nNumAll++;
}

//========================================
// �f�X�g���N�^
//========================================
CEnemy::~CEnemy()
{
	m_nNumAll--;
}

//========================================
// ����
//========================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos)
{
	CEnemy *pEnemy = new CEnemy;

	pEnemy->SetModel(MODEL_ENEMY_00);

	// ����������
	pEnemy->Init();

	pEnemy->m_Info.pos = pos;
	pEnemy->SetPos(pEnemy->m_Info.pos);
	pEnemy->SetRot(pEnemy->m_Info.rot);
	pEnemy->SetColor(pEnemy->m_Info.col);
	return pEnemy;
}

//========================================
// ������
//========================================
HRESULT CEnemy::Init(void)
{
	CObjectX::Init();

	// ��ނ̐ݒ�
	SetType(TYPE_ENEMY);

	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, -0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 3.14f, 0.0f);
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nLife = 3;
	m_Info.nType = 0;

	// ����
	SetPos(m_Info.pos);
	SetRot(m_Info.rot);
	SetColor(m_Info.col);

	return S_OK;
}

//========================================
// �I��
//========================================
void CEnemy::Uninit(void)
{
	CSound *pSound = CManager::GetSound();

	pSound->StopSound();

	CObjectX::Uninit();
}

//========================================
// �X�V
//========================================
void CEnemy::Update(void)
{
	// �ߋ��̈ʒu�E�����̍X�V
	m_Info.posOld = m_Info.pos;
	m_Info.rotOld = m_Info.rot;

	// ��Ԑ���
	StateShift();

	SetPos(m_Info.pos);
	SetRot(m_Info.rot);
	SetColor(m_Info.col);

	CObjectX::Update();
}

//========================================
// �`��
//========================================
void CEnemy::Draw(void)
{
	CObjectX::Draw();
}

//========================================
// �q�b�g����
//========================================
void CEnemy::HitLife(int nDamage)
{
	CSound *pSound = CManager::GetSound();

	m_Info.nLife -= nDamage;

	if (m_Info.nLife <= 0)
	{
		// �p�[�e�B�N������
		CParticleX *pObj = CParticleX::Create();
		pObj->Par_SetPos(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 20, m_Info.pos.z));
		pObj->Par_SetRot(INIT_D3DXVECTOR3);
		pObj->Par_SetMove(D3DXVECTOR3(10.0f, 3.0f, 10.0f));
		pObj->Par_SetType(0);
		pObj->Par_SetLife(100);
		pObj->Par_SetCol(D3DXCOLOR(0.3f, 0.8f, 0.8f, 1.0f));
		pObj->Par_SetForm(15);

		// �G�̔j��
		Uninit();

		// �X�R�A�ݒ�
		CScore::SetScore(300);

		// ������SE�Đ�
		pSound->PlaySound(3);

		return;
	}
	else
	{
		// �q�b�gSE�̍Đ�
		pSound->PlaySound(2);

		// �_���[�W���
		SetState(STATE_DAMAGE);


		// �p�[�e�B�N������
		CParticleX *pObj = CParticleX::Create();
		pObj->Par_SetPos(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 20, m_Info.pos.z));
		pObj->Par_SetRot(INIT_D3DXVECTOR3);
		pObj->Par_SetMove(D3DXVECTOR3(10.0f, 3.0f, 10.0f));
		pObj->Par_SetType(0);
		pObj->Par_SetLife(50);
		pObj->Par_SetCol(D3DXCOLOR(0.3, 0.8f, 0.8f, 1.0f));
		pObj->Par_SetForm(15);
	}
}

//========================================
// ��Ԑݒ�
//========================================
void CEnemy::SetState(STATE state)
{
	// ���
	switch (state)
	{
	case STATE_NORMAL: { /* �ʏ��� */

		 // ��Ԃ̐ݒ�
		m_Info.state = STATE_NORMAL;

		// �_���[�W�F�̐ݒ�
		m_Info.col = D3DXCOLOR(1.0f, 1.0f, 1.1f, 1.0f);
	}
	   break;

	case STATE_DAMAGE: { /* �_���[�W��� */

		m_Info.state = STATE_DAMAGE;	// ��Ԑݒ�
		m_Info.nCntState = 10;			// ����

		// �_���[�W�F�̐ݒ�
		m_Info.col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	}
	   break;
	}
}

//========================================
// ��Ԑ���
//========================================
void CEnemy::StateShift(void)
{
	// ���
	switch (m_Info.state)
	{
	case STATE_NORMAL: { /* �ʏ��� */

	}
	   break;
	case STATE_DAMAGE: { /* �_���[�W��� */

		 // ��Ԃ�ؑւ���
		if (--m_Info.nCntState <= 0)
		{
			// �ʏ��Ԃɂ���
			SetState(STATE_NORMAL);
		}

	}
	   break;
	}

}

//========================================
// �ǂݍ���
//========================================
void CEnemy::Load(void)
{
	//// �ǂݍ���

	//// ���I�m��

	//for (int nRow1 = 0; nRow1 < 0; nRow1++)
	//{
	//	for (int nLine = 0; nLine < 0; nLine++)
	//	{
	//		switch (nLine)
	//		{
	//			// ���
	//		case SET_TYPE:
	//		{
	//			pSet[nRow1].nType = 0;
	//		}
	//		break;

	//		// �ʒu
	//		case SET_POS:
	//		{
	//			pSet[nRow1].pos.x = 0.0f; nLine++;
	//			pSet[nRow1].pos.y = 0.0f; nLine++;
	//			pSet[nRow1].pos.z = 0.0f;
	//		}
	//		break;

	//		// �ړ���
	//		case SET_SPEED:
	//		{
	//			pSet[nRow1].nSpeed = 0;
	//		}
	//		break;

	//		// ����ID
	//		case SET_UNIT:
	//		{
	//			pSet[nRow1].nStage = 0;
	//		}
	//		break;

	//		// �X�e�[�WID
	//		case SET_STAGE:
	//		{
	//			pSet[nRow1].nStage = 0;
	//		}
	//		break;
	//		}
	//	}
	//}
}

//========================================
// �z�u
//========================================
void CEnemy::SetEnemy(int nStage, int nUnit)
{
	for (int nCntSet = 0; nCntSet < m_nNumAll; nCntSet++, pSet++)
	{
		if (!pSet->bSet && pSet->nStage == nStage && pSet->nUnit == nUnit)
		{


			pSet->bSet = true;
		}
	}
}