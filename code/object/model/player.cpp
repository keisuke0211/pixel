//========================================
// 
// プレイヤー処理
// 
//========================================
// *** player.cpp ***
//========================================
#include "player.h"
#include "../../scene/game.h"
#include "../../scene/title.h"
#include "../../scene/pause.h"
#include "motion.h"
#include "../../manager.h"
#include "../../system/camera.h"
#include "../../system/input.h"
#include "../../system/sound.h"
#include "../../system/physics.h"
#include "bullet.h"
#include "enemy.h"
#include "block.h"
#include "bullet_cube.h"
#include "../EFFECT/particleX.h"
#include "../../scene/pause.h"
#include "../model/model.h"

//****************************************
// マクロ定義
//****************************************
#define JUMP_POWER		(7.0f)		// ジャンプ量
#define GRAVITY_MAG		(0.08f)		// 重力係数 0.08
#define GRAVITY_POWER	(9.5f)		// 重力加速度
#define POS_DIAMETER	(0.3f)		// 移動倍率
#define ROT_DIAMETER	(0.25f)		// 回転倍率
#define POS_RANGE_WIDE	(3)			// 判定の拡張
#define DUST_MAXCNT		(15)		// カウントの最大値
#define CUBE_LIFE1		(120)		// 壁や床に配置した場合の寿命

// 静的変数
bool CPlayer::m_bCubeSet = false;

// 定義
const float CPlayer::PLAYER_SPEED = 40.0f;

//========================================
// コンストラクタ
//========================================
CPlayer::CPlayer(int nPriority) : CMotionModel(nPriority)
{
	// 値をクリア
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.posOld = INIT_D3DXVECTOR3;
	m_Info.targetPos = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.rotOld = INIT_D3DXVECTOR3;
	m_Info.moveRot = INIT_D3DXVECTOR3;
	m_Info.targetRot = INIT_D3DXVECTOR3;
	m_Info.move = INIT_D3DXVECTOR3;
	m_Info.fWidth = INIT_FLOAT;
	m_Info.fHeight = INIT_FLOAT;
	m_Info.fDepth = INIT_FLOAT;
	m_Info.bMove = false;
	m_Info.bJump = false;
	m_Info.bMotion = false;
	m_Info.bAction = false;
	m_Info.bMovePosX = false;
	m_Info.bMovePosZ = false;
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
	CPlayer *pPlayer  = new CPlayer;

	// 初期化処理
	pPlayer->Init();

	return pPlayer;
}

