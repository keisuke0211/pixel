//========================================
// 
// �v���C���[����
// 
//========================================
// *** player.cpp ***
//========================================
#include "player.h"
#include "../../manager.h"
#include "../../camera.h"
#include "../../input.h"
#include "../../sound.h"
#include "../../physics.h"
#include "bullet.h"
#include "enemy.h"

//****************************************
// �}�N����`
//****************************************
#define JUMP_POWER		(7.0f)		// �W�����v��
#define GRAVITY_MAG		(0.08f)		// �d�͌W�� 0.08
#define GRAVITY_POWER	(9.5f)		// �d�͉����x
#define ROT_DIAMETER	(0.15f)		// ��]�{��

#define ROT_FORCE_BY_CURSOR	(D3DXVECTOR3(0.0005f,0.00075f,0.0f))	// �J�[�\���̉�]��

// ��`
const float CPlayer::PLAYER_SPEED = 1.0f;

//========================================
// �R���X�g���N�^
//========================================
CPlayer::CPlayer(int nPriority) : CMotionModel(nPriority)
{
	// �l���N���A
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.moveRot = INIT_D3DXVECTOR3;
	m_Info.targetRot = INIT_D3DXVECTOR3;
	m_Info.move = INIT_D3DXVECTOR3;
	m_Info.fWidth = INIT_FLOAT;
	m_Info.fHeight = INIT_FLOAT;
	m_Info.fDepth = INIT_FLOAT;
	m_Info.bMove = false;
	m_Info.bJump = false;
}

//========================================
// �f�X�g���N�^
//========================================
CPlayer::~CPlayer()
{

}

//========================================
// ����
//========================================
CPlayer *CPlayer::Create(void)
{
	CPlayer *pPlayer = NULL;

	if (pPlayer != NULL)
	{
		return pPlayer;
	}

	// �I�u�W�F�N�g2D�̐���
	pPlayer = new CPlayer;

	// ����������
	pPlayer->Init();

	return pPlayer;
}

//========================================
// ������
//========================================
HRESULT CPlayer::Init(void)
{
	CCamera *pCamera = CManager::GetCamera();	// �J�����̎擾

	CMotionModel::Init();

	// ��ނ̐ݒ�
	SetType(TYPE_PLAYER);

	m_Info.pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.col = INIT_D3DXCOLOR;
	
	// ����
	//SetMotion("data\\GAMEDATA\\MODEL\\Player\\PLAYER_DATA.txt");
	SetPos(m_Info.pos);
	SetRot(m_Info.rot);

	return S_OK;
}

//========================================
// �I��
//========================================
void CPlayer::Uninit(void)
{
	CMotionModel::Uninit();
}

//========================================
// �X�V
//========================================
void CPlayer::Update(void)
{
	// �L�[���͏���
	KeyInput();

	// �ʒu�X�V����
	UpdatePos();

	// ����/�ړ�����/�ڕW�����𐧌�
	RotControl(&m_Info.rot);
	RotControl(&m_Info.moveRot);
	RotControl(&m_Info.targetRot);

	// �p�x��ڕW�p�x�Ɍ����Đ��ڂ���
	m_Info.rot.y += AngleDifference(m_Info.rot.y, m_Info.targetRot.y) * ROT_DIAMETER;

	SetRot(m_Info.rot);

	CMotionModel::Update();
}

//========================================
// �`��
//========================================
void CPlayer::Draw(void)
{
	CMotionModel::Draw();
}

