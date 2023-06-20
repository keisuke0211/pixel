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
#include "../../physics.h"


// 定義
const float CPlayer::PLAYER_SPEED = 2.5f;
int CPlayer::nCnt = -1;

//========================================
// コンストラクタ
//========================================
CPlayer::CPlayer(int nPriority) : CMotionModel(nPriority)
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
	nCnt++;
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

	CMotionModel::Init();

	// 種類の設定
	SetType(TYPE_PLAYER);

	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 3.14f, 0.0f);
	m_Info.col = INIT_D3DXCOLOR;
	
	// 生成
	SetMotion("data\\GAMEDATA\\MODEL\\Player\\PLAYER_DATA.txt");
	SetPos(m_Info.pos);
	SetRot(m_Info.rot);

	return S_OK;
}

//========================================
// 終了
//========================================
void CPlayer::Uninit(void)
{
	CMotionModel::Uninit();
}

//========================================
// 更新
//========================================
void CPlayer::Update(void)
{
	// 移動処理
	KeyInput();

	// 位置更新処理
	UpdatePos();

	CMotionModel::Update();
}

//========================================
// 描画
//========================================
void CPlayer::Draw(void)
{
	CMotionModel::Draw();
}

//========================================
// キーボードの入力処理
//========================================
void CPlayer::KeyInput(void)
{
	// --- 取得 ---------------------------------
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// キーボード
	CInputMouse *pInputMouse = CManager::GetInputMouse();			// マウス
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();		// ジョイパット

	if (pInputKeyboard->GetPress(DIK_A))
	{
		if (pInputKeyboard->GetPress(DIK_W)) { MoveKeyboard(DIRECTION_LEFT_BACK); }			// 左奥移動
		else if (pInputKeyboard->GetPress(DIK_S)) { MoveKeyboard(DIRECTION_LEFT_FRONT); }	// 左手前移動
		else { MoveKeyboard(DIRECTION_LEFT); }		// 左移動
	}
	else if (pInputKeyboard->GetPress(DIK_D))
	{
		if (pInputKeyboard->GetPress(DIK_W)) { MoveKeyboard(DIRECTION_RIGHT_BACK); }		// 右奥移動
		else if (pInputKeyboard->GetPress(DIK_S)) { MoveKeyboard(DIRECTION_RIGHT_FRONT); }	// 右手前移動
		else { MoveKeyboard(DIRECTION_RIGHT); }		// 右移動
	}
	else if (pInputKeyboard->GetPress(DIK_W)) { MoveKeyboard(DIRECTION_BACK); }		// 奥移動
	else if (pInputKeyboard->GetPress(DIK_S)) { MoveKeyboard(DIRECTION_FRONT); }	// 手前移動
}

//========================================
// キーボードの移動処理
//========================================
void CPlayer::MoveKeyboard(DIRECTION drct)
{
	// --- 代入 ---------------------------------
	m_Info.moveRot = m_Info.rot;	// 移動向き

	// --- 移動 ---------------------------------

	// 移動向きに円周率を代入
	m_Info.moveRot.y = D3DX_PI;

	switch (drct)
	{
	case DIRECTION_LEFT:m_Info.moveRot.y *= -0.5f; break;			// 左
	case DIRECTION_RIGHT:m_Info.moveRot.y *= 0.5f; break;			// 右
	case DIRECTION_BACK:m_Info.moveRot.y *= 0.0f; break;			// 奥
	case DIRECTION_FRONT:m_Info.moveRot.y *= 1.0f; break;			// 手前
	case DIRECTION_LEFT_BACK:m_Info.moveRot.y *= -0.25f; break;		// 左奥
	case DIRECTION_LEFT_FRONT:m_Info.moveRot.y *= -0.75f; break;	// 左手前
	case DIRECTION_RIGHT_BACK:m_Info.moveRot.y *= 0.25f; break;		// 右奥
	case DIRECTION_RIGHT_FRONT:m_Info.moveRot.y *= 0.75f; break;	// 右手前
	}

	// 位置更新
	MovePos(PLAYER_SPEED);
}

//========================================
// 移動処理
//========================================
void CPlayer::MovePos(float fMove)
{
	// --- 取得 ---------------------------------
	CCamera *pCamera = CManager::GetCamera();		// カメラ

	D3DXVECTOR3 posV = pCamera->GetInfo().posV;	// 視点
	D3DXVECTOR3 posR = pCamera->GetInfo().posR;	// 注視点

	// 視点から注視点までの角度
	float fAngle
		= FindAngle(D3DXVECTOR3(posV.x, posV.z, 0.0f), D3DXVECTOR3(posR.x, posR.z, 0.0f));

	m_Info.moveRot.y += fAngle;

	m_Info.move.x += sinf(m_Info.moveRot.y) * fMove;
	m_Info.move.z += cosf(m_Info.moveRot.y) * fMove;
}

//========================================
// 位置更新
//========================================
void CPlayer::UpdatePos(void)
{
	// --- 取得 ---------------------------------
	CCamera *pCamera = CManager::GetCamera();		// カメラ

	// 移動量の代入
	m_Info.pos += m_Info.move;

	// 移動量の減衰
	m_Info.move.x *= 0.8f;
	m_Info.move.z *= 0.8f;

	SetPos(m_Info.pos);

	// 目標向きに移動向きを代入
	m_Info.targetRot = m_Info.moveRot;

	// カメラの注視点を設定
	pCamera->SetPosR(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 95, m_Info.pos.z));
}