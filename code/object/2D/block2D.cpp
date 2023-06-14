//========================================
// 
// �u���b�N����
// 
//========================================
//  *** block2D.cpp ***
//========================================
#include "block2D.h"
#include "../../manager.h"
#include "../../renderer.h"

// �ÓI�ϐ��錾
LPDIRECT3DTEXTURE9 CBlock2D::m_pTexture = { NULL };

// �R���X�g���N�^
CBlock2D::CBlock2D(int nPriority) : CObject2D(nPriority)
{
	// �l���N���A
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.fWidth = INIT_FLOAT;
	m_Info.fHeight = INIT_FLOAT;
}

// �f�X�g���N�^
CBlock2D::~CBlock2D()
{

}

//========================================
// �e�N�X�`���ǂݍ���
//========================================
HRESULT CBlock2D::Load(char *pPath)
{
	if (pPath != NULL)
	{
		//m_nTexture++;	// �e�N�X�`�������Z

		// �f�o�C�X�擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// �e�N�X�`���̓ǂݍ���
		if (FAILED(D3DXCreateTextureFromFile(pDevice, pPath, &m_pTexture)))
		{
			m_pTexture = NULL;
		}
	}

	return S_OK;
}

//========================================
// �e�N�X�`���j��
//========================================
void CBlock2D::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < 1; nCntTex++)
	{
		if (m_pTexture != NULL)
		{
			m_pTexture->Release();
			m_pTexture = NULL;
		}
	}
}

//========================================
// ����
//========================================
CBlock2D *CBlock2D::Create(D3DXVECTOR3 pos)
{
	CBlock2D *pBlock = NULL;

	if (pBlock != NULL)
	{
		return pBlock;
	}

	// �I�u�W�F�N�g2D�̐���
	pBlock = new CBlock2D;

	pBlock->m_Info.pos = pos;

	// ����������
	pBlock->Init();

	return pBlock;
}

//========================================
// ������
//========================================
HRESULT CBlock2D::Init(void)
{
	CObject2D::Init();

	// ��ނ̐ݒ�
	SetType(TYPE_BLOCK);

	m_Info.fWidth = 50.0f;
	m_Info.fHeight = 50.0f;

	// ����
	SetPos(m_Info.pos);
	SetSize(m_Info.fWidth, m_Info.fHeight);
	SetColor(INIT_D3DXCOLOR);

	// �e�N�X�`���̊��蓖��
	BindTexture(9);

	return S_OK;
}

//========================================
// �I��
//========================================
void CBlock2D::Uninit(void)
{
	CObject2D::Uninit();
}


//========================================
// �X�V
//========================================
void CBlock2D::Update(void)
{
	CObject2D::Update();
}

//========================================
// �`��
//========================================
void CBlock2D::Draw(void)
{
	/*CObject2D::Draw();*/
}