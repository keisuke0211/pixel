//========================================
// 
// カメラ処理
// 
//========================================
// *** camera.cpp ***
//========================================
#include "camera.h"
#include "../manager.h"
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
	/* カメラ情報 */
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
	m_Info.nScreen = SCREEN_NONE;		// 投影モード

	/* 保存情報 */
	m_Save.posV = INIT_D3DXVECTOR3;		// 視点
	m_Save.posR = INIT_D3DXVECTOR3;		// 注視点
	m_Save.rot = INIT_D3DXVECTOR3;		// 向き
	m_Save.spin = INIT_D3DXVECTOR3;		// 回転量
	m_Save.fVerticalMove = INIT_FLOAT;	// 縦の移動量
	m_Save.fHeight = INIT_FLOAT;		// 高さ
	m_Save.fDistance = INIT_FLOAT;		// 距離
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
HRESULT CCamera::Init(void)
{
	/* カメラ情報 */
	m_Info.posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// カメラの位置
	m_Info.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 見る場所
	m_Info.posOldR = INIT_D3DXVECTOR3;				// 前回の視点R3;
	m_Info.posOldV = INIT_D3DXVECTOR3;				// 前回の注視点R3;
	m_Info.vecU = INIT_VEC;							// 上方向ベクトル
	m_Info.rot = INIT_D3DXVECTOR3;					// 向き
	m_Info.spin = INIT_D3DXVECTOR3;					// 回転力
	m_Info.fDistance = 100.0f;						// 距離
	m_Info.fHeight = 0.05f;							// 高さ
	m_Info.fVerticalMove = INIT_FLOAT;				// 縦の移動量
	m_Info.nScreen = SCREEN_3D;						// 投影モード

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

	// 過去の位置を代入
	m_Info.posOldV = m_Info.posV;
	m_Info.posOldR = m_Info.posR;

	if (pInputMouse->GetPress(CInputMouse::MOUSE_RIGHT))
	{// マウスの右ボタンが押されている間

		 // カーソルの移動量に応じて回転

		if (m_Info.nScreen == SCREEN_3D)
		{
			AxisRotationCamera(DIRECTION_UP, pInputMouse->GetCursorMove().y * CAMERA_ROT_FORCE_BY_CURSOR.x);
		}
		AxisRotationCamera(DIRECTION_LEFT, pInputMouse->GetCursorMove().x * CAMERA_ROT_FORCE_BY_CURSOR.y);	
	}
	else if (pInputJoypad->GetStick().aTplDiameter[CInputJoypad::STICK_TYPE_RIGHT] > 0.1f)
	{
		AxisRotationCamera(DIRECTION_UP, (cosf(pInputJoypad->GetStick().aAngle[CInputJoypad::STICK_TYPE_RIGHT]) * pInputJoypad->GetStick().aTplDiameter[CInputJoypad::STICK_TYPE_RIGHT]) * CAMERA_ROT_FORCE_BY_STICK.x);
		AxisRotationCamera(DIRECTION_LEFT, (sinf(pInputJoypad->GetStick().aAngle[CInputJoypad::STICK_TYPE_RIGHT]) * pInputJoypad->GetStick().aTplDiameter[CInputJoypad::STICK_TYPE_RIGHT]) * CAMERA_ROT_FORCE_BY_STICK.y);
	}

	m_Info.rot += m_Info.spin;					// 向きを更新
	m_Info.spin *= CAMERA_SPIN_DAMP;			// 回転量を減衰
	m_Info.fHeight += m_Info.fVerticalMove;		// 高さを更新
	m_Info.fVerticalMove *= CAMERA_SPIN_DAMP;	// 縦方向の移動量を減衰

	// 向きを制御
	RotControl(&m_Info.rot);

	// 高さを制御
	FloatControl(&m_Info.fHeight, D3DX_PI * 0.30f, D3DX_PI * 0.01f);

	//// 視点の位置設定
	//m_Info.posV.x = m_Info.posR.x + (sinf(m_Info.rot.y + D3DX_PI) * (m_Info.fDistance * (1.0 - fabsf(m_Info.fHeight))));
	//m_Info.posV.y = m_Info.posR.y + (m_Info.fDistance * m_Info.fHeight);
	//m_Info.posV.z = m_Info.posR.z + (cosf(m_Info.rot.y + D3DX_PI) * (m_Info.fDistance * (1.0 - fabsf(m_Info.fHeight))));

	if (pInputKeyboard->GetTrigger(DIK_Q) == true || pInputMouse->GetTrigger(CInputMouse::MOUSE_5) == true)
	{// マウスのサイドボタン2を押したら

		// 画面設定
		SetScreen();
	}

	if (pInputKeyboard->GetPress(DIK_UP))
	{
		m_Info.posV.z += 1.0f;
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

	switch (m_Info.nScreen)
	{
	case SCREEN_2D: {	// 平行投影
		D3DXMatrixOrthoLH(&m_Info.mtxProjection,
			SCREEN_WIDTH / 2,						/* 画面の幅 */
			SCREEN_HEIGHT / 2,						/* 画面の高さ */
			1.0f,									/* Z値の最小値 */
			1500.0f);								/* Z値の最大値 */
	}
		break;

	case SCREEN_3D: {	// 透視投影
		D3DXMatrixPerspectiveFovLH(&m_Info.mtxProjection,
			D3DXToRadian(90.0f),							/* 視野角 */
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		/*画面のアスペクト比*/
			10.0f,											/*Z値の最小値*/
			2000.0f);										/*Z値の最大値*/
	}
		break;
	}

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
// カメラの画面設定
//========================================
void CCamera::SetScreen(void)
{
	// 投影モードの切り替え

	switch (m_Info.nScreen)
	{
	case SCREEN_2D: {	// 平行投影
		
		// 保存情報を代入する
		m_Info.posV = m_Save.posV;						// 視点
		m_Info.posR = m_Save.posR;						// 注視点
		m_Info.rot  = m_Save.rot;						// 向き
		m_Info.spin = m_Save.spin;						// 回転量
		m_Info.fHeight = m_Save.fHeight;				// 高さ
		m_Info.fDistance = m_Save.fDistance;			// 距離
		m_Info.fVerticalMove = m_Save.fVerticalMove;	// 縦の移動量

		m_Info.nScreen = SCREEN_3D;
	}
	 break;

	case SCREEN_3D: {	// 透視投影
		
		// 情報を保存する
		m_Save.posV = m_Info.posV;						// 視点
		m_Save.posR = m_Info.posR;						// 注視点
		m_Save.rot	= m_Info.rot;						// 向き
		m_Save.spin	= m_Info.spin;						// 回転量
		m_Save.fHeight = m_Info.fHeight;				// 高さ
		m_Save.fDistance = m_Info.fDistance;			// 距離
		m_Save.fVerticalMove = m_Info.fVerticalMove;	// 縦の移動量

		// 向きを初期化
		m_Info.rot.y = 0.0f;

		m_Info.nScreen = SCREEN_2D;
	}
	 break;
	}
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