//========================================
// 初期化
//========================================
HRESULT CPlayer::Init(void)
{
	m_bCubeSet = false;
	CCamera *pCamera = CManager::GetCamera();	// カメラの取得

	CMotionModel::Init();

	// 種類の設定
	SetType(TYPE_PLAYER);

	m_Info.pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	m_Info.targetPos = m_Info.pos;
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.col = INIT_D3DXCOLOR;
	
	// 生成
	SetPos(m_Info.pos);
	SetRot(m_Info.rot);
	SetColor(m_Info.col);

	// カメラの注視点を設定
	pCamera->SetPosR(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 95, m_Info.pos.z));
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
	bool bPause = CPause::IsPause();

	if (!bPause)
	{
		// 過去の位置・向きの更新
		m_Info.posOld = m_Info.pos;
		m_Info.rotOld = m_Info.rot;

		bool bStart = CTitle::IsStart();

		if (bStart)
		{
			// キー入力処理
			KeyInput();
		}
		// 位置更新処理
		UpdatePos();

		// カメラの当たり判定
		CameraCollision();

		// 向き/移動向き/目標向きを制御
		RotControl(&m_Info.rot);
		RotControl(&m_Info.moveRot);
		RotControl(&m_Info.targetRot);

		// 角度を目標角度に向けて推移する
		m_Info.rot.y += AngleDifference(m_Info.rot.y, m_Info.targetRot.y) * ROT_DIAMETER;

		SetRot(m_Info.rot);

		CMotionModel::Update();
	}
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
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// キーボード
	CMouse *pInputMouse = CManager::GetInputMouse();			// マウス
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// ジョイパット

	m_Info.bMove = true;

	if (pInputJoypad->GetRepeat(CJoypad::JOYKEY_LEFT) || pInputJoypad->GetStick(0).aAngleRepeat[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_LEFT])
	{
		MoveInput(DIRECTION_LEFT);
	}
	else if (pInputJoypad->GetRepeat(CJoypad::JOYKEY_RIGHT) || pInputJoypad->GetStick(0).aAngleRepeat[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_RIGHT])
	{
		MoveInput(DIRECTION_RIGHT);
	}
	else if (pInputJoypad->GetRepeat(CJoypad::JOYKEY_DOWN) || pInputJoypad->GetStick(0).aAngleRepeat[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_DOWN])
	{
		MoveInput(DIRECTION_FRONT);
	}
	else if (pInputJoypad->GetRepeat(CJoypad::JOYKEY_UP) || pInputJoypad->GetStick(0).aAngleRepeat[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_UP])
	{
		MoveInput(DIRECTION_BACK);
	}
	else if (pInputKeyboard->GetRepeat(DIK_A)) { MoveInput(DIRECTION_LEFT);}	// 左移動
	else if (pInputKeyboard->GetRepeat(DIK_D)) { MoveInput(DIRECTION_RIGHT);}	// 右移動
	else if (pInputKeyboard->GetRepeat(DIK_W)) { MoveInput(DIRECTION_BACK); }	// 奥移動
	else if (pInputKeyboard->GetRepeat(DIK_S)) { MoveInput(DIRECTION_FRONT); }	// 手前移動
	else
	{
		if (m_Info.bAction && (m_Info.move.x < 0.02f && m_Info.move.x > -0.02f) && (m_Info.move.z < 0.02f && m_Info.move.z > -0.02f))
		{
			CMotion *pMotion = CMotionModel::GetMotion();	// モーション情報
			pMotion->SetNumMotion(0, true);

			m_Info.bAction = false;
			m_Info.bMotion = false;
		}

		m_Info.bMove = false;
	}

	// ジャンプ
	if (pInputKeyboard->GetTrigger(DIK_SPACE) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_A))
	{
		if (m_Info.bJump == false)
		{
			m_Info.bJump = true;	// ジャンプフラグを真にする
			m_Info.move.y += JUMP_POWER;
		}
	}

	// 攻撃
	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputMouse->GetTrigger(CMouse::MOUSE_LEFT) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_B))
	{
		CBullet::Create(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 15, m_Info.pos.z), m_Info.rot);
	}

	// 最初の弾を止める
	BulletStop();

	// 位置更新
	MovePos(PLAYER_SPEED);
}

