//========================================
// 
// �L���[�u����
// 
//========================================
// *** block.cpp ***
//========================================
#include "bullet_cube.h"
#include "model.h"
#include "../../sound.h"
#include "../../csv_file.h"

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
	// �l���N���A
	m_Info.pos = INIT_D3DXVECTOR3;		// �ʒu
	m_Info.posOld = INIT_D3DXVECTOR3;	// �ʒu(�ߋ�)
	m_Info.movePos = INIT_D3DXVECTOR3;	// �ړ��ʒu
	m_Info.targetPos = INIT_D3DXVECTOR3;// �ړI�ʒu
	m_Info.rot = INIT_D3DXVECTOR3;		// ����
	m_Info.rotOld = INIT_D3DXVECTOR3;	// ����(�ߋ�)
	m_Info.size = INIT_D3DXVECTOR3;		// �傫��
	m_Info.col = INIT_D3DXCOLOR;		// �F
	m_Info.nType = 0;					// ���
	m_Info.nStandTime = 0;				// �ҋ@����
	m_Info.bContact = false;			// �ڐG�t���O
	m_Info.bActivation = false;			// �����t���O
	m_Info.nLife = 0;					// ����
	m_Info.nLifeMax = 0;				// �����̍ő�l
	m_Info.fRadius = 0.0f;				// ���a
	m_Info.nCntRadius = 0;				// ���a����	
	m_Info.fRadiusRate = 0.0f;			// ���a�̊���
	m_Info.bSet = false;				// �z�u�t���O
	m_Info.nID = 0;						// �������g��ID
}

//========================================
// �f�X�g���N�^
//========================================
CCube::~CCube()
{

}

