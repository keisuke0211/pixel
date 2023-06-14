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
#include "physics.h"

//****************************************
// �N���X
//****************************************
class CCamera : public CPhysics
{
public:

	// ***** �\���� *****

	// �J�������
	typedef struct
	{
		D3DXMATRIX mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
		D3DXMATRIX mtxView;			// �r���[�}�g���b�N�X

		D3DXVECTOR3 posV;			// ���݂̎��_
		D3DXVECTOR3 posR;			// ���݂̒����_
		D3DXVECTOR3 posOldV;		// �O��̎��_
		D3DXVECTOR3 posOldR;		// �O��̒����_
		D3DXVECTOR3 vecU;			// ������x�N�g��
		D3DXVECTOR3 rot;			// ����
		D3DXVECTOR3 spin;			// ��]��

		float fDistance;			// ����
		float fHeight;				// ����
		float fVerticalMove;		// �c�̈ړ���
	} Info;

	// ***** �֐� *****
	CCamera();	// �R���X�g���N�^
	~CCamera();	// �f�X�g���N�^

	HRESULT lnit(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V

	/* �ݒ� */
	void SetCamera(void);							// �J����
	void SetPosV(D3DXVECTOR3 pos, int nIdx = 0);	// ���_
	void SetPosR(D3DXVECTOR3 pos, int nIdx = 0);	// �����_

	/* �擾 */
	Info GetInfo() { return m_Info; }			// �v���C���[���

private:

	// ***** �֐� *****
	void AxisRotationCamera(DIRECTION drct, float fRot, int nIdx = 0); //��]����

	// ***** �ϐ� *****
	Info m_Info;		// �J����

};

#endif