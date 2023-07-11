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

	// �ڐG����
	/*if (!pCube->Contact(VECTOR_X, pCube->m_Info.pos))
	{
		
	}*/
	/*if (!pCube->Contact(VECTOR_Y, pCube->m_Info.pos))
	{

	}*/
	/*if (!pCube->Contact(VECTOR_Z, pCube->m_Info.pos))
	{

	}*/

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

				// �������g�̎擾
				D3DXVECTOR3 posOld = GetPosOld();	// �ʒu(�ߋ�)
				float fWidth = GetWidth();			// ��
				float fHeight = GetHeight();		// ����
				float fDepth = GetDepth();			// ���s��

				// ����̎擾
				D3DXVECTOR3 PairPos = pObj->GetPos();	// �ʒu
				float fPairWidth = pObj->GetWidth();	// ��
				float fPairHeight = pObj->GetHeight();	// ����
				float fPairDepth = pObj->GetDepth();	// ���s��

				fPairWidth *= SIZE_DIAMETER;	// ��
				fPairHeight *= SIZE_DIAMETER;	// ����
				fPairDepth *= SIZE_DIAMETER;	// ���s��

				switch (vector)
				{
				case VECTOR_X: {	/* X���� */

					if ((pos.x + fWidth) > (PairPos.x - fPairWidth) &&
						(pos.x - fWidth) < (PairPos.x + fPairWidth))
					{// �u���b�N���E���E�����ɂ��鎞�A

						if ((pos.x + fWidth) >= (PairPos.x - fPairWidth) &&
							(posOld.x + fWidth) <= (PairPos.x - fPairWidth))
						{// ������߂荞��ł��鎞

							bHit = true;
							pos.x = (PairPos.x - fPairWidth) - (fWidth);
						}
						else if ((pos.x - fWidth) <= (PairPos.x + fPairWidth) &&
							(posOld.x - fWidth) >= (PairPos.x + fPairWidth))
						{// �E����߂荞��ł��鎞

							bHit = true;
							pos.x = (PairPos.x + fPairWidth) + (fWidth);
						}
					}
				}
				   break;
				case VECTOR_Y: {	/* Y���� */

					if ((pos.x + fWidth) > (PairPos.x - fPairWidth) &&
						(pos.x - fWidth) < (PairPos.x + fPairWidth))
					{// ���ӂƉE�ӂ�����̕��̓����̎��A

						if ((pos.y + fHeight) > (PairPos.y - fPairHeight) &&
							(posOld.y + fHeight) <= (PairPos.y - fPairHeight))
						{// ������߂荞��ł��鎞

							bHit = true;
							pos.y = (PairPos.y - (fPairHeight / COLLSION_DIAMETER)) - fHeight;
						}
						else if ((pos.y - fHeight) < (PairPos.y + fPairHeight) &&
							(posOld.y - fHeight) >= (PairPos.y + fPairHeight))
						{// �ォ��߂荞��ł��鎞

							bHit = true;
							pos.y = (PairPos.y + (fPairHeight / COLLSION_DIAMETER)) + fHeight;
						}
					}
				}
				   break;
				case VECTOR_Z: {	/* Z���� */

					if ((pos.x + fWidth) > (PairPos.x - fPairWidth) &&
						(pos.x - fWidth) < (PairPos.x + fPairWidth))
					{// ���ӂƉE�ӂ�����̕��̓����̎��A

						if ((pos.z + fDepth) >= (PairPos.z - fPairDepth) &&
							(posOld.z + fDepth) <= (PairPos.z - fPairDepth))
						{// �O����߂荞��ł��鎞

							bHit = true;
							pos.z = (PairPos.z - fPairDepth) - fDepth;
						}
						else if ((pos.z - fDepth) <= (PairPos.z + fPairDepth) &&
							(posOld.z - fDepth) >= (PairPos.z + fPairDepth))
						{// ������߂荞��ł��鎞

							bHit = true;
							pos.z = (PairPos.z + fPairDepth) + fDepth;
						}
					}
				}
				   break;
				}

				if (bHit)
				{
					m_Info.pos = pos;

					return TRUE;
				}
			}
		}
	}
	return FALSE;
}