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
#include "csv_file.h"
#include "object\model\model.h"
#include "object\object.h"
#include "object\UI\score.h"
#include "object\UI\time.h"
#include "object\UI\text2D.h"
#include "object\model\block.h"
#include "object\model\player.h"
#include "object\model\enemy.h"
#include "object\BG\bg_side.h"
#include "object\BG\bg_ceiling.h"

// �ÓI�����o�ϐ�
CRenderer *CManager::m_pRenderer = NULL;
CCamera *CManager::m_pCamera = NULL;	// �J����
CLight *CManager::m_pLight = NULL;		// ���C�g
CSound *CManager::m_pSound = NULL;
CTexture *CManager::m_pTexture = NULL;
CInputKeyboard *CManager::m_InputKeyboard = NULL;
CInputMouse *CManager::m_InputMouse = NULL;
CInputJoypad *CManager::m_InputJoypad = NULL;
CPlayer *CManager::m_pPlayer = NULL;
CBlock *CManager::m_pBlock = NULL;
CEnemy *CManager::m_pEnemy = NULL;

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
	// �����_���[�̐���
	m_pRenderer = new CRenderer;

	// �����_���[�̏���������
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{// ���������������s�����ꍇ
		return E_FAIL;
	}

	// �L�[�{�[�h�̐���
	m_InputKeyboard = new CInputKeyboard;

	// �L�[�{�[�h�̏�����
	if (FAILED(m_InputKeyboard->Init(hinstance, hWnd)))
	{
		return E_FAIL;
	}

	// �}�E�X�̐���
	m_InputMouse = new CInputMouse;

	// �}�E�X�̏�����
	if (FAILED(m_InputMouse->Init(hinstance, hWnd)))
	{
		return E_FAIL;
	}

	// �W���C�p�b�g�̐���
	m_InputJoypad = new CInputJoypad;

	// �W���C�p�b�g�̏�����
	if (FAILED(m_InputJoypad->Init()))
	{
		return E_FAIL;
	}

	// �J�����̐���
	m_pCamera = new CCamera;

	// �J�����̏�����
	if (FAILED(m_pCamera->Init()))
	{
		return E_FAIL;
	}

	// ���C�g�̐���
	m_pLight = new CLight;

	// ���C�g�̏�����
	if (FAILED(m_pLight->Init()))
	{
		return E_FAIL;
	}

	// �T�E���h�̐���
	m_pSound = new CSound;

	// �T�E���h�̓ǂݍ���
	m_pSound->Load();

	// �T�E���h�̏�����
	if (FAILED(m_pSound->Init(hWnd)))
	{
		return E_FAIL;
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

	// �w�i(����)�̐���
	CBgSide *pBgsky = CBgSide::Create();	

	// �w�i(�V��)�̐���
	CBgCeiling *pBgCeiling = CBgCeiling::Create();

	// �u���b�N�̐���
	LoodBlock();

	CPlayer *pPlayer = CPlayer::Create();
	pPlayer->SetMotion("data\\GAMEDATA\\MODEL\\Player\\PLAYER_DATA.txt");

	// �G�̐���
	LoodEnemy();

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

	{
		{// �ړ����@�e�L�X�g
		 // �e�L�X�g2D����
			CText2D *pObj = CText2D::Create();

			// �ʒu�ݒ�
			pObj->SetPos(D3DXVECTOR3(32.0f, 32.0f, 0.0f));
			// �T�C�Y�ݒ�
			pObj->SetSize(16.0f, 16.0f);
			// ������ݒ�
			pObj->SetString("MOVE : W A D S");
		}

		{// �W�����v���@�e�L�X�g
		 // �e�L�X�g2D����
			CText2D *pObj = CText2D::Create();

			// �ʒu�ݒ�
			pObj->SetPos(D3DXVECTOR3(32.0f, 48.0f, 0.0f));
			// �T�C�Y�ݒ�
			pObj->SetSize(16.0f, 16.0f);
			// ������ݒ�
			pObj->SetString("JUMP : SPACE");
		}

		{// �ˌ����@�e�L�X�g
		 // �e�L�X�g2D����
			CText2D *pObj = CText2D::Create();

			// �ʒu�ݒ�
			pObj->SetPos(D3DXVECTOR3(32.0f, 64.0f, 0.0f));
			// �T�C�Y�ݒ�
			pObj->SetSize(16.0f, 16.0f);
			// ������ݒ�
			pObj->SetString("SHOT : ENTER & MOUSE_LEFT");
		}

		{// �z�u�e�L�X�g
		 // �e�L�X�g2D����
			CText2D *pObj = CText2D::Create();

			// �ʒu�ݒ�
			pObj->SetPos(D3DXVECTOR3(32.0f, 80.0f, 0.0f));
			// �T�C�Y�ݒ�
			pObj->SetSize(16.0f, 16.0f);
			// ������ݒ�
			pObj->SetString("SET_CUBE : E");
		}

		{// �J�����؂�ւ��e�L�X�g
		 // �e�L�X�g2D����
			CText2D *pObj = CText2D::Create();

			// �ʒu�ݒ�
			pObj->SetPos(D3DXVECTOR3(32.0f, 128.0f, 0.0f));
			// �T�C�Y�ݒ�
			pObj->SetSize(16.0f, 16.0f);
			// ������ݒ�
			pObj->SetString("CAMERA_MODE : Q");
		}

		{// �J�����ړ����@�e�L�X�g
		 // �e�L�X�g2D����
			CText2D *pObj = CText2D::Create();

			// �ʒu�ݒ�
			pObj->SetPos(D3DXVECTOR3(32.0f, 144.0f, 0.0f));
			// �T�C�Y�ݒ�
			pObj->SetSize(16.0f, 16.0f);
			// ������ݒ�
			pObj->SetString("CAMERA_MOVE : MOUSE_RIGHT");
		}

		{// ���Z�b�g���@�e�L�X�g
		 // �e�L�X�g2D����
			CText2D *pObj = CText2D::Create();

			// �ʒu�ݒ�
			pObj->SetPos(D3DXVECTOR3(32.0f, 176.0f, 0.0f));
			// �T�C�Y�ݒ�
			pObj->SetSize(16.0f, 16.0f);
			// ������ݒ�
			pObj->SetString("RESET:R");
		}
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
	m_InputKeyboard->Update();		// �L�[�{�[�h
	m_InputMouse->Update();			// �}�E�X
	m_InputJoypad->Update();		// �W���C�p�b�g(�{�^��)
	m_InputJoypad->UpdateStick();	// �W���C�p�b�g(�X�e�B�b�N)	
	m_pCamera->Update();			// �J����
	m_pLight->Update();				// ���C�g
	m_pRenderer->Update();			// �����_���[

	// �G�l�~�[�̑S�� �����Z�b�g�{�^��
	if (CEnemy::GetEnemyAll() <= 0 || m_InputKeyboard->GetTrigger(DIK_R))
	{
		CPlayer::ReleaseAll(CObject::TYPE_PLAYER);

		CPlayer *pPlayer = CPlayer::Create();
		pPlayer->SetMotion("data\\GAMEDATA\\MODEL\\Player\\PLAYER_DATA.txt");

		// �X�R�A�ݒ�
		CScore::SetScore();

		SetEnemy();
	}

}

//========================================
// �`��
//========================================
void CManager::Draw(void)
{
	m_pRenderer->Draw();	// �����_���[
}

//========================================
// �Z�b�g�G�l�~�[
//========================================
void CManager::SetEnemy(void)
{
	// �G��S�Ĕj��
	CObject::ReleaseAll(CObject::TYPE_ENEMY);

	// �G�̐���
	LoodEnemy();
}

//========================================
// �u���b�N�̓ǂݍ���
//========================================
void CManager::LoodBlock(void)
{
	CSVFILE *pFile = new CSVFILE;

	// �ǂݍ���
	pFile->FileLood("data\\GAMEDATA\\BLOCK\\STAGE_DATA.csv", true, true, ',');

	// �s���̎擾
	int nRowMax = pFile->GetRowSize();

	// �e�f�[�^�ɑ��
	for (int nRow = 0; nRow < nRowMax; nRow++)
	{
		// �z�u���̐���
		int nType;				// ���
		D3DXVECTOR3 pos;		// �ʒu

		// �񐔂̎擾
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			string sData = pFile->GetData(nRow, nLine);

			switch (nLine)
			{
			case 0:	pFile->ToValue(nType, sData); break;	// ���
			case 1:	pFile->ToValue(pos.x, sData); break;	// �ʒu X
			case 2:	pFile->ToValue(pos.y, sData); break;	// �ʒu Y
			case 3:	pFile->ToValue(pos.z, sData); break;	// �ʒu Z
			}
		}

		// �ő吔�ɒB������Ԃ�
		if (nRow == nRowMax - 1)	// (�� - ��̍ő吔 - �w�b�_�[�̗�)
		{
			return;
		}

		// �z�u
		CBlock *pObj = CBlock::Create(nType, pos);
	}

	// �������J��
	delete pFile;
	pFile = NULL;
}

