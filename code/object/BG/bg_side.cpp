//========================================
// 
// �w�i�i���ʁj�y 3D_MULTI �z����
// 
//========================================
// *** bg_side.h ***
//========================================
#include "bg_side.h"
#include "../../manager.h"
#include "../../system/renderer.h"
#include "../../system/texture.h"
#include "../../scene/pause.h"

// �ÓI�ϐ�
float CBgSide::m_aTexV[3] = { 0.0f };

//****************************************
// �}�N����`
//****************************************

// ���_�t�H�[�}�b�g�y3D_MULTI�z
#define FVF_VERTEX_3D_MULTI (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX3)

#define BG_HEIGHT			(500.0f)	// ����
#define BG_RADIUS			(1080.0f)	// ���a
#define BG_DIVISION_WIDTH	(32)		// ������
#define BG_DIVISION_HEIGHT	(1)			// ��������
#define BG_POS				(D3DXVECTOR3(-100.0f,200.0f,100.0f))	// �ʒu

//****************************************
// �R���X�g���N�^
//****************************************
CBgSide::CBgSide(int nPriority) : CObject(nPriority)
{
	m_pos = INIT_D3DXVECTOR3;
	m_rot = INIT_D3DXVECTOR3;
	m_color = INIT_D3DXCOLOR;
}
//****************************************
// �f�X�g���N�^
//****************************************
CBgSide::~CBgSide()
{

}

//========================================
// ��������
//========================================
CBgSide *CBgSide::Create(void)
{
	CBgSide *pObj = new CBgSide;

	if (pObj != NULL)
	{
		// ����������
		pObj->Init();
	}

	return pObj;
}

//========================================
// ����������
//========================================
HRESULT CBgSide::Init(void)
{
	m_pos = BG_POS;

	SetType(TYPE_BG);

	// �f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D_MULTI) * ((BG_DIVISION_WIDTH + 1) * (BG_DIVISION_HEIGHT + 1)),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D_MULTI,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D_MULTI *pVtx;	// �ݒ�p�|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W/�@���x�N�g��/�e�N�X�`�����W�̐ݒ�
	for (int nCntHeight = 0; nCntHeight < BG_DIVISION_HEIGHT + 1; nCntHeight++)
	{
		for (int nCntWidth = 0; nCntWidth < BG_DIVISION_WIDTH + 1; nCntWidth++)
		{
			// �ʒu
			pVtx[(nCntHeight * (BG_DIVISION_WIDTH + 1)) + nCntWidth].pos
				= D3DXVECTOR3(
					sinf(-D3DX_PI + (nCntWidth * ((D3DX_PI * 2) / BG_DIVISION_WIDTH))) * BG_RADIUS,
					BG_HEIGHT - (nCntHeight * (BG_HEIGHT / BG_DIVISION_HEIGHT)),
					cosf(-D3DX_PI + (nCntWidth * ((D3DX_PI * 2) / BG_DIVISION_WIDTH))) * BG_RADIUS);

			// �@���x�N�g��
			pVtx[(nCntHeight * (BG_DIVISION_WIDTH + 1)) + nCntWidth].nor
				= D3DXVECTOR3(
					sinf(-D3DX_PI + (nCntWidth * ((D3DX_PI * 2) / BG_DIVISION_WIDTH))),
					0.0f,
					cosf(-D3DX_PI + (nCntWidth * ((D3DX_PI * 2) / BG_DIVISION_WIDTH))));;

			// �e�N�X�`���P
			pVtx[(nCntHeight * (BG_DIVISION_WIDTH + 1)) + nCntWidth].tex1
				= D3DXVECTOR2(
					nCntWidth * (8.0f / (float)BG_DIVISION_WIDTH),
					nCntHeight * (1.0f / (float)BG_DIVISION_HEIGHT));

			// �e�N�X�`��2
			pVtx[(nCntHeight * (BG_DIVISION_WIDTH + 1)) + nCntWidth].texM
				= D3DXVECTOR2(
					nCntWidth * (8.0f / (float)BG_DIVISION_WIDTH),
					nCntHeight * (1.0f / (float)BG_DIVISION_HEIGHT));

			// �e�N�X�`��3
			pVtx[(nCntHeight * (BG_DIVISION_WIDTH + 1)) + nCntWidth].texM2
				= D3DXVECTOR2(
					nCntWidth * (8.0f / (float)BG_DIVISION_WIDTH),
					nCntHeight * (1.0f / (float)BG_DIVISION_HEIGHT));
		}
	}

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * ((BG_DIVISION_HEIGHT * 2 * (BG_DIVISION_WIDTH + 1)) + ((BG_DIVISION_HEIGHT - 1) * 2)),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuf,
		NULL);

	WORD *pIdx;	// �C���f�b�N�X���ւ̃|�C���^

	// �C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��f�[�^�ւ̃|�C���^���擾
	m_pIdxBuf->Lock(0, 0, (void**)&pIdx, 0);

	// ���_�ԍ��f�[�^�̐ݒ�
	int nCntIdx = 0;	// �C���f�b�N�X�̃J�E���g

	for (int nCntDepth = 0; nCntDepth < BG_DIVISION_HEIGHT; nCntDepth++)
	{
		for (int nCntWidth = 0; nCntWidth < BG_DIVISION_WIDTH + 1; nCntWidth++)
		{
			pIdx[nCntIdx] = (nCntWidth + ((BG_DIVISION_WIDTH + 1) * (nCntDepth + 1)));
			pIdx[nCntIdx + 1] = nCntWidth + ((BG_DIVISION_WIDTH + 1) * nCntDepth);
			nCntIdx += 2;
		}

		if (nCntDepth < BG_DIVISION_HEIGHT - 1)
		{
			pIdx[nCntIdx] = ((BG_DIVISION_WIDTH + 1) * (nCntDepth + 1)) - 1;
			pIdx[nCntIdx + 1] = (BG_DIVISION_WIDTH + 1) * (nCntDepth + 2);
			nCntIdx += 2;
		}
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuf->Unlock();

	for (int nCntVtx = 0; nCntVtx < ((BG_DIVISION_WIDTH + 1) * (BG_DIVISION_HEIGHT + 1)); nCntVtx++)
	{
		// ���_�J���[�̐ݒ�
		pVtx[nCntVtx].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// �e�N�X�`���ݒ�
	CTexture *pTexture = CManager::GetTexture();

	m_pTextureMeshfield1 = pTexture->GetAddress(CTexture::TEX_SKY01);
	m_pTextureMeshfield2 = pTexture->GetAddress(CTexture::TEX_SKY02);
	m_pTextureMeshfield3 = pTexture->GetAddress(CTexture::TEX_SKY03);

	return S_OK;
}

//========================================
// �I������
//========================================
void CBgSide::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuf != NULL)
	{
		m_pIdxBuf->Release();
		m_pIdxBuf = NULL;
	}
}

