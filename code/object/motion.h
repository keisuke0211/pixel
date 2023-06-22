//========================================
// 
// ���[�V��������
// 
//========================================
// *** motion.h ***
//========================================
#include "../main.h"

#ifndef _MOTION_H_
#define _MOTION_H_

//****************************************
// �O���錾
//****************************************
class CModel;
class CParts;

//****************************************
// �N���X
//****************************************
class CMotion
{
public:

	// ***** ��` *****
	static const unsigned int MYMAX_MOTION = 128;		// ���[�V�������̍ő吔
	static const unsigned int MAX_MODEL_PARTS = 128;	// ���f�����̍ő吔
	static const unsigned int MAX_KEY = 64;				// �L�[�̍ő吔
	static const unsigned int MAX_KEYSET = 64;			// �L�[�ݒ�̍ő吔
	static const unsigned int MOTION_BLEND_FRAM = 12;	// ���[�V�����u�����h�̃t���[����	

	// ***** �\���� *****

	// �L�[���
	typedef struct
	{
		D3DXVECTOR3		pos;	// ���݈ʒu
		D3DXVECTOR3		rot;	// ���݂̌���
	}Key;

	// �L�[�ݒ�
	typedef struct
	{
		int	nFrame;		// �t���[����
		Key	*pKey;		// �L�[���
	}KeySet;

	// ���[�V�����ݒ�
	typedef struct
	{
		int		nNumKey;		// �L�[��
		int		nCntKeySet;		// �L�[�Z�b�g�J�E���g
		int		nCntFrame;		// �t���[���J�E���g
		bool	bLoop;			// ���[�v�g�p��
		bool	bMotion;		// ���[�V�������s���Ă��邩
		KeySet	*pKeySet;		// �L�[�ݒ���
	}Motion;



	// ***** �֐� *****

	CMotion(const char *pFileName);	// �R���X�g���N�^
	~CMotion();						// �f�X�g���N�^

	/* ���C�� */
	void Update(void);		// �X�V
	void Uninit(void);		// �I��

	/* �p�[�c */

	// �ݒ�
	void SetParts(D3DXMATRIX mtxWorld, const bool IsColor, const D3DXCOLOR color);

	// ���̏ꏊ�ɔz�u
	void SetPartsOrigin(void);	

	/* ���[�V���� */
	void SetMotion(const int nCntMotionSet);	// �����ݒ�
	void SetNumMotion(const int nNumMotion);	// ���[�V�����ԍ��̐ݒ�

	// ���[�V���������s���Ă��邩�̐ݒ�
	void SetUseMotion(bool bMotion) { m_bMotion = bMotion; }

	// ���[�V�����u�����h�����s���Ă��邩�ݒ�
	void SetMotionBlend(bool bMotionBlend) { m_bMotionBlend = bMotionBlend; }

	/* �擾 */
	int GetMaxParts(void) { return m_nMaxParts; }		// �p�[�c�̍ő吔
	bool GetMotion(void) { return m_bMotion; }			// ���[�V���������s���Ă��邩
	bool GetMotionBlend() { return m_bMotionBlend; }	// ���[�V�����u�����h�����s���Ă��邩

	float NormalizeAngle(float *pAngle);				// �p�x�̐��K��

private:

	// ***** �֐� *****
	void Init(void);							// ������
	void PlayMotion(void);						// ���[�V�����̍Đ�
	void MotionBlend(void);						// ���[�V�����u�����h
	void LoodMotion(const char *pFileName);		// ���[�V�����ǂݍ���
	void CntReset(const int nNumMotionOld);		// �J�E���g���Z�b�g

	// ***** �ϐ� *****
	CModel		*m_pParent;								// �e
	Motion		*m_motion;								// ���[�V����
	CParts		**m_ppParts;							// �p�[�c
	char		m_partsFile[MAX_MODEL_PARTS][0xff];		// �p�[�c��X�t�@�C����
	int			m_nMaxParts;							// �p�[�c��
	int			m_nNumMotion;							// �������[�V����
	bool		m_bMotion;								// ���[�V�������s����
	bool		m_bMotionBlend;							// ���[�V�����u�����h
};

#endif