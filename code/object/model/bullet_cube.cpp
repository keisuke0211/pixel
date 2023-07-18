//========================================
// 
// �L���[�u����
// 
//========================================
// *** block.cpp ***
//========================================
#include "bullet_cube.h"
#include "particleX.h"
#include "model.h"
#include "../../sound.h"
#include "../../csv_file.h"

// �ÓI�ϐ�
int CCube::m_nNumAll = -1;
int CCube::m_nNumBom = 1;
bool CCube::bLeadSet = false;

//========================================
// �}�N����`
//========================================
#define RADIUS_TIME			(20)	// ���a�E���ڎ���
#define SIZE_DIAMETER		(2.0f)	// �T�C�Y�̔{��
#define COLLSION_DIAMETER	(1.0f)	// ����̔{��

//========================================
// �R���X�g���N�^
//========================================
CCube::CCube(int nPriority) : CObjectX(nPriority)
{
	m_nNumAll++;	// ���������Z

	// �l���N���A
	m_Info.pos = INIT_D3DXVECTOR3;		// �ʒu
	m_Info.posOld = INIT_D3DXVECTOR3;	// �ʒu(�ߋ�)
	m_Info.movePos = INIT_D3DXVECTOR3;	// �ړ��ʒu
	m_Info.targetPos = INIT_D3DXVECTOR3;// �ړI�ʒu
	m_Info.rot = INIT_D3DXVECTOR3;		// ����
	m_Info.rotOld = INIT_D3DXVECTOR3;	// ����(�ߋ�)
	m_Info.size = INIT_D3DXVECTOR3;		// �傫��
	m_Info.col = INIT_D3DXCOLOR;		// �F
	m_Info.nShape = -1;					// �`��
	m_Info.nStandTime = 0;				// �ҋ@����
	m_Info.bContact = false;			// �ڐG�t���O
	m_Info.bActivation = false;			// �����t���O
	m_Info.nLife = 0;					// ����
	m_Info.nLifeMax = 0;				// �����̍ő�l
	m_Info.fRadius = 0.0f;				// ���a
	m_Info.nCntRadius = 0;				// ���a����	
	m_Info.fRadiusRate = 0.0f;			// ���a�̊���
	m_Info.bSet = false;				// �z�u�t���O
	m_Info.nID = m_nNumAll;				// �������g��ID
}

//========================================
// �f�X�g���N�^
//========================================
CCube::~CCube()
{
	m_nNumAll--;	// �������Z
}

//========================================
// ����
//========================================
CCube *CCube::Create(int nShape, D3DXVECTOR3 pos)
{
	CCube *pCube = NULL;

	if (pCube != NULL)
	{
		return pCube;
	}

	// �I�u�W�F�N�g2D�̐���
	pCube = new CCube;

	pCube->m_Info.nCntRadius = RADIUS_TIME;
	pCube->m_Info.fRadiusRate = 0.0f;
	pCube->m_Info.bSet = false;
	pCube->SetModel(MODEL_BULLET + nShape);

	// ����������
	pCube->Init();

	pCube->m_Info.nShape = nShape;
	pCube->m_Info.nLife = 300;
	pCube->m_Info.nLifeMax = 300;
	pCube->CubeSetPos(pos);
	pCube->SetPos(pos);

	// �ʒu�␳
	/* X��	*/if (pCube->Correction(VECTOR_X, pCube->m_Info.pos)) { return pCube; }
	/* Y��	*/if (pCube->Correction(VECTOR_Y, pCube->m_Info.pos)) { return pCube; }
	/* Z��	*/if (pCube->Correction(VECTOR_Z, pCube->m_Info.pos)) { return pCube; }

	return pCube;
}

//========================================
// ������
//========================================
HRESULT CCube::Init(void)
{
	CObjectX::Init();

	// ��ނ̐ݒ�
	SetType(TYPE_CUBE);

	m_Info.pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nShape = 0;
	m_Info.fRadius = 1.0f;

	// ����
	SetPos(m_Info.pos);
	//SetRot(m_Info.rot);
	SetScale(m_Info.size);
	SetColor(m_Info.col);

	// �P�ڂ̃L���[�u�Ȃ�
	if (m_Info.nID == 0)
	{
		// �擪�t���O��^�ɂ���
		bLeadSet = true;
	}

	return S_OK;
}

//========================================
// �I��
//========================================
void CCube::Uninit(void)
{
	CObjectX::Uninit();
}

