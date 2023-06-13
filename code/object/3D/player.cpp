//========================================
// 
// プレイヤー処理
// 
//========================================
// *** player.cpp ***
//========================================
#include "player.h"
#include "../../manager.h"
#include "../../renderer.h"
#include "../../camera.h"
#include "../../input.h"
#include "../../sound.h"
#include "../../camera.h"

// 定義
const float CPlayer::PLAYER_SPEED = 2.5f;

//========================================
// コンストラクタ
//========================================
CPlayer::CPlayer(int nPriority) : CObjectX(nPriority)
{
	// 値をクリア
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.moveRot = INIT_D3DXVECTOR3;
	m_Info.targetRot = INIT_D3DXVECTOR3;
	m_Info.move = INIT_D3DXVECTOR3;
	m_Info.fWidth = INIT_FLOAT;
	m_Info.fHeight = INIT_FLOAT;
	m_Info.fDepth = INIT_FLOAT;
}

//========================================
// デストラクタ
//========================================
CPlayer::~CPlayer()
{

}

//========================================
// 生成
//========================================
CPlayer *CPlayer::Create(void)
{
	CPlayer *pPlayer = NULL;

	if (pPlayer != NULL)
	{
		return pPlayer;
	}

	// オブジェクト2Dの生成
	pPlayer = new CPlayer;

	// 初期化処理
	pPlayer->Init();

	return pPlayer;
}

//========================================
// 初期化
//========================================
HRESULT CPlayer::Init(void)
{
	CCamera *pCamera = CManager::GetCamera();	// カメラの取得

	CObjectX::Init();

	// 種類の設定
	SetType(TYPE_PLAYER);

	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f,0.0f);
	m_Info.col = INIT_D3DXCOLOR;
	
	// 生成
	SetPos(m_Info.pos);
	SetSize();
	SetRot(m_Info.rot);

	return S_OK;
}

//========================================
// 終了
//========================================
void CPlayer::Uninit(void)
{
	CObjectX::Uninit();
}

//========================================
// 更新
//========================================
void CPlayer::Update(void)
{
	// 移動処理
	MovePos();

	// 位置更新
	UpdatePos();

	CObjectX::Update();
}

//========================================
// 描画
//========================================
void CPlayer::Draw(void)
{
	CObjectX::Draw();
}

//========================================
// 移動処理
//========================================
void CPlayer::MovePos(void)
{
	// --- 代入 ---------------------------------
	m_Info.moveRot = m_Info.rot;	// 移動向き

	// --- 取得 ---------------------------------
	CCamera *pCamera = CManager::GetCamera();						// カメラ
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// キーボード
	CInputMouse *pInputMouse = CManager::GetInputMouse();			// マウス
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();		// ジョイパット

	
	// --- 移動 ---------------------------------
	if (pInputKeyboard->GetPress(DIK_D) == true || pInputJoypad->GetJoypadPress(CInputJoypad::JOYKEY_RIGHT, 0) == true)
	{// 右
		m_Info.moveRot.y = D3DX_PI;
		m_Info.moveRot.y *= 0.5f;

		float fAngle;	// 角度

		fAngle = atan2f(pCamera->GetInfo().posR.z - pCamera->GetInfo().posV.z, pCamera->GetInfo().posR.x - pCamera->GetInfo().posV.x);

		fAngle -= (D3DX_PI * 0.5f);
		fAngle *= -1;

		m_Info.moveRot.y += fAngle;

		m_Info.move.x += sinf(m_Info.moveRot.y) * PLAYER_SPEED;
		m_Info.move.z += cosf(m_Info.moveRot.y) * PLAYER_SPEED;
	}
	else if (pInputKeyboard->GetPress(DIK_A) == true || pInputJoypad->GetJoypadPress(CInputJoypad::JOYKEY_LEFT, 0) == true)
	{// 左
		m_Info.move.x -= PLAYER_SPEED;
	}
	else if (pInputKeyboard->GetPress(DIK_W) == true || pInputJoypad->GetJoypadPress(CInputJoypad::JOYKEY_UP, 0) == true)
	{// 上
		m_Info.move.z += PLAYER_SPEED;
	}
	else if (pInputKeyboard->GetPress(DIK_S) == true || pInputJoypad->GetJoypadPress(CInputJoypad::JOYKEY_DOWN, 0) == true)
	{// 下
		m_Info.move.z -= PLAYER_SPEED;
	}

	// 移動量の代入
	m_Info.pos += m_Info.move;

	// 移動量の減衰
	m_Info.move.x *= 0.8f;
	m_Info.move.z *= 0.8f;

	SetPos(m_Info.pos);

	// カメラの注視点を設定
	pCamera->SetPosR(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 95, m_Info.pos.z));
}
//========================================
// 位置更新
//========================================
void CPlayer::UpdatePos(void)
{


	// 目標向きに移動向きを代入
	m_Info.targetRot = m_Info.moveRot;
}