//========================================
// 
// プレイヤー処理
// 
//========================================
// *** player.cpp ***
//========================================
#include "player2D.h"
#include "../../manager.h"
#include "../../renderer.h"
#include "../../input.h"
#include "../../sound.h"
#include "bullet.h"
#include "../object2D.h"

//****************************************
// マクロ定義
//****************************************
#define JUMP_POWER		(-40.0f)// ジャンプ量
#define GRAVITY_MAG		(0.08f)	// 重力係数
#define GRAVITY_POWER	(9.0f)	// 重力加速度

// 定義
const float CPlayer2D::PLAYER_SPEED = 2.5f;

// 静的メンバ変数
LPDIRECT3DTEXTURE9 CPlayer2D::m_pTexture[CPlayer2D::MAX_TEXTURE] = { NULL };
int CPlayer2D::m_nTexture = -1;

// コンストラクタ
CPlayer2D::CPlayer2D(int nPriority) : CObject2D(nPriority)
{
	// 値をクリア
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.move = INIT_D3DXVECTOR3;
	m_Info.fWidth = INIT_FLOAT;
	m_Info.fHeight = INIT_FLOAT;
	m_Info.bJump = false;


	bShot = false;
}

// デストラクタ
CPlayer2D::~CPlayer2D()
{

}

//========================================
// テクスチャの読み込み
//========================================
HRESULT CPlayer2D::Load(char *pPath)
{
	if (pPath != NULL)
	{
		m_nTexture++;	// テクスチャ数加算

		// デバイス取得
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// テクスチャの読み込み
		if (FAILED(D3DXCreateTextureFromFile(pDevice, pPath, &m_pTexture[m_nTexture])))
		{
			m_pTexture[m_nTexture] = NULL;
		}
	}

	return S_OK;
}

//========================================
// テクスチャの破棄
//========================================
void CPlayer2D::Unload(void)
{
	// テクスチャの破棄
	for (int nCntTex = 0; nCntTex < m_nTexture; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}

//========================================
// 生成
//========================================
CPlayer2D *CPlayer2D::Create(void)
{
	CPlayer2D *pPlayer = NULL;

	if (pPlayer != NULL)
	{
		return pPlayer;
	}

	// オブジェクト2Dの生成
	pPlayer = new CPlayer2D;

	// 初期化処理
	pPlayer->Init();

	return pPlayer;
}
//========================================
// 初期化
//========================================
HRESULT CPlayer2D::Init(void)
{
	CObject2D::Init();
	
	// 種類の設定
	SetType(TYPE_PLAYER);

	m_Info.pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_Info.fWidth = 75.0f;
	m_Info.fHeight = 75.0f;

	// 生成
	SetPos(m_Info.pos);
	SetSize(m_Info.fWidth,m_Info.fHeight);
	SetRot(m_Info.rot);
	SetColor(INIT_D3DXCOLOR);
	SetPtn(25);
	SetPtnInfo(5, 8, 46, false, 0);

	// テクスチャの割り当て
	BindTexture(m_pTexture[0]);

	return S_OK;
}

//========================================
// 終了
//========================================
void CPlayer2D::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================
// 更新
//========================================
void CPlayer2D::Update(void)
{
	// 移動・物理処理
	Physics();

	CObject2D::Update();
}

//========================================
// 描画
//========================================
void CPlayer2D::Draw(void)
{
	CObject2D::Draw();
}

//========================================
// 移動・物理処理
//========================================
void CPlayer2D::Physics(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// キーボードの取得
	CInputMouse *pInputMouse = CManager::GetInputMouse();			// マウスの取得
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();		// ジョイパットの取得

	// --- 移動 ---------------------------------

	if (pInputKeyboard->GetPress(DIK_D) == true || pInputJoypad->GetJoypadPress(CInputJoypad::JOYKEY_RIGHT, 0) == true)
	{// 右
		m_Info.move.x += PLAYER_SPEED;
		SetPtn(25);
	}
	else if (pInputKeyboard->GetPress(DIK_A) == true || pInputJoypad->GetJoypadPress(CInputJoypad::JOYKEY_LEFT, 0) == true)
	{// 左
		m_Info.move.x -= PLAYER_SPEED;
		SetPtn(35);
	}

	//移動量を更新(減衰させる)
	m_Info.move.x += (0.0f - m_Info.move.x) * 0.25f;

	// --- ジャンプ ---------------------------------
	if (pInputKeyboard->GetPress(DIK_SPACE) == true || pInputJoypad->GetJoypadPress(CInputJoypad::JOYKEY_A, 0) == true)
	{
		if (m_Info.bJump == false)
		{
			m_Info.bJump = true;	// ジャンプフラグを真にする
			m_Info.move.y += JUMP_POWER;
		}
	}

	m_Info.pos += m_Info.move;

	// 移動量を更新(減衰)

	//Ｙの移動量に重力を加算
	m_Info.move.y += (GRAVITY_POWER - m_Info.move.y) * GRAVITY_MAG;

	// ブロックとの当たり判定
	m_Info.pos = Collision(m_Info.pos);

	

	// 位置の更新
	SetPos(m_Info.pos);

	CSound *pSound = CManager::GetSound();

	// マウス

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		CBullet::Create(m_Info.pos, D3DXVECTOR3(0.0f, -7.5f, 0.0f), false);
		CBullet::Create(m_Info.pos, D3DXVECTOR3(0.0f, -7.5f, 0.0f), true);
		pSound->PlaySound(1);
	}
	else if (pInputMouse->GetTrigger(CInputMouse::MOUSE_RIGHT) == true)
	{
		CBullet::Create(m_Info.pos, D3DXVECTOR3(0.0f, -7.5f, 0.0f), false);
		pSound->PlaySound(1);
	}

	else if (pInputMouse->GetTrigger(CInputMouse::MOUSE_LEFT) == true)
	{
		CBullet::Create(m_Info.pos, D3DXVECTOR3(0.0f, -7.5f, 0.0f), true);
		pSound->PlaySound(1);
	}
}

