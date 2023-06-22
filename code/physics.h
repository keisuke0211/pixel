//========================================
// 
// 物理関連
// 
//========================================
//  *** physics.h ***
//========================================
#ifndef _PHYSICS_H_
#define _PHYSICS_H_
#include "main.h"

//****************************************
// クラス
//****************************************
class CPhysics
{
public:

	// ***** 列挙型 *****

	// 4方向
	typedef enum
	{
		DIRECTION_UP,			// 上
		DIRECTION_DOWN,			// 下
		DIRECTION_LEFT,			// 左
		DIRECTION_RIGHT,		// 右
		DIRECTION_BACK,			// 奥
		DIRECTION_FRONT,		// 手前

		DIRECTION_LEFT_BACK,	// 左奥
		DIRECTION_LEFT_FRONT,	// 左手前
		DIRECTION_RIGHT_BACK,	// 右奥
		DIRECTION_RIGHT_FRONT,	// 右手前
		DIRECTION_MAX,
	}DIRECTION;

	// ***** 関数 *****
	CPhysics();		// コンストラクタ
	~CPhysics();	// デストラクタ

	void IntControl(int *pData, int nMax, int nMin);				// int型の値の制御処理
	void IntLoopControl(int *pData, int nMax, int nMin);			// int型の値のループ制御処理
	void FloatControl(float *pData, float fMax, float fMin);		// float型の値の制御処理
	void FloatLoopControl(float *pData, float fMax, float fMin);	// float型の値のループ制御処理

	float FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 targetPos);		// 2点の角度を求める
	void RotControl(D3DXVECTOR3 *pRot);								// 向きを制御

	float AngleDifference(float fAngle, float fTargetAngle);		// 角度の差を求める
	void ControlAngle(float *pAngle);								// 角度の制御

private:

};
#endif