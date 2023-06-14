//========================================
// 
// �����֘A
// 
//========================================
//  *** physics.cpp ***
//========================================
#include "physics.h"

//========================================
// �R���X�g���N�^
//========================================
CPhysics::CPhysics()
{

}

//========================================
// �f�X�g���N�^
//========================================
CPhysics::~CPhysics()
{

}
//========================================
// int�^�̒l�̐��䏈��
//========================================
void CPhysics::IntControl(int *pData, int nMax, int nMin)
{
	if (*pData > nMax)
	{// �ő�l�������Ă������A
	 // �ő�l����
		*pData = nMax;
	}
	else if (*pData < nMin)
	{// �ŏ��l��������Ă������A
	 // �ŏ��l����
		*pData = nMin;
	}
}

//========================================
// int�^�̒l�̃��[�v���䏈��
//========================================
void CPhysics::IntLoopControl(int *pData, int nMax, int nMin)
{
	if (*pData >= nMax)
	{// �ő�l�ȏ�̎��A
	 // �ŏ��l����
		*pData = nMin;
	}
	else if (*pData < nMin)
	{// �ŏ��l��������Ă������A
	 // �ő�l����
		*pData = nMax - 1;
	}
}

//========================================
// float�^�̒l�̐��䏈��
//========================================
void CPhysics::FloatControl(float *pData, float fMax, float fMin)
{
	if (*pData > fMax)
	{// �ő�l�������Ă������A
	 // �ő�l����
		*pData = fMax;
	}
	else if (*pData < fMin)
	{// �ŏ��l��������Ă������A
	 // �ŏ��l����
		*pData = fMin;
	}
}

//========================================
// float�^�̒l�̃��[�v���䏈��
//========================================
void CPhysics::FloatLoopControl(float *pData, float fMax, float fMin)
{
	if (*pData > fMax)
	{// �ő�l�������Ă������A
	 // �ő�l�����Z
		*pData -= (fMax - fMin);
	}
	else if (*pData < fMin)
	{// �ŏ��l��������Ă������A
	 // �ő�l�����Z
		*pData += (fMax - fMin);
	}
}

//========================================
// 2�_�̊p�x�����߂�
//========================================
float CPhysics::FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 targetPos)
{
	float fAngle;	// �p�x

	fAngle = atan2f(targetPos.y - pos.y, targetPos.x - pos.x);

	fAngle -= (D3DX_PI * 0.5f);
	fAngle *= -1;

	return fAngle;
}

//========================================
// �����̐��䏈��
//========================================
void CPhysics::RotControl(D3DXVECTOR3 *pRot)
{
	FloatLoopControl(&pRot->x, D3DX_PI, -D3DX_PI);
	FloatLoopControl(&pRot->y, D3DX_PI, -D3DX_PI);
	FloatLoopControl(&pRot->z, D3DX_PI, -D3DX_PI);
}