//========================================
// 移動量の更新
//========================================
void CPlayer2D::AddMove(float fRoty)
{
	// 移動量
	m_Info.move.x += sinf(D3DX_PI * fRoty) * PLAYER_SPEED;
	m_Info.move.y += cosf(D3DX_PI * fRoty) * PLAYER_SPEED;

	m_Info.pos += m_Info.move;
}

//========================================
// 当たり判定
//========================================
D3DXVECTOR3 CPlayer2D::Collision(D3DXVECTOR3 pos)
{
	for (int nCntPriority = 0; nCntPriority < TYPE_MAX; nCntPriority++)
	{
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			// オブジェクトを取得
			CObject *pObj = GetObjectPointer(nCntPriority, nCntObj);

			if (pObj != NULL)
			{// 使用されている時、

				// 種類を取得
				TYPE type = pObj->GetType();

				if (type == TYPE_BLOCK)
				{// 種類がブロックの時、

					//  プレイヤーの取得
					D3DXVECTOR3 PosOld = GetPosOld();		// 位置(過去)
					float fWidth = m_Info.fWidth * 0.5;		// 幅
					float fHeight = m_Info.fHeight *0.5;	// 高さ

					// ブロックの取得
					D3DXVECTOR3 BlockPos = pObj->GetPos();			// 位置
					float fBlockWidth = pObj->GetWidth() * 0.5;		// 幅
					float fBlockeHight = pObj->GetHeight() * 0.5;	// 高さ	

					/* 当たり判定 */

					// プレイヤーがブロックの上辺～下辺の間にいる時
					if ((pos.y + fHeight) > (BlockPos.y - fBlockeHight) &&
						(pos.y - fHeight) < (BlockPos.y + fBlockeHight))
					{
						if ((pos.x + fWidth) >= (BlockPos.x - fBlockWidth) &&
							(PosOld.x + fWidth) <= (BlockPos.x - fBlockWidth))
						{// 左からめり込んでいる時

							pos.x = (BlockPos.x - fBlockWidth) - fWidth;
						}
						else if ((pos.x - fWidth) <= (BlockPos.x + fBlockWidth) &&
							(PosOld.x - fWidth) >= (BlockPos.x + fBlockWidth))
						{// 右からめり込んでいる時

							pos.x = (BlockPos.x + fBlockWidth) + fWidth;
						}
					}

					// プレイヤーがブロックの左辺～右辺の間にいる時

					if ((pos.x + fWidth) > (BlockPos.x - fBlockWidth) &&
						(pos.x - fWidth) < (BlockPos.x + fBlockWidth))
					{
						if ((pos.y + fHeight) >= (BlockPos.y - fBlockeHight) &&
							(PosOld.y + fHeight) <= (BlockPos.y - fBlockeHight))
						{// 上からめり込んでいる時

							pos.y = (BlockPos.y - fBlockeHight) - fHeight;
							m_Info.move.y = 0.0f;
							m_Info.bJump = false;
						}
						else if ((pos.y - fHeight) <= (BlockPos.y + fBlockeHight) &&
							(PosOld.y - fHeight) >= (BlockPos.y + fBlockeHight))
						{// 下からめり込んでいる時
							pos.y = (BlockPos.y + (fBlockeHight + fHeight));

							//プレイヤーが上昇中
							if (m_Info.move.y < 0.0f)
							{
								//Ｙの移動量を0に
								m_Info.move.y = 0.0f;
							}
						}
					}
				}
			}
		}
	}
	return pos;
}