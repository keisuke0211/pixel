//========================================
// 
// �����֘A & ���ʏ��
// 
//========================================
//  *** physics.h ***
//========================================
#ifndef _PHYSICS_H_
#define _PHYSICS_H_
#include "../main.h"

//****************************************
// �N���X
//****************************************
class CPhysics
{
public:

	// ***** �񋓌^ *****

	// ���f�����
	enum MODEL
	{
		MODEL_GRASS_00 = 0,	// ���u���b�N 1�~1�~1
		MODEL_GRASS_01,		// ���u���b�N 3�~1�~1
		MODEL_GRASS_02,		// ���u���b�N 5�~1�~1
		MODEL_GRASS_03,		// ���u���b�N 3�~3�~1
		MODEL_GRASS_04,		// ���u���b�N 5�~5�~1
		MODEL_SOIL_00,		// �y�u���b�N 1�~1�~1
		MODEL_SOIL_01,		// �y�u���b�N 3�~1�~1
		MODEL_SOIL_02,		// �y�u���b�N 5�~1�~1
		MODEL_SOIL_03,		// �y�u���b�N 1�~3�~1
		MODEL_SOIL_04,		// �y�u���b�N 1�~5�~1
		MODEL_SOIL_05,		// �y�u���b�N 3�~1�~3
		MODEL_SOIL_06,		// �y�u���b�N 5�~1�~5
		MODEL_SOIL_07,		// �y�u���b�N 3�~3�~1
		MODEL_SOIL_08,		// �y�u���b�N 5�~5�~1
		MODEL_TNT_00,		// TNT(��)
		MODEL_BULLET,		// �e
		MODEL_PLAYER_00,	// �v���C���[ ��
		MODEL_PLAYER_01,	// �v���C���[ ��
		MODEL_PLAYER_02,	// �v���C���[ ����
		MODEL_PLAYER_03,	// �v���C���[ �E��
		MODEL_PLAYER_04,	// �v���C���[ ����
		MODEL_PLAYER_05,	// �v���C���[ �E��
		MODEL_ENEMY_00,		// ���G�l�~�[
		MODEL_EFFECT_00,	// �G�t�F�N�g�@���q
		MODEL_MAX
	};

	// �x�N�g���̎��
	enum VECTOR
	{
		VECTOR_X,		// X����
		VECTOR_Y,		// Y����
		VECTOR_Z,		// Z����
		VECTOR_NONE,	// ����
		VECTOR_MAX
	};

	// 4����
	enum DIRECTION
	{
		DIRECTION_UP,			// ��
		DIRECTION_DOWN,			// ��
		DIRECTION_LEFT,			// ��
		DIRECTION_RIGHT,		// �E
		DIRECTION_BACK,			// ��
		DIRECTION_FRONT,		// ��O

		DIRECTION_LEFT_BACK,	// ����
		DIRECTION_LEFT_FRONT,	// ����O
		DIRECTION_RIGHT_BACK,	// �E��
		DIRECTION_RIGHT_FRONT,	// �E��O
		DIRECTION_MAX,
	};

	// ***** �֐� *****
	CPhysics();		// �R���X�g���N�^
	virtual~CPhysics();	// �f�X�g���N�^

	void IntControl(int *pData, int nMax, int nMin);				// int�^�̒l�̐��䏈��
	void IntLoopControl(int *pData, int nMax, int nMin);			// int�^�̒l�̃��[�v���䏈��
	void FloatControl(float *pData, float fMax, float fMin);		// float�^�̒l�̐��䏈��
	void FloatLoopControl(float *pData, float fMax, float fMin);	// float�^�̒l�̃��[�v���䏈��

	float FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 targetPos);		// 2�_�̊p�x�����߂�
	void RotControl(D3DXVECTOR3 *pRot);								// �����𐧌�

	float AngleDifference(float fAngle, float fTargetAngle);		// �p�x�̍������߂�
	void ControlAngle(float *pAngle);								// �p�x�̐���

private:

};
#endif