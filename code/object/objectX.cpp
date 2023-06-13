//========================================
// 
// �I�u�W�F�N�g�y X�t�@�C�� �z����
// 
//========================================
// *** objectX.cpp ***
//========================================
#include "objectX.h"
#include "../manager.h"
#include "../renderer.h"
#include "../texture.h"


//========================================
// �R���X�g���N�^
//========================================
CObjectX::CObjectX(int nPriority)
{
	// �l���N���A����
	m_pos = INIT_D3DXVECTOR3;		// �ʒu
	m_posOld = INIT_D3DXVECTOR3;	// �ʒu(�ߋ�)
	m_rot = INIT_D3DXVECTOR3;		// ����
	m_color = INIT_D3DXCOLOR;		// �F
	m_fHeight = INIT_FLOAT;			// ����
	m_fWidth = INIT_FLOAT;			// ��
	m_fDepth = INIT_FLOAT;			// ���s��
}

//========================================
// �f�X�g���N�^
//========================================
CObjectX::~CObjectX()
{

}

//========================================
// ����
//========================================
CObjectX *CObjectX::Create(void)
{
	CObjectX *pObj3D = NULL;

	if (pObj3D != NULL)
	{
		return pObj3D;
	}

	// �I�u�W�F�N�g3D�̐���
	pObj3D = new CObjectX;

	// ����������
	pObj3D->Init();

	return pObj3D;
}
//========================================
// ������
//========================================
HRESULT CObjectX::Init(void)
{
	// �f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCntType = 0; nCntType < 1; nCntType++)
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX("data/OBJECT3D/Luna.x",
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat,
			NULL,
			&m_dwNumMat,
			&m_pMesh);

		D3DXMATERIAL *pMat;	// �}�e���A���̃|�C���^

		// �K�v�Ȑ��̃|�C���^�𓮓I�Ɋm�ۂ���
		if (m_dwNumMat >= 1)
		{
			m_pTexture = new LPDIRECT3DTEXTURE9[m_dwNumMat];
		}
		else
		{
			m_pTexture = NULL;
		}


		// �}�e���A�����ɑ΂���|�C���^���擾
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{// �e�N�X�`���t�@�C�������݂���

			 // �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &m_pTexture[nCntMat]);
			}
		}
	}

	return S_OK;
}

//========================================
// �I��
//========================================
void CObjectX::Uninit(void)
{
	//���b�V���̔j��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;

	}

	//���_�o�b�t�@�̔j��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;

	}
	//�e�N�X�`���̔j��
	for (int nCnt = 0; nCnt < m_dwNumMat; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}

	// �e�N�X�`���|�C���^�̔j��
	delete[] m_pTexture;
}

//========================================
// �X�V
//========================================
void CObjectX::Update(void)
{

}

//========================================
// �`��
//========================================
void CObjectX::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				// �}�e���A���f�[�^�ւ̃|�C���^

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	for (int nCntItem = 0; nCntItem < 1; nCntItem++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		//���f���̃T�C�Y��ύX
		/*D3DXMatrixScaling(&m_mtxWorld, m_fWidth, m_fHeight, m_fDepth);*/

		// �����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
		{
			// �}�e���A���̎擾
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_pTexture[nCntMat]);

			// ���f��(�p�[�c)�̕`��
			m_pMesh->DrawSubset(nCntMat);
		}
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}
