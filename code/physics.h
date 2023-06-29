//========================================
// 
// 物理関連 & 共通情報
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

	// モデル種類
	typedef enum
	{
		MODEL_GRASS_00 = 0,	// 草ブロック 1×１×1
		MODEL_SOIL_00,		// 土ブロック 1×１×1
		MODEL_BULLET,		// 弾
		MODEL_PLAYER_00,	// プレイヤー 体
		MODEL_PLAYER_01,	// プレイヤー 頭
		MODEL_PLAYER_02,	// プレイヤー 左手
		MODEL_PLAYER_03,	// プレイヤー 右手
		MODEL_PLAYER_04,	// プレイヤー 左足
		MODEL_PLAYER_05,	// プレイヤー 右足
		MODEL_ENEMY_00,		// 仮エネミー
		MODEL_EFFECT_00,	// エフェクト　粒子
		MODEL_MAX
	}MODEL;

	// ベクトルの種類
	typedef enum
	{
		VECTOR_X,		// X方向
		VECTOR_Y,		// Y方向
		VECTOR_Z,		// Z方向
		VECTOR_NONE,	// 無し
		VECTOR_MAX
	}VECTOR;

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