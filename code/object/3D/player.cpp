//========================================
// 
// プレイヤー処理
// 
//========================================
// *** player.cpp ***
//========================================
#include "player.h"
#include "../../manager.h"
#include "../../camera.h"
#include "../../input.h"
#include "../../sound.h"
#include "../../physics.h"
#include "bullet.h"

//****************************************
// マクロ定義
//****************************************
#define JUMP_POWER		(7.5f)		// ジャンプ量
#define GRAVITY_MAG		(0.08f)		// 重力係数 0.08
#define GRAVITY_POWER	(8.5f)		// 重力加速度
#define ROT_DIAMETER	(0.15f)		// 回転倍率

#define ROT_FORCE_BY_CURSOR	(D3DXVECTOR3(0.0005f,0.00075f,0.0f))	// カーソルの回転力

// 定義
const float CPlayer::PLAYER_SPEED = 1.0f;

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
	m_Info.bMove = false;
	m_Info.bJump = false;
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

	m_Info.pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	// キー入力処理
	KeyInput();

	// 位置更新処理
	UpdatePos();

	// 向き/移動向き/目標向きを制御
	RotControl(&m_Info.rot);
	RotControl(&m_Info.moveRot);
	RotControl(&m_Info.targetRot);

	// 角度を目標角度に向けて推移する
	m_Info.rot.y += AngleDifference(m_Info.rot.y, m_Info.targetRot.y) * ROT_DIAMETER;

	SetRot(m_Info.rot);

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
// キー入力処理
//========================================
void CPlayer::KeyInput(void)
{
	// --- 取得 ---------------------------------
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// キーボード
	CInputMouse *pInputMouse = CManager::GetInputMouse();			// マウス
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();		// ジョイパット

	m_Info.bMove = true;

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
	else if (pInputKeyboard->GetPress(DIK_W)) { MoveKeyboard(DIRECTION_BACK); }				// 奥移動
	else if (pInputKeyboard->GetPress(DIK_S)) { MoveKeyboard(DIRECTION_FRONT); }			// 手前移動
	else
	{
		m_Info.bMove = false;
	}

	// ジャンプ
	if (pInputKeyboard->GetTrigger(DIK_SPACE) || pInputJoypad->GetJoypadTrigger(CInputJoypad::JOYKEY_A))
	{
		if (m_Info.bJump == false)
		{
			m_Info.bJump = true;	// ジャンプフラグを真にする
			m_Info.move.y += JUMP_POWER;
		}
	}

	// 攻撃
	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputMouse->GetTrigger(CInputMouse::MOUSE_LEFT) || pInputJoypad->GetJoypadTrigger(CInputJoypad::JOYKEY_B))
	{
		CBullet::Create(D3DXVECTOR3(m_Info.pos.x,m_Info.pos.y + 20,m_Info.pos.z),m_Info.rot);
	}

	// 位置更新
	MovePos(PLAYER_SPEED);
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
	case DIRECTION_LEFT			:m_Info.moveRot.y *= -0.5f; break;	// 左
	case DIRECTION_RIGHT		:m_Info.moveRot.y *= 0.5f;	break;	// 右
	case DIRECTION_BACK			:m_Info.moveRot.y *= 0.0f;	break;	// 奥
	case DIRECTION_FRONT		:m_Info.moveRot.y *= 1.0f;	break;	// 手前
	case DIRECTION_LEFT_BACK	:m_Info.moveRot.y *= -0.25f; break;	// 左奥
	case DIRECTION_LEFT_FRONT	:m_Info.moveRot.y *= -0.75f; break;	// 左手前
	case DIRECTION_RIGHT_BACK	:m_Info.moveRot.y *= 0.25f; break;	// 右奥
	case DIRECTION_RIGHT_FRONT	:m_Info.moveRot.y *= 0.75f; break;	// 右手前
	}
}

//========================================
// 移動処理
//========================================
void CPlayer::MovePos(float fMove)
{
	// --- 取得 ---------------------------------
	CCamera *pCamera = CManager::GetCamera();				// カメラ
	CInputMouse *pInputMouse = CManager::GetInputMouse();	// マウス

	D3DXVECTOR3 posV = pCamera->GetInfo().posV;	// 視点
	D3DXVECTOR3 posR = pCamera->GetInfo().posR;	// 注視点

	if (!m_Info.bMove || pInputMouse->GetPress(CInputMouse::MOUSE_RIGHT))
	{
		fMove = 0.0f;
	}

	if (m_Info.bMove)
	{
		// 視点から注視点までの角度
		float fAngle
			= FindAngle(D3DXVECTOR3(posV.x, posV.z, 0.0f), D3DXVECTOR3(posR.x, posR.z, 0.0f));

		m_Info.moveRot.y += fAngle;
	}

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

	//Ｙの移動量に重力を加算
	m_Info.move.y -= (GRAVITY_POWER - m_Info.move.y) * GRAVITY_MAG;

	// ブロックとの当たり判定
	Collision(m_Info.pos);


	SetPos(m_Info.pos);

	// 目標向きに移動向きを代入
	m_Info.targetRot = m_Info.moveRot;

	// カメラの注視点を設定
	pCamera->SetPosR(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 95, m_Info.pos.z));
}

