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

// コンストラクタ
CCamera::CCamera()
{
	m_posR = INIT_D3DXVECTOR3;		// 現在の視点
	m_posV = INIT_D3DXVECTOR3;		// 現在の注視点
	m_posOldR = INIT_D3DXVECTOR3;	// 前回の視点R3;
	m_posOldV = INIT_D3DXVECTOR3;	// 前回の注視点R3;
	m_vecU = INIT_VEC;				// 上方向ベクトル
	m_rot = INIT_D3DXVECTOR3;		// 向き
	m_ra = INIT_FLOAT;
	m_rb = INIT_FLOAT;
	m_rc = INIT_FLOAT;
	m_length = INIT_FLOAT;

	m_MousePos = INIT_D3DXVECTOR3;
	m_MousePosOld = INIT_D3DXVECTOR3;
	m_nCnt = 0;
}

// デストラクタ
CCamera::~CCamera()
{

}

//========================================
// 初期化
//========================================
HRESULT CCamera::lnit(void)
{
	m_posV = D3DXVECTOR3(0.0f, 100.0f, -120.0f);	//カメラの位置
	m_posR = D3DXVECTOR3(0.0f, 100.0f, 0.0f);		//見る場所
	m_posOldR = INIT_D3DXVECTOR3;	// 前回の視点R3;
	m_posOldV = INIT_D3DXVECTOR3;	// 前回の注視点R3;
	m_vecU = INIT_VEC;				// 上方向ベクトル
	m_rot = INIT_D3DXVECTOR3;		// 向き

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
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// キーボードの取得
	CInputMouse *pInputMouse = CManager::GetInputMouse();			// マウスの取得
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();		// ジョイパットの取得

	float MoveX, MoveY;
	int MoveZ;

	m_nCnt++;
	if ((m_nCnt % 2) == 0)
	{
		// 過去の位置
		m_MousePosOld = pInputMouse->GetPos();
	}

	// 現在の位置
	m_MousePos = pInputMouse->GetPos();

	// 過去の位置を代入
	m_posOldV = m_posV;
	m_posOldR = m_posR;

	// 距離の計算
	m_ra = m_posV.x - m_posR.x;
	m_rb = m_posV.z - m_posR.z;
	m_length = sqrtf(m_ra * m_ra + m_rb * m_rb);


	MoveX = m_MousePos.x - m_MousePosOld.x;
	MoveY = m_MousePos.y - m_MousePosOld.y;

	// 移動
	if (pInputMouse->GetPress(CInputMouse::MOUSE_LEFT) == true && pInputMouse->GetPress(CInputMouse::MOUSE_RIGHT) == true)
	{
		m_posV.x += MoveX;
		m_posV.z += MoveY;

		m_posR.x += MoveX;
		m_posR.z += MoveY;

		MoveZ = pInputMouse->GetWheel();

		if (MoveZ > 0 || MoveZ < 0)
		{
			float MoveRot;

			if (MoveZ >= 0)
			{
				MoveRot = 0.0f;
			}
			else if (MoveZ <= 0)
			{
				MoveRot = 3.1425f;
			}

			m_posV.x += sinf(MoveRot - (m_rot.z * D3DX_PI)) * CAMERA_SPEED;
			m_posV.z += cosf(MoveRot - (m_rot.z * D3DX_PI)) * CAMERA_SPEED;

			m_posR.x += sinf(MoveRot - (m_rot.z * D3DX_PI)) * CAMERA_SPEED;
			m_posR.z += cosf(MoveRot - (m_rot.z * D3DX_PI)) * CAMERA_SPEED;
		}
	}
	else if (pInputMouse->GetPress(CInputMouse::MOUSE_RIGHT) == true)
	{// 上下の移動
		m_rot.z += MoveX / 100;

		MoveZ = pInputMouse->GetWheel();

		if (MoveZ > 0 || MoveZ < 0)
		{
			float MoveRot;

			if (MoveZ >= 0)
			{
				MoveRot = 1.0f;
			}
			else if (MoveZ <= 0)
			{
				MoveRot = -1.0f;
			}

			m_posV.y += MoveRot;
			m_posR.y += MoveRot;
		}
	}
	else if (pInputMouse->GetPress(CInputMouse::MOUSE_LEFT) == true)
	{//横の回転・視点
		m_rot.z += MoveX / 100;

		m_posV.x = m_posR.x + sinf(D3DX_PI * (1.0f - m_rot.z)) * m_length;
		m_posV.z = m_posR.z + cosf(D3DX_PI * (1.0f - m_rot.z)) * m_length;
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
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(90.0f),						/* 視野角 */
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	/*画面のアスペクト比*/
		10.0f,										/*Z値の最小値*/
		1000.0f);									/*Z値の最大値*/

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,		/*視点*/
		&m_posR,		/*注視点*/
		&m_vecU);		/*上方向ベクトル*/

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}