//========================================
// 
// �J��������
// 
//========================================
// *** camera.h ***
//========================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//****************************************
// �}�N����`
//****************************************
#define CAMERA_SPEED			(50)			// �ړ����x�iX�EZ���W�j

//****************************************
// �N���X
//****************************************
class CCamera
{
public:

	// ***** �֐� *****
	CCamera();	// �R���X�g���N�^
	~CCamera();	// �f�X�g���N�^

	HRESULT lnit(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V

	void SetCamera(void);	// �ݒ�

private:

	// ***** �ϐ� *****
	D3DXMATRIX m_mtxProjection;		// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;			// �r���[�}�g���b�N�X

	D3DXVECTOR3 m_posV;				// ���݂̎��_
	D3DXVECTOR3 m_posR;				// ���݂̒����_
	D3DXVECTOR3 m_posOldV;			// �O��̎��_
	D3DXVECTOR3 m_posOldR;			// �O��̒����_
	D3DXVECTOR3 m_vecU;				// ������x�N�g��
	D3DXVECTOR3 m_rot;				// ����

	D3DXVECTOR3 m_MousePos;			// ���݂̎��_
	D3DXVECTOR3 m_MousePosOld;		// �O��̎��_
	int m_nCnt;
	float m_ra, m_rb, m_rc;
	float m_length;
};

#endif