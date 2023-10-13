//========================================
// 
// �`�揈��
// 
//========================================
// *** renderer.cpp ***
//========================================
#include "renderer.h"
#include "../object\object.h"
#include "../manager.h"
#include "../object/BG/test.h"
#include "../system/camera.h"

// �ÓI�ϐ�
LPD3DXFONT CRenderer::m_pFont = NULL;	// �t�H���g

//========================================
// �R���X�g���N�^
//========================================
CRenderer::CRenderer()
{
	// �l���N���A����
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
}

//========================================
// �f�X�g���N�^
//========================================
CRenderer::~CRenderer()
{

}

//========================================
// �`��̏���������
//========================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;        //�f�B�X�v���C���[�h

	//Direct3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}
	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));   //�p�����[�^�̃[���N���A

	m_d3dpp.BackBufferWidth = SCREEN_WIDTH;								//�Q�[����ʃT�C�Y(��)
	m_d3dpp.BackBufferHeight = SCREEN_HEIGHT;							//�Q�[����ʃT�C�Y(����)
	m_d3dpp.BackBufferFormat = d3ddm.Format;							//�o�b�N�o�b�t�@�̌`��
	m_d3dpp.BackBufferCount = 1;										//�o�b�N�o�b�t�@�̐�
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;							//�_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	m_d3dpp.EnableAutoDepthStencil = TRUE;								//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//�f�v�X�o�b�t�@�Ƃ���16bit���g��
	m_d3dpp.Windowed = bWindow;											//�E�C���h�E���[�h
	m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//���t���b�V�����[�g
	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;			//�C���^�[�o��

																		//Direct3D�f�o�C�X������
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,                     //�`�揈��
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,//���_����
		&m_d3dpp,
		&m_pD3DDevice)))                    //�`�揈���ƒ��_�������n�[�h�E�F�A�ōs��
	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,//�`�揈��
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,//���_����
			&m_d3dpp,
			&m_pD3DDevice)))
		{
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,                     //�`�揈��
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,//���_����
				&m_d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�f�o�b�N�\���p�t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PALETTE,
		"Terminal", &m_pFont);

	//�����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);//D3DCULL_NONE�@�J�����O���� D3DCULL_CW �\�ʃJ�����O�@D3DCULL_CCW�@���ʃJ�����O
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	LPDIRECT3DSURFACE9 pRenderDef, pZBuffDef;

	// �����_�����O�^�[�Q�b�g�p�e�N�X�`���̍쐬
	m_pD3DDevice->CreateTexture(SCREEN_HEIGHT,
		SCREEN_HEIGHT,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&m_apTextureMT[0],
		NULL);

	m_pD3DDevice->CreateTexture(SCREEN_HEIGHT,
		SCREEN_HEIGHT,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&m_apTextureMT[1],
		NULL);

	// �e�N�X�`�������_�����O�p�C���^�[�t�F�[�X�̐���
	m_apTextureMT[0]->GetSurfaceLevel(0, &m_apRenderMT[0]);
	m_apTextureMT[1]->GetSurfaceLevel(0, &m_apRenderMT[1]);

	// �e�N�X�`�������_�����O�pZ�o�b�t�@�̐���
	m_pD3DDevice->CreateDepthStencilSurface(SCREEN_WIDTH,
		SCREEN_HEIGHT,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		&m_pZBuffMT,
		NULL);
	
	// ���݂̃����_�����O�^�[�Q�b�g���擾�i�ۑ��j
	m_pD3DDevice->GetRenderTarget(0, &pRenderDef);

	// ���݂�Z�o�b�t�@���擾�i�ۑ��j
	m_pD3DDevice->GetDepthStencilSurface(&pZBuffDef);

	// �����_�����O�^�[�Q�b�g�𐶐������e�N�X�`���ɐݒ�
	m_pD3DDevice->SetRenderTarget(0, m_apRenderMT[0]);
	m_pD3DDevice->SetRenderTarget(0, m_apRenderMT[1]);

	// Z�o�b�t�@�𐶐�����Z�o�b�t�@�ɐݒ�
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);

	// �����_�����O�^�[�Q�b�g�p�̃e�N�X�`���N���A
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// �����_�����O�^�[�Q�b�g�����ɖ߂�
	m_pD3DDevice->SetRenderTarget(0, pRenderDef);

	// Z�o�b�t�@�����ɖ߂�
	m_pD3DDevice->SetDepthStencilSurface(pZBuffDef);

	// �e�N�X�`�������_�����O�p�r���[�|�[�g�̐ݒ�
	m_viewportMT.X = 0;
	m_viewportMT.Y = 0;
	m_viewportMT.Width = SCREEN_WIDTH;
	m_viewportMT.Height = SCREEN_HEIGHT;
	m_viewportMT.MinZ = 0.0f;
	m_viewportMT.MaxZ = 1.0f;

	{
		// ���_�o�b�t�@�̐���
		m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&m_pVtxBuffMT,
			NULL);

		// �ݒ�p�|�C���^
		VERTEX_2D *pVtx;

		// ���_�o�b�t�@�̃��b�N�ƒ��_���ւ̃|�C���^���擾
		m_pVtxBuffMT->Lock(0, 0, (void **)&pVtx, 0);

		D3DXVECTOR3 m_pos = D3DXVECTOR3(620.0f,320.0f,0.0f);	// �ʒu
		D3DXVECTOR3 m_rot = INIT_D3DXVECTOR3;	// ����
		D3DXCOLOR m_color = INIT_D3DXCOLOR;	// �F
		float m_fWidth = 1280.0f;			// ��
		float m_fHeight = 720.0f;			// ����

		// �Ίp���̒���
		float fLength = sqrtf((m_fWidth * m_fWidth) + (m_fHeight * m_fHeight)) * 0.5f;
		// �Ίp���̊p�x
		float fAngle = atan2f(m_fWidth, m_fHeight);

		// ���_���W��ݒ�
		pVtx[0].pos.x = m_pos.x + sinf(m_rot.y - (D3DX_PI - fAngle)) * fLength;
		pVtx[0].pos.y = m_pos.y + cosf(m_rot.y - (D3DX_PI - fAngle)) * fLength;
		pVtx[1].pos.x = m_pos.x + sinf(m_rot.y + (D3DX_PI - fAngle)) * fLength;
		pVtx[1].pos.y = m_pos.y + cosf(m_rot.y + (D3DX_PI - fAngle)) * fLength;
		pVtx[2].pos.x = m_pos.x + sinf(m_rot.y - fAngle) * fLength;
		pVtx[2].pos.y = m_pos.y + cosf(m_rot.y - fAngle) * fLength;
		pVtx[3].pos.x = m_pos.x + sinf(m_rot.y + fAngle) * fLength;
		pVtx[3].pos.y = m_pos.y + cosf(m_rot.y + fAngle) * fLength;

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

		// ���_�o�b�t�@�̔j��
		m_pVtxBuffMT->Unlock();
	}
	return S_OK;
}