//========================================
// �G�l�~�[�̓ǂݍ���
//========================================
void CManager::LoodEnemy(void)
{
	CSVFILE *pFile = new CSVFILE;

	// �ǂݍ���
	pFile->FileLood("data\\GAMEDATA\\ENEMY\\STAGE_DATA1.csv", true, true, ',');

	// �s���̎擾
	int nRowMax = pFile->GetRowSize();

	// �e�f�[�^�ɑ��
	for (int nRow = 0; nRow < nRowMax; nRow++)
	{
		// �z�u���̐���
		int nType,nMove;	// ���
		D3DXVECTOR3 pos;	// �ʒu

		// �񐔂̎擾
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			string sData = pFile->GetData(nRow, nLine);

			switch (nLine)
			{
			case 0:	pFile->ToValue(nType, sData); break;	// ���
			case 1:	pFile->ToValue(nMove, sData); break;	// �ړ����
			case 2:	pFile->ToValue(pos.x, sData); break;	// �ʒu X
			case 3:	pFile->ToValue(pos.y, sData); break;	// �ʒu Y
			case 4:	pFile->ToValue(pos.z, sData); break;	// �ʒu Z
			}
		}

		// �ő吔�ɒB������Ԃ�
		if (nRow == nRowMax - 1)	// (�� - ��̍ő吔 - �w�b�_�[�̗�)
		{
			return;
		}

		// �z�u
		CEnemy *pObj = CEnemy::Create(nType, nMove,pos);
	}

	// �������J��
	delete pFile;
	pFile = NULL;
}