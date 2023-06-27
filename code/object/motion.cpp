//========================================
// 
// ���[�V��������
// 
//========================================
// *** motion.cpp ***
//========================================
#include "motion.h"
#include "model.h"
#include "parts.h"
#include "../texture.h"
#include "../manager.h"
#include "../renderer.h"


//========================================
// �R���X�g���N�^
//========================================
CMotion::CMotion(const char *pFileName)
{
	// �l���N���A����
	memset(&m_partsFile, 0, sizeof(m_partsFile));	// �p�[�c��
	m_motion = NULL;								// ���[�V������
	m_ppParts = NULL;								// �p�[�c
	m_nMaxParts = 0;								// �p�[�c��
	LoodMotion(pFileName);							// ���[�V�����ǂݍ���
	m_nNumMotion = 0;								// �������[�V����
	m_bMotion = false;								// ���[�V�������s����
	m_bMotionBlend = false;							// ���[�V�����u�����h
}

//========================================
// �f�X�g���N�^
//========================================
CMotion::~CMotion()
{

}

//========================================
// ������
//========================================
void CMotion::Init(void)
{
	// �J�E���g�̃��Z�b�g
	for (int nCntMotion = 0; nCntMotion < MYMAX_MOTION; nCntMotion++)
	{
		CntReset(nCntMotion);
	}
}

//========================================
// �I��
//========================================
void CMotion::Uninit(void)
{
	for (int nCntMotion = 0; nCntMotion < MYMAX_MOTION; nCntMotion++)
	{
		if (&m_motion[nCntMotion] != NULL)
		{// �������̉��
			if (m_motion[nCntMotion].pKeySet != NULL)
			{
				for (int nCntKey = 0; nCntKey < m_motion[nCntMotion].nNumKey; nCntKey++)
				{
					if (m_motion[nCntMotion].pKeySet[nCntKey].pKey != NULL)
					{
						delete m_motion[nCntMotion].pKeySet[nCntKey].pKey;
						m_motion[nCntMotion].pKeySet[nCntKey].pKey = NULL;
					}
				}
				delete m_motion[nCntMotion].pKeySet;
				m_motion[nCntMotion].pKeySet = NULL;
			}
		}
	}

	if (m_motion != NULL)
	{// �������̉��
		delete[] m_motion;
		m_motion = NULL;
	}

	for (int nCntParts = 0; nCntParts < m_nMaxParts; nCntParts++)
	{
		if (m_ppParts[nCntParts] != NULL)
		{
			delete m_ppParts[nCntParts];
			m_ppParts[nCntParts] = NULL;
		}
	}

	if (m_ppParts != NULL)
	{
		delete[] m_ppParts;
		m_ppParts = NULL;
	}
}

//========================================
// �X�V
//========================================
void CMotion::Update(void)
{
	if (m_bMotionBlend)
	{
		MotionBlend();
	}
	else if (m_bMotion
		&& !m_bMotionBlend)
	{
		PlayMotion();
	}
}

//========================================
//----------------------------------------
// �p�[�c
//----------------------------------------
//========================================

//========================================
// �p�[�c�ݒ�
//========================================
void CMotion::SetParts(D3DXMATRIX mtxWorld, const bool IsColor, const D3DXCOLOR color)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCntParts = 0; nCntParts < m_nMaxParts; nCntParts++)
	{// ���f���̕`��
		if (IsColor)
		{
			m_ppParts[nCntParts]->SetColor(color);
		}

		//�@�e���f�����w�肳��Ă��邩
		if (m_ppParts[nCntParts]->GetParent() != NULL)
		{
			m_ppParts[nCntParts]->Draw(IsColor);
		}
		else
		{
			m_ppParts[nCntParts]->Draw(mtxWorld, IsColor);
		}
	}

	// �V�K�[�x�l��Z�o�b�t�@�̐[�x�l�������l�Ȃ�e�X�g�����ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}

