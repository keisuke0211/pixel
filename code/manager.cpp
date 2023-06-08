//========================================
// 
// マネージャー処理
// 
//========================================
// *** manager.cpp ***
//========================================
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "texture.h"
#include "input.h"
#include "object\object.h"
#include "object\object2D.h"
#include "object\2D\score.h"
#include "object\2D\text2D.h"
#include "object\bg.h"
#include "object\bg_Multi.h"
#include "object\2D\block2D.h"
#include "object\3D\player.h"
#include "object\3D\enemy.h"

// 静的メンバ変数
CRenderer *CManager::m_pRenderer = NULL;
CSound *CManager::m_pSound = NULL;
CTexture *CManager::m_pTexture = NULL;
CInputKeyboard *CManager::m_InputKeyboard = NULL;
CInputMouse *CManager::m_InputMouse = NULL;
CInputJoypad *CManager::m_InputJoypad = NULL;
CNumber *CManager::m_Number = NULL;
CBg *CManager::m_pBg = NULL;
CPlayer *CManager::m_pPlayer = NULL;
CBullet *CManager::m_pBullet = NULL;
CExplosion *CManager::m_Explosion = NULL;

// コンストラクタ
CManager::CManager()
{
	
}

// デストラクタ
CManager::~CManager()
{

}
//========================================
// 初期化
//========================================
HRESULT CManager::Init(HINSTANCE hinstance, HWND hWnd, BOOL bWindow)
{
	if (m_pRenderer == NULL)
	{
		// レンダラーの生成
		m_pRenderer = new CRenderer;

		// レンダラーの初期化
		m_pRenderer->Init(hWnd, bWindow);
	}

	if (m_InputKeyboard == NULL)
	{
		// キーボードの生成
		m_InputKeyboard = new CInputKeyboard;

		// キーボードの初期化
		m_InputKeyboard->Init(hinstance, hWnd);
	}

	if (m_InputMouse == NULL)
	{
		// マウスの生成
		m_InputMouse = new CInputMouse;

		// マウスの初期化
		m_InputMouse->Init(hinstance, hWnd);
	}

	if (m_InputJoypad == NULL)
	{
		// ジョイパットの生成
		m_InputJoypad = new CInputJoypad;

		// ジョイパットの初期化
		m_InputJoypad->Init();
	}

	if (m_pSound == NULL)
	{
		// サウンドの生成
		m_pSound = new CSound;

		// サウンドの読み込み
		m_pSound->Load();

		// サウンドの初期化
		m_pSound->Init(hWnd);
	}
	
	// 読み込み
	Load();

	// 背景の生成
	for (int nCntBg = 0; nCntBg < 3; nCntBg++)
	{
		CBgMulti::Create(D3DXVECTOR3((nCntBg + 1)* 0.0005f, 0.0f, 0.0f), nCntBg);
	}

	for (int nCntObj = 0; nCntObj < 25; nCntObj++)
	{
		CBlock2D::Create(D3DXVECTOR3((35.0f + (nCntObj * 50.0f)), 650.0f, 0.0f));
	}

	// プレイヤーの生成
	for (int nCntPlayer = 0; nCntPlayer < CPlayer::PLAYER_MAX; nCntPlayer++)
	{
		CPlayer::Create();
	}

	// 敵の生成
	for (int nCntPlayer = 0; nCntPlayer < CEnemy::MAX_ENEMY; nCntPlayer++)
	{
		if (nCntPlayer <= 14)
		{
			CEnemy::Create(D3DXVECTOR3((100.0f + (nCntPlayer * 75.0f)), 50.0f, 0.0f));
		}
		else
		{
			CEnemy::Create(D3DXVECTOR3((100.0f + ((nCntPlayer - 15) * 75.0f)), 100.0f, 0.0f));
		}
	}
	
	{
		// スコア生成
		CScore *pObj = CScore::Create();

		// サイズ設定
		pObj->SetSize(20.0f, 20.0f);
		// 位置設定
		pObj->SetPos(D3DXVECTOR3(SCREEN_WIDTH - 250.0f, 32.0f, 0.0f));

		// スコア設定
		CScore::SetScore();
	}
	return S_OK;
}

//========================================
// 終了
//========================================
void CManager::Uninit(void)
{
	// キーボードの破棄
	if (m_InputKeyboard != NULL)
	{
		m_InputKeyboard->Uninit();

		delete m_InputKeyboard;
		m_InputKeyboard = NULL;
	}

	// マウスの破棄
	if (m_InputMouse != NULL)
	{
		m_InputMouse->Uninit();

		delete m_InputMouse;
		m_InputMouse = NULL;
	}

	// ジョイパットの破棄
	if (m_InputJoypad != NULL)
	{
		m_InputJoypad->Uninit();

		delete m_InputJoypad;
		m_InputJoypad = NULL;
	}

	// レンダラーの破棄
	if (m_pRenderer != NULL)
	{
		// レンダラー
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	// サウンドの破棄
	if (m_pSound != NULL)
	{
		// サウンド
		m_pSound->Uninit();

		delete m_pSound;
		m_pSound = NULL;
	}

	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Unload();

		delete m_pTexture;
		m_pTexture = NULL;
	}	
}

//========================================
// 更新
//========================================
void CManager::Update(void)
{
	// キーボード
	m_InputKeyboard->Update();

	// マウス
	m_InputMouse->Update();

	// ジョイパット
	m_InputJoypad->Update();

	// レンダラー
	m_pRenderer->Update();
}

//========================================
// 描画
//========================================
void CManager::Draw(void)
{
	// レンダラー
	m_pRenderer->Draw();
}
//========================================
// 読み込み
//========================================
void CManager::Load(void)
{
	if (m_pTexture == NULL)
	{
		// テクスチャの生成
		m_pTexture = new CTexture;

		// テクスチャ
		m_pTexture->Load();
	}
}