//========================================
// �X�V����
//========================================
void CBgSide::Update(void)
{
	bool bPause = CPause::IsPause();

	if (!bPause)
	{
		VERTEX_3D_MULTI *pVtx;	// �ݒ�p�|�C���^

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�e�N�X�`�����W�̊J�n�ʒu(X��)�̍X�V
		m_aTexV[0] += 0.0006f;
		m_aTexV[1] += 0.0004f;
		m_aTexV[2] += 0.0003f;

		// �e�N�X�`�����W�̍X�V
		for (int nCntHeight = 0; nCntHeight < BG_DIVISION_HEIGHT + 1; nCntHeight++)
		{
			for (int nCntWidth = 0; nCntWidth < BG_DIVISION_WIDTH + 1; nCntWidth++)
			{
				// �e�N�X�`���P
				pVtx[(nCntHeight * (BG_DIVISION_WIDTH + 1)) + nCntWidth].tex1
					= D3DXVECTOR2(
						m_aTexV[0] + (nCntWidth * (8.0f / (float)BG_DIVISION_WIDTH)),
						nCntHeight * (1.0f / (float)BG_DIVISION_HEIGHT));

				// �e�N�X�`��2
				pVtx[(nCntHeight * (BG_DIVISION_WIDTH + 1)) + nCntWidth].texM
					= D3DXVECTOR2(
						m_aTexV[1] + (nCntWidth * (8.0f / (float)BG_DIVISION_WIDTH)),
						nCntHeight * (1.0f / (float)BG_DIVISION_HEIGHT));

				// �e�N�X�`��3
				pVtx[(nCntHeight * (BG_DIVISION_WIDTH + 1)) + nCntWidth].texM2
					= D3DXVECTOR2(
						m_aTexV[2] + (nCntWidth * (8.0f / (float)BG_DIVISION_WIDTH)),
						nCntHeight * (1.0f / (float)BG_DIVISION_HEIGHT));
			}
		}

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//========================================
// �`�揈��
//========================================
void CBgSide::Draw(void)
{
	// �f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX	mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// ���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�		

	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_BLENDTEXTUREALPHA);
	pDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
	pDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
	pDevice->SetTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	pDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_BLENDTEXTUREALPHA);
	pDevice->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_CURRENT);
	pDevice->SetTextureStageState(2, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
	pDevice->SetTextureStageState(2, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D_MULTI));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuf);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D_MULTI);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTextureMeshfield1);
	pDevice->SetTexture(1, m_pTextureMeshfield2);
	pDevice->SetTexture(2, m_pTextureMeshfield3);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		((BG_DIVISION_WIDTH + 1) * (BG_DIVISION_HEIGHT + 1)),
		0,
		((BG_DIVISION_WIDTH * BG_DIVISION_HEIGHT) * 2) + (4 * (BG_DIVISION_HEIGHT - 1)));

	// �e�N�X�`���X�e�[�W�X�e�[�g��߂�
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	pDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	pDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
	pDevice->SetTextureStageState(2, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(2, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(2, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// ���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}