//========================================
// ���̏ꏊ�ɔz�u
//========================================
void CMotion::SetPartsOrigin(void)
{
	for (int nCntParts = 0; nCntParts < m_nMaxParts; nCntParts++)
	{
		// �ʒu�̐ݒ�
		m_ppParts[nCntParts]->SetPos(m_ppParts[nCntParts]->GetPosOrigin());

		//	�����̐ݒ�
		m_ppParts[nCntParts]->SetRot(m_ppParts[nCntParts]->GetRotOrigin());
	}
}

//========================================
//----------------------------------------
// ���[�V����
//----------------------------------------
//========================================

//========================================
// �����ݒ�
//========================================
void CMotion::SetMotion(const int nCntMotionSet)
{
	CMotion::Motion *motion = (m_motion + nCntMotionSet);

	for (int nCntParts = 0; nCntParts < m_nMaxParts; nCntParts++)
	{
		// �ϐ��錾
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ʒu
		D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ����
		D3DXVECTOR3 posOrigin = m_ppParts[nCntParts]->GetPosOrigin();		// ���̈ʒu
		D3DXVECTOR3 rotOrigin = m_ppParts[nCntParts]->GetRotOrigin();		// ���̌���

		// �ʒu�̐ݒ�
		pos = (posOrigin + motion->pKeySet[motion->nCntKeySet].pKey[nCntParts].pos);

		//	�����̐ݒ�
		rot = (rotOrigin + motion->pKeySet[motion->nCntKeySet].pKey[nCntParts].rot);

		// �p�x�̐��K��
		NormalizeAngle(&rot.x);
		NormalizeAngle(&rot.y);
		NormalizeAngle(&rot.z);

		// ���̍X�V
		m_ppParts[nCntParts]->SetPos(pos);
		m_ppParts[nCntParts]->SetRot(rot);
	}
}

//========================================
// ���[�V�����ԍ��̐ݒ�
//========================================
void CMotion::SetNumMotion(const int nNumMotion)
{
	// ���[�V�����J�E���g�̃��Z�b�g
	CntReset(m_nNumMotion);

	// ���[�V�����ԍ��̐ݒ�
	m_nNumMotion = nNumMotion;

	// ���[�V�����u�����h���s��
	m_bMotionBlend = true;
	m_bMotion = true;
}