//========================================
// キーボードの移動処理
//========================================
void CPlayer::MoveInput(DIRECTION drct)
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
	CCamera *pCamera = CManager::GetCamera();		// カメラ
	D3DXVECTOR3 posV = pCamera->GetInfo().posV;		// 視点
	D3DXVECTOR3 posR = pCamera->GetInfo().posR;		// 注視点
	CMotion *pMotion = CMotionModel::GetMotion();	// モーション情報
	bool pPlayMotion = pMotion->GetMotion();		// モーション実行しているか

	if (!m_Info.bMove)
	{
		fMove = 0.0f;
	}

	if (m_Info.bMove)
	{
		// 視点から注視点までの角度
		float fAngle
			= FindAngle(D3DXVECTOR3(posV.x, posV.z, 0.0f), D3DXVECTOR3(posR.x, posR.z, 0.0f));

		ControlAngle(&fAngle);

		// 角度のを４分割にする
		{
			if (fAngle < D3DX_PI * -0.75 ||
				fAngle > D3DX_PI * 0.75)
			{
				fAngle = 3.14f;
			}
			else if (fAngle > D3DX_PI * -0.25 &&
				fAngle < D3DX_PI * 0.25)
			{
				fAngle = 0.0f;
			}
			else if (fAngle > D3DX_PI * -0.75 &&
				fAngle < D3DX_PI * -0.25)
			{
				fAngle = -1.57f;
			}
			else if (fAngle > D3DX_PI * 0.25 &&
				fAngle < D3DX_PI * 0.75)
			{
				fAngle = 1.57f;
			}
		}
		m_Info.moveRot.y += fAngle;

		// 移動モーション
		if (pMotion != NULL && !m_Info.bMotion)
		{
			pMotion->SetNumMotion(1,true);

			m_Info.bMotion = true;
			m_Info.bAction = true;
		}

		// 移動推移フラグ
		if (!m_Info.bMovePosX)
		{
			m_Info.bMovePosX = true;
		}
		if (!m_Info.bMovePosZ)
		{
			m_Info.bMovePosZ = true;
		}
	}
	else
	{
		if (pMotion != NULL && !m_Info.bMotion && !pPlayMotion)
		{
			pMotion->SetNumMotion(0,false);
		}
	}

	if (!pPlayMotion)
	{
		m_Info.bMotion = false;
	}

	float MoveX = round(sinf(m_Info.moveRot.y) * fMove);
	float MoveZ = round(cosf(m_Info.moveRot.y) * fMove);

	m_Info.targetPos.x += MoveX;
	m_Info.targetPos.z += MoveZ;

	if (m_Info.bMovePosX)
	{
		// X方向の当たり判定
		if (TargetCollision(PRIO_BLOCK, TYPE_BLOCK, VECTOR_X, m_Info.targetPos) ||
			TargetCollision(PRIO_CUBE, TYPE_CUBE, VECTOR_X, m_Info.targetPos) ||
			TargetCollision(PRIO_OBJECT, TYPE_ENEMY, VECTOR_X, m_Info.targetPos))
		{
			m_Info.targetPos.x -= MoveX;

			if (m_Info.pos.x > m_Info.targetPos.x - POS_RANGE_WIDE && m_Info.pos.x < m_Info.targetPos.x + POS_RANGE_WIDE)
			{
				m_Info.bMovePosX = false;
			}
		}
	}

	if (m_Info.bMovePosZ)
	{
		// Z方向の当たり判定
		if (TargetCollision(PRIO_BLOCK, TYPE_BLOCK, VECTOR_Z, m_Info.targetPos) ||
			TargetCollision(PRIO_CUBE, TYPE_CUBE, VECTOR_Z, m_Info.targetPos) ||
			TargetCollision(PRIO_OBJECT, TYPE_ENEMY, VECTOR_Z, m_Info.targetPos))
		{
			m_Info.targetPos.z -= MoveZ;

			if (m_Info.pos.z > m_Info.targetPos.z - POS_RANGE_WIDE && m_Info.pos.z < m_Info.targetPos.z + POS_RANGE_WIDE)
			{
				m_Info.bMovePosZ = false;
			}
		}
	}
}

