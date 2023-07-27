//========================================
// 
// �u���b�N����
// 
//========================================
// *** block.cpp ***
//========================================
#include "block.h"
#include "bullet_cube.h"
#include "model.h"
#include "../EFFECT/particleX.h"
#include "../../system/sound.h"
#include "../../system/csv_file.h"

//========================================
// �}�N����`
//========================================
#define TNT_COLLSION		(3.0f)	// TNT�̔����̔���

//========================================
// �R���X�g���N�^
//========================================
CBlock::CBlock(int nPriority) : CObjectX(nPriority)
{
	// �l���N���A
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.posOld = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.rotOld = INIT_D3DXVECTOR3;
	m_Info.size = INIT_D3DXVECTOR3;
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nType = 0;
	m_Info.fRadius = 0.0f;
	m_Info.nCntRadius = 0;
	m_Info.fRadiusRate = 0.0f;
	m_Info.bSet = false;
	m_Info.nEraseTime = 0;
	m_Info.bErase = false;
}

//========================================
// �f�X�g���N�^
//========================================
CBlock::~CBlock()
{

}

//========================================
// ����
//========================================
CBlock *CBlock::Create(int nType,D3DXVECTOR3 pos)
{
	CBlock *pBlock = NULL;

	if (pBlock != NULL)
	{
		return pBlock;
	}

	// �I�u�W�F�N�g2D�̐���
	pBlock = new CBlock;

	pBlock->SetModel(nType);

	// ����������
	pBlock->Init();

	pBlock->m_Info.nType = nType;
	pBlock->SetBlockPos(pos);

	return pBlock;
}

//========================================
// ������
//========================================
HRESULT CBlock::Init(void)
{
	CObjectX::Init();

	// ��ނ̐ݒ�
	SetType(TYPE_BLOCK);

	m_Info.pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.size = D3DXVECTOR3(1.0f,1.0f,1.0f);
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nType = 0;
	m_Info.fRadius = 1.0f;

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
void CBlock::Uninit(void)
{
	CObjectX::Uninit();
}

//========================================
// �X�V
//========================================
void CBlock::Update(void)
{
	// �ߋ��̈ʒu�E�����̍X�V
	m_Info.posOld = m_Info.pos;
	m_Info.rotOld = m_Info.rot;

	SetPos(m_Info.pos);
	//SetRot(m_Info.rot);
	SetScale(m_Info.size);

	if (m_Info.bErase)
	{// �t���O���^�̎��A

		if (--m_Info.nEraseTime <= 0)
		{
			if (m_Info.nType == MODEL_TNT_00)
			{
				// TNT�̏���
				TntBlock();
			}

			// �j��
			Uninit();

			return;
		}
	}

	CObjectX::Update();
}

//========================================
// �`��
//========================================
void CBlock::Draw(void)
{
	CObjectX::Draw();
}

//========================================
// Hit����
//========================================
void CBlock::HitBlock(void)
{
	if (m_Info.nType == MODEL_TNT_00)
	{
		m_Info.nEraseTime = 20;
		m_Info.bErase = true;
	}
}

//========================================
// TNT�u���b�N
//========================================
void CBlock::TntBlock(void)
{
	// �p�[�e�B�N������
	CParticleX *pObj = CParticleX::Create();
	pObj->Par_SetPos(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y, m_Info.pos.z));
	pObj->Par_SetRot(INIT_D3DXVECTOR3);
	pObj->Par_SetMove(D3DXVECTOR3(25.0f, 15.0f, 25.0f));
	pObj->Par_SetType(0);
	pObj->Par_SetLife(100);
	pObj->Par_SetCol(D3DXCOLOR(0.9f, 0.0f, 0.0f, 1.0f));
	pObj->Par_SetForm(10);

	// �L���[�u�Ƃ̓����蔻��
	ModelCollsion(PRIO_CUBE, TYPE_CUBE,m_Info.pos);
}

//========================================
// �I�u�W�F�N�g�̓����蔻��
//========================================
void CBlock::ModelCollsion(PRIO nPrio, TYPE nType, D3DXVECTOR3 pos)
{
	// �擪�I�u�W�F�N�g���擾
	CObject *pObj = CObject::GetTop(nPrio);

	while (pObj != NULL)
	{// �g�p����Ă��鎞�A

		 // ���̃I�u�W�F�N�g
		CObject *pObjNext = pObj->GetNext();

		TYPE type;

		// ��ނ��擾
		type = pObj->GetType();

		if (type == nType)
		{// �I��������ނ̎��A

			 // �u���b�N�̎擾
			int nBlockType = GetBlockType();	// ���
			float fWidth = GetWidth();			// ��
			float fHeight = GetHeight();		// ����
			float fDepth = GetDepth();			// ���s��

			if (nBlockType == MODEL_TNT_00)
			{
				// �T�C�Y����
				fWidth *= TNT_COLLSION;	// ��
				fHeight *= TNT_COLLSION;// ����
				fDepth *= TNT_COLLSION;	// ���s��
			}

			// ����̎擾
			D3DXVECTOR3 PairPos = pObj->GetPos();		// �ʒu
			D3DXVECTOR3 PairPosOld = pObj->GetPosOld();	// �ʒu(�ߋ�)
			float fPairWidth = pObj->GetWidth();		// ��
			float fPairHeight = pObj->GetHeight();		// ����
			float fPairDepth = pObj->GetDepth();		// ���s��

			// �����蔻��
			if (Collsion(pos, PairPos, D3DXVECTOR3(fWidth, fHeight, fDepth), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
			{// ����������

				switch (nType)
				{
				case TYPE_CUBE:
				{
					// �_�C�i�~�b�N�L���X�g����
					CCube *pCube = dynamic_cast<CCube*>(pObj);

					// HIT����
					pCube->SetCubeLife(20);
				}
				break;
				}
			}
		}

		pObj = pObjNext;	// ���̃I�u�W�F�N�g����
	}
}