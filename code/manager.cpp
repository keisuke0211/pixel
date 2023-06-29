//========================================
// 
// �}�l�[�W���[����
// 
//========================================
// *** manager.cpp ***
//========================================
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "light.h"
#include "sound.h"
#include "texture.h"
#include "input.h"
#include "object\model.h"
#include "object\object.h"
#include "object\2D\score.h"
#include "object\2D\time.h"
#include "object\2D\text2D.h"
#include "object\2D\bg2D.h"
#include "object\2D\bg_Multi2D.h"
#include "object\3D\floor.h"
#include "object\3D\block.h"
#include "object\3D\player.h"
#include "object\3D\enemy.h"
#include "object\3D\effectX.h"

// �ÓI�����o�ϐ�
CRenderer *CManager::m_pRenderer = NULL;
CCamera *CManager::m_pCamera = NULL;	// �J����
CLight *CManager::m_pLight = NULL;		// ���C�g
CSound *CManager::m_pSound = NULL;
CTexture *CManager::m_pTexture = NULL;
CInputKeyboard *CManager::m_InputKeyboard = NULL;
CInputMouse *CManager::m_InputMouse = NULL;
CInputJoypad *CManager::m_InputJoypad = NULL;
CBg *CManager::m_pBg = NULL;
CPlayer *CManager::m_pPlayer = NULL;
CBlock *CManager::m_pBlock = NULL;
CEnemy *CManager::m_pEnemy = NULL;
CBullet *CManager::m_pBullet = NULL;


//========================================
// �R���X�g���N�^
//========================================
CManager::CManager()
{
	
}

//========================================
// �f�X�g���N�^
//========================================
CManager::~CManager()
{

}

//========================================
// ������
//========================================
HRESULT CManager::Init(HINSTANCE hinstance, HWND hWnd, BOOL bWindow)
{
	if (m_pRenderer == NULL)
	{
		// �����_���[�̐���
		m_pRenderer = new CRenderer;

		// �����_���[�̏�����
		m_pRenderer->Init(hWnd, bWindow);
	}

	if (m_InputKeyboard == NULL)
	{
		// �L�[�{�[�h�̐���
		m_InputKeyboard = new CInputKeyboard;

		// �L�[�{�[�h�̏�����
		m_InputKeyboard->Init(hinstance, hWnd);
	}

	if (m_InputMouse == NULL)
	{
		// �}�E�X�̐���
		m_InputMouse = new CInputMouse;

		// �}�E�X�̏�����
		m_InputMouse->Init(hinstance, hWnd);
	}

	if (m_InputJoypad == NULL)
	{
		// �W���C�p�b�g�̐���
		m_InputJoypad = new CInputJoypad;

		// �W���C�p�b�g�̏�����
		m_InputJoypad->Init();
	}

	if (m_pCamera == NULL)
	{
		// �J�����̐���
		m_pCamera = new CCamera;

		// �J�����̏�����
		m_pCamera->lnit();
	}

	if (m_pLight == NULL)
	{
		// ���C�g�̐���
		m_pLight = new CLight;

		// ���C�g�̏�����
		m_pLight->lnit();
	}

	if (m_pSound == NULL)
	{
		// �T�E���h�̐���
		m_pSound = new CSound;

		// �T�E���h�̓ǂݍ���
		m_pSound->Load();

		// �T�E���h�̏�����
		m_pSound->Init(hWnd);
	}
	
	if (m_pTexture == NULL)
	{
		// �e�N�X�`���̐���
		m_pTexture = new CTexture;

		// �e�N�X�`��
		m_pTexture->Load();
	}

	// ���f���̏�����
	CModel::InitModel();

	// �w�i�̐���
	//for (int nCntBg = 0; nCntBg < 3; nCntBg++)
	//{
	//	/*CBgMulti::Create(D3DXVECTOR3((nCntBg + 1)* 0.0005f, 0.0f, 0.0f), nCntBg);*/
	//}
	
	//CFloor::Create();

	// �u���b�N�̐���
	CBlock::Load();

	CPlayer::Create();

	// �G�̐���

	for (int nCnt = 0; nCnt < 11; nCnt++)
	{
		CEnemy::Create(D3DXVECTOR3(400.0f + (nCnt * -75), -20.0f, -150.0f));
	}

	/*CEffectX *pObj = CEffectX::Create();
	pObj->Eff_SetPos(D3DXVECTOR3(0.0f, 20.0f, 0.0f));
	pObj->Eff_SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pObj->Eff_SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pObj->Eff_SetType(1);
	pObj->Eff_SetLife(1000);
	pObj->Eff_SetCol(D3DXCOLOR(0.1f, 0.f, 0.8f, 1.0f));
	pObj->Eff_SetRadius(1.0f);*/

	{
		// �^�C������
		CTime *pObj = CTime::Create();

		// �T�C�Y�ݒ�
		pObj->SetSize(20.0f, 20.0f);

		// �ʒu�ݒ�
		pObj->SetPos(D3DXVECTOR3(SCREEN_WIDTH - 260.0f, 32.0f, 0.0f));

		// �^�C���ݒ�
		pObj->SetTime(99);
	}

	{
		// �X�R�A����
		CScore *pObj = CScore::Create();

		// �T�C�Y�ݒ�
		pObj->SetSize(20.0f, 20.0f);

		// �ʒu�ݒ�
		pObj->SetPos(D3DXVECTOR3(SCREEN_WIDTH - 260.0f, 52.0f, 0.0f));

		// �X�R�A�ݒ�
		CScore::SetScore();
	}
	return S_OK;
}

//========================================
// �I��
//========================================
void CManager::Uninit(void)
{
	// �L�[�{�[�h�̔j��
	if (m_InputKeyboard != NULL)
	{
		m_InputKeyboard->Uninit();

		delete m_InputKeyboard;
		m_InputKeyboard = NULL;
	}

	// �}�E�X�̔j��
	if (m_InputMouse != NULL)
	{
		m_InputMouse->Uninit();

		delete m_InputMouse;
		m_InputMouse = NULL;
	}

	// �W���C�p�b�g�̔j��
	if (m_InputJoypad != NULL)
	{
		m_InputJoypad->Uninit();

		delete m_InputJoypad;
		m_InputJoypad = NULL;
	}

	// ���f���̏I��
	CModel::UninitModel();

	// �����_���[�̔j��
	if (m_pRenderer != NULL)
	{
		// �����_���[
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	// ���C�g�̔j��
	if (m_pLight != NULL)
	{
		// ���C�g
		m_pLight->Uninit();

		delete m_pLight;
		m_pLight = NULL;
	}

	// �J�����̔j��
	if (m_pCamera != NULL)
	{
		// �J����
		m_pCamera->Uninit();

		delete m_pCamera;
		m_pCamera = NULL;
	}

	// �T�E���h�̔j��
	if (m_pSound != NULL)
	{
		// �T�E���h
		m_pSound->StopSound();
		m_pSound->Uninit();

		delete m_pSound;
		m_pSound = NULL;
	}

	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Unload();

		delete m_pTexture;
		m_pTexture = NULL;
	}	
}

//========================================
// �X�V
//========================================
void CManager::Update(void)
{
	m_InputKeyboard->Update();	// �L�[�{�[�h
	m_InputMouse->Update();		// �}�E�X
	m_InputJoypad->Update();	// �W���C�p�b�g
	m_pCamera->Update();		// �J����
	m_pLight->Update();			// ���C�g
	m_pRenderer->Update();		// �����_���[
}

//========================================
// �`��
//========================================
void CManager::Draw(void)
{
	m_pRenderer->Draw();	// �����_���[
}
