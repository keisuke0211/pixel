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
	pEffect2D->BindTexture(7);

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