//========================================
// �L�[���͏���
//========================================
void CPlayer::KeyInput(void)
{
	// --- �擾 ---------------------------------
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CInputMouse *pInputMouse = CManager::GetInputMouse();			// �}�E�X
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();		// �W���C�p�b�g

	m_Info.bMove = true;

	if (pInputKeyboard->GetPress(DIK_A))
	{
		if (pInputKeyboard->GetPress(DIK_W)) { MoveKeyboard(DIRECTION_LEFT_BACK); }			// �����ړ�
		else if (pInputKeyboard->GetPress(DIK_S)) { MoveKeyboard(DIRECTION_LEFT_FRONT); }	// ����O�ړ�
		else { MoveKeyboard(DIRECTION_LEFT); }		// ���ړ�
	}
	else if (pInputKeyboard->GetPress(DIK_D))
	{
		if (pInputKeyboard->GetPress(DIK_W)) { MoveKeyboard(DIRECTION_RIGHT_BACK); }		// �E���ړ�
		else if (pInputKeyboard->GetPress(DIK_S)) { MoveKeyboard(DIRECTION_RIGHT_FRONT); }	// �E��O�ړ�
		else { MoveKeyboard(DIRECTION_RIGHT); }		// �E�ړ�
	}
	else if (pInputKeyboard->GetPress(DIK_W)) { MoveKeyboard(DIRECTION_BACK); }				// ���ړ�
	else if (pInputKeyboard->GetPress(DIK_S)) { MoveKeyboard(DIRECTION_FRONT); }			// ��O�ړ�
	else
	{
		m_Info.bMove = false;
	}

	// �W�����v
	if (pInputKeyboard->GetTrigger(DIK_SPACE) || pInputJoypad->GetJoypadTrigger(CInputJoypad::JOYKEY_A))
	{
		if (m_Info.bJump == false)
		{
			m_Info.bJump = true;	// �W�����v�t���O��^�ɂ���
			m_Info.move.y += JUMP_POWER;
		}
	}

	// �U��
	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputMouse->GetTrigger(CInputMouse::MOUSE_LEFT) || pInputJoypad->GetJoypadTrigger(CInputJoypad::JOYKEY_B))
	{
		CBullet::Create(D3DXVECTOR3(m_Info.pos.x,m_Info.pos.y + 20,m_Info.pos.z),m_Info.rot);
	}

	// �ʒu�X�V
	MovePos(PLAYER_SPEED);
}

//========================================
// �L�[�{�[�h�̈ړ�����
//========================================
void CPlayer::MoveKeyboard(DIRECTION drct)
{
	// --- ��� ---------------------------------
	m_Info.moveRot = m_Info.rot;	// �ړ�����

	// --- �ړ� ---------------------------------

	// �ړ������ɉ~��������
	m_Info.moveRot.y = D3DX_PI;

	switch (drct)
	{
	case DIRECTION_LEFT			:m_Info.moveRot.y *= -0.5f; break;	// ��
	case DIRECTION_RIGHT		:m_Info.moveRot.y *= 0.5f;	break;	// �E
	case DIRECTION_BACK			:m_Info.moveRot.y *= 0.0f;	break;	// ��
	case DIRECTION_FRONT		:m_Info.moveRot.y *= 1.0f;	break;	// ��O
	case DIRECTION_LEFT_BACK	:m_Info.moveRot.y *= -0.25f; break;	// ����
	case DIRECTION_LEFT_FRONT	:m_Info.moveRot.y *= -0.75f; break;	// ����O
	case DIRECTION_RIGHT_BACK	:m_Info.moveRot.y *= 0.25f; break;	// �E��
	case DIRECTION_RIGHT_FRONT	:m_Info.moveRot.y *= 0.75f; break;	// �E��O
	}
}

//========================================
// �ړ�����
//========================================
void CPlayer::MovePos(float fMove)
{
	// --- �擾 ---------------------------------
	CCamera *pCamera = CManager::GetCamera();				// �J����
	CInputMouse *pInputMouse = CManager::GetInputMouse();	// �}�E�X

	D3DXVECTOR3 posV = pCamera->GetInfo().posV;	// ���_
	D3DXVECTOR3 posR = pCamera->GetInfo().posR;	// �����_

	if (!m_Info.bMove || pInputMouse->GetPress(CInputMouse::MOUSE_RIGHT))
	{
		fMove = 0.0f;
	}

	if (m_Info.bMove)
	{
		// ���_���璍���_�܂ł̊p�x
		float fAngle
			= FindAngle(D3DXVECTOR3(posV.x, posV.z, 0.0f), D3DXVECTOR3(posR.x, posR.z, 0.0f));

		m_Info.moveRot.y += fAngle;
	}

	m_Info.move.x += sinf(m_Info.moveRot.y) * fMove;
	m_Info.move.z += cosf(m_Info.moveRot.y) * fMove;
}

//========================================
// �ʒu�X�V
//========================================
void CPlayer::UpdatePos(void)
{
	// --- �擾 ---------------------------------
	CCamera *pCamera = CManager::GetCamera();		// �J����

	{
		// �ړ��ʂ̑��
		m_Info.pos.x += m_Info.move.x;

		// �ړ��ʂ̌���
		m_Info.move.x *= 0.8f;

		// X�����̓����蔻��
		m_Info.pos = Collision(VECTOR_X, m_Info.pos);
	}

	{
		// �ړ��ʂ̑��
		m_Info.pos.z += m_Info.move.z;

		// �ړ��ʂ̌���
		m_Info.move.z *= 0.8f;

		// Z�����̓����蔻��
		m_Info.pos = Collision(VECTOR_Z, m_Info.pos);
	}

	{

		// �ړ��ʂ̑��
		m_Info.pos.y += m_Info.move.y;

		//�x�̈ړ��ʂɏd�͂����Z
		m_Info.move.y -= (GRAVITY_POWER - m_Info.move.y) * GRAVITY_MAG;

		// Y�����̓����蔻��
		m_Info.pos = Collision(VECTOR_Y, m_Info.pos);
	}
	SetPos(m_Info.pos);

	// �ڕW�����Ɉړ���������
	m_Info.targetRot = m_Info.moveRot;

	// �J�����̒����_��ݒ�
	pCamera->SetPosR(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 95, m_Info.pos.z));
}

