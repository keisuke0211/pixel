//========================================
// 
// �G�l�~�[����
// 
//========================================
// *** enemy.cpp ***
//========================================
#include "enemy.h"
#include "../../scene/pause.h"
#include "../../manager.h"
#include "../../system/renderer.h"
#include "../../system/sound.h"
#include "../UI/score.h"
#include "../EFFECT/particleX.h"
#include "block.h"
#include "bullet_cube.h"
#include "../../system/input.h"

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
	m_Info.nCntTime = 0;
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
CEnemy *CEnemy::Create(int nType, int nMove, D3DXVECTOR3 pos)
{
	CEnemy *pEnemy = new CEnemy;

	pEnemy->SetModel(MODEL_ENEMY_00 + nType);

	// ����������
	pEnemy->Init();

	pEnemy->m_Info.pos = pos;
	pEnemy->m_Info.nMove = nMove;
	pEnemy->SetPos(pEnemy->m_Info.pos);
	pEnemy->SetRot(pEnemy->m_Info.rot);
	pEnemy->SetColor(pEnemy->m_Info.col);

	if (pEnemy->m_Info.nMove == 1)
	{
		pEnemy->m_Info.move = D3DXVECTOR3(0.0f, 0.0f, 3.0f);
	}

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

	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	bool bPause = CPause::IsPause();

	if (!bPause)
	{

		// �ߋ��̈ʒu�E�����̍X�V
		m_Info.posOld = m_Info.pos;
		m_Info.rotOld = m_Info.rot;

		// ��Ԑ���
		StateShift();

		// �ړ��ʂ̑��
		m_Info.pos.x += m_Info.move.x;

		// �����蔻��
		if (Collsion(VECTOR_X, m_Info.pos))
		{

		}

		// �ړ��ʂ̑��
		m_Info.pos.z += m_Info.move.z;

		if (Collsion(VECTOR_Z, m_Info.pos))
		{

		}

		// ���̈ړ�����
		if (++m_Info.nCntTime >= 240 && m_Info.nMove == 1)
		{
			m_Info.move.z *= -1;
			m_Info.nCntTime = 0;

			if (m_Info.rot.y == 0.0f)
			{
				m_Info.rot.y = 3.14f;
			}
			else if (m_Info.rot.y = 3.14f)
			{
				m_Info.rot.y = 0.0f;
			}
			SetRot(m_Info.rot);
		}

		CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h

		SetPos(m_Info.pos);
		SetColor(m_Info.col);

		CObjectX::Update();
	}
}

//========================================
// �`��
//========================================
void CEnemy::Draw(void)
{
	CObjectX::Draw();
}

