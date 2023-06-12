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
// マクロ定義
//****************************************
#define CAMERA_SPEED			(50)			// 移動速度（X・Z座標）

//****************************************
// クラス
//****************************************
class CCamera
{
public:

	// ***** 関数 *****
	CCamera();	// コンストラクタ
	~CCamera();	// デストラクタ

	HRESULT lnit(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新

	void SetCamera(void);	// 設定

private:

	// ***** 変数 *****
	D3DXMATRIX m_mtxProjection;		// プロジェクションマトリックス
	D3DXMATRIX m_mtxView;			// ビューマトリックス

	D3DXVECTOR3 m_posV;				// 現在の視点
	D3DXVECTOR3 m_posR;				// 現在の注視点
	D3DXVECTOR3 m_posOldV;			// 前回の視点
	D3DXVECTOR3 m_posOldR;			// 前回の注視点
	D3DXVECTOR3 m_vecU;				// 上方向ベクトル
	D3DXVECTOR3 m_rot;				// 向き

	D3DXVECTOR3 m_MousePos;			// 現在の視点
	D3DXVECTOR3 m_MousePosOld;		// 前回の視点
	int m_nCnt;
	float m_ra, m_rb, m_rc;
	float m_length;
};

#endif