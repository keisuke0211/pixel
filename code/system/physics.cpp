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

	fAngle = fAngle;

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

//========================================
// 角度の差を求める
//========================================
float CPhysics::AngleDifference(float fAngle, float fTargetAngle)
{
	float fAngleDifference = 0.0f;	// 角度の差

	// 角度を制御する
	ControlAngle(&fAngle);

	if ((fAngle >= 0.0f) && (fTargetAngle >= 0.0f))
	{// どちらの角度もプラスの時、
	 // 角度の差を設定
		fAngleDifference = fTargetAngle - fAngle;

		return fAngleDifference;
	}
	else if ((fAngle <= 0.0f) && (fTargetAngle <= 0.0f))
	{// どちらの角度もマイナスの時、
	 // 角度の差を設定
		fAngleDifference = fTargetAngle - fAngle;

		return fAngleDifference;
	}

	if ((fAngle >= 0.0f) && (fTargetAngle <= 0.0f))
	{// 角度がプラスで、目標角度がマイナスの時、
		if (fAngle - D3DX_PI <= fTargetAngle)
		{// 目標角度が下側に近い時、
		 // 角度の差を設定
			fAngleDifference = fTargetAngle - fAngle;
		}
		else if (fAngle - D3DX_PI >= fTargetAngle)
		{// 目標角度が上側に近い時、
		 // 角度の差を設定
			fAngleDifference = (D3DX_PI - fAngle) + (D3DX_PI + fTargetAngle);
		}
	}

	if ((fAngle <= 0.0f) && (fTargetAngle >= 0.0f))
	{// 角度がマイナスで、目標角度がプラスの時、
		if (fAngle + D3DX_PI >= fTargetAngle)
		{// 目標角度が下側に近い時、
		 // 角度の差を設定
			fAngleDifference = fTargetAngle - fAngle;
		}
		else if (fAngle + D3DX_PI <= fTargetAngle)
		{// 目標角度が上側に近い時、
		 // 角度の差を設定
			fAngleDifference = -(D3DX_PI + fAngle) - (D3DX_PI - fTargetAngle);
		}
	}

	return fAngleDifference;
}

//========================================
// 角度を制御する
//========================================
void CPhysics::ControlAngle(float *pAngle)
{
	if (*pAngle > D3DX_PI)
	{// プラスの円周率を上回っている時、
		*pAngle = (D3DX_PI - (*pAngle - D3DX_PI)) * -1;
	}
	else if (*pAngle < -D3DX_PI)
	{// マイナスの円周率を下回っている時、
		*pAngle = (D3DX_PI + (*pAngle + D3DX_PI));
	}
}
