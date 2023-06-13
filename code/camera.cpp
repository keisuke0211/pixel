//========================================
// 
// カメラ処理
// 
//========================================
// *** camera.cpp ***
//========================================
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

//****************************************
// マクロ定義
//****************************************
#define CAMERA_ROT_FORCE_BY_CURSOR	(D3DXVECTOR3(0.0005f,0.00075f,0.0f))	// カーソルの回転力
#define CAMERA_ROT_FORCE_BY_STICK	(D3DXVECTOR3(0.004f,-0.006f,0.0f))		// スティックの回転力
#define CAMERA_SPIN_DAMP			(0.9f)									// 回転の減少値
#define CAMERA_SPEED				(50)									// 移動速度（X・Z座標）

//========================================
// コンストラクタ
//========================================
CCamera::CCamera()
{
	m_Info.posR = INIT_D3DXVECTOR3;		// 現在の視点
	m_Info.posV = INIT_D3DXVECTOR3;		// 現在の注視点
	m_Info.posOldR = INIT_D3DXVECTOR3;	// 前回の視点R3;
	m_Info.posOldV = INIT_D3DXVECTOR3;	// 前回の注視点R3;
	m_Info.vecU = INIT_VEC;				// 上方向ベクトル
	m_Info.rot = INIT_D3DXVECTOR3;		// 向き
	m_Info.spin = INIT_D3DXVECTOR3;		// 回転量
	m_Info.fDistance = INIT_FLOAT;		// 距離
	m_Info.fHeight = INIT_FLOAT;		// 高さ
	m_Info.fVerticalMove = INIT_FLOAT;	// 縦の移動量
}

//========================================
// デストラクタ
//========================================
CCamera::~CCamera()
{

}

//========================================
// 初期化
//========================================
HRESULT CCamera::lnit(void)
{
	m_Info.posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//カメラの位置
	m_Info.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//見る場所
	m_Info.posOldR = INIT_D3DXVECTOR3;	// 前回の視点R3;
	m_Info.posOldV = INIT_D3DXVECTOR3;	// 前回の注視点R3;
	m_Info.vecU = INIT_VEC;				// 上方向ベクトル
	m_Info.rot = INIT_D3DXVECTOR3;		// 向き
	m_Info.spin = INIT_D3DXVECTOR3;		// 回転力
	m_Info.fDistance = 100.0f;			// 距離
	m_Info.fHeight = 0.25f;				// 高さ
	m_Info.fVerticalMove = INIT_FLOAT;	// 縦の移動量

	return S_OK;
}

//========================================
// 終了
//========================================
void CCamera::Uninit(void)
{

}

//========================================
// 更新
//========================================
void CCamera::Update(void)
{
	// --- 取得---------------------------------
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// キーボード
	CInputMouse *pInputMouse = CManager::GetInputMouse();			// マウス
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();		// ジョイパット

	m_Info.rot += m_Info.spin;					// 向きを更新
	m_Info.spin *= CAMERA_SPIN_DAMP;			// 回転量を減衰
	m_Info.fHeight += m_Info.fVerticalMove;		// 高さを更新
	m_Info.fVerticalMove *= CAMERA_SPIN_DAMP;	// 縦方向の移動量を減衰

	// 過去の位置を代入
	m_Info.posOldV = m_Info.posV;
	m_Info.posOldR = m_Info.posR;

	if (pInputMouse->GetPress(CInputMouse::MOUSE_RIGHT) == true)
	{// マウスの右ボタンが押されている間

		 // カーソルの移動量に応じて回転
		AxisRotationCamera(DIRECTION_UP, pInputMouse->GetCursorMove().y * CAMERA_ROT_FORCE_BY_CURSOR.x);
		AxisRotationCamera(DIRECTION_LEFT, pInputMouse->GetCursorMove().x * CAMERA_ROT_FORCE_BY_CURSOR.y);
	}
}

//========================================
// 設定
//========================================
void CCamera::SetCamera(void)
{
	//デバイスの所得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_Info.mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_Info.mtxProjection,
		D3DXToRadian(90.0f),						/* 視野角 */
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	/*画面のアスペクト比*/
		10.0f,										/*Z値の最小値*/
		1000.0f);									/*Z値の最大値*/

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_Info.mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_Info.mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_Info.mtxView,
		&m_Info.posV,		/*視点*/
		&m_Info.posR,		/*注視点*/
		&m_Info.vecU);		/*上方向ベクトル*/

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_Info.mtxView);
}

//========================================
// カメラの回転処理
//========================================
void CCamera::AxisRotationCamera(DIRECTION drct, float fRot, int nIdx)
{
	// 方向に応じて向きの移動量を更新
	switch (drct)
	{
	case DIRECTION_UP:m_Info.fVerticalMove += fRot; break;
	case DIRECTION_DOWN:m_Info.fVerticalMove -= fRot; break;
	case DIRECTION_LEFT:m_Info.spin.y -= fRot; break;
	case DIRECTION_RIGHT:m_Info.spin.y += fRot; break;
	}
}

//========================================
// カメラの視点設定
//========================================
void CCamera::SetPosV(D3DXVECTOR3 pos, int nIdx)
{
	// 視点の位置を代入
	m_Info.posV = pos;

	// 注視点の位置を設定
	m_Info.posR.x = m_Info.posV.x + (sinf(m_Info.rot.y) * (m_Info.fDistance * (1.0f - fabsf(m_Info.fHeight))));
	m_Info.posR.y = m_Info.posV.y + (m_Info.fDistance * m_Info.fHeight);
	m_Info.posR.z = m_Info.posV.z + (cosf(m_Info.rot.y) * (m_Info.fDistance * (1.0f - fabsf(m_Info.fHeight))));
}

//========================================
// カメラの注視点設定
//========================================
void CCamera::SetPosR(D3DXVECTOR3 pos, int nIdx)
{
	// 注視点の位置を代入
	m_Info.posR = pos;

	// 視点の位置を設定
	m_Info.posV.x = m_Info.posR.x + (sinf(m_Info.rot.y) * (m_Info.fDistance * (1.0f - fabsf(m_Info.fHeight))));
	m_Info.posV.y = m_Info.posR.y + (m_Info.fDistance * m_Info.fHeight);
	m_Info.posV.z = m_Info.posR.z + (cosf(m_Info.rot.y) * (m_Info.fDistance * (1.0f - fabsf(m_Info.fHeight))));
}