//========================================
// 位置更新
//========================================
void CPlayer::UpdatePos(void)
{
	// --- 取得 ---------------------------------
	CCamera *pCamera = CManager::GetCamera();		// カメラ

	{
		//	移動推移
		if (m_Info.bMovePosX)
		{
			// 位置を目標位置に向けて推移する
			m_Info.pos.x += PosDifference(m_Info.pos.x, m_Info.targetPos.x) * POS_DIAMETER;

			if (m_Info.pos.x > m_Info.targetPos.x - POS_RANGE_WIDE && m_Info.pos.x < m_Info.targetPos.x + POS_RANGE_WIDE)
			{
				m_Info.pos.x = m_Info.targetPos.x;
				m_Info.bMovePosX = false;
			}
		}

		// X方向の当たり判定
		m_Info.pos = Collision(PRIO_BLOCK,TYPE_BLOCK,VECTOR_X, m_Info.pos);
		m_Info.pos = Collision(PRIO_CUBE, TYPE_CUBE, VECTOR_X, m_Info.pos);
		m_Info.pos = Collision(PRIO_OBJECT, TYPE_ENEMY, VECTOR_X, m_Info.pos);
	}

	{
		if (m_Info.bMovePosZ)
		{
			// 位置を目標位置に向けて推移する
			m_Info.pos.z += PosDifference(m_Info.pos.z, m_Info.targetPos.z) * POS_DIAMETER;

			if (m_Info.pos.z > m_Info.targetPos.z - POS_RANGE_WIDE && m_Info.pos.z < m_Info.targetPos.z + POS_RANGE_WIDE)
			{
				m_Info.pos.z = m_Info.targetPos.z;
				m_Info.bMovePosZ = false;
			}
		}

		// Z方向の当たり判定
		m_Info.pos = Collision(PRIO_BLOCK, TYPE_BLOCK, VECTOR_Z, m_Info.pos);
		m_Info.pos = Collision(PRIO_CUBE, TYPE_CUBE, VECTOR_Z, m_Info.pos);
		m_Info.pos = Collision(PRIO_OBJECT, TYPE_ENEMY, VECTOR_Z, m_Info.pos);

	}

	{
		// 移動量の代入
		m_Info.pos.y += m_Info.move.y;

		//Ｙの移動量に重力を加算
		m_Info.move.y -= (GRAVITY_POWER - m_Info.move.y) * GRAVITY_MAG;

		// Y方向の当たり判定
		m_Info.pos = Collision(PRIO_BLOCK, TYPE_BLOCK, VECTOR_Y, m_Info.pos);
		m_Info.pos = Collision(PRIO_CUBE, TYPE_CUBE, VECTOR_Y, m_Info.pos);
		m_Info.pos = Collision(PRIO_OBJECT, TYPE_ENEMY, VECTOR_Y, m_Info.pos);


		float fSize = 10.0f;
		// 当たり判定（落下死用）
		if ((m_Info.pos.y - fSize) < (-120) &&
			(m_Info.posOld.y - fSize) >= (-120))
		{// 落下したら
			m_Info.pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
			m_Info.targetPos = m_Info.pos;

			CModel::SetPlayerShadow(true);
		}

		if (m_Info.pos.y <= -12.5)
		{
			CModel::SetPlayerShadow(false);
		}
	}

	// 位置の設定
	SetPos(m_Info.pos);

	// 目標向きに移動向きを代入
	m_Info.targetRot = m_Info.moveRot;


	bool bExit = CBlock::IsExitCamera();

	if (!bExit)
	{
		// カメラの注視点を設定
		pCamera->SetPosR(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 95, m_Info.pos.z));
	}
}