//========================================
// ���f���Ƃ̓����蔻��
//========================================
D3DXVECTOR3 CPlayer::Collision(VECTOR vector, D3DXVECTOR3 pos)
{
	for (int nCntObj = 0; nCntObj < GetNumAll(); nCntObj++)
	{
		// �I�u�W�F�N�g���擾
		CObject *pObj = GetObjectPointer(PRIO_OBJX, nCntObj);

		if (pObj != NULL)
		{// �g�p����Ă��鎞�A

		 // ��ނ��擾
			TYPE type = pObj->GetType();

			if (type == TYPE_BLOCK)
			{// ��ނ��u���b�N�̎��A

			 // �v���C���[�̊e�p�[�c�̎擾
				D3DXVECTOR3 PosOld = GetPosOld();	// �ʒu(�ߋ�)
				D3DXVECTOR3 Scale = GetSize();
				float fSize = 10.0f;

				// �u���b�N�̎擾
				D3DXVECTOR3 PairPos = pObj->GetPos();	// �ʒu
				float fPairWidth = pObj->GetWidth();	// ��
				float fPairHeight = pObj->GetHeight();	// ����
				float fPairDepth = pObj->GetDepth();	// ���s��

				// --- �����蔻�� ----------------------------------------------
				switch (vector)
				{
				case VECTOR_X: {	/* X���� */

					if ((pos.z + fSize) > (PairPos.z - fPairDepth) &&
						(pos.z - fSize) < (PairPos.z + fPairDepth) &&
						(pos.y + fSize) > (PairPos.y - fPairHeight) &&
						(pos.y - fSize) < (PairPos.y + fPairHeight))
					{// ���ӂƎ�O�ӂ�����̕��̓����̎��A

						if ((pos.x + fSize) > (PairPos.x - fPairWidth) &&
							(PosOld.x + fSize) <= (PairPos.x - fPairWidth))
						{// ������߂荞��ł��鎞

							pos.x = (PairPos.x - fPairWidth) - fSize;
						}
						else if ((pos.x - fSize) < (PairPos.x + fPairWidth) &&
							(PosOld.x - fSize) >= (PairPos.x + fPairWidth))
						{// �E����߂荞��ł��鎞

							pos.x = (PairPos.x + fPairWidth) + fSize;
						}
					}
				}
				   break;
				case VECTOR_Y: {	/* Y���� */

					if ((pos.x + fSize) > (PairPos.x - fPairWidth) &&
						(pos.x - fSize) < (PairPos.x + fPairWidth) &&
						(pos.z + fSize) > (PairPos.z - fPairDepth) &&
						(pos.z - fSize) < (PairPos.z + fPairDepth))
					{// ���ӂƉE�ӂ�����̕��̓����̎��A

						if ((pos.y + fSize) > (PairPos.y - fPairHeight) &&
							(PosOld.y + fSize) <= (PairPos.y - fPairHeight))
						{// ������߂荞��ł��鎞

							pos.y = (PairPos.y - fPairHeight) - fSize;

							//�v���C���[���㏸��
							if (m_Info.move.y > 0.0f)
							{
								//�x�̈ړ��ʂ�0��
								m_Info.move.y = 0.0f;
							}
						}
						else if ((pos.y - fSize) < (PairPos.y + fPairHeight) &&
							(PosOld.y - fSize) >= (PairPos.y + fPairHeight))
						{// �ォ��߂荞��ł��鎞
							pos.y = (PairPos.y + fPairHeight) + fSize;

							m_Info.move.y = 0.0f;
							m_Info.bJump = false;

						}
					}
				}
				   break;
				case VECTOR_Z: {	/* Z���� */

					if ((pos.x + fSize) > (PairPos.x - fPairWidth) &&
						(pos.x - fSize) < (PairPos.x + fPairWidth) &&
						(pos.y + fSize) > (PairPos.y - fPairHeight) &&
						(pos.y - fSize) < (PairPos.y + fPairHeight))
					{// ���ӂƎ�O�ӂ�����̕��̓����̎��A

						if ((pos.z + fSize) > (PairPos.z - fPairDepth) &&
							(PosOld.z + fSize) <= (PairPos.z - fPairDepth))
						{// ������߂荞��ł��鎞

							pos.z = (PairPos.z - fPairDepth) - fSize;
						}
						else if ((pos.z - fSize) < (PairPos.z + fPairDepth) &&
							(PosOld.z - fSize) >= (PairPos.z + fPairDepth))
						{// �E����߂荞��ł��鎞

							pos.z = (PairPos.z + fPairDepth) + fSize;
						}
					}
				}
				   break;
				}
			}
			else if (type = TYPE_ENEMY)
			{// ��ނ��G�l�~�[�̎�
			 // �v���C���[�̊e�p�[�c�̎擾
				D3DXVECTOR3 PosOld = GetPosOld();	// �ʒu(�ߋ�)
				D3DXVECTOR3 Scale = GetSize();
				float fSize = 10.0f;

				// �u���b�N�̎擾
				D3DXVECTOR3 PairPos = pObj->GetPos();	// �ʒu
				float fPairWidth = pObj->GetWidth();	// ��
				float fPairHeight = pObj->GetHeight();	// ����
				float fPairDepth = pObj->GetDepth();	// ���s��

				// --- �����蔻�� ----------------------------------------------
				switch (vector)
				{
				case VECTOR_X: {	/* X���� */

					if ((pos.z + fSize) > (PairPos.z - fPairDepth) &&
						(pos.z - fSize) < (PairPos.z + fPairDepth) &&
						(pos.y + fSize) > (PairPos.y - fPairHeight) &&
						(pos.y - fSize) < (PairPos.y + fPairHeight))
					{// ���ӂƎ�O�ӂ�����̕��̓����̎��A

						if ((pos.x + fSize) > (PairPos.x - fPairWidth) &&
							(PosOld.x + fSize) <= (PairPos.x - fPairWidth))
						{// ������߂荞��ł��鎞

							pos.x = (PairPos.x - fPairWidth) - fSize;
						}
						else if ((pos.x - fSize) < (PairPos.x + fPairWidth) &&
							(PosOld.x - fSize) >= (PairPos.x + fPairWidth))
						{// �E����߂荞��ł��鎞

							pos.x = (PairPos.x + fPairWidth) + fSize;
						}
					}
				}
				   break;
				case VECTOR_Y: {	/* Y���� */

					if ((pos.x + fSize) > (PairPos.x - fPairWidth) &&
						(pos.x - fSize) < (PairPos.x + fPairWidth) &&
						(pos.z + fSize) > (PairPos.z - fPairDepth) &&
						(pos.z - fSize) < (PairPos.z + fPairDepth))
					{// ���ӂƉE�ӂ�����̕��̓����̎��A

						if ((pos.y + fSize) > (PairPos.y - fPairHeight) &&
							(PosOld.y + fSize) <= (PairPos.y - fPairHeight))
						{// ������߂荞��ł��鎞

							pos.y = (PairPos.y - fPairHeight) - fSize;
						}
						else if ((pos.y - fSize) < (PairPos.y + fPairHeight) &&
							(PosOld.y - fSize) >= (PairPos.y + fPairHeight))
						{// �ォ��߂荞��ł��鎞

							pos.y = (PairPos.y + fPairHeight) + fSize;
						}
					}
				}
				   break;
				case VECTOR_Z: {	/* Z���� */

					if ((pos.x + fSize) > (PairPos.x - fPairWidth) &&
						(pos.x - fSize) < (PairPos.x + fPairWidth) &&
						(pos.y + fSize) > (PairPos.y - fPairHeight) &&
						(pos.y - fSize) < (PairPos.y + fPairHeight))
					{// ���ӂƎ�O�ӂ�����̕��̓����̎��A

						if ((pos.z + fSize) > (PairPos.z - fPairDepth) &&
							(PosOld.z + fSize) <= (PairPos.z - fPairDepth))
						{// ������߂荞��ł��鎞

							pos.z = (PairPos.z - fPairDepth) - fSize;
						}
						else if ((pos.z - fSize) < (PairPos.z + fPairDepth) &&
							(PosOld.z - fSize) >= (PairPos.z + fPairDepth))
						{// �E����߂荞��ł��鎞

							pos.z = (PairPos.z + fPairDepth) + fSize;
						}
					}
				}
				   break;
				}
			}

		}
	}
	return pos;
}