//========================================
// �X�V
//========================================
void CCube::Update(void)
{
	// �ߋ��̈ʒu�E�����̍X�V
	m_Info.posOld = m_Info.pos;
	m_Info.rotOld = m_Info.rot;

	// ���a����
	if (m_Info.bSet == false)
	{
		m_Info.fRadiusRate = (float)m_Info.nCntRadius / (float)RADIUS_TIME;
		m_Info.fRadius = 1 * (1.0f - m_Info.fRadiusRate);

		if (--m_Info.nCntRadius <= 0)
		{
			m_Info.bSet = true;
		}
	}

	// �`�ɂ�锚������
	if (!m_Info.bActivation && m_Info.bSet)
	{
		//// �ڐG����
		//if (Contact(VECTOR_X, m_Info.pos))
		//{
		//	m_Info.bContact = true;
		//}

		//if (Contact(VECTOR_Y, m_Info.pos))
		//{
		//	m_Info.bContact = true;
		//}

		//if (Contact(VECTOR_Z, m_Info.pos))
		//{
		//	m_Info.bContact = true;
		//}

		//if (m_Info.bContact)
		//{
		//	switch (m_Info.nShape)
		//	{
		//	case SHAPE_LINE:	/* ���� */
		//		m_Info.col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		//		break;
		//	case SHAPE_SQUARE:	/* �l�p */
		//		m_Info.col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		//		break;
		//	}

		//	m_Info.nStandTime = 90;
		//	m_Info.bActivation = true;
		//}
	}

	// ��������
	if (m_Info.bActivation)
	{
		// �ҋ@����	
		if (--m_Info.nStandTime <= 0)
		{
			// �p�[�e�B�N������
			CParticleX *pObj = CParticleX::Create();
			pObj->Par_SetPos(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 20, m_Info.pos.z));
			pObj->Par_SetRot(INIT_D3DXVECTOR3);
			pObj->Par_SetMove(D3DXVECTOR3(10.0f, 5.0f, 10.0f));
			pObj->Par_SetType(0);
			pObj->Par_SetLife(50);
			pObj->Par_SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
			pObj->Par_SetForm(25);

			Uninit();
			return;
		}
		else if (m_Info.nStandTime <= (RADIUS_TIME))
		{
			m_Info.fRadius -= m_Info.fRadius / m_Info.nStandTime;
			m_Info.col.a *= ((float)m_Info.nStandTime / RADIUS_TIME);
		}
		else if (m_Info.nStandTime <= (RADIUS_TIME * 2))
		{
			m_Info.fRadius -= m_Info.fRadius / m_Info.nStandTime;
		}
	}

	// ��������
	if (m_Info.bSet && !m_Info.bContact)
	{
		// ����
		if (--m_Info.nLife <= 0)
		{
			// �P�ڂ̃L���[�u�Ȃ�
			if (m_Info.nID == 0)
			{
				// �擪�t���O���U�ɂ���
				bLeadSet = false;
			}

			// �p�[�e�B�N������
			CParticleX *pObj = CParticleX::Create();
			pObj->Par_SetPos(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y, m_Info.pos.z));
			pObj->Par_SetRot(INIT_D3DXVECTOR3);
			pObj->Par_SetMove(D3DXVECTOR3(15.0f, 15.0f, 15.0f));
			pObj->Par_SetType(0);
			pObj->Par_SetLife(100);
			pObj->Par_SetCol(D3DXCOLOR(0.3f, 0.8f, 0.8f, 1.0f));
			pObj->Par_SetForm(10);

			// ���͂ɃL���[�u�����邩
			Contact(0, VECTOR_X, m_Info.pos);
			Contact(0, VECTOR_Y, m_Info.pos);
			Contact(0, VECTOR_Z, m_Info.pos);

			// �I�u�W�F�N�g�j��
			Uninit();

			m_nNumBom = 1;

			return;
		}
		else if (m_Info.nLife <= (RADIUS_TIME * 2))
		{
			m_Info.fRadius -= m_Info.fRadius / m_Info.nLife;
		}
		else if (m_Info.nLife <= RADIUS_TIME)
		{
			m_Info.fRadius -= m_Info.fRadius / m_Info.nLife;
			m_Info.col.a *= ((float)m_Info.nLife / RADIUS_TIME);
		}
	}

	// �T�C�Y�̍X�V
	m_Info.size = D3DXVECTOR3(m_Info.fRadius, m_Info.fRadius, m_Info.fRadius);

	SetPos(m_Info.pos);
	//SetRot(m_Info.rot);
	SetScale(m_Info.size);
	SetColor(m_Info.col);

	CObjectX::Update();
}

//========================================
// �`��
//========================================
void CCube::Draw(void)
{
	CObjectX::Draw();
}

