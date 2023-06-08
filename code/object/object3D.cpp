//========================================
// 
// �I�u�W�F�N�g�y 3D �z����
// 
//========================================
// *** object3D.cpp ***
//========================================
#include "../manager.h"
#include "object3D.h"
#include "../renderer.h"
#include "../texture.h"

// �R���X�g���N�^
CObject3D::CObject3D()
{
	// �l���N���A����
	m_pos = INIT_D3DXVECTOR3;
	m_size = INIT_D3DXVECTOR2;
	m_nTexture = 0;
	m_fAngle = INIT_FLOAT;
	m_fLength = INIT_FLOAT;
	m_fRotY = INIT_FLOAT;
}

// �f�X�g���N�^
CObject3D::~CObject3D()
{

}
//========================================
// ��������
//========================================
CObject3D *CObject3D::Create(void)
{
	CObject3D *pObj3D = NULL;

	if (pObj3D != NULL)
	{
		return pObj3D;
	}

	// �I�u�W�F�N�g2D�̐���
	pObj3D = new CObject3D;

	// ����������
	pObj3D->Init();

	return pObj3D;
}

//========================================
// ����������
//========================================
HRESULT CObject3D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// �ݒ�p�|�C���^
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	// ���_���W��ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, -0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, -0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, -0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, -0.0f);

	// ���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@�̔j��
	m_pVtxBuff->Unlock();

	return S_OK;
}

//========================================
// �I������
//========================================
void CObject3D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//========================================
// �X�V����
//========================================
void CObject3D::Update(void)
{

}

//========================================
// �`�揈��
//========================================
void CObject3D::Draw(void)
{
	// �f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;										//�v�Z�p�}�g���b�N�X


	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	////�����𔽉f
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

	//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	////�ʒu�𔽉f
	//D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`���ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//========================================
// �ʒu�ݒ�
//========================================
void CObject3D::SetPos(const D3DXVECTOR3& pos)
{
	// �ʒu�̑��
	m_pos = pos;

	// �ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	// ���_���W��ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_fRotY + m_fAngle + -D3DX_PI) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_fRotY + m_fAngle + -D3DX_PI) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_fRotY + -m_fAngle + D3DX_PI) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_fRotY + -m_fAngle + D3DX_PI) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_fRotY + m_fAngle * -1.0f) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_fRotY + m_fAngle * -1.0f) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_fRotY + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_fRotY + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	// ���_�o�b�t�@�̔j��
	m_pVtxBuff->Unlock();
}

//========================================
// �����ݒ�
//========================================
void CObject3D::SetRot(const float& rotY)
{
	// Y���̑��
	m_fRotY = rotY;

	//�@�ʒu�ݒ�
	SetPos(m_pos);
}

//========================================
// �T�C�Y�ݒ�
//========================================
void CObject3D::SetSize(const D3DXVECTOR2& size)
{
	// �T�C�Y�̑��
	m_size = size;

	// �����E�p�x�̐ݒ�
	m_fLength = sqrtf(m_size.x * m_size.x + m_size.y * m_size.y) * 0.5f;
	m_fAngle = atan2f(m_size.x, m_size.y);

	// �ʒu�̐ݒ�
	SetPos(m_pos);
}

//========================================
// �F�ݒ�
//========================================
void CObject3D::SetColor(const D3DXCOLOR& color)
{
	// �T�C�Y�̑��
	m_color = color;

	// �ݒ�p�|�C���^
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	// ���_�J���[
	pVtx[0].col = D3DXCOLOR(m_color.r, m_color.g, m_color.b, m_color.a);
	pVtx[1].col = D3DXCOLOR(m_color.r, m_color.g, m_color.b, m_color.a);
	pVtx[2].col = D3DXCOLOR(m_color.r, m_color.g, m_color.b, m_color.a);
	pVtx[3].col = D3DXCOLOR(m_color.r, m_color.g, m_color.b, m_color.a);

	// ���_�o�b�t�@�̔j��
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �e�N�X�`���̊��蓖��
//=============================================================================
void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 m_pTexture1)
{
	m_pTexture = m_pTexture1;
}

//========================================
// �e�N�X�`���ݒ�
//========================================
void CObject3D::SetTex(PositionVec4 tex)
{
	VERTEX_2D *pVtx; //���_�ւ̃|�C���^

					 //���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(tex.P0, tex.P2);
	pVtx[1].tex = D3DXVECTOR2(tex.P1, tex.P2);
	pVtx[2].tex = D3DXVECTOR2(tex.P0, tex.P3);
	pVtx[3].tex = D3DXVECTOR2(tex.P1, tex.P3);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}