//========================================
// モデルとの当たり判定
//========================================
D3DXVECTOR3 CPlayer::Collision(PRIO nPrio, TYPE nType, VECTOR vector, D3DXVECTOR3 pos)
{
	// 先頭オブジェクトを取得
	CObject *pObj = CObject::GetTop(nPrio);

	while (pObj != NULL)
	{// 使用されている時、

		// 次のオブジェクト
		CObject *pObjNext = pObj->GetNext();

		// 種類を取得
		TYPE type = pObj->GetType();

		// プレイヤーの各パーツの取得
		D3DXVECTOR3 PosOld = GetPosOld();	// 位置(過去)
		D3DXVECTOR3 RotOld = GetRotOld();	// 向き(過去)
		D3DXVECTOR3 Scale = GetSize();
		float fSizeXZ = 20.0f;
		float fSizeY = 10.0f;

		if (type == nType)
		{// 種類がブロックの時、

			// ブロックの取得
			D3DXVECTOR3 PairPos = pObj->GetPos();		// 位置
			D3DXVECTOR3 PairPosOld = pObj->GetPosOld();	// 位置(過去)
			D3DXVECTOR3 PairRot = pObj->GetRot();		// 向き
			D3DXVECTOR3 PairRotOld = pObj->GetRotOld();	// 向き(過去)

			float fPairWidth = pObj->GetWidth();	// 幅
			float fPairHeight = pObj->GetHeight();	// 高さ
			float fPairDepth = pObj->GetDepth();	// 奥行き

			fPairWidth = round(fPairWidth);
			fPairHeight = round(fPairHeight);
			fPairDepth = round(fPairDepth);

			// ゴールブロックだと
			if (type == TYPE_BLOCK)
			{
				// ダイナミックキャストする
				CBlock *pBlock = dynamic_cast<CBlock*>(pObj);

				int nBlockType = pBlock->GetBlockType();
				if (nBlockType == MODEL_GOAL)
				{
					fPairWidth *= 0.8f;
					fPairHeight *= 0.8f;
					fPairDepth *= 0.8f;

					// クリア
					{
						bool bClear = CTitle::IsClear();
						if (!bClear)
						{
							if (Collsion(pos, pBlock->GetBlockPos(), D3DXVECTOR3(fSizeXZ, fSizeY, fSizeXZ), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
							{
								CTitle::SetClear(true);
							}
						}
					}

					pObj = pObjNext;	// 次のオブジェクトを代入
					continue;
				}
			}

			// --- 当たり判定 ----------------------------------------------
			switch (vector)
			{
			case VECTOR_X: {	/* X方向 */

				if (CollsionX(pos, PairPos, D3DXVECTOR3(fSizeXZ, fSizeY, fSizeXZ), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
				{// 奥辺と手前辺が相手の幅の内側の時、

					if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fSizeXZ, fSizeY, fSizeXZ), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_LEFT))
					{// 左からめり込んでいる時
						pos.x = (PairPos.x - fPairWidth) - fSizeXZ;
					}
					else if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fSizeXZ, fSizeY, fSizeXZ), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_RIGHT))
					{// 右からめり込んでいる時
						pos.x = (PairPos.x + fPairWidth) + fSizeXZ;
					}
				}
			}
						   break;
			case VECTOR_Y: {	/* Y方向 */

				if (CollsionY(pos, PairPos, D3DXVECTOR3(fSizeXZ, fSizeY, fSizeXZ), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
				{// 左辺と右辺が相手の幅の内側の時、

					if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fSizeXZ, fSizeY, fSizeXZ), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_DOWN))
					{// 下からめり込んでいる時
						pos.y = (PairPos.y - fPairHeight) - fSizeY;

						if (nType != TYPE_ENEMY)
						{
							//プレイヤーが上昇中
							if (m_Info.move.y > 0.0f)
							{
								//Ｙの移動量を0に
								m_Info.move.y = 0.0f;
							}
						}
					}
					else if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fSizeXZ, fSizeY, fSizeXZ), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_UP))
					{// 上からめり込んでいる時

						if (nType != TYPE_CUBE)
						{
							pos.y = (PairPos.y + fPairHeight) + fSizeY;
						}
						else
						{
							pos.y = (PairPos.y + fPairHeight) + fSizeY;
						}

						m_Info.move.y = 0.0f;
						m_Info.bJump = false;
					}
				}
			}
						   break;
			case VECTOR_Z: {	/* Z方向 */

				if (CollsionZ(pos, PairPos, D3DXVECTOR3(fSizeXZ, fSizeY, fSizeXZ), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
				{// 奥辺と手前辺が相手の幅の内側の時、

					if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fSizeXZ, fSizeY, fSizeXZ), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_BACK))
					{// 後ろからめり込んでいる時
						pos.z = (PairPos.z - fPairDepth) - fSizeXZ;
					}
					else if (CollsionDirection(pos, PairPos, PosOld, PairPosOld, D3DXVECTOR3(fSizeXZ, fSizeY, fSizeXZ), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth), DIRECTION_FRONT))
					{// 前からめり込んでいる時
						pos.z = (PairPos.z + fPairDepth) + fSizeXZ;
					}
				}
			}
						   break;
			}
		}
		pObj = pObjNext;	// 次のオブジェクトを代入
	}
	return pos;
}