//========================================
// ���[�V�����̍Đ�
//========================================
void CMotion::PlayMotion(void)
{
	CMotion::Motion *motion = (m_motion + m_nNumMotion);

	for (int nCntParts = 0; nCntParts < m_nMaxParts; nCntParts++)
	{
		// �ϐ��錾
		D3DXVECTOR3 pos = m_ppParts[nCntParts]->GetPos();			// �ʒu
		D3DXVECTOR3 rot = m_ppParts[nCntParts]->GetRot();			// ����
		D3DXVECTOR3 posDest = m_ppParts[nCntParts]->GetPosDest();	// �ړI�̈ʒu
		D3DXVECTOR3 rotDest = m_ppParts[nCntParts]->GetRotDest();	// �ړI�̌���

		if (motion->nCntFrame == 0)
		{// �t���[���J�E���g��0�̎�
		 // �ϐ��錾
			D3DXVECTOR3 posOrigin = m_ppParts[nCntParts]->GetPosOrigin();		// ���̈ʒu
			D3DXVECTOR3 rotOrigin = m_ppParts[nCntParts]->GetRotOrigin();		// ���̌���

			// �ړI�̈ʒu�ƌ����̎Z�o
			posDest = (posOrigin + motion->pKeySet[motion->nCntKeySet].pKey[nCntParts].pos) - pos;
			rotDest = (rotOrigin + motion->pKeySet[motion->nCntKeySet].pKey[nCntParts].rot) - rot;

			// �p�x�̐��K��
			NormalizeAngle(&rotDest.x);
			NormalizeAngle(&rotDest.y);
			NormalizeAngle(&rotDest.z);

			// ���̍X�V
			m_ppParts[nCntParts]->SetPosDest(posDest);
			m_ppParts[nCntParts]->SetRotDest(rotDest);
		}

		// �ϐ��錾
		D3DXVECTOR3 addPos = D3DXVECTOR3(posDest / (float)(motion->pKeySet[motion->nCntKeySet].nFrame));
		D3DXVECTOR3 addRot = D3DXVECTOR3(rotDest / (float)(motion->pKeySet[motion->nCntKeySet].nFrame));

		// �ʒu�̉��Z
		pos += addPos;

		//	�����̉��Z
		rot += addRot;

		// �p�x�̐��K��
		NormalizeAngle(&rot.x);
		NormalizeAngle(&rot.y);
		NormalizeAngle(&rot.z);

		// ���̍X�V
		m_ppParts[nCntParts]->SetPos(pos);
		m_ppParts[nCntParts]->SetRot(rot);
	}

	// �t���[���J�E���g�̉��Z
	motion->nCntFrame++;

	if (motion->nCntFrame >= motion->pKeySet[motion->nCntKeySet].nFrame)
	{// �t���[���J�E���g���w��̃t���[�����𒴂����ꍇ
	 // �t���[�����̏�����
		motion->nCntFrame = 0;

		// �Đ����̃L�[�ԍ����̉��Z
		motion->nCntKeySet++;

		if (motion->nCntKeySet >= motion->nNumKey && motion->bLoop)
		{// �Đ����̃L�[���J�E���g���L�[���̍ő�l�𒴂����Ƃ��A���̃��[�V���������[�v���g�p���Ă���
		 // �Đ����̃L�[���J�E���g��������
			motion->nCntKeySet = 0;

		}
		else if (motion->nCntKeySet >= motion->nNumKey)
		{
			motion->nCntKeySet = 0;
			m_bMotion = false;
		}
	}
}

//========================================
// ���[�V�����u�����h
//========================================
void CMotion::MotionBlend(void)
{
	CMotion::Motion* motion = (m_motion + m_nNumMotion);

	for (int nCntParts = 0; nCntParts < m_nMaxParts; nCntParts++)
	{
		// �ϐ��錾
		D3DXVECTOR3 pos = m_ppParts[nCntParts]->GetPos();			// �ʒu
		D3DXVECTOR3 rot = m_ppParts[nCntParts]->GetRot();			// ����
		D3DXVECTOR3 posDest = m_ppParts[nCntParts]->GetPosDest();	// �ړI�̈ʒu
		D3DXVECTOR3 rotDest = m_ppParts[nCntParts]->GetRotDest();	// �ړI�̌���

		if (motion->nCntFrame == 0)
		{// �t���[���J�E���g��0�̎�
		 // �ϐ��錾
			D3DXVECTOR3 posOrigin = m_ppParts[nCntParts]->GetPosOrigin();		// ���̈ʒu
			D3DXVECTOR3 rotOrigin = m_ppParts[nCntParts]->GetRotOrigin();		// ���̌���

			// �ړI�̈ʒu�ƌ����̎Z�o
			CMotion::Key myKey = motion->pKeySet[motion->nCntKeySet].pKey[nCntParts];
			posDest = posOrigin + myKey.pos - pos;
			rotDest = rotOrigin + myKey.rot - rot;

			// �p�x�̐��K��
			NormalizeAngle(&rotDest.x);
			NormalizeAngle(&rotDest.y);
			NormalizeAngle(&rotDest.z);
			
			// ���̍X�V
			m_ppParts[nCntParts]->SetPosDest(posDest);
			m_ppParts[nCntParts]->SetRotDest(rotDest);
		}

		// �ϐ��錾
		D3DXVECTOR3 addPos = D3DXVECTOR3(posDest / (float)(MOTION_BLEND_FRAM));
		D3DXVECTOR3 addRot = D3DXVECTOR3(rotDest / (float)(MOTION_BLEND_FRAM));

		// �ʒu�̉��Z
		pos += addPos;

		//	�����̉��Z
		rot += addRot;

		// �p�x�̐��K��
		NormalizeAngle(&rot.x);
		NormalizeAngle(&rot.y);
		NormalizeAngle(&rot.z);

		// ���̍X�V
		m_ppParts[nCntParts]->SetPos(pos);
		m_ppParts[nCntParts]->SetRot(rot);
	}

	// �t���[���J�E���g�̉��Z
	motion->nCntFrame++;

	if (motion->nCntFrame >= MOTION_BLEND_FRAM)
	{// �t���[���J�E���g���w��̃t���[�����𒴂����ꍇ

		motion->nCntFrame = 0;	// �t���[�����̏�����
		motion->nCntKeySet++;	// �Đ����̃L�[�ԍ����̉��Z

		m_bMotionBlend = false;
	}
}

