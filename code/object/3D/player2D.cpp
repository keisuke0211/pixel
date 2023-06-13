//========================================
// 
// �v���C���[����
// 
//========================================
// *** player.cpp ***
//========================================
#include "player2D.h"
#include "../../manager.h"
#include "../../renderer.h"
#include "../../input.h"
#include "../../sound.h"
#include "bullet.h"
#include "../object2D.h"

//****************************************
// �}�N����`
//****************************************
#define JUMP_POWER		(-40.0f)// �W�����v��
#define GRAVITY_MAG		(0.08f)	// �d�͌W��
#define GRAVITY_POWER	(9.0f)	// �d�͉����x

// ��`
const float CPlayer2D::PLAYER_SPEED = 2.5f;

// �ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CPlayer2D::m_pTexture[CPlayer2D::MAX_TEXTURE] = { NULL };
int CPlayer2D::m_nTexture = -1;

// �R���X�g���N�^
CPlayer2D::CPlayer2D(int nPriority) : CObject2D(nPriority)
{
	// �l���N���A
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.move = INIT_D3DXVECTOR3;
	m_Info.fWidth = INIT_FLOAT;
	m_Info.fHeight = INIT_FLOAT;
	m_Info.bJump = false;


	bShot = false;
}

// �f�X�g���N�^
CPlayer2D::~CPlayer2D()
{

}

//========================================
// �e�N�X�`���̓ǂݍ���
//========================================
HRESULT CPlayer2D::Load(char *pPath)
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
void CPlayer2D::Unload(void)
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
// ����
//========================================
CPlayer2D *CPlayer2D::Create(void)
{
	CPlayer2D *pPlayer = NULL;

	if (pPlayer != NULL)
	{
		return pPlayer;
	}

	// �I�u�W�F�N�g2D�̐���
	pPlayer = new CPlayer2D;

	// ����������
	pPlayer->Init();

	return pPlayer;
}
//========================================
// ������
//========================================
HRESULT CPlayer2D::Init(void)
{
	CObject2D::Init();
	
	// ��ނ̐ݒ�
	SetType(TYPE_PLAYER);

	m_Info.pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_Info.fWidth = 75.0f;
	m_Info.fHeight = 75.0f;

	// ����
	SetPos(m_Info.pos);
	SetSize(m_Info.fWidth,m_Info.fHeight);
	SetRot(m_Info.rot);
	SetColor(INIT_D3DXCOLOR);
	SetPtn(25);
	SetPtnInfo(5, 8, 46, false, 0);

	// �e�N�X�`���̊��蓖��
	BindTexture(m_pTexture[0]);

	return S_OK;
}

//========================================
// �I��
//========================================
void CPlayer2D::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================
// �X�V
//========================================
void CPlayer2D::Update(void)
{
	// �ړ��E��������
	Physics();

	CObject2D::Update();
}

//========================================
// �`��
//========================================
void CPlayer2D::Draw(void)
{
	CObject2D::Draw();
}

//========================================
// �ړ��E��������
//========================================
void CPlayer2D::Physics(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h�̎擾
	CInputMouse *pInputMouse = CManager::GetInputMouse();			// �}�E�X�̎擾
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();		// �W���C�p�b�g�̎擾

	// --- �ړ� ---------------------------------

	if (pInputKeyboard->GetPress(DIK_D) == true || pInputJoypad->GetJoypadPress(CInputJoypad::JOYKEY_RIGHT, 0) == true)
	{// �E
		m_Info.move.x += PLAYER_SPEED;
		SetPtn(25);
	}
	else if (pInputKeyboard->GetPress(DIK_A) == true || pInputJoypad->GetJoypadPress(CInputJoypad::JOYKEY_LEFT, 0) == true)
	{// ��
		m_Info.move.x -= PLAYER_SPEED;
		SetPtn(35);
	}

	//�ړ��ʂ��X�V(����������)
	m_Info.move.x += (0.0f - m_Info.move.x) * 0.25f;

	// --- �W�����v ---------------------------------
	if (pInputKeyboard->GetPress(DIK_SPACE) == true || pInputJoypad->GetJoypadPress(CInputJoypad::JOYKEY_A, 0) == true)
	{
		if (m_Info.bJump == false)
		{
			m_Info.bJump = true;	// �W�����v�t���O��^�ɂ���
			m_Info.move.y += JUMP_POWER;
		}
	}

	m_Info.pos += m_Info.move;

	// �ړ��ʂ��X�V(����)

	//�x�̈ړ��ʂɏd�͂����Z
	m_Info.move.y += (GRAVITY_POWER - m_Info.move.y) * GRAVITY_MAG;

	// �u���b�N�Ƃ̓����蔻��
	m_Info.pos = Collision(m_Info.pos);

	

	// �ʒu�̍X�V
	SetPos(m_Info.pos);

	CSound *pSound = CManager::GetSound();

	// �}�E�X

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		CBullet::Create(m_Info.pos, D3DXVECTOR3(0.0f, -7.5f, 0.0f), false);
		CBullet::Create(m_Info.pos, D3DXVECTOR3(0.0f, -7.5f, 0.0f), true);
		pSound->PlaySound(1);
	}
	else if (pInputMouse->GetTrigger(CInputMouse::MOUSE_RIGHT) == true)
	{
		CBullet::Create(m_Info.pos, D3DXVECTOR3(0.0f, -7.5f, 0.0f), false);
		pSound->PlaySound(1);
	}

	else if (pInputMouse->GetTrigger(CInputMouse::MOUSE_LEFT) == true)
	{
		CBullet::Create(m_Info.pos, D3DXVECTOR3(0.0f, -7.5f, 0.0f), true);
		pSound->PlaySound(1);
	}
}