//========================================
// 移動先のブロックがあるか
//========================================
bool CPlayer::TargetCollision(PRIO nPrio, TYPE nType, VECTOR vector, D3DXVECTOR3 pos)
{
	bool bHit = false;

	// 先頭オブジェクトを取得
	CObject *pObj = CObject::GetTop(nPrio);

	while (pObj != NULL)
	{// 使用されている時、

	 // 次のオブジェクト
		CObject *pObjNext = pObj->GetNext();

		// 種類を取得
		TYPE type = pObj->GetType();

		// プレイヤーの各パーツの取得
		D3DXVECTOR3 PosOld = pos;			// 位置(過去)
		float fSizeXZ = 20.0f;
		float fSizeY = 10.0f;

		if (type == nType)
		{// 種類がブロックの時、

			// 相手の取得
			D3DXVECTOR3 PairPos = pObj->GetPos();		// 位置
			D3DXVECTOR3 PairPosOld = pObj->GetPosOld();	// 位置(過去)
			D3DXVECTOR3 PairRot = pObj->GetRot();		// 向き
			D3DXVECTOR3 PairRotOld = pObj->GetRotOld();	// 向き(過去)

			float fPairWidth = pObj->GetWidth();	// 幅
			float fPairHeight = pObj->GetHeight();	// 高さ
			float fPairDepth = pObj->GetDepth();	// 奥行き

			// --- 当たり判定 ----------------------------------------------
			switch (vector)
			{
			case VECTOR_X: {	/* X方向 */

				if (Collsion(pos, PairPos, D3DXVECTOR3(fSizeXZ, fSizeY, fSizeXZ), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
				{// 奥辺と手前辺が相手の幅の内側の時、

					bHit = true;
				}
			}
			   break;
			case VECTOR_Z: {	/* Z方向 */

				if (Collsion(pos, PairPos, D3DXVECTOR3(fSizeXZ, fSizeY, fSizeXZ), D3DXVECTOR3(fPairWidth, fPairHeight, fPairDepth)))
				{// 奥辺と手前辺が相手の幅の内側の時、

					bHit = true;
				}
			}
			   break;
			}
		}

		if (bHit)
		{
			return TRUE;
		}

		pObj = pObjNext;	// 次のオブジェクトを代入
	}
	return FALSE;
}

//========================================
// カメラの当たり判定
//========================================
void CPlayer::CameraCollision(void)
{

}

//========================================
// 弾停止
//========================================
void CPlayer::BulletStop(void)
{
	// --- 取得 ---------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// キーボード
	CMouse *pInputMouse = CManager::GetInputMouse();			// マウス
	CJoypad *pInputJoypad = CManager::GetInputJoypad();		// ジョイパット

	// 先頭オブジェクトを取得
	CObject *pObj = CObject::GetTop(PRIO_OBJECT);

	while (pObj != NULL)
	{// 使用されている時、

		 // 次のオブジェクト
		CObject *pObjNext = pObj->GetNext();

		TYPE type = pObj->GetType();	// 種類を取得

		if (type == TYPE_BULLET)
		{// 種類がバレットの時、

			// ダイナミックキャストする
			CBullet *pBullet = dynamic_cast<CBullet*>(pObj);


			if (pInputKeyboard->GetTrigger(DIK_E) || pInputMouse->GetTrigger(CMouse::MOUSE_4) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_X))
			{
				// ID取得
				int nID = pBullet->GetID();
				bool nCubeSet = false;

				// 先頭フラグの取得
				nCubeSet = CCube::GetLeadSet();

				if (!nCubeSet)
				{

					int nType = pBullet->GetType();
					D3DXVECTOR3 pos = pBullet->GetPos();

					// キューブの生成
					CCube::Create(nType, pos, CUBE_LIFE1);
					m_bCubeSet = true;

					// オブジェクト破棄
					pObj->Uninit();
				}
			}
		}
		pObj = pObjNext;	// 次のオブジェクトを代入
	}
}