//========================================
// �ʒu�␳
//========================================
bool CCube::Correction(VECTOR vector, D3DXVECTOR3 pos)
{
	// �擪�I�u�W�F�N�g���擾
	CObject *pObj = CObject::GetTop(PRIO_CUBE);

	while (pObj != NULL)
	{// �g�p����Ă��鎞�A

		//�@����t���O
		bool bHit = false;

		// ���̃I�u�W�F�N�g
		CObject *pObjNext = pObj->GetNext();

		int ID;
		TYPE type;

		// ��ނ��擾
		type = pObj->GetType();

		if (type == TYPE_CUBE)
		{// ��ނ��L���[�u�̏ꍇ

			// �_�C�i�~�b�N�L���X�g����
			CCube *pCube = dynamic_cast<CCube*>(pObj);

			// ID���擾
			ID = pCube->GetID();

			if (m_Info.nID != ID)
			{// �����ȊO�̃L���[�u��������A

				// �������g�̎擾
				float fWidth = GetWidth();		// ��
				float fHeight = GetHeight();	// ����
				float fDepth = GetDepth();		// ���s��

				// ����̎擾
				D3DXVECTOR3 PairPos = pObj->GetPos();	// �ʒu
				float fPairWidth = pObj->GetWidth();	// ��
				float fPairHeight = pObj->GetHeight();	// ����
				float fPairDepth = pObj->GetDepth();	// ���s��

				//�@���S�_����̋���
				float fCubeWidth = fPairWidth * SIZE_DIAMETER;		// ��
				float fCubeHeight = fPairHeight * SIZE_DIAMETER;	// ����
				float fCubeDepth = fPairDepth * SIZE_DIAMETER;		// ���s��

				// �T�C�Y����
				fPairWidth *= COLLSION_DIAMETER;	// ��
				fPairHeight *= COLLSION_DIAMETER;	// ����
				fPairDepth *= COLLSION_DIAMETER;	// ���s��

				// �e�����̓����蔻��
				D3DXVECTOR3 PairUpPos = D3DXVECTOR3(PairPos.x, PairPos.y + fCubeHeight, PairPos.z);		// ��
				D3DXVECTOR3 PairDownPos = D3DXVECTOR3(PairPos.x, PairPos.y - fCubeHeight, PairPos.z);	// ��
				D3DXVECTOR3 PairLeftPos = D3DXVECTOR3(PairPos.x + fCubeWidth, PairPos.y, PairPos.z);	// ��
				D3DXVECTOR3 PairRightPos = D3DXVECTOR3(PairPos.x - fCubeWidth, PairPos.y, PairPos.z);	// �E
				D3DXVECTOR3 PairBackPos = D3DXVECTOR3(PairPos.x, PairPos.y, PairPos.z + fCubeDepth);	// ��
				D3DXVECTOR3 PairFrontPos = D3DXVECTOR3(PairPos.x, PairPos.y, PairPos.z - fCubeDepth);	// ��O

				switch (vector)
				{
				case VECTOR_X: {	/* X���� */

					if (Collsion(pos, PairLeftPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
					{// ����
						m_Info.pos = PairLeftPos;
						break;
					}

					if (Collsion(pos, PairRightPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
					{// �E��
						m_Info.pos = PairRightPos;
						break;
					}
				}
							   break;
				case VECTOR_Y: {	/* Y���� */

					if (Collsion(pos, PairUpPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
					{// �㑤
						m_Info.pos = PairUpPos;
						break;
					}

					if (Collsion(pos, PairDownPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
					{// ����
						m_Info.pos = PairDownPos;
						break;
					}
				}
							   break;
				case VECTOR_Z: {	/* Z���� */

					if (Collsion(pos, PairBackPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
					{// ����
						m_Info.pos = PairBackPos;
						break;
					}

					if (Collsion(pos, PairFrontPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
					{// ��O��
						m_Info.pos = PairFrontPos;
						break;
					}
				}
							   break;
				}

				// ���肪�^�Ȃ� TRUE ��Ԃ�
				if (bHit)
				{
					return TRUE;
				}
			}
		}

		pObj = pObjNext;	// ���̃I�u�W�F�N�g����
	}
	return FALSE;
}

//========================================
// �ڐG����
//========================================
bool CCube::Contact(int mode, VECTOR vector, D3DXVECTOR3 pos)
{
	// �擪�I�u�W�F�N�g���擾
	CObject *pObj = CObject::GetTop(PRIO_CUBE);

	while (pObj != NULL)
	{// �g�p����Ă��鎞�A

		bool bHit = false;

		// ���̃I�u�W�F�N�g
		CObject *pObjNext = pObj->GetNext();

		int ID;
		TYPE type;

		// ��ނ��擾
		type = pObj->GetType();

		if (type == TYPE_CUBE)
		{// ��ނ��L���[�u�̏ꍇ

			// �_�C�i�~�b�N�L���X�g����
			CCube *pCube = dynamic_cast<CCube*>(pObj);

			// ID���擾
			ID = pCube->GetID();

			// �z�u�t���O���擾
			bool bSet = pCube->CubeGetSet();

			if(!pCube->m_Info.bBom)
			{
				if (m_Info.nID != ID && bSet)
				{// �����ȊO�̃L���[�u��������A

					// �������g�̎擾
					float fWidth = GetWidth();		// ��
					float fHeight = GetHeight();	// ����
					float fDepth = GetDepth();		// ���s��

					// ����̎擾
					D3DXVECTOR3 PairPos = pCube->GetPos();	// �ʒu
					float fPairWidth = pCube->GetWidth();	// ��
					float fPairHeight = pCube->GetHeight();	// ����
					float fPairDepth = pCube->GetDepth();	// ���s��

					//�@���S�_����̋���
					float fCubeWidth = fPairWidth * SIZE_DIAMETER;		// ��
					float fCubeHeight = fPairHeight * SIZE_DIAMETER;	// ����
					float fCubeDepth = fPairDepth * SIZE_DIAMETER;		// ���s��

					// �T�C�Y����
					fPairWidth *= COLLSION_DIAMETER;	// ��
					fPairHeight *= COLLSION_DIAMETER;	// ����
					fPairDepth *= COLLSION_DIAMETER;	// ���s��

					// �e�����̓����蔻��
					D3DXVECTOR3 PairUpPos = D3DXVECTOR3(PairPos.x, PairPos.y + fCubeHeight, PairPos.z);		// ��
					D3DXVECTOR3 PairDownPos = D3DXVECTOR3(PairPos.x, PairPos.y - fCubeHeight, PairPos.z);	// ��
					D3DXVECTOR3 PairLeftPos = D3DXVECTOR3(PairPos.x + fCubeWidth, PairPos.y, PairPos.z);	// ��
					D3DXVECTOR3 PairRightPos = D3DXVECTOR3(PairPos.x - fCubeWidth, PairPos.y, PairPos.z);	// �E
					D3DXVECTOR3 PairBackPos = D3DXVECTOR3(PairPos.x, PairPos.y, PairPos.z + fCubeDepth);	// ��
					D3DXVECTOR3 PairFrontPos = D3DXVECTOR3(PairPos.x, PairPos.y, PairPos.z - fCubeDepth);	// ��O

					switch (vector)
					{
					case VECTOR_X: {	/* X���� */

						if (Collsion(pos, PairLeftPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
						{// ����

							bHit = true;
							break;
						}

						if (Collsion(pos, PairRightPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
						{// �E��

							bHit = true;
							break;
						}
					}
					   break;
					case VECTOR_Y: {	/* Y���� */

						if (Collsion(pos, PairUpPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
						{// �㑤

							bHit = true;
							break;
						}

						if (Collsion(pos, PairDownPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
						{// ����

							bHit = true;
							break;
						}
					}
					   break;
					case VECTOR_Z: {	/* Z���� */

						if (Collsion(pos, PairBackPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
						{// ����

							bHit = true;
							break;
						}

						if (Collsion(pos, PairFrontPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
						{// ��O��

							bHit = true;
							break;
						}
					}
					   break;
					}

					// ���肪�^�Ȃ� TRUE ��Ԃ�
					if (bHit)
					{
						// �A������
						if (mode == 0)
						{
							pCube->Destruction(pCube);
						}
						return TRUE;
					}
				}
			}
		}

		pObj = pObjNext;	// ���̃I�u�W�F�N�g����
	}
	return FALSE;
}

//========================================
// �����蔻��
//========================================
bool CCube::Collsion(D3DXVECTOR3 pos, D3DXVECTOR3 PairPos, D3DXVECTOR3 size, D3DXVECTOR3 PairSize)
{
	// ����t���O
	bool bHit = false;

	if ((pos.x + size.x) > (PairPos.x - PairSize.x) &&
		(pos.x - size.x) < (PairPos.x + PairSize.x) &&
		(pos.y + size.y) > (PairPos.y - PairSize.y) &&
		(pos.y - size.y) < (PairPos.y + PairSize.y) &&
		(pos.z + size.z) > (PairPos.z - PairSize.z) &&
		(pos.z - size.z) < (PairPos.z + PairSize.z))
	{// �u���b�N��������ɂ��鎞�A

		return TRUE;
	}

	return FALSE;
}

//========================================
// �j�󏈗�
//========================================
void CCube::Destruction(CCube *pCube)
{
	// �I�u�W�F�N�g�j��
	pCube->m_Info.nLife = 20 + m_nNumBom;
	pCube->m_Info.bBom = true;

	m_nNumBom++;
	// ���͂ɃL���[�u�����邩
	pCube->Contact(0, VECTOR_X, pCube->m_Info.pos);
	pCube->Contact(0, VECTOR_Y, pCube->m_Info.pos);
	pCube->Contact(0, VECTOR_Z, pCube->m_Info.pos);
}