//========================================
// ブロックとの当たり判定
//========================================
void CPlayer::Collision(D3DXVECTOR3 pos)
{
	for (int nCntObj = 0; nCntObj < GetNumAll(); nCntObj++)
	{
		// オブジェクトを取得
		CObject *pObj = GetObjectPointer(PRIO_OBJX, nCntObj);

		if (pObj != NULL)
		{// 使用されている時、

			// 種類を取得
			TYPE type = pObj->GetType();

			if (type == TYPE_BLOCK)
			{// 種類がブロックの時、

				// プレイヤーの各パーツの取得
				D3DXVECTOR3 PosOld = GetPosOld();	// 位置(過去)
				D3DXVECTOR3 Scale = GetSize();
				float fSize = 10.0f;


				// ブロックの取得
				D3DXVECTOR3 BlockPos = pObj->GetPos();	// 位置
				float BlockWidth = pObj->GetWidth();	// 幅
				float BlockHeight = pObj->GetHeight();	// 高さ
				float BlockDepth = pObj->GetDepth();	// 奥行き


				// --- 当たり判定 ----------------------------------------------

					/* X方向 */
				if ((pos.z + fSize) > (BlockPos.z - BlockDepth) &&
					(pos.z - fSize) < (BlockPos.z + BlockDepth) &&
					(pos.y + fSize) > (BlockPos.y - BlockHeight) &&
					(pos.y - fSize) < (BlockPos.y + BlockHeight))
				{// 奥辺と手前辺が相手の幅の内側の時、

					if ((pos.x + fSize) > (BlockPos.x - BlockWidth) &&
						(PosOld.x + fSize) <= (BlockPos.x - BlockWidth))
					{// 左からめり込んでいる時

						pos.x = (BlockPos.x - BlockWidth) - fSize;
					}
					else if ((pos.x - fSize) < (BlockPos.x + BlockWidth) &&
						(PosOld.x - fSize) >= (BlockPos.x + BlockWidth))
					{// 右からめり込んでいる時

						pos.x = (BlockPos.x + BlockWidth) + fSize;
					}
				}

				/* Y方向 */
				if ((pos.x + fSize) > (BlockPos.x - BlockWidth) &&
					(pos.x - fSize) < (BlockPos.x + BlockWidth) &&
					(pos.z + fSize) > (BlockPos.z - BlockDepth) &&
					(pos.z - fSize) < (BlockPos.z + BlockDepth))
				{// 左辺と右辺が相手の幅の内側の時、

					if ((pos.y + fSize) > (BlockPos.y - BlockHeight) &&
						(PosOld.y + fSize) <= (BlockPos.y - BlockHeight))
					{// 下からめり込んでいる時

						pos.y = (BlockPos.y - BlockHeight) - fSize;

						//プレイヤーが上昇中
						if (m_Info.move.y > 0.0f)
						{
							//Ｙの移動量を0に
							m_Info.move.y = 0.0f;
						}
					}
					else if ((pos.y - fSize) < (BlockPos.y + BlockHeight) &&
						(PosOld.y - fSize) >= (BlockPos.y + BlockHeight))
					{// 上からめり込んでいる時
						pos.y = (BlockPos.y + BlockHeight) + fSize;

						m_Info.move.y = 0.0f;
						m_Info.bJump = false;

					}
				}

				/* Z方向 */
				if ((pos.x + fSize) > (BlockPos.x - BlockWidth) &&
					(pos.x - fSize) < (BlockPos.x + BlockWidth) &&
					(pos.y + fSize) > (BlockPos.y - BlockHeight) &&
					(pos.y - fSize) < (BlockPos.y + BlockHeight))
				{// 奥辺と手前辺が相手の幅の内側の時、

					if ((pos.z + fSize) > (BlockPos.z - BlockDepth) &&
						(PosOld.z + fSize) <= (BlockPos.z - BlockDepth))
					{// 左からめり込んでいる時

						pos.z = (BlockPos.z - BlockDepth) - fSize;
					}
					else if ((pos.z - fSize) < (BlockPos.z + BlockDepth) &&
						(PosOld.z - fSize) >= (BlockPos.z + BlockDepth))
					{// 右からめり込んでいる時

						pos.z = (BlockPos.z + BlockDepth) + fSize;
					}
				}
			}
		}
	}
	m_Info.pos = pos;
}
