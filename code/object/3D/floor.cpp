//========================================
// 
// ������
// 
//========================================
// *** floor.cpp ***
//========================================
#include "floor.h"
#include "../../manager.h"
#include "../../renderer.h"

// �ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CFloor::m_pTexture[CFloor::MAX_TEXTURE] = { NULL };
int CFloor::m_nTexture = -1;

// �R���X�g���N�^
CFloor::CFloor(int nPriority) : CObject3D(nPriority)
{
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.fHeight = INIT_FLOAT;
	m_Info.fWidth = INIT_FLOAT;
}

// �f�X�g���N�^
CFloor::~CFloor()
{

}

//========================================
// ����
//========================================
CFloor *CFloor::Create(void)
{
	CFloor *pFloor = NULL;

	if (pFloor != NULL)
	{
		return pFloor;
	}

	// �I�u�W�F�N�g2D�̐���
	pFloor = new CFloor;

	// ����������
	pFloor->Init();

	return pFloor;
}

//========================================
// ������
//========================================
HRESULT CFloor::Init(void)
{
	CObject3D::Init();

	// ��ނ̐ݒ�
	SetType(TYPE_FLOOR);

	m_Info.pos = D3DXVECTOR3(0.0f,60.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 3.141592f);
	m_Info.fWidth = 250.0f;
	m_Info.fHeight = 250.0f;

	// ����
	SetPos(m_Info.pos);
	SetRot(m_Info.rot);
	SetSize(m_Info.fWidth, m_Info.fHeight);
	SetColor(INIT_D3DXCOLOR);

	// �e�N�X�`���̊��蓖��
	BindTexture(m_pTexture[0]);

	return S_OK;
}

//========================================
// �I��
//========================================
void CFloor::Uninit(void)
{
	CObject3D::Uninit();
}

//========================================
// �X�V
//========================================
void CFloor::Update(void)
{
	CObject3D::Update();
}

//========================================
// �`��
//========================================
void CFloor::Draw(void)
{
	CObject3D::Draw();
}

//========================================
// �e�N�X�`���̓ǂݍ���
//========================================
HRESULT CFloor::Load(char *pPath)
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
void CFloor::Unload(void)
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