//========================================
// �ړ��ʂ̍X�V
//========================================
void CPlayer2D::AddMove(float fRoty)
{
	// �ړ���
	m_Info.move.x += sinf(D3DX_PI * fRoty) * PLAYER_SPEED;
	m_Info.move.y += cosf(D3DX_PI * fRoty) * PLAYER_SPEED;

	m_Info.pos += m_Info.move;
}

//========================================
// �����蔻��
//========================================
D3DXVECTOR3 CPlayer2D::Collision(D3DXVECTOR3 pos)
{
	for (int nCntPriority = 0; nCntPriority < TYPE_MAX; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			// �I�u�W�F�N�g���擾
			CObject *pObj = GetObjectPointer(nCntPriority, nCntObj);

			if (pObj != NULL)
			{// �g�p����Ă��鎞�A

				// ��ނ��擾
				TYPE type = pObj->GetType();

				if (type == TYPE_BLOCK)
				{// ��ނ��u���b�N�̎��A

					//  �v���C���[�̎擾
					D3DXVECTOR3 PosOld = GetPosOld();		// �ʒu(�ߋ�)
					float fWidth = m_Info.fWidth * 0.5;		// ��
					float fHeight = m_Info.fHeight *0.5;	// ����

					// �u���b�N�̎擾
					D3DXVECTOR3 BlockPos = pObj->GetPos();			// �ʒu
					float fBlockWidth = pObj->GetWidth() * 0.5;		// ��
					float fBlockeHight = pObj->GetHeight() * 0.5;	// ����	

					/* �����蔻�� */

					// �v���C���[���u���b�N�̏�Ӂ`���ӂ̊Ԃɂ��鎞
					if ((pos.y + fHeight) > (BlockPos.y - fBlockeHight) &&
						(pos.y - fHeight) < (BlockPos.y + fBlockeHight))
					{
						if ((pos.x + fWidth) >= (BlockPos.x - fBlockWidth) &&
							(PosOld.x + fWidth) <= (BlockPos.x - fBlockWidth))
						{// ������߂荞��ł��鎞

							pos.x = (BlockPos.x - fBlockWidth) - fWidth;
						}
						else if ((pos.x - fWidth) <= (BlockPos.x + fBlockWidth) &&
							(PosOld.x - fWidth) >= (BlockPos.x + fBlockWidth))
						{// �E����߂荞��ł��鎞

							pos.x = (BlockPos.x + fBlockWidth) + fWidth;
						}
					}

					// �v���C���[���u���b�N�̍��Ӂ`�E�ӂ̊Ԃɂ��鎞

					if ((pos.x + fWidth) > (BlockPos.x - fBlockWidth) &&
						(pos.x - fWidth) < (BlockPos.x + fBlockWidth))
					{
						if ((pos.y + fHeight) >= (BlockPos.y - fBlockeHight) &&
							(PosOld.y + fHeight) <= (BlockPos.y - fBlockeHight))
						{// �ォ��߂荞��ł��鎞

							pos.y = (BlockPos.y - fBlockeHight) - fHeight;
							m_Info.move.y = 0.0f;
							m_Info.bJump = false;
						}
						else if ((pos.y - fHeight) <= (BlockPos.y + fBlockeHight) &&
							(PosOld.y - fHeight) >= (BlockPos.y + fBlockeHight))
						{// ������߂荞��ł��鎞
							pos.y = (BlockPos.y + (fBlockeHight + fHeight));

							//�v���C���[���㏸��
							if (m_Info.move.y < 0.0f)
							{
								//�x�̈ړ��ʂ�0��
								m_Info.move.y = 0.0f;
							}
						}
					}
				}
			}
		}
	}
	return pos;
}