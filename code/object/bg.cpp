//========================================
// 
// �w�i����
// 
//========================================
// *** bg.cpp ***
//========================================
#include "bg.h"
#include "../manager.h"
#include "../renderer.h"
#include "object2D.h"

// �ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CBg::m_pTexture[MAX_TEXTURE] = { NULL };	// ���L�e�N�X�`��
int CBg::m_nTexture = -1;

// �R���X�g���N�^
CBg::CBg(int nPriority) : CObject2D(nPriority)
{
	m_texPos = INIT_D3DXVECTOR3;
	m_texMove = INIT_D3DXVECTOR3;
	m_nTexture = -1;
	m_Type = 0;
}

// �f�X�g���N�^
CBg::~CBg()
{

}

//========================================
// �e�N�X�`���̓ǂݍ���
//========================================
HRESULT CBg::Load(char *pPath)
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
void CBg::Unload(void)
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
// ��������
//========================================
CBg *CBg::Create(D3DXVECTOR3 move, int nType)
{
	CBg *pBg = NULL;

	if (pBg != NULL)
	{
		return pBg;
	}

	// �I�u�W�F�N�g2D�̐���
	pBg = new CBg;

	pBg->m_texMove = move;
	pBg->m_Type = nType;

	// ����������
	pBg->Init();

	return pBg;
}

//========================================
// ������
//========================================
HRESULT CBg::Init(void)
{
	CObject2D::Init();

	// ��ނ̐ݒ�
	SetType(TYPE_BG);

	// ����
	SetPos(D3DXVECTOR3(SCREEN_WIDTH /2, SCREEN_HEIGHT / 2, 0.0f));
	SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	SetRot(INIT_D3DXVECTOR3);
	SetColor(INIT_D3DXCOLOR);

	// �e�N�X�`���̊��蓖��
	BindTexture(m_pTexture[m_Type]);

	return S_OK;
}

//========================================
// �I��
//========================================
void CBg::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================
// �X�V
//========================================
void CBg::Update(void)
{
	//�e�N�X�`�����W�̊J�n�ʒu(V�l)�̍X�V
	m_texPos += m_texMove;


	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffPolygon = GetVtxBuff();	// ���_�o�b�t�@�擾

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	// �A�j���[�V��������
	Animation();

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(m_texPos.x, m_texPos.y);
	pVtx[1].tex = D3DXVECTOR2(m_texPos.x + 1.0f, m_texPos.y);
	pVtx[2].tex = D3DXVECTOR2(m_texPos.x, m_texPos.y + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_texPos.x + 1.0f, m_texPos.y + 1.0f);

	// �e�N�X�`�����W�X�V
	m_texPos += m_texMove;

	// ���_���W�̐ݒ�
	SetVtxPos(pVtx);

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuffPolygon->Unlock();
}

//========================================
// �`��
//========================================
void CBg::Draw(void)
{
	CObject2D::Draw();
}