//========================================
// ����
//========================================
CCube *CCube::Create(int nType, D3DXVECTOR3 pos)
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
	pCube->SetModel(MODEL_BULLET + nType);

	// ����������
	pCube->Init();

	pCube->m_Info.nType = nType;
	pCube->m_Info.nLife = 300;
	pCube->m_Info.nLifeMax = 300;
	pCube->CubeSetPos(pos);
	pCube->SetPos(pos);

	// �ʒu�␳
	/* ��	*/if (pCube->Correction(DIRECTION_UP, pCube->m_Info.pos)) { return pCube; }
	/* ��	*/if (pCube->Correction(DIRECTION_DOWN, pCube->m_Info.pos)) { return pCube; }
	/* ��	*/if (pCube->Correction(DIRECTION_LEFT, pCube->m_Info.pos)) { return pCube; }
	/* �E	*/if (pCube->Correction(DIRECTION_RIGHT, pCube->m_Info.pos)) { return pCube; }
	/* ��	*/if (pCube->Correction(DIRECTION_BACK, pCube->m_Info.pos)) { return pCube; }
	/* ��O	*/if (pCube->Correction(DIRECTION_FRONT, pCube->m_Info.pos)) { return pCube; }

	
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
	m_Info.nType = 0;
	m_Info.fRadius = 1.0f;
	m_Info.nID = GetID();

	// ����
	SetPos(m_Info.pos);
	//SetRot(m_Info.rot);
	SetScale(m_Info.size);
	SetColor(m_Info.col);

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

	if (m_Info.bSet && !m_Info.bContact)
	{
		// ����
		if (--m_Info.nLife <= 0)
		{
			Uninit();
			return;
		}
		else if (m_Info.nLife <= RADIUS_TIME)
		{
			m_Info.fRadius -= m_Info.fRadius / m_Info.nLife;
			m_Info.col.a *= ((float)m_Info.nLife / RADIUS_TIME);

			SetColor(m_Info.col);
		}
	}

	// �T�C�Y�̍X�V
	m_Info.size = D3DXVECTOR3(m_Info.fRadius, m_Info.fRadius, m_Info.fRadius);

	SetPos(m_Info.pos);
	//SetRot(m_Info.rot);
	SetScale(m_Info.size);

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
bool CCube::Correction(DIRECTION direction, D3DXVECTOR3 pos)
{
	for (int nCntObj = 0; nCntObj < GetNumAll(); nCntObj++)
	{
		//�@����t���O
		bool bHit = false;

		// �I�u�W�F�N�g�̃|�C���^
		CObject *pObj;

		// �I�u�W�F�N�g���擾
		pObj = GetObjectPointer(PRIO_OBJX, nCntObj);

		if (pObj != NULL)
		{
			int ID;
			TYPE type;

			// ID���擾
			ID = pObj->GetID();

			// ��ނ��擾
			type = pObj->GetType();

			if (type == TYPE_CUBE && m_Info.nID != ID)
			{// ��ނ��L���[�u�̏ꍇ

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

				// ��������������
				fPairWidth *= 0.5f;		// ��
				fPairHeight *= 0.5f;	// ����
				fPairDepth *= 0.5f;		// ���s��

				// �e�����̓����蔻��
				D3DXVECTOR3 PairUpPos = D3DXVECTOR3(PairPos.x, PairPos.y + fCubeHeight, PairPos.z);		// ��
				D3DXVECTOR3 PairDownPos = D3DXVECTOR3(PairPos.x, PairPos.y - fCubeHeight, PairPos.z);	// ��
				D3DXVECTOR3 PairLeftPos = D3DXVECTOR3(PairPos.x + fCubeWidth, PairPos.y, PairPos.z);	// ��
				D3DXVECTOR3 PairRightPos = D3DXVECTOR3(PairPos.x - fCubeWidth, PairPos.y, PairPos.z);	// �E
				D3DXVECTOR3 PairBackPos = D3DXVECTOR3(PairPos.x, PairPos.y, PairPos.z + fCubeDepth);	// ��
				D3DXVECTOR3 PairFrontPos = D3DXVECTOR3(PairPos.x, PairPos.y, PairPos.z - fCubeDepth);	// ��O

				switch (direction)
				{
				case DIRECTION_UP: {	/* �� */

					if ((pos.x + fWidth) > (PairUpPos.x - fPairWidth) &&
						(pos.x - fWidth) < (PairUpPos.x + fPairWidth) &&
						(pos.y + fDepth) > (PairUpPos.y - fPairDepth) &&
						(pos.y - fDepth) < (PairUpPos.y + fPairDepth) &&
						(pos.z + fDepth) > (PairUpPos.z - fPairDepth) &&
						(pos.z - fDepth) < (PairUpPos.z + fPairDepth))
					{// �u���b�N�������ɂ��鎞�A

						bHit = true;
						pos = PairUpPos;
					}
				}
				   break;
				case DIRECTION_DOWN: {	/* �� */

					if ((pos.x + fWidth) > (PairDownPos.x - fPairWidth) &&
						(pos.x - fWidth) < (PairDownPos.x + fPairWidth) &&
						(pos.y + fDepth) > (PairDownPos.y - fPairDepth) &&
						(pos.y - fDepth) < (PairDownPos.y + fPairDepth) &&
						(pos.z + fDepth) > (PairDownPos.z - fPairDepth) &&
						(pos.z - fDepth) < (PairDownPos.z + fPairDepth))
					{// �u���b�N�������ɂ��鎞�A

						bHit = true;
						pos = PairDownPos;
					}
				}
				   break;
				case DIRECTION_LEFT: {	/* �� */

					if ((pos.x + fWidth) > (PairLeftPos.x - fPairWidth) &&
						(pos.x - fWidth) < (PairLeftPos.x + fPairWidth) &&
						(pos.y + fDepth) > (PairLeftPos.y - fPairDepth) &&
						(pos.y - fDepth) < (PairLeftPos.y + fPairDepth) &&
						(pos.z + fDepth) > (PairLeftPos.z - fPairDepth) &&
						(pos.z - fDepth) < (PairLeftPos.z + fPairDepth))
					{// �u���b�N�������ɂ��鎞�A

						bHit = true;
						pos = PairLeftPos;
					}
				}
				   break;
				case DIRECTION_RIGHT: {	/* �E */

					if ((pos.x + fWidth) > (PairRightPos.x - fPairWidth) &&
						(pos.x - fWidth) < (PairRightPos.x + fPairWidth) &&
						(pos.y + fDepth) > (PairRightPos.y - fPairDepth) &&
						(pos.y - fDepth) < (PairRightPos.y + fPairDepth) &&
						(pos.z + fDepth) > (PairRightPos.z - fPairDepth) &&
						(pos.z - fDepth) < (PairRightPos.z + fPairDepth))
					{// �u���b�N�������ɂ��鎞�A

						bHit = true;
						pos = PairRightPos;
					}
				}
				   break;
				case DIRECTION_BACK: {	/* �� */

					if ((pos.x + fWidth) > (PairBackPos.x - fPairWidth) &&
						(pos.x - fWidth) < (PairBackPos.x + fPairWidth) &&
						(pos.y + fDepth) > (PairBackPos.y - fPairDepth) &&
						(pos.y - fDepth) < (PairBackPos.y + fPairDepth) &&
						(pos.z + fDepth) > (PairBackPos.z - fPairDepth) &&
						(pos.z - fDepth) < (PairBackPos.z + fPairDepth))
					{// �u���b�N�������ɂ��鎞�A

						bHit = true;
						pos = PairBackPos;
					}
				}
				   break;
				case DIRECTION_FRONT: {	/* ��O */

					if ((pos.x + fWidth) > (PairFrontPos.x - fPairWidth) &&
						(pos.x - fWidth) < (PairFrontPos.x + fPairWidth) &&
						(pos.y + fDepth) > (PairFrontPos.y - fPairDepth) &&
						(pos.y - fDepth) < (PairFrontPos.y + fPairDepth) &&
						(pos.z + fDepth) > (PairFrontPos.z - fPairDepth) &&
						(pos.z - fDepth) < (PairFrontPos.z + fPairDepth))
					{// �u���b�N�������ɂ��鎞�A

						bHit = true;
						pos = PairFrontPos;
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
	}
	return FALSE;
}

//========================================
// �ڐG����
//========================================
bool CCube::Contact(VECTOR vector, D3DXVECTOR3 pos)
{
	for (int nCntObj = 0; nCntObj < GetNumAll(); nCntObj++)
	{
		bool bHit = false;

		CObject *pObj;

		// �I�u�W�F�N�g���擾
		pObj = GetObjectPointer(PRIO_OBJX, nCntObj);

		if (pObj != NULL)
		{
			int ID;
			TYPE type;

			// ID���擾
			ID = pObj->GetID();

			// ��ނ��擾
			type = pObj->GetType();

			if (type == TYPE_CUBE && m_Info.nID != ID)
			{// ��ނ��L���[�u�̏ꍇ

				switch (vector)
				{
				case VECTOR_X: {	/* X���� */

					if (Collsion(DIRECTION_LEFT, pObj))
					{// ����
						break;
					}

					if (Collsion(DIRECTION_RIGHT, pObj))
					{// �E��
						break;
					}
				}
				   break;
				case VECTOR_Y: {	/* Y���� */

					if (Collsion(DIRECTION_UP, pObj))
					{// �㑤
						break;
					}

					// ����
					if (Collsion(DIRECTION_DOWN, pObj))
					{
						break;
					}
				}
				   break;
				case VECTOR_Z: {	/* Z���� */

					if (Collsion(DIRECTION_BACK, pObj))
					{// ����
						break;
					}

					// ��O��
					if (Collsion(DIRECTION_FRONT, pObj))
					{
						break;
					}
				}
				   break;
				}

				if (bHit)
				{
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

//========================================
// �����蔻��
//========================================
bool CCube::Collsion(DIRECTION direction, CObject *pObj)
{
	// ����t���O
	bool bHit = false;

	// �������g�̎擾
	D3DXVECTOR3 pos = GetPos();		// �ʒu
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

	// ��������������
	fPairWidth *= 0.5f;		// ��
	fPairHeight *= 0.5f;	// ����
	fPairDepth *= 0.5f;		// ���s��

	// �e�����̓����蔻��
	D3DXVECTOR3 PairUpPos = D3DXVECTOR3(PairPos.x, PairPos.y + fCubeHeight, PairPos.z);		// ��
	D3DXVECTOR3 PairDownPos = D3DXVECTOR3(PairPos.x, PairPos.y - fCubeHeight, PairPos.z);	// ��
	D3DXVECTOR3 PairLeftPos = D3DXVECTOR3(PairPos.x + fCubeWidth, PairPos.y, PairPos.z);	// ��
	D3DXVECTOR3 PairRightPos = D3DXVECTOR3(PairPos.x - fCubeWidth, PairPos.y, PairPos.z);	// �E
	D3DXVECTOR3 PairBackPos = D3DXVECTOR3(PairPos.x, PairPos.y, PairPos.z + fCubeDepth);	// ��
	D3DXVECTOR3 PairFrontPos = D3DXVECTOR3(PairPos.x, PairPos.y, PairPos.z - fCubeDepth);	// ��O

	switch (direction)
	{
	case DIRECTION_UP: {	/* �� */

		if ((pos.x + fWidth) > (PairUpPos.x - fPairWidth) &&
			(pos.x - fWidth) < (PairUpPos.x + fPairWidth) &&
			(pos.y + fDepth) > (PairUpPos.y - fPairDepth) &&
			(pos.y - fDepth) < (PairUpPos.y + fPairDepth) &&
			(pos.z + fDepth) > (PairUpPos.z - fPairDepth) &&
			(pos.z - fDepth) < (PairUpPos.z + fPairDepth))
		{// �u���b�N�������ɂ��鎞�A

			bHit = true;
		}
	}
	  break;
	case DIRECTION_DOWN: {	/* �� */

		if ((pos.x + fWidth) > (PairDownPos.x - fPairWidth) &&
			(pos.x - fWidth) < (PairDownPos.x + fPairWidth) &&
			(pos.y + fDepth) > (PairDownPos.y - fPairDepth) &&
			(pos.y - fDepth) < (PairDownPos.y + fPairDepth) &&
			(pos.z + fDepth) > (PairDownPos.z - fPairDepth) &&
			(pos.z - fDepth) < (PairDownPos.z + fPairDepth))
		{// �u���b�N�������ɂ��鎞�A

			bHit = true;
		}
	}
	 break;
	case DIRECTION_LEFT: {	/* �� */

		if ((pos.x + fWidth) > (PairLeftPos.x - fPairWidth) &&
			(pos.x - fWidth) < (PairLeftPos.x + fPairWidth) &&
			(pos.y + fDepth) > (PairLeftPos.y - fPairDepth) &&
			(pos.y - fDepth) < (PairLeftPos.y + fPairDepth) &&
			(pos.z + fDepth) > (PairLeftPos.z - fPairDepth) &&
			(pos.z - fDepth) < (PairLeftPos.z + fPairDepth))
		{// �u���b�N�������ɂ��鎞�A

			bHit = true;
		}
	}
	 break;
	case DIRECTION_RIGHT: {	/* �E */

		if ((pos.x + fWidth) > (PairRightPos.x - fPairWidth) &&
			(pos.x - fWidth) < (PairRightPos.x + fPairWidth) &&
			(pos.y + fDepth) > (PairRightPos.y - fPairDepth) &&
			(pos.y - fDepth) < (PairRightPos.y + fPairDepth) &&
			(pos.z + fDepth) > (PairRightPos.z - fPairDepth) &&
			(pos.z - fDepth) < (PairRightPos.z + fPairDepth))
		{// �u���b�N�������ɂ��鎞�A

			bHit = true;
		}
	}
	  break;
	case DIRECTION_BACK: {	/* �� */

		if ((pos.x + fWidth) > (PairBackPos.x - fPairWidth) &&
			(pos.x - fWidth) < (PairBackPos.x + fPairWidth) &&
			(pos.y + fDepth) > (PairBackPos.y - fPairDepth) &&
			(pos.y - fDepth) < (PairBackPos.y + fPairDepth) &&
			(pos.z + fDepth) > (PairBackPos.z - fPairDepth) &&
			(pos.z - fDepth) < (PairBackPos.z + fPairDepth))
		{// �u���b�N�������ɂ��鎞�A

			bHit = true;
		}
	}
	 break;
	case DIRECTION_FRONT: {	/* ��O */

		if ((pos.x + fWidth) > (PairFrontPos.x - fPairWidth) &&
			(pos.x - fWidth) < (PairFrontPos.x + fPairWidth) &&
			(pos.y + fDepth) > (PairFrontPos.y - fPairDepth) &&
			(pos.y - fDepth) < (PairFrontPos.y + fPairDepth) &&
			(pos.z + fDepth) > (PairFrontPos.z - fPairDepth) &&
			(pos.z - fDepth) < (PairFrontPos.z + fPairDepth))
		{// �u���b�N�������ɂ��鎞�A
			
			bHit = true;
		}
	}
	  break;
	}

	// ���肪�^�Ȃ� TRUE ��Ԃ�
	if (bHit)
	{
		return TRUE;
	}

	return FALSE;
}