//========================================
// �p�[�c�ƃ��[�V�����̓ǂݍ���
//========================================
void CMotion::LoodMotion(const char *pFileName)
{
	// �ϐ��錾
	char aString[128] = {};			// �������r�p�̕ϐ�
	char g_aEqual[128] = {};		// ���ǂݍ��ݗp�ϐ�
	int	nCntKeySet = 0;				// KeySet�J�E���g
	int	nCntKey = 0;				// Key�J�E���g
	int nCntFileName = 0;			// �t�@�C����
	int nCntParts = 0;				// �p�[�c���̃J�E���g
	int nCntMotion = 0;				// ���[�V�������̃J�E���g

		// �t�@�C���|�C���^�̐錾
		FILE * pFile;

		//�t�@�C�����J��
		pFile = fopen(pFileName, "r");

		if (pFile != NULL)
		{//�t�@�C�����J�����ꍇ
			fscanf(pFile, "%s", &aString);

			while (strncmp(&aString[0], "SCRIPT", 6) != 0)
			{// �����񂪈�v�����ꍇ
				aString[0] = {};
				// ������̓ǂݍ���
				fscanf(pFile, "%s", &aString[0]);
			}
			while (strncmp(&aString[0], "END_SCRIPT", 10) != 0)
			{
				fscanf(pFile, "%s", &aString[0]);

				if (strncmp(&aString[0], "#", 1) == 0)
				{// ���ǂݍ���
					fgets(&aString[0], sizeof(aString), pFile);
				}

				if (strcmp(&aString[0], "MODEL_FILENAME") == 0)
				{// �t�@�C�����̓ǂݍ���
					fscanf(pFile, "%s", &g_aEqual[0]);
					fscanf(pFile, "%s", &m_partsFile[nCntFileName][0]);
					nCntFileName++;
				}

				if (strcmp(&aString[0], "CHARACTERSET") == 0)
				{// �L�����N�^�[�̓ǂݍ���
					while (strcmp(&aString[0], "END_CHARACTERSET") != 0)
					{
						fscanf(pFile, "%s", &aString[0]);

						if (strncmp(&aString[0], "#", 1) == 0)
						{// ���ǂݍ���
							fgets(&aString[0], sizeof(aString), pFile);
						}

						if (strcmp(&aString[0], "NUM_PARTS") == 0)
						{// �ǂݍ��ރp�[�c��
							fscanf(pFile, "%s", &g_aEqual[0]);
							fscanf(pFile, "%d", &m_nMaxParts);

							// �������̉��
							m_ppParts = new CParts*[m_nMaxParts];
							m_motion = new Motion[MYMAX_MOTION];
							for (int i = 0; i < MYMAX_MOTION; i++)
							{
								m_motion[i].pKeySet = NULL;
							}
							assert(m_ppParts != NULL && m_motion != NULL);

							for (int i = 0; i < m_nMaxParts; i++)
							{// �p�[�c�̐���
								m_ppParts[i] = CParts::Create();
							}
						}

						if (strcmp(&aString[0], "PARTSSET") == 0)
						{// �p�[�c�̓ǂݍ���
							while (strcmp(&aString[0], "END_PARTSSET") != 0)
							{
								fscanf(pFile, "%s", &aString[0]);

								if (strncmp(&aString[0], "#", 1) == 0)
								{// ���ǂݍ���
									fgets(&aString[0], sizeof(aString), pFile);
								}

								if (strcmp(&aString[0], "INDEX") == 0)
								{// �^�C�v�̓ǂݍ���
									int nType = -1;
									fscanf(pFile, "%s", &g_aEqual[0]);
									fscanf(pFile, "%d", &nType);

									// �}�e���A�����̎擾
									CModel::MODEL_MATERIAL *pMaterial = CModel::GetMaterial();

									for (int nCntModel = 0; nCntModel < CModel::GetMaxModel(); nCntModel++)
									{
										if (strcmp(&m_partsFile[nType][0], &pMaterial[nCntModel].aFileName[0]) == 0)
										{// ���f����ID�̐ݒ�
											m_ppParts[nCntParts]->SetModelID(nCntModel);
											break;
										}
									}
								}
								if (strcmp(&aString[0], "PARENT") == 0)
								{// �e�̓ǂݍ���
									int nIdxParent = -1;
									fscanf(pFile, "%s", &g_aEqual[0]);
									fscanf(pFile, "%d", &nIdxParent);

									if (nIdxParent != -1)
									{// �e�̃��f���̐ݒ�
										m_ppParts[nCntParts]->SetParent(m_ppParts[nIdxParent]);
									}
								}
								if (strcmp(&aString[0], "POS") == 0)
								{// �ʒu�̓ǂݍ���
									D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
									fscanf(pFile, "%s", &g_aEqual[0]);
									fscanf(pFile, "%f", &pos.x);
									fscanf(pFile, "%f", &pos.y);
									fscanf(pFile, "%f", &pos.z);
									m_ppParts[nCntParts]->SetPos(pos);
									m_ppParts[nCntParts]->SetPosOrigin(pos);
								}
								if (strcmp(&aString[0], "ROT") == 0)
								{// �����̓ǂݍ���
									D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
									fscanf(pFile, "%s", &g_aEqual[0]);
									fscanf(pFile, "%f", &rot.x);
									fscanf(pFile, "%f", &rot.y);
									fscanf(pFile, "%f", &rot.z);
									m_ppParts[nCntParts]->SetRot(rot);
									m_ppParts[nCntParts]->SetRotOrigin(rot);
								}
							}

							// �p�[�c�J�E���g�̃C���N�������g
							nCntParts++;
						}
					}
				}
				if (strcmp(&aString[0], "MOTIONSET") == 0)
				{// ���[�V�����̓ǂݍ���
					while (strcmp(&aString[0], "END_MOTIONSET") != 0)
					{
						fscanf(pFile, "%s", &aString[0]);

						if (strncmp(&aString[0], "#", 1) == 0)
						{// ���ǂݍ���
							fgets(&aString[0], sizeof(aString), pFile);
						}

						if (strcmp(&aString[0], "LOOP") == 0)
						{// ���[�v�L���̓ǂݍ���
							fscanf(pFile, "%s", &g_aEqual[0]);
							fscanf(pFile, "%d", (int*)(&m_motion[nCntMotion].bLoop));
						}
						if (strcmp(&aString[0], "NUM_KEY") == 0)
						{// �L�[���̓ǂݍ���
							fscanf(pFile, "%s", &g_aEqual[0]);
							fscanf(pFile, "%d", &m_motion[nCntMotion].nNumKey);

							// �������̊m��
							m_motion[nCntMotion].pKeySet = new KeySet[m_motion[nCntMotion].nNumKey];
							assert(m_motion[nCntMotion].pKeySet != NULL);

							for (int nCntNumKeySet = 0; nCntNumKeySet < m_motion[nCntMotion].nNumKey; nCntNumKeySet++)
							{
								m_motion[nCntMotion].pKeySet[nCntNumKeySet].pKey = new Key[m_nMaxParts];
								assert(m_motion[nCntMotion].pKeySet[nCntNumKeySet].pKey != NULL);
							}
						}
						if (strcmp(&aString[0], "KEYSET") == 0)
						{// �L�[�Z�b�g�̓ǂݍ���
							while (strcmp(&aString[0], "END_KEYSET") != 0)
							{
								fscanf(pFile, "%s", &aString[0]);

								if (strncmp(&aString[0], "#", 1) == 0)
								{// ���ǂݍ���
									fgets(&aString[0], sizeof(aString), pFile);
								}

								if (strcmp(&aString[0], "FRAME") == 0)
								{// �t���[�����̓ǂݍ���
									fscanf(pFile, "%s", &g_aEqual[0]);
									fscanf(pFile, "%d", &m_motion[nCntMotion].pKeySet[nCntKeySet].nFrame);
								}
								if (strcmp(&aString[0], "KEY") == 0)
								{// �L�[�̓ǂݍ���
									while (strcmp(&aString[0], "END_KEY") != 0)
									{
										fscanf(pFile, "%s", &aString[0]);

										if (strncmp(&aString[0], "#", 1) == 0)
										{// ���ǂݍ���
											fgets(&aString[0], sizeof(aString), pFile);
										}

										if (strcmp(&aString[0], "POS") == 0)
										{// �ʒu�̓ǂݍ���
											fscanf(pFile, "%s", &g_aEqual[0]);
											fscanf(pFile, "%f", &m_motion[nCntMotion].pKeySet[nCntKeySet].pKey[nCntKey].pos.x);
											fscanf(pFile, "%f", &m_motion[nCntMotion].pKeySet[nCntKeySet].pKey[nCntKey].pos.y);
											fscanf(pFile, "%f", &m_motion[nCntMotion].pKeySet[nCntKeySet].pKey[nCntKey].pos.z);
										}
										if (strcmp(&aString[0], "ROT") == 0)
										{// �����̓ǂݍ���
											fscanf(pFile, "%s", &g_aEqual[0]);
											fscanf(pFile, "%f", &m_motion[nCntMotion].pKeySet[nCntKeySet].pKey[nCntKey].rot.x);
											fscanf(pFile, "%f", &m_motion[nCntMotion].pKeySet[nCntKeySet].pKey[nCntKey].rot.y);
											fscanf(pFile, "%f", &m_motion[nCntMotion].pKeySet[nCntKeySet].pKey[nCntKey].rot.z);
										}
									}

									// �L�[�J�E���g�̃C���N�������g
									nCntKey++;
								}
							}

							// �L�[�J�E���g�̏�����
							nCntKey = 0;

							// �L�[�Z�b�g�J�E���g�̃C���N�������g
							nCntKeySet++;
						}
					}
					// �L�[�Z�b�g�J�E���g�̏�����
					nCntKeySet = 0;

					// �p�[�c���̃C���N�������g
					nCntMotion++;
				}
			}

			//�t�@�C�������
			fclose(pFile);
		}
		else
		{//�t�@�C�����J���Ȃ��ꍇ
			assert(false);
		}

		// ������
		Init();
}

//========================================
// �J�E���g���Z�b�g
//========================================
void CMotion::CntReset(const int nNumMotionOld)
{
	m_motion[nNumMotionOld].nCntFrame = 0;
	m_motion[nNumMotionOld].nCntKeySet = 0;
}

//=============================================================================
// ���[�V�������K��
//=============================================================================
float CMotion::NormalizeAngle(float *pAngle)
{
	if (*pAngle >= D3DX_PI)
	{// 3.14���傫��
		*pAngle -= D3DX_PI * 2.0f;
	}
	else if (*pAngle <= -D3DX_PI)
	{// -3.14��菬����
		*pAngle += D3DX_PI * 2.0f;
	}
	return *pAngle;
}