//========================================
// �`��̏I������
//========================================
void CRenderer::Uninit(void)
{
	// �I�u�W�F�N�g�̑S�̂̔j��
	CObject::ReleaseAll();

	//�f�o�b�N�\���p�t�H���g�̔j��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}

	// �f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}


	// �I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//========================================
// �`��̍X�V����
//========================================
void CRenderer::Update(void)
{
	CObject::UpdateAll();		// �I�u�W�F�N�g�S��
}

//========================================
// �`��̕`�揈��
//========================================
void CRenderer::Draw(void)
{
	//��ʃN���A(�o�b�N�o�b�t�@&Z�o�b�t�@�̃N���A)
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	CCamera *pCamera = CManager::GetCamera();		// �J�����̎擾
	D3DXVECTOR3 posV = pCamera->GetInfo().posV;		// ���_
	D3DXVECTOR3 posR = pCamera->GetInfo().posR;		// �����_
	D3DXVECTOR3 vecU = pCamera->GetInfo().vecU;		// ������x�N�g��

	// �����^�����O�^�[�Q�b�g���e�N�X�`��[0]�ɐݒ�
	ChangeTarget(posV, posR, vecU);

	// �e�N�X�`��[0]���N���A
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ

		// �I�u�W�F�N�g�S�̂̕`�揈��
		CObject::DrawAll();

		// �t�B�[�h�o�b�N�p�|���S���Ƀe�N�X�`��[1]�𒣂�t���ĕ`��
		m_pD3DDevice->SetStreamSource(0, m_pVtxBuffMT, 0, sizeof(VERTEX_2D));
		m_pD3DDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���ݒ�
		m_pD3DDevice->SetTexture(0, m_apTextureMT[1]);

		// �|���S���̕`��
		m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		// �����_�����O�^�[�Q�b�g�����ɖ߂�
		m_pD3DDevice->SetRenderTarget(0, m_apRenderMT[0]);

		// �t�B�[�h�o�b�N�p�|���S���Ƀe�N�X�`��[0]�𒣂�t���ĕ`��

		// �e�N�X�`���ݒ�
		m_pD3DDevice->SetTexture(0, m_apTextureMT[0]);

		// �|���S���̕`��
		m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		// �e�N�X�`��[0] �� �e�N�X�`��[1] �����ւ���
		LPDIRECT3DSURFACE9 pRenderWk;
		LPDIRECT3DTEXTURE9 pTextureWk;

		pRenderWk = m_apRenderMT[0];
		m_apRenderMT[0] = m_apRenderMT[1];
		m_apRenderMT[1] = pRenderWk;

		pTextureWk = m_apTextureMT[0];
		m_apTextureMT[0] = m_apTextureMT[1];
		m_apTextureMT[1] = pTextureWk;

		//�`��I��
		m_pD3DDevice->EndScene();

#ifdef _DEBUG
		
		//FPS�̕\��
		DrawFPS();

#endif // _DEBUG
	}
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//========================================
// �����_�����O�^�[�Q�b�g�̕ύX
//========================================
void CRenderer::ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 vecU)
{
	D3DXMATRIX mtxView, mtxProjection;
	float fAspect;

	// �����_�����O�^�[�Q�b�g�𐶐������e�N�X�`���ɐݒ�
	m_pD3DDevice->SetRenderTarget(0, m_apRenderMT[0]);

	// Z�o�b�t�@�𐶐�����Z�o�b�t�@�ɐݒ�
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);

	// �e�N�X�`�������_�����O�p�̃r���[�|�[�g��ݒ�
	m_pD3DDevice->SetViewport(&m_viewportMT);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&mtxView,
		&posV,		/*���_*/
		&posR,		/*�����_*/
		&vecU);		/*������x�N�g��*/

	// �r���[�}�g���b�N�X�̐ݒ�
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&mtxProjection,
		D3DXToRadian(45.0f),							/* ����p */
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		/*��ʂ̃A�X�y�N�g��*/
		10.0f,											/*Z�l�̍ŏ��l*/
		2000.0f);										/*Z�l�̍ő�l*/

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}

//========================================
//	�e�N�X�`�������_�����O�̎擾
//========================================
LPDIRECT3DTEXTURE9 CRenderer::GetTextureMT(void)
{
	return m_apTextureMT[0];
}

//========================================
// FPS����
//========================================
void CRenderer::DrawFPS(void)
{
	//�e�L�X�g�̕`�揈��
	RECT rect = { 0,230,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[521];

	//������ɑ��
	sprintf(&aStr[0], "FPS:%d\n", GetFps());

	//�e�L�X�g�̕`��
	m_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}