//========================================
// �����蔻��
//========================================
bool CEnemy::Collsion(VECTOR vector, D3DXVECTOR3 pos)
{
	bool bHit = false;

	for (int nCntPrio = 0; nCntPrio < PRIO_MAX; nCntPrio++)
	{
		// �擪�I�u�W�F�N�g���擾
		CObject *pObj = CObject::GetTop(nCntPrio);

		while (pObj != NULL)
		{// �g�p����Ă��鎞�A

			// ���̃I�u�W�F�N�g
			CObject *pObjNext = pObj->GetNext();

			// ��ނ��擾
			TYPE type = pObj->GetType();

			// �G�l�~�[�̊e�p�[�c�̎擾
			D3DXVECTOR3 PosOld = GetPosOld();	// �ʒu(�ߋ�)
			D3DXVECTOR3 RotOld = GetRotOld();	// ����(�ߋ�)
			float fWidth = GetWidth();			// ��
			float fHeight = GetHeight();		// ����
			float fDepth = GetDepth();			// ���s��

			// �e��ނ̓����蔻��
			if (type == TYPE_BLOCK)
			{// �u���b�N��������

				// �u���b�N�̎擾
				D3DXVECTOR3 PairPos = pObj->GetPos();		// �ʒu
				D3DXVECTOR3 PairPosOld = pObj->GetPosOld();	// �ʒu(�ߋ�)
				float fPairWidth = pObj->GetWidth();		// ��
				float fPairHeight = pObj->GetHeight();		// ����
				float fPairDepth = pObj->GetDepth();		// ���s��

				switch (vector)
				{
				case VECTOR_X: {	/* X���� */

					if ((pos.z + fDepth) > (PairPos.z - fPairDepth) &&
						(pos.z - fDepth) < (PairPos.z + fPairDepth) &&
						(pos.y + fHeight) > (PairPos.y - fPairHeight) &&
						(pos.y - fHeight) < (PairPos.y + fPairHeight))
					{// ���ӂƎ�O�ӂ��u���b�N�̕��̓����̎��A

						if ((pos.x + fWidth) >= (PairPos.x - fPairWidth) &&
							(PosOld.x + fWidth) <= (PairPos.x - fPairWidth))
						{// ������߂荞��ł��鎞

							bHit = true;
							pos.x = (PairPos.x - fPairWidth) - fWidth;
						}
						else if ((pos.x - fWidth) <= (PairPos.x + fPairWidth) &&
							(PosOld.x - fWidth) >= (PairPos.x + fPairWidth))
						{// �E����߂荞��ł��鎞

							bHit = true;
							pos.x = (PairPos.x + fPairWidth) + fWidth;
						}
					}
				}
				   break;
				case VECTOR_Y: {	/* Y���� */

					if ((pos.x + fWidth) > (PairPos.x - fPairWidth) &&
						(pos.x - fWidth) < (PairPos.x + fPairWidth) &&
						(pos.z + fDepth) > (PairPos.z - fPairDepth) &&
						(pos.z - fDepth) < (PairPos.z + fPairDepth))
					{// ���ӂƉE�ӂ�����̕��̓����̎��A

						if ((pos.y + fHeight) > (PairPos.y - fPairHeight) &&
							(PosOld.y + fHeight) <= (PairPos.y - fPairHeight))
						{// ������߂荞��ł��鎞

							bHit = true;
							pos.y = (PairPos.y - fPairHeight) - fHeight;
						}
						else if ((pos.y - fHeight) < (PairPos.y + fPairHeight) &&
							(PosOld.y - fHeight) >= (PairPos.y + fPairHeight))
						{// �ォ��߂荞��ł��鎞

							bHit = true;
							pos.y = (PairPos.y + fPairHeight) + fHeight;
						}
					}
				}
				   break;
				case VECTOR_Z: {	/* Z���� */

					if ((pos.x + fWidth) > (PairPos.x - fPairWidth) &&
						(pos.x - fWidth) < (PairPos.x + fPairWidth) &&
						(pos.y + fHeight) > (PairPos.y - fPairHeight) &&
						(pos.y - fHeight) < (PairPos.y + fPairHeight))
					{// ���ӂƉE�ӂ�����̕��̓����̎��A

						if ((pos.z + fDepth) >= (PairPos.z - fPairDepth) &&
							(PosOld.z + fDepth) <= (PairPos.z - fPairDepth))
						{// �O����߂荞��ł��鎞

							bHit = true;
							pos.z = (PairPos.z - fPairDepth) - fDepth;
						}
						else if ((pos.z - fDepth) <= (PairPos.z + fPairDepth) &&
							(PosOld.z - fDepth) >= (PairPos.z + fPairDepth))
						{// ������߂荞��ł��鎞

							bHit = true;
							pos.z = (PairPos.z + fPairDepth) + fDepth;
						}
					}
				}
				   break;
				}

			}
			else if (type == TYPE_CUBE)
			{// �L���[�u��������

				 // �L���[�u�̎擾
				D3DXVECTOR3 PairPos = pObj->GetPos();		// �ʒu
				D3DXVECTOR3 PairPosOld = pObj->GetPosOld();	// �ʒu(�ߋ�)
				float fPairWidth = pObj->GetWidth();		// ��
				float fPairHeight = pObj->GetHeight();		// ����
				float fPairDepth = pObj->GetDepth();		// ���s��

				switch (vector)
				{
				case VECTOR_X: {	/* X���� */

					if ((pos.z + fDepth) > (PairPos.z - fPairDepth) &&
						(pos.z - fDepth) < (PairPos.z + fPairDepth) &&
						(pos.y + fHeight) > (PairPos.y - fPairHeight) &&
						(pos.y - fHeight) < (PairPos.y + fPairHeight))
					{// ���ӂƎ�O�ӂ��u���b�N�̕��̓����̎��A

						if ((pos.x + fWidth) >= (PairPos.x - fPairWidth) &&
							(PosOld.x + fWidth) <= (PairPos.x - fPairWidth))
						{// ������߂荞��ł��鎞

							bHit = true;
							pos.x = (PairPos.x - fPairWidth) - fWidth;
						}
						else if ((pos.x - fWidth) <= (PairPos.x + fPairWidth) &&
							(PosOld.x - fWidth) >= (PairPos.x + fPairWidth))
						{// �E����߂荞��ł��鎞

							bHit = true;
							pos.x = (PairPos.x + fPairWidth) + fWidth;
						}
					}
				}
				   break;
				case VECTOR_Y: {	/* Y���� */

					if ((pos.x + fWidth) > (PairPos.x - fPairWidth) &&
						(pos.x - fWidth) < (PairPos.x + fPairWidth) &&
						(pos.z + fDepth) > (PairPos.z - fPairDepth) &&
						(pos.z - fDepth) < (PairPos.z + fPairDepth))
					{// ���ӂƉE�ӂ�����̕��̓����̎��A

						if ((pos.y + fHeight) > (PairPos.y - fPairHeight) &&
							(PosOld.y + fHeight) <= (PairPos.y - fPairHeight))
						{// ������߂荞��ł��鎞

							bHit = true;
							pos.y = (PairPos.y - fPairHeight) - fHeight;
						}
						else if ((pos.y - fHeight) < (PairPos.y + fPairHeight) &&
							(PosOld.y - fHeight) >= (PairPos.y + fPairHeight))
						{// �ォ��߂荞��ł��鎞

							bHit = true;
							pos.y = (PairPos.y + fPairHeight) + fHeight;
						}
					}
				}
				   break;
				case VECTOR_Z: {	/* Z���� */

					if ((pos.x + fWidth) > (PairPos.x - fPairWidth) &&
						(pos.x - fWidth) < (PairPos.x + fPairWidth) &&
						(pos.y + fHeight) > (PairPos.y - fPairHeight) &&
						(pos.y - fHeight) < (PairPos.y + fPairHeight))
					{// ���ӂƉE�ӂ�����̕��̓����̎��A

						if ((pos.z + fDepth) >= (PairPos.z - fPairDepth) &&
							(PosOld.z + fDepth) <= (PairPos.z - fPairDepth))
						{// �O����߂荞��ł��鎞

							bHit = true;
							pos.z = (PairPos.z - fPairDepth) - fDepth;
						}
						else if ((pos.z - fDepth) <= (PairPos.z + fPairDepth) &&
							(PosOld.z - fDepth) >= (PairPos.z + fPairDepth))
						{// ������߂荞��ł��鎞

							bHit = true;
							pos.z = (PairPos.z + fPairDepth) + fDepth;
						}
					}
				}
				   break;
				}
			}

			if (bHit)
			{
				if (type == TYPE_BLOCK)
				{

				}
				else if (type == TYPE_CUBE)
				{
					// �_�C�i�~�b�N�L���X�g����
					CCube *pCube = dynamic_cast<CCube*>(pObj);

					pCube->SetCubeLife(1);
				}
				return TRUE;
			}
			pObj = pObjNext;	// ���̃I�u�W�F�N�g����
		}
	}
	return FALSE;
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