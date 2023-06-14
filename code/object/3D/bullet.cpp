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
#include "../2D/score.h"
#include "../2D/effect2D.h"

// �ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CBullet::m_pTexture[MAX_TEXTURE] = {NULL};	// ���L�e�N�X�`��
int CBullet::m_nTexture = -1;

// �R���X�g���N�^
CBullet::CBullet(int nPriority) : CObject2D(nPriority)
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

// �f�X�g���N�^
CBullet::~CBullet()
{

}

//========================================
// �e�N�X�`���̓ǂݍ���
//========================================
HRESULT CBullet::Load(char *pPath)
{
	if (pPath != NULL)
	{
		m_nTexture++;	// �e�N�X�`�������Z

		// �f�o�C�X�擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// �e�N�X�`���̓ǂݍ���
		if (FAILED(D3DXCreateTextureFromFile(pDevice, pPath, &m_pTexture[m_nTexture])))
		{
			m_pTexture[m_nTexture] = NULL;
		}
	}

	return S_OK;
}

//========================================
// �e�N�X�`���̔j��
//========================================
void CBullet::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < m_nTexture; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}

//========================================
// ����
//========================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,bool bShot)
{
	CBullet *pBullet = NULL;

	if (pBullet != NULL)
	{
		return pBullet;
	}

	// �I�u�W�F�N�g2D�̐���
	pBullet = new CBullet;

	if (bShot == true)
	{
		pBullet->m_Info.pos = D3DXVECTOR3(pos.x - 21, pos.y - 20, pos.z);
		pBullet->m_Info.nType = 0;
	}
	else
	{
		pBullet->m_Info.pos = D3DXVECTOR3(pos.x + 21, pos.y - 20, pos.z);
		pBullet->m_Info.nType = 1;
	}

	pBullet->m_Info.move = move;
	pBullet->m_Info.nLife = 70;
	pBullet->m_Info.bShot = bShot;

	// ����������
	pBullet->Init();

	return pBullet;
}
//========================================
// ������
//========================================
HRESULT CBullet::Init(void)
{
	CObject2D::Init();

	m_Info.fWidth = 15.0f;
	m_Info.fHeight = 25.0f;

	// ��ނ̐ݒ�
	SetType(TYPE_BULLET);

	SetPos(m_Info.pos);
	SetSize(m_Info.fWidth, m_Info.fHeight);
	SetRot(m_Info.rot);
	SetColor(INIT_D3DXCOLOR);

	// �e�N�X�`���̊��蓖��
	BindTexture(m_Info.nType + 4);

	return S_OK;
}

//========================================
// �I��
//========================================
void CBullet::Uninit(void)
{
	CObject2D::Uninit();
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

	CEffect2D *pObj = CEffect2D::Create();
	pObj->SetPos(m_Info.pos);
	pObj->SetRot(m_Info.rot);
	pObj->SetSize(10.0f, 15.0f);

	switch (m_Info.nType)
	{
	case 0:
		pObj->SetColor(D3DXCOLOR(0.1f, 0.5f, 1.0f, 1.0f));
		break;
	case 1:
		pObj->SetColor(D3DXCOLOR(0.1f, 1.0f, 0.25f, 1.0f));
		break;
	}
	pObj->SetLife(10);

	// �G�Ƃ̓����蔻��
	if(CollsionEnemy(m_Info.pos))
	{
		return;
	}

	CObject2D::Update();
}

//========================================
// �`��
//========================================
void CBullet::Draw(void)
{
	CObject2D::Draw();
}

//========================================
// �G�Ƃ̓����蔻��
//========================================
bool CBullet::CollsionEnemy(D3DXVECTOR3 pos)
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

  				if (type == TYPE_ENEMY)
				{// ��ނ��G�̏ꍇ

					// �_�C�i�~�b�N�L���X�g����
					CEnemy *pEnemy = dynamic_cast<CEnemy*>(pObj);


					// �G�Əd�Ȃ���
					if ((m_Info.pos.x + m_Info.fWidth) <= (pObj->GetPos().x + pObj->GetWidth()) &&
						(m_Info.pos.x - m_Info.fWidth) >= (pObj->GetPos().x - pObj->GetWidth()) &&
						(m_Info.pos.y + m_Info.fHeight) <= (pObj->GetPos().y + pObj->GetHeight()) &&
						(m_Info.pos.y - m_Info.fHeight) >= (pObj->GetPos().y - pObj->GetHeight()))
					{//�G�ƒe����������

						// �G�̔j��
						pEnemy->HitLife(1);

						// �e�̔j��
						Uninit();

						// �X�R�A�����Z

						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}