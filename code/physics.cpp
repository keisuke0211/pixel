//========================================
// 
// 物理関連
// 
//========================================
//  *** physics.cpp ***
//========================================
#include "physics.h"

//========================================
// コンストラクタ
//========================================
CPhysics::CPhysics()
{

}

//========================================
// デストラクタ
//========================================
CPhysics::~CPhysics()
{

}
//========================================
// int型の値の制御処理
//========================================
void CPhysics::IntControl(int *pData, int nMax, int nMin)
{
	if (*pData > nMax)
	{// 最大値を上回っていた時、
	 // 最大値を代入
		*pData = nMax;
	}
	else if (*pData < nMin)
	{// 最小値を下回っていた時、
	 // 最小値を代入
		*pData = nMin;
	}
}

//========================================
// int型の値のループ制御処理
//========================================
void CPhysics::IntLoopControl(int *pData, int nMax, int nMin)
{
	if (*pData >= nMax)
	{// 最大値以上の時、
	 // 最小値を代入
		*pData = nMin;
	}
	else if (*pData < nMin)
	{// 最小値を下回っていた時、
	 // 最大値を代入
		*pData = nMax - 1;
	}
}

//========================================
// float型の値の制御処理
//========================================
void CPhysics::FloatControl(float *pData, float fMax, float fMin)
{
	if (*pData > fMax)
	{// 最大値を上回っていた時、
	 // 最大値を代入
		*pData = fMax;
	}
	else if (*pData < fMin)
	{// 最小値を下回っていた時、
	 // 最小値を代入
		*pData = fMin;
	}
}

//========================================
// float型の値のループ制御処理
//========================================
void CPhysics::FloatLoopControl(float *pData, float fMax, float fMin)
{
	if (*pData > fMax)
	{// 最大値を上回っていた時、
	 // 最大値分減算
		*pData -= (fMax - fMin);
	}
	else if (*pData < fMin)
	{// 最小値を下回っていた時、
	 // 最大値分加算
		*pData += (fMax - fMin);
	}
}

//========================================
// 2点の角度を求める
//========================================
float CPhysics::FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 targetPos)
{
	float fAngle;	// 角度

	fAngle = atan2f(targetPos.y - pos.y, targetPos.x - pos.x);

	fAngle -= (D3DX_PI * 0.5f);
	fAngle *= -1;

	return fAngle;
}

//========================================
// 向きの制御処理
//========================================
void CPhysics::RotControl(D3DXVECTOR3 *pRot)
{
	FloatLoopControl(&pRot->x, D3DX_PI, -D3DX_PI);
	FloatLoopControl(&pRot->y, D3DX_PI, -D3DX_PI);
	FloatLoopControl(&pRot->z, D3DX_PI, -D3DX_PI);
}