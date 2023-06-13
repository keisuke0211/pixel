//========================================
// 
// カメラ処理
// 
//========================================
// *** camera.h ***
//========================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//****************************************
// クラス
//****************************************
class CCamera
{
public:

	// ***** 構造体 *****

	// カメラ情報
	typedef struct
	{
		D3DXMATRIX mtxProjection;	// プロジェクションマトリックス
		D3DXMATRIX mtxView;			// ビューマトリックス

		D3DXVECTOR3 posV;			// 現在の視点
		D3DXVECTOR3 posR;			// 現在の注視点
		D3DXVECTOR3 posOldV;		// 前回の視点
		D3DXVECTOR3 posOldR;		// 前回の注視点
		D3DXVECTOR3 vecU;			// 上方向ベクトル
		D3DXVECTOR3 rot;			// 向き
		D3DXVECTOR3 spin;			// 回転量

		float fDistance;			// 距離
		float fHeight;				// 高さ
		float fVerticalMove;		// 縦の移動量
	} Info;

	// ***** 関数 *****
	CCamera();	// コンストラクタ
	~CCamera();	// デストラクタ

	HRESULT lnit(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新

	/* 設定 */
	void SetCamera(void);							// カメラ
	void SetPosV(D3DXVECTOR3 pos, int nIdx = 0);	// 視点
	void SetPosR(D3DXVECTOR3 pos, int nIdx = 0);	// 注視点

	/* 取得 */
	Info GetInfo() { return m_Info; }			// プレイヤー情報

private:

	// ***** 列挙型 *****

	// 4方向
	typedef enum
	{
		DIRECTION_UP,			// 上
		DIRECTION_DOWN,			// 下
		DIRECTION_LEFT,			// 左
		DIRECTION_RIGHT,		// 右
		DIRECTION_MAX,
	}DIRECTION;

	// ***** 関数 *****

	void AxisRotationCamera(DIRECTION drct, float fRot, int nIdx = 0); //回転処理

	// ***** 変数 *****
	Info m_Info;		// カメラ

};

#endif