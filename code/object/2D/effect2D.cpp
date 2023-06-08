//========================================
//
// �G�t�F�N�g�y 2D �z
//
//========================================
// *** effect2D.cpp ***
//========================================
#include "effect2D.h"
#include "../../manager.h"
#include "../../renderer.h"

// �ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CEffect2D::m_pTexture[MAX_TEXTURE] = { NULL };	// ���L�e�N�X�`��
int CEffect2D::m_nTexture = -1;

// �R���X�g���N�^
CEffect2D::CEffect2D(int nPriority) : CObject2D(nPriority)
{
	// �l���N���A
	m_color = INIT_D3DXCOLOR;
	m_nLife = 0;
	m_nLifeMax = 0;
}

// �f�X�g���N�^
CEffect2D::~CEffect2D()
{

}

//========================================
// �e�N�X�`���̓ǂݍ���
//========================================
HRESULT CEffect2D::Load(char *pPath)
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
void CEffect2D::Unload(void)
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
CEffect2D *CEffect2D::Create(void)
{
	// �I�u�W�F�N�g2D
	CEffect2D *pEffect2D = NULL;

	// �I�u�W�F�N�g2D�̐���
	pEffect2D = new CEffect2D;

	// ����������
	pEffect2D->Init();

	// �e�N�X�`�����蓖��
	pEffect2D->BindTexture(m_pTexture[0]);

	return pEffect2D;
}

//========================================
// ������
//========================================
HRESULT CEffect2D::Init(void)
{
	// ����������
	CObject2D::Init();

	// ��ސݒ�
	SetType(TYPE_EFFECT);

	return S_OK;
}

//========================================
// �I��
//========================================
void CEffect2D::Uninit(void)
{
	// �I������
	CObject2D::Uninit();
}

//========================================
// �X�V
//========================================
void CEffect2D::Update(void)
{
	if (--m_nLife <= 0)
	{// �������s�������A
		Uninit();		// �I������
		return;
	}

	// �F�������ɉ����������x�ōĐݒ�
	D3DXCOLOR setCol = m_color;
	setCol.a *= (float)m_nLife / m_nLifeMax;


	SetEffColor(setCol);
	CObject2D::Update();
}

//========================================
// �`��
//========================================
void CEffect2D::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �A���t�@�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �`�揈��
	CObject2D::Draw();

	// �A���t�@�u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
