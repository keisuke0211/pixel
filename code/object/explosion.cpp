//========================================
// 
// ��������
// 
//========================================
// *** explosion.cpp ***
//========================================
#include "explosion.h"
#include "../manager.h"
#include "../renderer.h"
#include "object2D.h"
#include "3D\bullet.h"

// �ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture[CExplosion::MAX_TEXTURE] = { NULL };
int CExplosion::m_nTexture = -1;

// �R���X�g���N�^
CExplosion::CExplosion(int nPriority) : CObject2D(nPriority)
{
	// �l���N���A
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nCounterAnim = 0;
	m_Info.nPatternAnim = 0;
	m_Info.nLife = 0;
}

// �f�X�g���N�^
CExplosion::~CExplosion()
{

}

//========================================
// �e�N�X�`���̓ǂݍ���
//========================================
HRESULT CExplosion::Load(char *pPath)
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
void CExplosion::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; ++nCntTex)
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
CExplosion *CExplosion::Create(D3DXVECTOR3 pos)
{
	CExplosion *pExplosion = NULL;

	if (pExplosion != NULL)
	{
		return pExplosion;
	}

	// �I�u�W�F�N�g2D�̐���
	pExplosion = new CExplosion;

	pExplosion->m_Info.pos = pos;

	// ����������
	pExplosion->Init();

	return pExplosion;
}

//========================================
// ������
//========================================
HRESULT CExplosion::Init(void)
{
	CObject2D::Init();

	// ��ނ̐ݒ�
	SetType(TYPE_EFFECT);

	// ����
	SetPos(m_Info.pos);
	SetSize(50.0f,50.0f);
	SetRot(INIT_D3DXVECTOR3);
	SetColor(INIT_D3DXCOLOR);
	SetPtnInfo(8, 1, 8, true, 5);

	m_Info.nLife = 40;

	// �e�N�X�`���̊��蓖��
	BindTexture(m_pTexture[0]);

	return S_OK;
}

//========================================
// �I��
//========================================
void CExplosion::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================
// �X�V
//========================================
void CExplosion::Update(void)
{
	if (--m_Info.nLife <= 0)
	{
		Release();
		return;
	}
	CObject2D::Update();

	// �A�j���\�V��������
	Animation();
}

//========================================
// �`��
//========================================
void CExplosion::Draw(void)
{
	CObject2D::Draw();
}