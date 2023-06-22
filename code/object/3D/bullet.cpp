//========================================
// 
// �o���b�g����
// 
//========================================
// *** bullet.cpp ***
//========================================
#include "bullet.h"
#include "../../manager.h"
#include "../../renderer.h"
#include "enemy.h"
#include "block.h"
#include "../2D/score.h"
#include "../2D/effect2D.h"

//========================================
// �R���X�g���N�^
//========================================
CBullet::CBullet(int nPriority) : CObjectX(nPriority)
{
	// �l���N���A
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.move = INIT_D3DXVECTOR3;
	m_Info.nType = 0;
	m_Info.nLife = 0;
	m_Info.fHeight = 0.0f;
	m_Info.fWidth = 0.0f;
}
//========================================
// �f�X�g���N�^
//========================================
CBullet::~CBullet()
{

}

//========================================
// ����
//========================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CBullet *pBullet = NULL;

	if (pBullet != NULL)
	{
		return pBullet;
	}

	// �o���b�g�̐���
	pBullet = new CBullet;

	pBullet->m_Info.pos = pos;
	pBullet->m_Info.move = move;
	pBullet->m_Info.nLife = 70;

	// ����������
	pBullet->Init();

	return pBullet;
}
//========================================
// ������
//========================================
HRESULT CBullet::Init(void)
{
	CObjectX::Init();

	m_Info.fWidth = 15.0f;
	m_Info.fHeight = 25.0f;

	// ��ނ̐ݒ�
	SetType(TYPE_BULLET);

	SetPos(m_Info.pos);
	SetRot(m_Info.rot);
	SetColor(INIT_D3DXCOLOR);

	return S_OK;
}

//========================================
// �I��
//========================================
void CBullet::Uninit(void)
{
	CObjectX::Uninit();
}

//========================================
// �X�V
//========================================
void CBullet::Update(void)
{
	// �����̌���
	if (--m_Info.nLife <= 0)
	{// �������s������

		// �e�̔j��
		Uninit();

		return;
	}

	// �ړ��ʂ���
	m_Info.pos += m_Info.move;

	SetPos(m_Info.pos);

	/*CEffect2D *pObj = CEffect2D::Create();
	pObj->SetPos(m_Info.pos);
	pObj->SetRot(m_Info.rot);
	pObj->SetSize(10.0f, 15.0f);
	pObj->SetLife(10);*/

	// �G�Ƃ̓����蔻��
	if(Collsion(m_Info.pos))
	{
		return;
	}
	CObjectX::Update();
}

//========================================
// �`��
//========================================
void CBullet::Draw(void)
{
	CObjectX::Draw();
}

//========================================
// �����蔻��
//========================================
bool CBullet::Collsion(D3DXVECTOR3 pos)
{
	int nCntEnemy = 0;

	for (int nCntPriority = 0; nCntPriority < TYPE_MAX; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < GetNumAll(); nCntObj++)
		{
			CObject *pObj;

			// �I�u�W�F�N�g���擾
			pObj = GetObjectPointer(nCntPriority, nCntObj);

			if (pObj != NULL)
			{
				TYPE type;

				// ��ނ��擾
				type = pObj->GetType();

  				if (type == TYPE_BLOCK)
				{// ��ނ��G�̏ꍇ

					// �o���b�g�̎擾
					D3DXVECTOR3 PosOld = GetPosOld();	// �ʒu(�ߋ�)
					float Width = GetWidth();		// ��
					float Height = GetHeight();		// ����
					float Depth = GetDepth();		// ���s��


					// �u���b�N�̎擾
					D3DXVECTOR3 BlockPos = pObj->GetPos();	// �ʒu
					float BlockWidth = pObj->GetWidth();	// ��
					float BlockHeight = pObj->GetHeight();	// ����
					float BlockDepth = pObj->GetDepth();	// ���s��


					// �G�Əd�Ȃ���
					if ((m_Info.pos.x + Width) <= (BlockPos.x + BlockWidth) &&
						(PosOld.x - Width) >= (BlockPos.x - BlockWidth) &&
						(m_Info.pos.y + Height) <= (BlockPos.y + BlockHeight) &&
						(PosOld.y - Height) >= (BlockPos.y - BlockHeight) &&
						(m_Info.pos.z + Depth) <= (BlockPos.z + BlockDepth) &&
						(PosOld.z - Depth) >= (BlockPos.z - BlockDepth))
					{//�e�ƃu���b�N����������

						// �u���b�N�𐶐�
						CBlock::Create(D3DXVECTOR3(pObj->GetPos().x, m_Info.pos.y , pObj->GetPos().z + 10));

						// �e�̔j��
						Uninit();

						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}