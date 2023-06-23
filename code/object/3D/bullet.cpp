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
// �}�N����`
//========================================
#define BULLET_SPEED (2.5f)	// �e�̑��x

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
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBullet *pBullet = NULL;

	if (pBullet != NULL)
	{
		return pBullet;
	}

	// �o���b�g�̐���
	pBullet = new CBullet;

	pBullet->m_Info.pos = pos;
	pBullet->m_Info.rot = rot;
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

	m_Info.move.x = sinf(m_Info.rot.y) * BULLET_SPEED;
	m_Info.move.z = cosf(m_Info.rot.y) * BULLET_SPEED;

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
	SetRot(m_Info.rot);

	/*CEffect2D *pObj = CEffect2D::Create();
	pObj->SetPos(m_Info.pos);
	pObj->SetRot(m_Info.rot);
	pObj->SetSize(10.0f, 15.0f);
	pObj->SetLife(10);*/

	// �����蔻��
	if(Collsion(m_Info.pos))
	{
		return;
	}
	/*CObjectX::Update();*/
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
	int nRot = 0;
	bool bHit = false;

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
					float fWidth = GetWidth();			// ��
					float fHeight = GetHeight();		// ����
					float fDepth = GetDepth();			// ���s��


					// �u���b�N�̎擾
					D3DXVECTOR3 BlockPos = pObj->GetPos();	// �ʒu
					float fBlockWidth = pObj->GetWidth();	// ��
					float fBlockHeight = pObj->GetHeight();	// ����
					float fBlockDepth = pObj->GetDepth();	// ���s��

					// �v���C���[���u���b�N�̎�O�`���̊Ԃɂ��鎞
					if ((pos.z + fDepth) > (BlockPos.z - fBlockDepth) &&
						(pos.z - fDepth) < (BlockPos.z + fBlockDepth))
					{
						if ((pos.x + fWidth) >= (BlockPos.x - fBlockWidth) &&
							(PosOld.x + fWidth) <= (BlockPos.x - fBlockWidth))
						{// ������߂荞��ł��鎞

							bHit = true;			// �t���O��^�ɂ���
							nRot = DIRECTION_LEFT;	// �����w��
						}
						else if ((pos.x - fWidth) <= (BlockPos.x + fBlockWidth) &&
							(PosOld.x - fWidth) >= (BlockPos.x + fBlockWidth))
						{// �E����߂荞��ł��鎞

							bHit = true;			// �t���O��^�ɂ���
							nRot = DIRECTION_RIGHT;	// �����w��
						}
					}

					// �v���C���[���u���b�N�̍��Ӂ`�E�ӂ̊Ԃɂ��鎞

					if ((pos.x + fWidth) > (BlockPos.x - fBlockWidth) &&
						(pos.x - fWidth) < (BlockPos.x + fBlockWidth))
					{
						if ((pos.z + fDepth) >= (BlockPos.z - fBlockDepth) &&
							(PosOld.z + fDepth) <= (BlockPos.z - fBlockDepth))
						{// �O����߂荞��ł��鎞

							bHit = true;			// �t���O��^�ɂ���
							nRot = DIRECTION_FRONT;	// �����w��
						}
						else if ((pos.z - fDepth) <= (BlockPos.z + fBlockDepth) &&
							(PosOld.z - fDepth) >= (BlockPos.z + fBlockDepth))
						{// ������߂荞��ł��鎞

							bHit = true;			// �t���O��^�ɂ���
							nRot = DIRECTION_BACK;	// �����w��
						}
					}

					// �������Ă����
					if (bHit)
					{
						// �u���b�N�̐���
						switch (nRot)
						{
						case DIRECTION_LEFT:	// ��
							CBlock::Create(1, D3DXVECTOR3(pObj->GetPos().x - fBlockWidth, m_Info.pos.y, pObj->GetPos().z));
							break;

						case DIRECTION_RIGHT:	// �E
							CBlock::Create(1, D3DXVECTOR3(pObj->GetPos().x + fBlockWidth, m_Info.pos.y, pObj->GetPos().z));
							break;

						case DIRECTION_FRONT:	// �O
							CBlock::Create(1, D3DXVECTOR3(pObj->GetPos().x, m_Info.pos.y, pObj->GetPos().z + fBlockDepth));
							break;

						case DIRECTION_BACK:	// ��
							CBlock::Create(1, D3DXVECTOR3(pObj->GetPos().x, m_Info.pos.y, pObj->GetPos().z - fBlockDepth));
							break;
						}

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